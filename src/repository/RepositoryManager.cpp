#include "RepositoryManager.hpp"
#include "VideoCamera.hpp"
#include <sstream>

namespace repository {
    std::string RepositoryManager::fetchData() {
        // 模拟从数据库或其他数据源获取数据
        return "Sample Data from Repository";
    }

    void RepositoryManager::registRouteHelp(const HelpDoc &doc) {
        // 将 HelpDoc 存储到容器中，键为 URL
        routeHelpDocs[doc.url] = doc;
    }

    std::string RepositoryManager::getRouteHelp() {
        std::ostringstream oss;
        for (const auto &[url, doc]: routeHelpDocs) {
            oss << "URL: " << doc.url << "\n";
            oss << "Protocol: " << (doc.protocol == Protocol::HTTP ? "HTTP" : "WEBSOCKET") << "\n";// 添加 Protocol 信息
            oss << "Description: " << doc.description << "\n";
            oss << "HTTP Methods: ";
            for (const auto &method: doc.httpMethods) {
                oss << method << " ";
            }
            oss << "\n";
            oss << "Request Example: " << doc.requestExample << "\n";
            oss << "Response Example: " << doc.responseExample << "\n";
            oss << "Error Codes: ";
            for (const auto &[code, description]: doc.errorCodes) {
                oss << code << ": " << description << " ";
            }
            oss << "\n";
            oss << "Permissions: " << doc.permissions << "\n";
            oss << "Version: " << doc.version << "\n";
            oss << "Notes: " << doc.notes << "\n";
            oss << "----------------------------------------\n";
        }
        return oss.str();
    }

    VideoCamera &RepositoryManager::operateCamera() {
        return VideoCamera::getInstance();
    }

    void RepositoryManager::addUser(crow::websocket::connection *conn) {
        users.insert(conn);
    }

    void RepositoryManager::removeUser(crow::websocket::connection *conn) {
        users.erase(conn);
    }

    std::unordered_set<crow::websocket::connection *> &RepositoryManager::getUsers() {
        return users;
    }

    std::map<std::string, HelpDoc> RepositoryManager::routeHelpDocs;// 初始化静态成员变量

    std::unordered_set<crow::websocket::connection *> RepositoryManager::users;//初始化用户的无序set容器

}// namespace repository