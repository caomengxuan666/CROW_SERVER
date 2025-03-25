#include "GaoDe/SDKParams.h"
#include "GaoDe/common_type.h"
#include <GaoDe/GuideSDK.h>
#include <GaoDe/porting_file.h>
#include <cassert>
#include <condition_variable>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <ostream>
#include <sstream>
#include <thread>
#pragma once

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
     * @brief        : 打开视频流,在rtsp://192.168.1.168:8554/(默认路径)上播放视频
     * @return       : bool
     * @note         : sdk写的很傻逼,有的设备有密码，有的没有，必须在打开视频流之前获取状态
                       如果有账号密码，那么这个视频流路径前面还得加上用户名和密码
    **/
    void openStream();

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

    /**
     * @author       : caomengxuan
     * @brief        : RGB的回调，需要在回调里面处理
     * @param         {GD_RGB_INFO} rgbInfo:
     * @param         {void} *param:
     * @return        {*}
    **/
    void RGBDataCallback(GD_RGB_INFO rgbInfo, void *param);
    /**
     * @author       : caomengxuan
     * @brief        : Y16的回调,需要在里面处理,比如说温度
     * @param         {GD_Y16_INFO} y16Info:
     * @param         {void} *param:
     * @return        {*}
    **/
    void Y16DataCallback(GD_Y16_INFO y16Info, void *param);
    /**
     * @author       : caomengxuan
     * @brief        : 状态回调，可以拿这个来判断是否连接成功
     * @param         {GD_STATE_INFO} stateInfo:
     * @param         {void} *param:
     * @return        {*}
    **/
    void StateCallback(GD_STATE_INFO stateInfo, void *param);


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
    int _camereid;
    bool _isInit;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::string _usrName;
    std::string _pwd;
    std::string _rtsp_url;
};

inline VideoCamera::VideoCamera() : _isFree(true), _isRecording(false), _camereid(1), _isInit(false) {
    // 查询设备 ID
    //彩色打印，显示VideoCamera对象产生
    std::cout << "\033[32mVideoCamera object created.\033[0m" << std::endl;

    _camereid = GetDeviceIDNotConnected("192.168.1.188");
    if (_camereid <= 0) {
        std::cout << "\033[31mFailed to get device ID!\033[0m" << std::endl;
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
            std::cout << "UserName: " << _usrName << std::endl;
            std::cout << "Password: " << _pwd << std::endl;
            // 拼接 RTSP URL
            _rtsp_url = "rtsp://" + _usrName + ":" + _pwd + "@192.168.1.188:8554/video";
            std::cout << "RTSP URL: " << _rtsp_url << std::endl;
        } else {
            std::cout << "Using default username and password instead" << std::endl;
            _rtsp_url = "rtsp://192.168.1.188:8554/video";
        }
        //打印VideoCamera可用
        std::cout << "\033[32mVideoCamera is available.\033[0m" << std::endl;
        std::cout << "\033[32mVideo DEVICE INDEX IS :" << _camereid << "\033[0m" << std::endl;
    }
    else{
        std::cout << "\033[31mVideoCamera is unavailable!\033[0m" << std::endl;
    }
}

inline VideoCamera::~VideoCamera() {
    if (_isInit) {
        stopRecording();// 停止录制（如果正在录制）
        disconnect();   // 断开连接

        _isInit = false;// 标记为未初始化

        // 彩色打印：绿色显示摄像机连接已关闭
        std::cout << "\033[32mCamera connection has been closed.\033[0m" << std::endl;
    }
    //彩色打印，显示VideoCamera对象销毁
    std::cout << "\033[32mVideoCamera object destroyed.\033[0m" << std::endl;
}

inline void VideoCamera::RGBDataCallback(GD_RGB_INFO rgbInfo, void *param) {
    auto *camera = static_cast<VideoCamera *>(param);
    if (rgbInfo.rgbData) {
        // 处理RGB数据
        //free(rgbInfo.rgbData);// 必须释放内存，(真实性存疑)
    }
}

inline void VideoCamera::Y16DataCallback(GD_Y16_INFO y16Info, void *param) {
    auto *camera = static_cast<VideoCamera *>(param);
    if (y16Info.y16Data) {
        // 处理Y16数据
        GD_TEMP_INFO info;
        RECT_T rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = y16Info.imgWidth - 1;
        rect.h = y16Info.imgHeight - 1;

        INT16_T pt = y16Info.y16Data[y16Info.imgHeight + y16Info.imgHeight / 2 - y16Info.imgWidth / 2];
        INT16_T cY16 = y16Info.y16OutputInfo.sY16_Center;
        FLOAT_T ft, st;
        //通过坐标得到Y16值计算中心点温度
        GetY16Temp(_camereid, pt, &ft);
        //通过参数行的中心点Y16值计算的温度
        GetY16Temp(_camereid, cY16, &st);

        //free(y16Info.y16Data);// 必须释放内存?这是AI说的,我没有看到任何例子，先不释放,释放不存在的内存，我们的项目就完蛋了。
    }
}

