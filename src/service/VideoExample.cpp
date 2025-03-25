#include "Gaode/GuideSDK.h"
#include <stdio.h>
VOID onRGBData(GD_RGB_INFO info, VOID *param){
        //显示图像
} void onY16Data(GD_Y16_INFO infoY16, VOID *param) {
    //Y16 数据处理
}
void onStateChanged(GD_STATE_INFO info, VOID *param) {
    //提示网络断开或者连上
}
int main() {
    DEVICE_INFO devInfo;
    VERSION_INFO verInfo;
    INT32_T devID, ret;
    WORKING_MODE mode = H264_MODE;
    FLOAT_T temp;
    INT32_T num = GetDeviceNum();
    printf("GetDeviceNum %d\n", num);
    devID = GetDeviceIDNotConnected("192.168.1.188");
    printf("devID %d\n", devID);
    GetDeviceInfo(devID, &devInfo);
    GetVersionInfo(devID, &verInfo);
    ret = OpenStream(devID, onRGBData, onY16Data, onStateChanged, (VOID *) devID, mode, 0);
    if (GUIDEIR_ERR == ret)
        return 0;
    ret=TakeScreenshot(devID, "D:/images/", ONLY_JPG);
    if (GUIDEIR_ERR == ret)
        return 0;
    getchar();
    POINT_T point;
    point.x = 100;
    point.y = 100;
    //实时画面中显示此坐标的温度
    ShowPointTemp(devID, point);
    //打快门操作
    ShutterControlEx(devID, SHUTTER_NOW, 0);
    getchar();
    FocusControlEx(devID, AUTO_FOCUS, 0);
    SetPaletteEx(devID, 3);
    getchar();
    CloseStream(devID);

    return 0;
}