/**
 * @FilePath     : /crow_server/src/controller/routes.hpp
 * @Description  :  
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-03-17 22:00:41
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/
#include "../service/ServiceManager.hpp"
#include "HelpDocManager.hpp"
#include "logHandler.hpp"
#include "version.h"
#include <crow/app.h>
#include <crow/http_request.h>
#include <crow/websocket.h>

namespace routes {
    class RouteManager {
    private:
        crow::SimpleApp app;

        void bindHttpRoutes() {
            // 注册根路由
            CROW_ROUTE(app, "/")
            ([this] {// 捕获 this 指针
                return service::HttpServiceManager::handleRoot();
            });
            HelpDocManager::registerHelpDoc("/", Protocol::HTTP, "Root route", {"GET"}, "{}", "{}", {}, "public", VERSIONS, "Root route description");

            // 注册/help 路由
            CROW_ROUTE(app, "/help")
            ([this] {// 捕获 this 指针
                return getRouteHelp();
            });
            HelpDocManager::registerHelpDoc("/help", Protocol::HTTP, "Help route", {"GET"}, "{}", "{}", {}, "public", VERSIONS, "Help route description");

            // 注册 /info 路由
            CROW_ROUTE(app, "/info")
            ([](const crow::request &req) {
                return service::HttpServiceManager::handleInfoRequest(req);
            });
            HelpDocManager::registerHelpDoc("/info", Protocol::HTTP, "Info route", {"GET"}, "{}", "{\"client_ip\": \"127.0.0.1\", \"time\": \"Mon Jan  1 00:00:00 2000\"}", {}, "user", VERSIONS, "Info route description");

            // 注册 /users路由
            CROW_ROUTE(app, "/usrs")
            ([]() {
                return service::HttpServiceManager::handleUserLists();
            });
            HelpDocManager::registerHelpDoc("/usrs", Protocol::HTTP, "User route", {"GET"}, "{}", "{\"status\": \"success\", \"users\": [{\"id\": 1, \"name\": \"user1\"}, {\"id\": 2, \"name\": \"user2\"}]}", {}, "admin", VERSIONS, "User route description");
        }

        void bindWebsocketRoutes() {
            CROW_WEBSOCKET_ROUTE(app, "/video")
                    .onaccept([](const crow::request &req, void **) -> bool {
                        return service::WebSocketServiceManager::OnVideoAccept();
                    })
                    .onopen([](crow::websocket::connection &conn) {
                        service::WebSocketServiceManager::OnVideoOpen(conn);
                    })
                    .onmessage([](crow::websocket::connection &conn, const std::string &data, bool is_binary) {
                        service::WebSocketServiceManager::OnVideoMessage(conn, data, is_binary);
                    })
                    .onerror([](crow::websocket::connection &conn, const std::string &error_message) {
                        service::WebSocketServiceManager::OnVideoError(conn, error_message);
                    })
                    .onclose([&](crow::websocket::connection &conn, const std::string &reason, int code) {
                        return service::WebSocketServiceManager::OnVideoClose(conn, reason);
                    });
            HelpDocManager::registerHelpDoc("/ws/video", Protocol::HTTP, "WebSocket online video stream/take a shot/video record",
                                            {"NONE"}, "", "", {}, "", VERSIONS, "RTSP will run at rtsp://192.168.1.168:8554/video as default.");
        }


    public:
        RouteManager() {}

        void run() {
            CustomLogger logger{2};
            crow::logger::setHandler(&logger);
            bindHttpRoutes();
            bindWebsocketRoutes();
            app.bindaddr("127.0.0.1").port(8081).run();
        }

        std::string getRouteHelp() {
            return repository::RepositoryManager::getRouteHelp();
        }
    };
}// namespace routes