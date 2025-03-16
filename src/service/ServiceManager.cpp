#include "ServiceManager.hpp"
#include <chrono>
#include <sstream>
// 引入SDK头文件
#include <GaoDe/GuideSDK.h>
#include <GaoDe/porting_file.h>

namespace service {
    std::string ServiceManager::handleExampleRequest(const crow::request& req) {
        // 处理/example请求的逻辑
        return "Example response";
    }

    std::string ServiceManager::handleInfoRequest(const crow::request& req) {
        auto client_ip = req.remote_ip_address;
        auto current_time = std::chrono::system_clock::now();
        auto time_str = std::chrono::system_clock::to_time_t(current_time);
        std::stringstream ss;
        ss << "Client IP: " << client_ip << ", Time: " << std::ctime(&time_str);
        return ss.str();
    }

    // 实现新的处理函数
    std::string ServiceManager::handleCaptureRequest(const crow::request& req) {
        // 获取设备ID，默认为1（可以根据实际需求从请求参数中获取）
        INT32_T devID = 1;

        // 定义图片保存路径
        const CHAR_T imgPath[] = "/myprojects/Demo/capture.jpg";

        // 调用SDK的拍摄功能
        INT32_T result = TakeScreenshotEx(devID, imgPath, IMG_TYPE::ONLY_JPG);

        if (result == GUIDEIR_OK) {
            // 拍摄成功，返回图片路径
            return std::string("Image captured successfully: ") + imgPath;
        } else {
            // 拍摄失败，返回错误信息
            return "Failed to capture image.";
        }
    }

    std::string ServiceManager::handleFileOperationRequest(const crow::request& req) {
        // 获取请求参数中的文件路径
        std::string filePath = req.url_params.get("file");
        if (filePath.empty()) {
            return "Error: Missing 'file' parameter in the request.";
        }

        // 打开文件
        HANDLE_T fileHandle = porting_file_open(filePath.c_str(), "r");
        if (!fileHandle) {
            return "Error: Failed to open file.";
        }

        // 读取文件内容
        const int bufferSize = 1024;
        BYTE_T buffer[bufferSize];
        INT32_T bytesRead = porting_file_read(fileHandle, buffer, bufferSize - 1);
        if (bytesRead < 0) {
            porting_file_close(fileHandle);
            return "Error: Failed to read file.";
        }

        // 关闭文件
        porting_file_close(fileHandle);

        // 构造返回结果
        buffer[bytesRead] = '\0'; // 确保字符串以 null 结尾
        std::string fileContent(reinterpret_cast<char*>(buffer));
        return "File content:\n" + fileContent;
    }
}