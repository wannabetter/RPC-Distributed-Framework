//
// Created by DELL on 2024/3/28.
//

#ifndef MPRPC_MPRPCCONTROLLER_H
#define MPRPC_MPRPCCONTROLLER_H

#include <string>
#include <google/protobuf/service.h>

class MprpcController : public google::protobuf::RpcController {
private:
    bool m_failed;
    std::string m_errText;
public:
    MprpcController();

    void Reset();

    bool Failed() const;

    std::string ErrorText() const;

    void SetFailed(const std::string &reason);

    void StartCancel();

    bool IsCanceled() const;

    void NotifyOnCancel(google::protobuf::Closure *callback);
};

#endif //MPRPC_MPRPCCONTROLLER_H
