#include "ServiceManager.hpp"
#include "../repository/RepositoryManager.hpp"
#include "VideoCamera.hpp"
#include <chrono>
#include <crow/common.h>
#include <filesystem>
#include <iomanip>
#include <memory>
#include <mutex>
#include <sstream>
// 引入SDK头文件
#include <GaoDe/GuideSDK.h>
#include <GaoDe/porting_file.h>

namespace service {

    std::mutex operate_mutex;
    crow::websocket::connection *active_conn = nullptr;// 记录当前活动连接

    // 定义命令处理函数类型
    using CommandHandler = std::function<void(crow::websocket::connection &, const std::string &)>;

    // 命令处理函数映射
    static std::map<std::string, CommandHandler> commandHandlers = {
            // 新增 record 命令处理逻辑
            {"record", [](crow::websocket::connection &conn, const std::string &command) {
                 auto &camera = VideoCamera::getInstance();
                 crow::json::rvalue msg = crow::json::load(command);
                 if (!msg || !msg.has("command")) {
                     conn.send_text(R"({"status": "error", "message": "Missing 'command' field."})");
                     return;
                 }

                 std::string subCommand = msg["command"].s();
                 if (subCommand == "start") {
                     if (!camera.isRecording()) {
                         std::cout << "start!" << std::endl;
                         camera.startRecording();
                         conn.send_text(R"({"status": "success", "message": "Recording started!"})");
                     } else {
                         conn.send_text(R"({"status": "error", "message": "Already recording."})");
                     }
                 } else if (subCommand == "stop") {
                     std::cout << "stop!" << std::endl;
                     if (camera.isRecording()) {
                         camera.stopRecording();
                         conn.send_text(R"({"status": "success", "message": "Recording stopped!"})");
                     } else {
                         conn.send_text(R"({"status": "error", "message": "Not recording."})");
                     }
                 } else if (subCommand == "capture") {
                     std::cout << "capture!" << std::endl;
                     camera.takeShot();
                     conn.send_text(R"({"status": "success", "message": "Photo captured!"})");
                 } else {
                     conn.send_text(R"({"status": "error", "message": "Invalid sub-command for 'record'.})");
                 }
             }},
            // 新增 setParam 命令处理逻辑
            {"setParam", [](crow::websocket::connection &conn, const std::string &command) {
                 auto &camera = VideoCamera::getInstance();
                 crow::json::rvalue msg = crow::json::load(command);
                 if (!msg || !msg.has("paramType") || !msg.has("paramValue")) {
                     conn.send_text(R"({"status": "error", "message": "Missing 'paramType' or 'paramValue' field."})");
                     return;
                 }

                 std::string paramTypeStr = msg["paramType"].s();
                 CameraParamType paramType;
                 if (paramTypeStr == "PIXEL_FORMAT") {
                     paramType = CameraParamType::PIXEL_FORMAT;
                 } else if (paramTypeStr == "ADJUST_LIGHT") {
                     paramType = CameraParamType::ADJUST_LIGHT;
                 } else if (paramTypeStr == "PALETTE") {
                     paramType = CameraParamType::PALETTE;
                 } else if (paramTypeStr == "ELECTRONIC_ZOOM") {
                     paramType = CameraParamType::ELECTRONIC_ZOOM;
                 } else if (paramTypeStr == "SHUTTER_CONTROL") {
                     paramType = CameraParamType::SHUTTER_CONTROL;
                 } else if (paramTypeStr == "CALC_PARAMETER") {
                     paramType = CameraParamType::CALC_PARAMETER;
                 } else if (paramTypeStr == "DEVICE_PORT") {
                     paramType = CameraParamType::DEVICE_PORT;
                 } else if (paramTypeStr == "ALARM_INFO") {
                     paramType = CameraParamType::ALARM_INFO;
                 } else {
                     conn.send_text(R"({"status": "error", "message": "Invalid 'paramType'."})");
                     return;
                 }

                 const void *paramValue = nullptr;
                 // 根据 paramType 解析 paramValue
                 switch (paramType) {
                     case CameraParamType::PIXEL_FORMAT: {
                         GD_PIXEL_FORMAT pixelFormat = static_cast<GD_PIXEL_FORMAT>(msg["paramValue"].i());
                         paramValue = &pixelFormat;
                         break;
                     }
                     case CameraParamType::ADJUST_LIGHT: {
                         MODULATE_PARAM_INFO lightParam;
                         lightParam.auto_moudulate = static_cast<BOOL_T>(msg["paramValue"]["auto_moudulate"].b());
                         lightParam.luminance = msg["paramValue"]["luminance"].i();
                         lightParam.contrast = msg["paramValue"]["contrast"].i();
                         paramValue = &lightParam;
                         break;
                     }
                     case CameraParamType::PALETTE: {
                         INT32_T paletteIndex = msg["paramValue"].i();
                         paramValue = &paletteIndex;
                         break;
                     }
                     case CameraParamType::ELECTRONIC_ZOOM: {
                         GD_ZOOM_SCALE zoomLevel = static_cast<GD_ZOOM_SCALE>(msg["paramValue"].i());
                         paramValue = &zoomLevel;
                         break;
                     }
                     case CameraParamType::SHUTTER_CONTROL: {
                         CMD_SHUTTER_TYPE shutterType = static_cast<CMD_SHUTTER_TYPE>(msg["paramValue"].i());
                         paramValue = &shutterType;
                         break;
                     }
                     case CameraParamType::CALC_PARAMETER: {
                         CALC_PARAM_INFO calcParam;
                         calcParam.emiss = msg["paramValue"]["emiss"].d();
                         calcParam.distance = msg["paramValue"]["distance"].d();
                         calcParam.humidity = msg["paramValue"]["humidity"].i();
                         calcParam.backTemp = msg["paramValue"]["backTemp"].d();
                         calcParam.backFlag = msg["paramValue"]["backFlag"].i();
                         calcParam.B = msg["paramValue"]["B"].d();
                         calcParam.KF = msg["paramValue"]["KF"].i();
                         calcParam.transmittance = msg["paramValue"]["transmittance"].d();
                         calcParam.coef0 = msg["paramValue"]["coef0"].i();
                         calcParam.coef1 = msg["paramValue"]["coef1"].i();
                         paramValue = &calcParam;
                         break;
                     }
                     case CameraParamType::DEVICE_PORT: {
                         std::pair<DEVICE_PORT_TYPE, UINT16_T> portInfo;
                         portInfo.first = static_cast<DEVICE_PORT_TYPE>(msg["paramValue"][0].i());
                         portInfo.second = static_cast<UINT16_T>(msg["paramValue"][1].i());
                         paramValue = &portInfo;
                         break;
                     }
                     case CameraParamType::ALARM_INFO: {
                         ALARM_INFO alarmInfo;
                         alarmInfo.state = msg["paramValue"]["state"].i();
                         alarmInfo.highLimit = msg["paramValue"]["highLimit"].i();
                         alarmInfo.lowLimit = msg["paramValue"]["lowLimit"].i();
                         alarmInfo.mode = msg["paramValue"]["mode"].i();
                         paramValue = &alarmInfo;
                         break;
                     }
                     default:
                         conn.send_text(R"({"status": "error", "message": "Unsupported parameter type."})");
                         return;
                 }

                 camera.setParams(paramType, paramValue);
                 conn.send_text(R"({"status": "success", "message": "Parameter set successfully!"})");
             }}};

    static void handleCommand(crow::websocket::connection &conn, const std::string &data) {
        try {
            crow::json::rvalue msg = crow::json::load(data);
            if (!msg) {
                conn.send_text(R"({"status": "error", "message": "Invalid JSON format."})");
                return;
            }

            // 获取 action 字段
            std::string action = msg["action"].s();
            CROW_LOG_INFO << "Received action: " << action;

            // 检查相机是否已初始化
            auto &camera = VideoCamera::getInstance();
            if (!camera.isInit()) {
                conn.send_text(R"({"status": "error", "message": "Camera is not initialized."})");
                return;
            }

            // 根据 action 调用对应的处理函数
            auto it = commandHandlers.find(action);
            if (it != commandHandlers.end()) {
                it->second(conn, data); // 将完整数据传递给处理函数
            } else {
                conn.send_text(R"({"status": "error", "message": "Invalid action."})");
            }
        } catch (const std::exception &e) {
            conn.send_text(R"({"status": "error", "message": "Invalid JSON format."})");
            CROW_LOG_ERROR << "Exception caught: " << e.what();
        }
    }

    std::string HttpServiceManager::handleInfoRequest(const crow::request &req) {
        auto client_ip = req.remote_ip_address;
        auto current_time = std::chrono::system_clock::now();
        auto time_str = std::chrono::system_clock::to_time_t(current_time);
        std::stringstream ss;
        ss << "Client IP: " << client_ip << ", Time: " << std::ctime(&time_str);
        return ss.str();
    }

    std::string HttpServiceManager::handleRoot() {
        return "<html><body><h1>Link Successfully to server!</h1><p>You can use route 'help' to get help!</p></body></html>";
    }


    std::string HttpServiceManager::handleUserLists() {
        std::stringstream ss;
        ss << "<h1>User Lists:</h1>";
        ss << "<ul>";
        int index = 1; // 初始化序号
        for (const auto &user: repository::RepositoryManager::getUsers()) {
            ss << "<li>" << index++ << ":    " << user << "</li>"; // 添加序号
        }
        ss << "</ul>";
        return ss.str();
    }

    bool WebSocketServiceManager::OnVideoAccept() {
        // 如果已经有活动连接，拒绝新连接的操作
        if (active_conn != nullptr) {
            return false;
        }
        return true;
    }

    void WebSocketServiceManager::OnVideoOpen(crow::websocket::connection &conn) {
        CROW_LOG_INFO << "websocket link success";
        // 加入用户
        repository::RepositoryManager::addUser(&conn);
        // 初始化相机
        //auto &camera = VideoCamera::getInstance();
        //camera.openStream();

        // 初始化互斥状态
        std::lock_guard<std::mutex> lock(operate_mutex);
        if (active_conn == nullptr) {
            active_conn = &conn;
        } else {
            // 如果已经有活动连接，警告新连接的操作,新连接在活动连接退出之前无权限操作，如果一个客户端重复多次连接会导致无法操作，额外注意
            conn.send_text(R"({"status": "warning", "message": "Another connection is already active."})");
        }
    }

    void WebSocketServiceManager::OnVideoMessage(crow::websocket::connection &conn, const std::string &data, bool is_binary) {
        if (is_binary) {
            // 如果是二进制数据，直接返回
            conn.send_binary(data);
            return;
        }

        std::lock_guard<std::mutex> lock(operate_mutex);
        if (active_conn != nullptr && active_conn != &conn) {
            // 如果已经有其他连接在操作，拒绝当前连接的操作
            conn.send_text(R"({"status": "error", "message": "Another connection is operating. Please try again later."})");
            return;
        }

        // 设置当前连接为活动连接
        active_conn = &conn;

        // 调用辅助函数处理命令
        handleCommand(conn, data);

        // 释放活动连接
        active_conn = nullptr;
    }

    void WebSocketServiceManager::OnVideoError(crow::websocket::connection &conn, const std::string &reason) {
        std::lock_guard<std::mutex> lock(operate_mutex);
        if (active_conn == &conn) {
            // 如果当前连接是活动连接，释放它
            active_conn = nullptr;
        }
        // 移除用户
        repository::RepositoryManager::removeUser(&conn);
        CROW_LOG_ERROR << " error" << "websocket error: " << reason;
    }

    void WebSocketServiceManager::OnVideoClose(crow::websocket::connection &conn, const std::string &reason) {
        std::lock_guard<std::mutex> lock(operate_mutex);
        if (active_conn == &conn) {
            // 如果当前连接是活动连接，释放它
            active_conn = nullptr;
        }
        // 移除用户
        repository::RepositoryManager::removeUser(&conn);
        CROW_LOG_ERROR << "websocket close" << " reason:" << reason;
    }


}// namespace service
