#ifndef MPRPC_MPRPCCHANNEL_H
#define MPRPC_MPRPCCHANNEL_H

#include "zookeeperutil.h"
#include <google/protobuf/service.h>

class MprpcChannel : public google::protobuf::RpcChannel {
public:
    void CallMethod(const google::protobuf::MethodDescriptor *method,
                    google::protobuf::RpcController *controller, const google::protobuf::Message *request,
                    google::protobuf::Message *response, google::protobuf::Closure *done) override;
};

#endif //MPRPC_MPRPCCHANNEL_H
