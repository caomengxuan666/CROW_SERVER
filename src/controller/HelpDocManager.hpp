/**
 * @FilePath     : /crow_server/src/controller/HelpDocManager.hpp
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-16 11:19:16
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
#pragma once

#include "../repository/RepositoryManager.hpp"// 引入 RepositoryManager


class HelpDocManager {
private:
    repository::RepositoryManager &repositoryManager;

public:
    HelpDocManager(repository::RepositoryManager &repoManager) : repositoryManager(repoManager) {}

    void registerHelpDoc(
            std::string url,
            std::string description,
            std::vector<std::string> httpMethods,
            std::string requestExample,
            std::string responseExample,
            std::map<int, std::string> errorCodes,
            std::string permissions,
            std::string version,
            std::string notes) {
        HelpDoc doc;
        doc.url = std::move(url);
        doc.description = std::move(description);
        doc.httpMethods = std::move(httpMethods);
        doc.requestExample = std::move(requestExample);
        doc.responseExample = std::move(responseExample);
        doc.errorCodes = std::move(errorCodes);
        doc.permissions = std::move(permissions);
        doc.version = std::move(version);
        doc.notes = std::move(notes);

        repositoryManager.registRouteHelp(doc);
    }
};
