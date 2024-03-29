//
// Created by DELL on 2024/3/24.
//

#ifndef MPRPC_MPRPCAPPLIACTION_H
#define MPRPC_MPRPCAPPLIACTION_H

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

class MprpcApplication {
private:
    static MprpcConfig m_config;
private:
    MprpcApplication() {}

    MprpcApplication(const MprpcApplication &) = delete;

    MprpcApplication(MprpcApplication &&) = delete;

public:
    static void Init(int argc, char *argv[]);

    static MprpcApplication &GetInstance();

    static MprpcConfig &GetConfig();
};

#endif //MPRPC_MPRPCAPPLIACTION_H
