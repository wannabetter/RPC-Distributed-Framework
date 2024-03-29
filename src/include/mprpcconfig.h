//
// Created by DELL on 2024/3/24.
//

#ifndef MPRPC_MPRPCCONFIG_H
#define MPRPC_MPRPCCONFIG_H

#include <string>
#include <unordered_map>

class MprpcConfig {
private:
    void Trim(std::string &src_buf);

    std::unordered_map<std::string, std::string> m_configMap;
public:
    void LoadConfigFile(const char *config_file);

    std::string Load(const std::string &key);

};

#endif //MPRPC_MPRPCCONFIG_H