//先注释了,个人感觉写这容易出BUG,感觉不如轮询了
inline void VideoCamera::StateCallback(GD_STATE_INFO stateInfo, void *param) {
    /*
    auto *camera = static_cast<VideoCamera *>(param);
    if (stateInfo.state == STREAM_CONNECT) {
        camera->_cv.notify_one();
    }
        */
}


inline void VideoCamera::openStream() {
    if (!_isInit || _camereid <= 0) {
        std::cerr << "Camera not initialized or invalid device ID!" << std::endl;
        return;
    }

    const char *url = _rtsp_url.c_str();

    // 使用Lambda表达式作为回调函数
    auto rgbCallback = [this](GD_RGB_INFO rgbInfo, void *param) {
        if (rgbInfo.rgbData) {
            // 处理RGB数据
            // free(rgbInfo.rgbData); // 根据实际情况决定是否释放内存，我反正觉得不用
        }
    };

    auto y16Callback = [this](GD_Y16_INFO y16Info, void *param) {
        if (y16Info.y16Data) {
            // 处理Y16数据
            GD_TEMP_INFO info;
            RECT_T rect;
            rect.x = 0;
            rect.y = 0;
            rect.w = y16Info.imgWidth - 1;
            rect.h = y16Info.imgHeight - 1;

            INT16_T pt = y16Info.y16Data[y16Info.imgHeight + y16Info.imgHeight / 2 - y16Info.imgWidth / 2];
            INT16_T cY16 = y16Info.y16OutputInfo.sY16_Center;
            FLOAT_T ft, st;
            GetY16Temp(_camereid, pt, &ft);
            GetY16Temp(_camereid, cY16, &st);
            GetRectTemp(_camereid, rect, CALC_TEMP_ALL, &info);
            //通过坐标获取的是矩形框的中心温度
            GetRectTemp(_camereid, rect, CALC_TEMP_CENTRE, &info);
            INT16_T pt2 = y16Info.y16Data[0];
            FLOAT_T ft2;
            GetY16Temp(_camereid, pt2, &ft2);


            double centerTemp = (INT32_T) (100 * ft + 0.5) * 0.01;
            //输出中心点温度
            std::cout << "centerTemp: " << centerTemp << std::endl;
            //todo 应该是在这里搞CSV，但是这个SDK也没有提供CSV的轮子，我还得自己根据需求造
        }
    };

    // 将Lambda表达式转换为函数指针
    auto rgbCallbackFunc = [](GD_RGB_INFO rgbInfo, void *param) {
        auto *camera = static_cast<VideoCamera *>(param);
        camera->RGBDataCallback(rgbInfo, param);
    };

    auto y16CallbackFunc = [](GD_Y16_INFO y16Info, void *param) {
        auto *camera = static_cast<VideoCamera *>(param);
        camera->Y16DataCallback(y16Info, param);
    };

    INT32_T result = OpenStream(
            _camereid,
            rgbCallbackFunc,// 使用转换后的函数指针
            y16CallbackFunc,// 使用转换后的函数指针
            nullptr,
            (VOID *) this,// 传递this指针作为回调参数
            WORKING_MODE::H264_MODE,
            url);

    if (result == GUIDEIR_ERR) {
        std::cerr << "Failed to open stream. Error code: " << result << std::endl;
        return;
    } else
        std::cout << "open stream" << std::endl;

    // 轮询检测设备状态，超时时间5s
    bool timeout = true;
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
        INT32_T state;
        if (GetDeviceState(_camereid, &state) == GUIDEIR_OK && state == STREAM_CONNECT) {
            std::cout << "Stream connected successfully." << std::endl;
            timeout = false;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (timeout) {
        std::cerr << "Stream connection timed out." << std::endl;
        disconnect();
        return;
    }

    // 显示(100,100)的温度，在视频上面
    POINT_T point;
    point.x = 100;
    point.y = 100;
    ShowPointTemp(_camereid, point);
}

VOID onRGBData(GD_RGB_INFO info, VOID *param) {
    //显示图像
}
void onY16Data(GD_Y16_INFO infoY16, VOID *param) {
    //Y16 数据处理
}
void onStateChanged(GD_STATE_INFO info, VOID *param) {
    //提示网络断开或者连上
}

inline void VideoCamera::takeShot() {
    if (!_isInit || _camereid <= 0) {
        std::cerr << "Camera not initialized or invalid device ID!" << std::endl;
        return;
    }

    static int ret = OpenStream(_camereid, onRGBData, onY16Data, onStateChanged, (VOID *) _camereid, H264_MODE, 0);
    if (GUIDEIR_ERR == ret)
        return ;

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

    // 拍摄图片
    std::cout << "_camera ID : " << _camereid << std::endl;
    INT32_T result = TakeScreenshotEx(_camereid, imgPath, IMG_TYPE::ONLY_JPG);
    if (result == GUIDEIR_OK || result == 1) {
        std::cout << "Image captured successfully: " << imgPath << std::endl;
    } else {
        std::cerr << "Failed to capture image. Error code: " << result << std::endl;
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