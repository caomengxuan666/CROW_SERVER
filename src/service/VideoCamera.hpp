#pragma once
#include "GaoDe/SDKParams.h"
#include "GaoDe/common_type.h"
#include <GaoDe/GuideSDK.h>
#include <GaoDe/porting_file.h>
#include <cassert>
#include <condition_variable>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <mutex>
#include <ostream>
#include <sstream>
#include <thread>
#include "../Utility/CsvWriter.h"
#include <chrono>
#include "PebbleLog.h"


void onStateChanged(GD_STATE_INFO info, VOID *param) {
    //提示网络断开或者连上
}
// 定义相机参数类型枚举
enum class CameraParamType {
    PIXEL_FORMAT,   // 像素格式
    ADJUST_LIGHT,   // 调整光线参数
    PALETTE,        // 调色板索引
    ELECTRONIC_ZOOM,// 电子变焦级别
    SHUTTER_CONTROL,// 快门控制类型
    CALC_PARAMETER, // 计算参数
    DEVICE_PORT,    // 设备端口信息
    ALARM_INFO      // 报警信息
};

class VideoCamera {
public:
    /**
     * @author       : caomengxuan
     * @brief        : 获取单例实例
     * @return       : VideoCamera&
    **/
    static VideoCamera &getInstance() {
        static VideoCamera instance;
        return instance;
    }

    /**
     * @author       : caomengxuan
     * @brief        : 拍照
     * @return       : void
    **/
    void takeShot();

    /**
     * @author       : caomengxuan
     * @brief        : 开始录制视频
     * @return       : void
    **/
    void startRecording();

    /**
     * @author       : caomengxuan
     * @brief        : 停止录制视频
     * @return       : void
    **/
    void stopRecording();

    /**
     * @author       : caomengxuan
     * @brief        : 关闭连接
     * @return       : void
    **/
    void disconnect();

        // 静态适配器函数
    static void StaticOnRgbData(GD_RGB_INFO Info, VOID *param) {
        static_cast<VideoCamera *>(param)->onRgbData(Info, param);
    }

    void onRgbData(GD_RGB_INFO Info, VOID *param);

    /**
     * @author       : caomengxuan
     * @brief        : 设置参数
     * @param        : VideoParams params
     * @return       : void
    **/
    void setParams(CameraParamType paramType, const void *param);

    const bool isRecording() const { return _isRecording; }
    const bool isFree() const { return _isFree; }
    void setFree(bool free) { _isFree = free; }

    const INT32_T getCameraID() const { return _camereid; }

    const bool isInit() const { return _isInit; }

    //获取我们的CSV保存路径
    const std::string getCsvPath() {return _csvPath;}


private:
    /**
     * @author       : caomengxuan
     * @brief        : 构造函数,在里面查询设备ID和IP,构造视频rtsp视频地址
     * @return        {*}
    **/
    VideoCamera();                                       // 私有构造函数
    ~VideoCamera();                                      // 私有析构函数
    VideoCamera(const VideoCamera &) = delete;           // 删除拷贝构造函数
    VideoCamera &operator=(const VideoCamera &) = delete;// 删除赋值操作符

    bool _isFree;
    bool _isRecording;// 标记是否正在录制
    bool _isShoting=true;    //标记是否正在拍照
    int _camereid;
    bool _isInit;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::string _usrName;
    std::string _pwd;
    std::string _rtsp_url;
    std::string _csvPath;
};

inline VideoCamera::VideoCamera() : _isFree(true), _isRecording(false), _camereid(1), _isInit(false) {
    // 查询设备 ID
    //彩色打印，显示VideoCamera对象产生
    PebbleLog::info("VideoCamera object created.");

    _camereid = GetDeviceIDNotConnected("192.168.1.168");
    if (_camereid <= 0) {
        PebbleLog::error("Failed to get device ID!");
    } else {
        _isInit = true;
    }

    //查询目标设备的URL_INFO信息
    URL_INFO info;
    if (GUIDEIR_OK == GetDeviceURLInfo(_camereid, &info)) {
        //这种情况之下是有默认用户名密码的，得拼接地址
        if (info.userName != "") {
            _usrName = info.userName;
            _pwd = info.passWord;
            PebbleLog::info("UserName: " + _usrName);
            PebbleLog::info("Password: " + _pwd);
            // 拼接 RTSP URL
            _rtsp_url = "rtsp://" + _usrName + ":" + _pwd + "@192.168.1.168:8554/video";
            PebbleLog::info("RTSP URL: " + _rtsp_url);
        } else {
            PebbleLog::info("Using default username and password instead");
            _rtsp_url = "rtsp://192.168.1.168:8554/video";
        }
        //打印VideoCamera可用
        PebbleLog::info("VideoCamera is available.");
        PebbleLog::info("Video DEVICE INDEX IS: " + std::to_string(_camereid));
    }
    else{
        PebbleLog::error("VideoCamera is unavailable!");
    }

        OpenStream(
            _camereid,
            &VideoCamera::StaticOnRgbData,                    // 普通函数
            nullptr,// 静态成员函数
            nullptr,
            this,// 传递 this 指针
            H264_MODE,
            0);

}

