#ifndef MPRPC_LOGGER_H
#define MPRPC_LOGGER_H

#include "lockqueue.h"


#define LOG_INFO(format, ...) \
do {                          \
    Logger &logger = Logger::GetInstance(); \
    logger.SetLogLevel(INFO); \
    char c[1024] = {0};       \
    snprintf(c,1024,format,##__VA_ARGS__);  \
    logger.Log(c); }while(0)

#define LOG_ERR(format, ...) \
do {                         \
    Logger &logger = Logger::GetInstance(); \
    logger.SetLogLevel(ERROR);              \
    char c[1024] = {0};      \
    snprintf(c,1024,format,##__VA_ARGS__);  \
    logger.Log(c); }while(0)

enum LogLevel {
    INFO,
    ERROR
};

class Logger {
private:
    int m_loglevel;
    LockQueue<std::string> m_lckQue;
private:
    Logger();

    Logger(const Logger &) = delete;

    Logger(const Logger &&) = delete;

public:

    static Logger &GetInstance();

    void SetLogLevel(LogLevel level);

    void Log(std::string msg);
};

#endif //MPRPC_LOGGER_H
