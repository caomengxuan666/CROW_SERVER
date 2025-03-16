/**
 * @FilePath     : /crow_server/src/controller/routes.hpp
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-16 11:21:39
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/

#pragma once

#include "../service/ServiceManager.hpp"
#include "HelpDocManager.hpp"
#include "logHandler.hpp"
#include "version.h"

namespace routes {
    class RouteManager {
    private:
        crow::SimpleApp app;
        service::ServiceManager serviceManager;
        repository::RepositoryManager repositoryManager;
        HelpDocManager helpDocManager;

        void bindHttpRoutes() {
            // 注册根路由
            CROW_ROUTE(app, "/")
            ([this] {
                return serviceManager.handleRoot();
            });
            helpDocManager.registerHelpDoc("/", "Root route", {"GET"}, "{}", "{}", {}, "public", VERSIONS, "Root route description");

            // 注册 /example 路由
            CROW_ROUTE(app, "/example")
            ([this](const crow::request &req) {
                return serviceManager.handleExampleRequest(req);
            });
            helpDocManager.registerHelpDoc("/example", "Example route", {"GET"}, "{\"param1\": \"value1\"}", "{\"status\": \"success\", \"data\": {\"key\": \"value\"}}", {{400, "Bad Request"}}, "user", VERSIONS, "Example route description");

            // 注册/help 路由
            CROW_ROUTE(app, "/help")
            ([this] {
                return getRouteHelp();
            });

            // 注册 /info 路由
            CROW_ROUTE(app, "/info")
            ([this](const crow::request &req) {
                return serviceManager.handleInfoRequest(req);
            });
            helpDocManager.registerHelpDoc("/info", "Info route", {"GET"}, "{}", "{\"client_ip\": \"127.0.0.1\", \"time\": \"Mon Jan  1 00:00:00 2000\"}", {}, "user", VERSIONS, "Info route description");

            // 注册 /capture 路由
            CROW_ROUTE(app, "/capture")
            ([this](const crow::request &req) {
                return serviceManager.handleCaptureRequest(req);
            });
            helpDocManager.registerHelpDoc("/capture", "Capture route", {"GET"}, "{}", "{\"status\": \"success\", \"path\": \"/myprojects/Demo/capture.jpg\"}", {{500, "Internal Server Error"}}, "admin", VERSIONS, "Capture route description");
        }

        void bindWebsocketRoutes() {
            //todo WebSocket路由绑定逻辑
        }

    public:
        RouteManager() : helpDocManager(repositoryManager) {}

        void run() {
            CustomLogger logger{2};
            crow::logger::setHandler(&logger);
            bindHttpRoutes();
            bindWebsocketRoutes();
            app.bindaddr("0.0.0.0").port(8081).multithreaded().run();
        }

        std::string getRouteHelp() {
            return repositoryManager.getRouteHelp();
        }
    };
}// namespace routes