#pragma once

#include <crow.h>
namespace service {
    class HttpServiceManager {
    public:
        static std::string handleInfoRequest(const crow::request &req);
        static std::string handleCaptureRequest(const crow::request &req);
        static std::string handleRoot();
        static std::string handleUserLists();
    };

    class WebSocketServiceManager {
    public:
        static bool OnVideoAccept();
        static void OnVideoOpen(crow::websocket::connection &conn);
        static void OnVideoMessage(crow::websocket::connection &conn, const std::string &data, bool is_binary);
        static void OnVideoError(crow::websocket::connection& conn, const std::string& reason);
        static void OnVideoClose(crow::websocket::connection& conn, const std::string& reason);
    };
}// namespace service