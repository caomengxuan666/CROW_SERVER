/**
 * @FilePath     : /crow_server/src/logHandler.hpp
 * @Description  :  消除crow内部日志库本身的时差问题
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-15 19:00:57
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
//获取指定格式的时间字符串
#pragma once
#include <crow.h>
#include <string>
inline std::string get_now_time(std::string format = "%Y-%m-%d %H:%M:%S") {
    time_t rawtime;
    struct tm *info;
    char buffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer, 80, format.c_str(), info);
    std::string stime(buffer);
    return stime;
}
//设置log记录器
class CustomLogger : public crow::ILogHandler {
public:
    int loglevel;
    CustomLogger(int loglevel) {
        this->loglevel = loglevel;
    }
    void log(std::string message, crow::LogLevel level) {
        // "message" doesn't contain the timestamp and loglevel
        // prefix the default logger does and it doesn't end
        // in a newline.
        int intlevel = (int) level;
        if (loglevel >= intlevel) {
            std::string time = get_now_time();
            std::cerr << time << " " << message << std::endl;
        }
    }
};
