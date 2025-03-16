#include "ServiceManager.hpp"
#include <chrono>
#include <filesystem>
#include <sstream>
// 引入SDK头文件
#include <GaoDe/GuideSDK.h>
#include <GaoDe/porting_file.h>
#include <ctime>
#include <iomanip>

namespace service {
    std::string ServiceManager::handleExampleRequest(const crow::request &req) {
        // 处理/example请求的逻辑
        return "Example response";
    }

    std::string ServiceManager::handleInfoRequest(const crow::request &req) {
        auto client_ip = req.remote_ip_address;
        auto current_time = std::chrono::system_clock::now();
        auto time_str = std::chrono::system_clock::to_time_t(current_time);
        std::stringstream ss;
        ss << "Client IP: " << client_ip << ", Time: " << std::ctime(&time_str);
        return ss.str();
    }


    std::string ServiceManager::handleCaptureRequest(const crow::request &req) {
        // 默认设备 ID
        INT32_T devID = 1;
        // 检查设备是否存在
        INT32_T deviceCount = GetDeviceNum();
        if (deviceCount <= 0) {
            return "No devices found. Please check the network connection.";
        }

        // 如果设备未连接，尝试连接
        INT32_T result = OpenStream(devID, nullptr, nullptr, nullptr, nullptr, WORKING_MODE::H264_MODE, nullptr);
        if (result != GUIDEIR_OK) {
            return "Failed to connect to the device.";
        }

        // 获取当前时间
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time);

        // 生成文件名，格式为：capture_YYYYMMDD_HHMMSS.jpg
        std::ostringstream oss;
        oss << "D:/images/capture_"
            << std::put_time(&now_tm, "%Y%m%d_%H%M%S")
            << ".jpg";
        std::string imgPath = oss.str();

        // 确保目录存在
        std::filesystem::path dirPath = "D:/images";
        if (!std::filesystem::exists(dirPath)) {
            std::filesystem::create_directory(dirPath);
        }

        // 调用拍摄功能
        result = TakeScreenshotEx(devID, imgPath.c_str(), IMG_TYPE::ONLY_JPG);
        if (result == GUIDEIR_OK) {
            return std::string("Image captured successfully: ") + imgPath;
        } else {
            return "Failed to capture image.";
        }
    }

    std::string ServiceManager::handleFileOperationRequest(const crow::request &req) {
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
        buffer[bytesRead] = '\0';// 确保字符串以 null 结尾
        std::string fileContent(reinterpret_cast<char *>(buffer));
        return "File content:\n" + fileContent;
    }

    std::string ServiceManager::handleRoot() {
        return "<html><body><h1>Link Successfully to server!</h1><p>You can use route 'help' to get help!</p></body></html>";
    }

    std::string ServiceManager::handleVideoRequest(const crow::request &req) {
        // 默认设备 ID
        INT32_T devID = 1;

        // 检查设备是否存在
        INT32_T deviceCount = GetDeviceNum();
        if (deviceCount <= 0) {
            return "No devices found. Please check the network connection.";
        }

        // 如果设备未连接，尝试连接
        INT32_T result = OpenStream(devID, nullptr, nullptr, nullptr, nullptr, WORKING_MODE::H264_MODE, nullptr);
        if (result != GUIDEIR_OK) {
            return "Failed to connect to the device.";
        }

        // 获取当前时间
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time);

        // 生成视频文件路径，格式为：videos/video_YYYYMMDD_HHMMSS.mp4
        std::ostringstream oss;
        oss << "D:/videos/video_"
            << std::put_time(&now_tm, "%Y%m%d_%H%M%S")
            << ".mp4";
        std::string videoPath = oss.str();

        // 确保目录存在
        std::filesystem::path dirPath = "D:/videos";
        if (!std::filesystem::exists(dirPath)) {
            std::filesystem::create_directory(dirPath);
        }

        // 启动视频录制
        result = StartRecordVideo(devID, videoPath.c_str(), GD_MEDIA_TYPE::MP4_MEDIA);
        if (result != GUIDEIR_OK) {
            return "Failed to start video recording.";
        }

        // 模拟录制一段时间（例如 10 秒）
        std::this_thread::sleep_for(std::chrono::seconds(10));

        // 停止视频录制
        result = StopRecordVideo(devID);
        if (result != GUIDEIR_OK) {
            return "Failed to stop video recording.";
        }

        return std::string("Video recorded successfully: ") + videoPath;
    }
}// namespace service