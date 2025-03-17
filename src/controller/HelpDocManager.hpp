#include "../repository/RepositoryManager.hpp" // 引入 RepositoryManager

class HelpDocManager {
private:
    static void registerHelpDocImpl(
            const char* url,
            Protocol protocol, // 添加 protocol 参数
            const char* description,
            const std::vector<std::string>& httpMethods,
            const char* requestExample,
            const char* responseExample,
            const std::map<int, std::string>& errorCodes,
            const char* permissions,
            const char* version,
            const char* notes) {
        HelpDoc doc;
        doc.url = url;
        doc.protocol = protocol; // 设置 protocol 字段
        doc.description = description;
        doc.httpMethods = httpMethods;
        doc.requestExample = requestExample;
        doc.responseExample = responseExample;
        doc.errorCodes = errorCodes;
        doc.permissions = permissions;
        doc.version = version;
        doc.notes = notes;

        repository::RepositoryManager::registRouteHelp(doc); // 使用静态方法
    }

public:
    static void registerHelpDoc(
            const char* url,
            Protocol protocol, // 添加 protocol 参数
            const char* description,
            const std::vector<std::string>& httpMethods,
            const char* requestExample,
            const char* responseExample,
            const std::map<int, std::string>& errorCodes,
            const char* permissions,
            const char* version,
            const char* notes) {
        registerHelpDocImpl(url, protocol, description, httpMethods, requestExample, responseExample, errorCodes, permissions, version, notes);
    }
};