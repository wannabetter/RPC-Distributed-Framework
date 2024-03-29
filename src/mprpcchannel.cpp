//
// Created by DELL on 2024/3/25.
//

#include <string>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "rpcheader.pb.h"
#include "mprpcchannel.h"
#include "mprpcappliaction.h"

void MprpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method,
                              google::protobuf::RpcController *controller, const google::protobuf::Message *request,
                              google::protobuf::Message *response, google::protobuf::Closure *done) {
    const google::protobuf::ServiceDescriptor *sd = method->service();
    std::string service_name = sd->name();
    std::string method_name = method->name();

    uint32_t args_size = 0;
    std::string args_str;
    if (request->SerializeToString(&args_str)) {
        args_size = args_str.size();
    } else {
        controller->SetFailed("serialize request error!");
        return;
    }

    mprpc::RpcHeader rpcHeader;
    rpcHeader.set_service_name(service_name);
    rpcHeader.set_method_name(method_name);
    rpcHeader.set_args_size(args_size);

    uint32_t head_size = 0;
    std::string rpc_header_str;
    if (rpcHeader.SerializeToString(&rpc_header_str)) {
        head_size = rpc_header_str.size();
    } else {
        controller->SetFailed("serialize rpc header error!");
        return;
    }

    std::string send_rpc_str;
    send_rpc_str.insert(0, std::string((char *) &head_size, 4));
    send_rpc_str += rpc_header_str;
    send_rpc_str += args_str;

    int cliendfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cliendfd == -1) {
        char err_txt[512] = {0};
        sprintf(err_txt, "create socket error! errno: %d", errno);
        controller->SetFailed(err_txt);
        return;
    }
    
    ZkClient zkCli;
    zkCli.Start();
    std::string method_path = "/" + service_name + "/" + method_name;
    std::string host_data = zkCli.GetData(method_path.c_str());
    if (host_data == "") {
        controller->SetFailed(method_path + " is not exist!");
        return;
    }
    int idx = host_data.find(":");
    if (idx == -1) {
        controller->SetFailed(method_path + " address is invalid");
        return;
    }
    std::string ip = host_data.substr(0, idx);
    uint32_t port = atoi(host_data.substr(idx + 1, host_data.size() - idx).c_str());

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(cliendfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        char err_txt[512] = {0};
        sprintf(err_txt, "connect error! errno: %d", errno);
        controller->SetFailed(err_txt);
        close(cliendfd);
        return;
    }

    if (send(cliendfd, send_rpc_str.c_str(), send_rpc_str.size(), 0) == -1) {
        char err_txt[512] = {0};
        sprintf(err_txt, "send error! errno: %d", errno);
        controller->SetFailed(err_txt);
        close(cliendfd);
        return;
    }

    char buf[1024] = {0};
    int recv_size = 0;
    if ((recv_size = recv(cliendfd, buf, 1024, 0)) == -1) {
        char err_txt[512] = {0};
        sprintf(err_txt, "recv error! errno: %d", errno);
        controller->SetFailed(err_txt);
        close(cliendfd);
        return;
    }

    if (!response->ParseFromArray(buf, recv_size)) {
        char err_txt[512] = {0};
        sprintf(err_txt, "parse error! response_str: %s", buf);
        controller->SetFailed(err_txt);
        close(cliendfd);
        return;
    }

    close(cliendfd);
}