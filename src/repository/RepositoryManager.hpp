/**
 * @FilePath     : /crow_server/src/repository/RepositoryManager.hpp
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-17 16:50:08
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
#include "VideoCamera.hpp"
#include <crow/websocket.h>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

enum class Protocol {
    HTTP,
    WEBSOCKET
};

struct HelpDoc {
    std::string url;
    std::vector<std::string> paramList;
    Protocol protocol;// 协议,可以是HTTP或者是WEBSOCKET
    std::string description;
    std::vector<std::string> httpMethods; // 支持的 HTTP 方法
    std::string requestExample;           // 请求示例
    std::string responseExample;          // 响应示例
    std::map<int, std::string> errorCodes;// 错误码和描述
    std::string permissions;              // 权限要求
    std::string version;                  // 版本信息
    std::string notes;                    // 备注
};

namespace repository {
    class RepositoryManager {
    public:
        static std::string fetchData();
        static void registRouteHelp(const HelpDoc &doc);
        static std::string getRouteHelp();
        static VideoCamera &operateCamera();// 返回已初始化的 VideoCamera 对象
        static void addUser(crow::websocket::connection *conn);
        static void removeUser(crow::websocket::connection *conn);
        static std::unordered_set<crow::websocket::connection *>&getUsers();

    private:
        static std::map<std::string, HelpDoc> routeHelpDocs;// 存储 HelpDoc 的容器
        static std::unordered_set<crow::websocket::connection *> users;
    };


}// namespace repository