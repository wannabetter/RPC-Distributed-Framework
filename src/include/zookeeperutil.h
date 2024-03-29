#ifndef MPRPC_ZOOKEEPERUTIL_H
#define MPRPC_ZOOKEEPERUTIL_H

#include <string>
#include <semaphore.h>
#include <zookeeper/zookeeper.h>

class ZkClient {
private:
    zhandle_t *m_zhandle;
public:
    ZkClient();

    ~ZkClient();

    void Start();

    void Create(const char *path, const char *data, int datalen, int state = 0);

    std::string GetData(const char *path);
};

#endif //MPRPC_ZOOKEEPERUTIL_H
