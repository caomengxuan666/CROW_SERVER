#include "ServiceManager.hpp"
#include "../repository/RepositoryManager.hpp"
#include <chrono>
#include <crow/common.h>
#include <filesystem>
#include <iomanip>
#include <sstream>
// 引入SDK头文件
#include <GaoDe/GuideSDK.h>
#include <GaoDe/porting_file.h>


namespace service {

    // 定义命令处理函数类型
    using CommandHandler = std::function<void(crow::websocket::connection &, const std::string &)>;

    // 命令处理函数映射
    static std::map<std::string, CommandHandler> commandHandlers = {
        {"start", [](crow::websocket::connection &conn, const std::string &command) {
            auto &camera = repository::RepositoryManager::operateCamera();
            if (!camera.isRecording()) {
                camera.startRecording();
                conn.send_text(R"({"status": "success", "message": "Recording started!"})");
            } else {
                conn.send_text(R"({"status": "error", "message": "Already recording."})");
            }
        }},
        {"stop", [](crow::websocket::connection &conn, const std::string &command) {
            auto &camera = repository::RepositoryManager::operateCamera();
            if (camera.isRecording()) {
                camera.stopRecording();
                conn.send_text(R"({"status": "success", "message": "Recording stopped!"})");
            } else {
                conn.send_text(R"({"status": "error", "message": "Not recording."})");
            }
        }},
        {"capture", [](crow::websocket::connection &conn, const std::string &command) {
            auto &camera = repository::RepositoryManager::operateCamera();
            camera.takeShot();
            conn.send_text(R"({"status": "success", "message": "Photo captured!"})");
        }},
        // 新增 record 命令处理逻辑
        {"record", [](crow::websocket::connection &conn, const std::string &command) {
            auto &camera = repository::RepositoryManager::operateCamera();
            crow::json::rvalue msg = crow::json::load(command);
            if (!msg || !msg.has("command")) {
                conn.send_text(R"({"status": "error", "message": "Missing 'command' field."})");
                return;
            }

            std::string subCommand = msg["command"].s();
            if (subCommand == "start") {
                if (!camera.isRecording()) {
                    camera.startRecording();
                    conn.send_text(R"({"status": "success", "message": "Recording started!"})");
                } else {
                    conn.send_text(R"({"status": "error", "message": "Already recording."})");
                }
            } else if (subCommand == "stop") {
                if (camera.isRecording()) {
                    camera.stopRecording();
                    conn.send_text(R"({"status": "success", "message": "Recording stopped!"})");
                } else {
                    conn.send_text(R"({"status": "error", "message": "Not recording."})");
                }
            } else {
                conn.send_text(R"({"status": "error", "message": "Invalid sub-command for 'record'.})");
            }
        }}
    };

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

            // 根据 action 调用对应的处理函数
            auto it = commandHandlers.find(action);
            if (it != commandHandlers.end()) {
                it->second(conn, data);  // 将完整数据传递给处理函数
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


    std::string HttpServiceManager::handleCaptureRequest(const crow::request &req) {
        // 使用设备IP获取设备ID（替代固定ID）
        INT32_T devID = GetDeviceIDNotConnected("192.168.1.168");// 实际IP
        if (devID <= 0) {
            return "Failed to get device ID for IP: 192.168.1.168";
        }

        // 定义回调函数（即使不需要处理数据，也需设置）
        RGBDataCB rgbCB = [](GD_RGB_INFO rgbInfo, void *param) {
            // 示例：验证数据有效性
            if (rgbInfo.rgbData == nullptr) {
                std::cerr << "Invalid RGB data received!" << std::endl;
            }
        };
        Y16DataCB y16CB = [](GD_Y16_INFO y16Info, void *param) {};

        // 连接设备并打开流
        INT32_T result = OpenStream(
                devID,
                rgbCB,
                y16CB,
                nullptr,
                nullptr,
                WORKING_MODE::H264_MODE,
                nullptr);
        if (result != GUIDEIR_OK) {
            return "Failed to open stream. Error code: " + std::to_string(result);
        }

        // 等待流初始化完成
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // 检查设备状态
        INT32_T state;
        if (GetDeviceState(devID, &state) != GUIDEIR_OK || state != STREAM_CONNECT) {
            CloseStream(devID);
            return "Device not connected after initialization.";
        }

        // 设置参数
        SetPixelFormatEx(devID, GD_PIXEL_FORMAT::RGB24_PIXEL_FORMAT);
        SetPaletteEx(devID, IRONRED);// 使用示例中的色带（如铁红）

        // 调焦和快门控制（示例中的关键步骤）
        FocusControlEx(devID, AUTO_FOCUS, nullptr);
        ShutterControlEx(devID, SHUTTER_NOW, nullptr);

        // 生成文件路径
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time);

        std::ostringstream oss;
        oss << "D:/images/capture_"
            << std::put_time(&now_tm, "%Y%m%d_%H%M%S")
            << ".jpg";
        std::string imgPath = oss.str();

        // 确保目录存在
        std::filesystem::path dirPath = "D:/images";
        if (!std::filesystem::exists(dirPath)) {
            std::filesystem::create_directories(dirPath);
        }

        // 拍摄图片
        result = TakeScreenshotEx(devID, imgPath.c_str(), IMG_TYPE::ONLY_JPG);
        if (result == GUIDEIR_OK || result == 1) {
            CloseStream(devID);
            return "Image captured successfully: " + imgPath;
        } else {
            CloseStream(devID);
            return "Failed to capture image. Error code: " + std::to_string(result);
        }
    }

    std::string HttpServiceManager::handleUserLists() {
        std::stringstream ss;
        ss << "<h1>User Lists:</h1>";
        ss << "<ul>";
        for (const auto &user: repository::RepositoryManager::getUsers()) {
            ss << "<li>" << user << "</li>";
        }
        ss << "</ul>";
        return ss.str();
    }

    bool WebSocketServiceManager::OnVideoAccept() {
        return true;
    }

    void WebSocketServiceManager::OnVideoOpen(crow::websocket::connection &conn) {
        CROW_LOG_INFO << "websocket link success";
        // 加入用户
        repository::RepositoryManager::addUser(&conn);
        //在这里直接初始化相机
        repository::RepositoryManager::operateCamera().initCamera();
        repository::RepositoryManager::operateCamera().openStream();
    }

    void WebSocketServiceManager::OnVideoMessage(crow::websocket::connection &conn, const std::string &data, bool is_binary) {
        if (is_binary) {
            // 如果是二进制数据，直接返回
            conn.send_binary(data);
            return;
        }

        // 调用辅助函数处理命令
        handleCommand(conn, data);
    }

    void WebSocketServiceManager::OnVideoError(crow::websocket::connection &conn, const std::string &reason) {
        //移除用户
        repository::RepositoryManager::removeUser(&conn);
        CROW_LOG_ERROR << " error" << "websocket error: " << reason;
    }

    void WebSocketServiceManager::OnVideoClose(crow::websocket::connection &conn, const std::string &reason) {
        //移除用户
        repository::RepositoryManager::removeUser(&conn);
        CROW_LOG_ERROR << "websocket close" << " reason:" << reason;
    }


}// namespace service