inline VideoCamera::~VideoCamera() {
    if (_isInit) {
        stopRecording();// 停止录制（如果正在录制）
        disconnect();   // 断开连接

        _isInit = false;// 标记为未初始化

        PebbleLog::info("Camera connection has been closed.");
    }
    PebbleLog::info("VideoCamera object destroyed.");
}


inline void VideoCamera::onRgbData(GD_RGB_INFO info, VOID *param) {
    //保证他在拍照的时候才去触发他。
    if (!_isShoting) return;
    if (!info.rgbData) {
        std::cerr << "Error: y16Data is null!" << std::endl;
        return;
    }
    // 获取图像的宽度和高度
    int imgWidth = info.imgWidth;
    int imgHeight = info.imgHeight;

    // 构建温度矩阵
    std::vector<FLOAT_T> tempMatrix(imgWidth * imgHeight);

    if (GetTempMatrixEx(_camereid, tempMatrix.data(), imgWidth, imgHeight) != GUIDEIR_OK) {
        std::cerr << "Failed to get temperature matrix." << std::endl;
        return ;
    }

    std::vector<std::vector<std::string>> csvData(imgHeight, std::vector<std::string>(imgWidth));
    for (INT32_T i = 0; i < imgHeight; ++i) {
        for (INT32_T j = 0; j < imgWidth; ++j) {
            csvData[i][j] = std::to_string(tempMatrix[i * imgWidth + j]);
        }
    }

     // 获取当前时间
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    // 获取当前时间的秒数
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // 格式化时间字符串
    std::ostringstream oss;
    oss << "temperature_matrix_"
        << std::put_time(&now_tm, "%Y%m%d_%H%M%S")
        << "_" << std::setw(3) << std::setfill('0') << now_ms.count()
        << ".csv";
    std::string filePath = oss.str();


    auto csvResult = Utility::CsvWriter::writeCsv(filePath, csvData);
    if (!csvResult.first) {
        PebbleLog::error("Failed to write CSV file");
    } else {
        PebbleLog::info("Temperature matrix saved to:  {}" ,csvResult.second);
    }
    _isShoting = false;
    return;
}

inline void VideoCamera::takeShot() {
    if (!_isInit || _camereid <= 0) {
        std::cerr << "Camera not initialized or invalid device ID!" << std::endl;
        return;
    }

    // 定义图片保存路径
    const CHAR_T imgPath[] = "D:/images/";

    // 设置参数
    SetPixelFormatEx(_camereid, GD_PIXEL_FORMAT::RGB24_PIXEL_FORMAT);
    SetPaletteEx(_camereid, IRONRED);

    // 调焦和快门控制（关键步骤）
    FocusControlEx(_camereid, AUTO_FOCUS, nullptr);
    ShutterControlEx(_camereid, SHUTTER_NOW, nullptr);

    // 确保目录存在
    std::filesystem::path dirPath = "D:/images/";
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }

    _isShoting = true;
    
    static int first_init = 0;
    if (first_init == 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        first_init = 1;
    }
 

    // 拍摄图片
    PebbleLog::info("_camera ID: {}",_camereid);
    INT32_T result = TakeScreenshotEx(_camereid, imgPath, IMG_TYPE::ONLY_JPG);
    if (result == GUIDEIR_OK || result == 1) {
        PebbleLog::info("Image captured successfully: {}",std::string(imgPath));
    } else {
        PebbleLog::error("Failed to capture image. Error code: " + std::to_string(result));
    }
    
}

