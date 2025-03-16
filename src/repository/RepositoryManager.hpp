#pragma once
#include <map>
#include <string>
#include <vector>

//todo 我也不知道能不能用的上这个层

struct HelpDoc {
    std::string url;
    std::vector<std::string> paramList;
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
        std::string fetchData();
        void registRouteHelp(const HelpDoc &doc);
        std::string getRouteHelp();

    private:
        std::map<std::string, HelpDoc> routeHelpDocs; // 存储 HelpDoc 的容器
    };
} // namespace repository