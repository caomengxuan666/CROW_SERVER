/**
 * @FilePath     : /crow_server/src/controller/routes.hpp
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-15 22:18:07
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/

#pragma once
#include "../service/ServiceManager.hpp"
#include "logHandler.hpp"
#include <crow.h>

namespace routes {
    class RouteManager {
    private:
        crow::SimpleApp app;
        service::ServiceManager serviceManager;

        void bindHttpRoutes() {
            /*example,看看服务器能不能用*/
            CROW_ROUTE(app, "/example")
            ([this](const crow::request &req) {
                return serviceManager.handleExampleRequest(req);
            });

            CROW_ROUTE(app, "/info")
            ([this](const crow::request &req) {
                return serviceManager.handleInfoRequest(req);
            });

            CROW_ROUTE(app, "/capture")
            ([this](const crow::request &req) {
                return serviceManager.handleCaptureRequest(req);
            });
        }

        void bindWebsocketRoutes() {
            //todo WebSocket路由绑定逻辑
        }

    public:
        void run() {
            CustomLogger logger{2};
            crow::logger::setHandler(&logger);
            bindHttpRoutes();
            bindWebsocketRoutes();
            app.bindaddr("0.0.0.0").port(8081).multithreaded().run();
        }
    };
}// namespace routes