inline void VideoCamera::startRecording() {
    if (!_isInit || _camereid <= 0) {
        std::cerr << "Camera not initialized or invalid device ID!" << std::endl;
        return;
    }

    if (_isRecording) {
        std::cerr << "Already recording." << std::endl;
        return;
    }

    // 生成文件路径
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    std::ostringstream oss;
    oss << "D:/videos/recording_"
        << std::put_time(&now_tm, "%Y%m%d_%H%M%S")
        << ".mp4";
    std::string videoPath = oss.str();

    // 确保目录存在
    std::filesystem::path dirPath = "D:/videos";
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }

    // 开始录制
    INT32_T result = StartRecordVideo(_camereid, videoPath.c_str(), GD_MEDIA_TYPE::MP4_MEDIA);
    if (result == GUIDEIR_OK) {
        _isRecording = true;
        std::cout << "Recording started: " << videoPath << std::endl;
    } else {
        std::cerr << "Failed to start recording. Error code: " << result << std::endl;
    }
}

inline void VideoCamera::stopRecording() {
    if (!_isInit || _camereid <= 0) {
        std::cerr << "Camera not initialized or invalid device ID!" << std::endl;
        return;
    }

    if (!_isRecording) {
        std::cerr << "Not recording." << std::endl;
        return;
    }

    // 停止录制
    INT32_T result = StopRecordVideo(_camereid);
    if (result == GUIDEIR_OK) {
        _isRecording = false;
        std::cout << "Recording stopped." << std::endl;
    } else {
        std::cerr << "Failed to stop recording. Error code: " << result << std::endl;
    }
}

inline void VideoCamera::disconnect() {
    if (!_isInit || _camereid <= 0) {
        std::cerr << "Camera not initialized or invalid device ID!" << std::endl;
        return;
    }

    INT32_T result = CloseStream(_camereid);
    if (result == GUIDEIR_OK) {
        std::cout << "Connection closed successfully." << std::endl;
    } else {
        std::cerr << "Failed to close connection. Error code: " << result << std::endl;
    }
}

inline void VideoCamera::setParams(CameraParamType paramType, const void *param) {
    if (!_isInit || _camereid <= 0) {
        std::cerr << "Camera not initialized or invalid device ID!" << std::endl;
        return;
    }

    INT32_T result = GUIDEIR_ERR;

    switch (paramType) {
        case CameraParamType::PIXEL_FORMAT: {
            auto pixelFormat = *static_cast<const GD_PIXEL_FORMAT *>(param);
            result = SetPixelFormatEx(_camereid, pixelFormat);
            break;
        }
        case CameraParamType::ADJUST_LIGHT: {
            auto lightParam = *static_cast<const MODULATE_PARAM_INFO *>(param);
            result = SetAdjustLightParameterEx(_camereid, lightParam);
            break;
        }
        case CameraParamType::PALETTE: {
            auto paletteIndex = *static_cast<const INT32_T *>(param);
            result = SetPaletteEx(_camereid, paletteIndex);
            break;
        }
        case CameraParamType::ELECTRONIC_ZOOM: {
            auto zoomLevel = *static_cast<const GD_ZOOM_SCALE *>(param);
            result = SetElecZoomPlus(_camereid, zoomLevel);
            break;
        }
        case CameraParamType::SHUTTER_CONTROL: {
            auto shutterType = *static_cast<const CMD_SHUTTER_TYPE *>(param);
            result = ShutterControlEx(_camereid, shutterType, nullptr);
            break;
        }
        case CameraParamType::CALC_PARAMETER: {
            auto calcParam = *static_cast<const CALC_PARAM_INFO *>(param);
            result = SetCalcParameter(_camereid, CALC_PARAM_ALL, calcParam);
            break;
        }
        case CameraParamType::DEVICE_PORT: {
            auto portInfo = *static_cast<const std::pair<DEVICE_PORT_TYPE, UINT16_T> *>(param);
            result = SetDevicePort(_camereid, portInfo.first, portInfo.second);
            break;
        }
        case CameraParamType::ALARM_INFO: {
            auto alarmInfo = *static_cast<const ALARM_INFO *>(param);
            result = SetAlarm(_camereid, alarmInfo);
            break;
        }
        default:
            std::cerr << "Unsupported parameter type!" << std::endl;
            return;
    }

    if (result == GUIDEIR_OK) {
        std::cout << "Parameter set successfully." << std::endl;
    } else {
        std::cerr << "Failed to set parameter. Error code: " << result << std::endl;
    }
}