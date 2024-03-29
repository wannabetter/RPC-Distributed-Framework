#ifndef MPRPC_RPCPROVIDER_H
#define MPRPC_RPCPROVIDER_H

#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>

#include "zookeeperutil.h"

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>

#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>

class RpcProvider {
private:
    muduo::net::EventLoop m_eventLoop;

    struct ServiceInfo {
        google::protobuf::Service *m_service;
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> m_methodMap;
    };

    std::unordered_map<std::string, ServiceInfo> m_serviceMap;
public:
    void NotifyService(google::protobuf::Service *service);

    void Run();

    void OnConnection(const muduo::net::TcpConnectionPtr &);

    void OnMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buffer, muduo::Timestamp timestamp);

    void SendRpcResponse(const muduo::net::TcpConnectionPtr &conn, google::protobuf::Message *response);
};

#endif //MPRPC_RPCPROVIDER_H
