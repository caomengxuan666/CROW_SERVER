#include "RepositoryManager.hpp"
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
        for (const auto& [url, doc] : routeHelpDocs) {
            oss << "URL: " << doc.url << "\n";
            oss << "Description: " << doc.description << "\n";
            oss << "HTTP Methods: ";
            for (const auto& method : doc.httpMethods) {
                oss << method << " ";
            }
            oss << "\n";
            oss << "Request Example: " << doc.requestExample << "\n";
            oss << "Response Example: " << doc.responseExample << "\n";
            oss << "Error Codes: ";
            for (const auto& [code, description] : doc.errorCodes) {
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
} // namespace repository