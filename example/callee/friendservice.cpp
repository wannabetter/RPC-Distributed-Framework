//
// Created by DELL on 2024/3/28.
//
#include <vector>
#include <string>
#include "logger.h"
#include <stdint.h>
#include <iostream>
#include "friend.pb.h"
#include "rpcprovider.h"
#include "mprpcappliaction.h"

class FriendService : public fixbug::FriendServiceRpc {
public:
    std::vector<std::string> GetFriendsList(uint32_t userid) {
        std::cout << "do GetFriendsList service! userid: " << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("zhang san");
        vec.push_back("li san");
        vec.push_back("wang san");
        return vec;
    }

    void GetFriendList(::google::protobuf::RpcController *controller,
                       const ::fixbug::GetFrinedListRequest *request,
                       ::fixbug::GetFrinedListResponse *response,
                       ::google::protobuf::Closure *done) {
        uint32_t userid = request->userid();
        std::vector<std::string> friendsList = GetFriendsList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for (auto &name: friendsList) {
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }

};

int main(int argc, char *argv[]) {

    LOG_INFO("first log message!");
    LOG_ERR("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);

    MprpcApplication::Init(argc, argv);

    RpcProvider provider;
    provider.NotifyService(new FriendService());
    provider.Run();


    return 0;
}