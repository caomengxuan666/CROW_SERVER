#include "GaoDe/GuideSDK.h"
#include "../Utility/CsvWriter.h"
#include <vector>
#include <string>
#include <iostream>

int main() {
    // Step 1: 搜索设备
    DEVICE_INFO devices[10];
    INT32_T deviceCount = SearchDevice(devices, 10);
    if (deviceCount <= 0) {
        std::cerr << "No devices found." << std::endl;
        return -1;
    }

    CONST CHAR_T* ip = devices[0].ipAddr; // 使用第一个设备的 IP 地址
    std::cout << "Connecting to device with IP: " << ip << std::endl;

    // Step 2: 打开视频流
    INT32_T devID = OpenStreamEx(ip, NULL, NULL, NULL, NULL, H264_MODE, NULL);
    if (devID <= 0) {
        std::cerr << "Failed to open stream." << std::endl;
        return -1;
    }

    // Step 3: 获取设备信息
    DEVICE_INFO devInfo;
    if (GetDeviceInfo(devID, &devInfo) != GUIDEIR_OK) {
        std::cerr << "Failed to get device info." << std::endl;
        CloseStream(devID);
        return -1;
    }

    INT32_T imgWidth = devInfo.imgWidth;
    INT32_T imgHeight = devInfo.imgHeight;
    std::vector<FLOAT_T> tempMatrix(imgWidth * imgHeight);

    // Step 4: 拍照
    CONST CHAR_T* imgPath = "D:/images";
    IMG_TYPE imgType = ONLY_JPG;

    if (TakeScreenshotEx(devID, imgPath, imgType) != GUIDEIR_OK) {
        std::cerr << "Failed to take screenshot." << std::endl;
        //CloseStream(devID);
        return -1;
    }

    // Step 5: 获取温度矩阵
    if (GetTempMatrixEx(devID, tempMatrix.data(), imgWidth, imgHeight) != GUIDEIR_OK) {
        std::cerr << "Failed to get temperature matrix." << std::endl;
        //CloseStream(devID);
        return -1;
    }

    // Step 6: 保存温度矩阵为 CSV 文件
    std::vector<std::vector<std::string>> csvData(imgHeight, std::vector<std::string>(imgWidth));
    for (INT32_T i = 0; i < imgHeight; ++i) {
        for (INT32_T j = 0; j < imgWidth; ++j) {
            csvData[i][j] = std::to_string(tempMatrix[i * imgWidth + j]);
        }
    }

    std::string csvFilePath = "D:/csv/temperature_matrix.csv";
    auto csvResult = Utility::CsvWriter::writeCsv(csvFilePath, csvData);
    if (!csvResult.first) {
        std::cerr << "Failed to write CSV file." << std::endl;
    } else {
        std::cout << "Temperature matrix saved to: " << csvResult.second << std::endl;
    }

    // Step 7: 关闭视频流
    //CloseStream(devID);

    return 0;
}