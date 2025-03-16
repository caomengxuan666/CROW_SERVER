#pragma once

#include <crow.h>
namespace service {
    class ServiceManager {
    public:
        std::string handleExampleRequest(const crow::request &req);
        std::string handleInfoRequest(const crow::request &req);
        std::string handleCaptureRequest(const crow::request &req);
        std::string handleFileOperationRequest(const crow::request &req);
        std::string handleRoot();
        std::string handleVideoRequest(const crow::request &req);
    };
}// namespace service