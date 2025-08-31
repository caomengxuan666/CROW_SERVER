/*************************************************
Copyright (C), 2019-2029, GuideIR Tech. Co., Ltd.
File name	: SDKParams.h
Author		: Guide Sensmart RD
Version		: 1.0
Date		: 2019/7/6
Description	:
*************************************************/
#ifndef SDK_PARAMS_H
#define SDK_PARAMS_H

#include "common_type.h"
#include <string.h>

#ifdef WINDOWS_PLATFORM
#define GUIDESDKAPI __declspec(dllexport)
#else
#define GUIDESDKAPI
#endif// WINDOWS_PLATFORM

#ifdef __cplusplus
#define GUIDESDK_STDC_START extern "C" {
#define GUIDESDK_STDC_END \
    }                     \
    ;
#else
#define GUIDESDK_STDC_START
#define GUIDESDK_STDC_END
#endif

typedef enum {
    NONE_MODE = 0,
    Y16_MODE = 1,//数据量过大，不建议使用
    H264_MODE = 2,
    Y16_AND_H264 = 3//数据量过大，不建议使用
} WORKING_MODE;

struct URL_INFO {
    CHAR_T userName[16];//用户名
    CHAR_T passWord[16];//密码
};

struct DEVICE_INFO {
    INT32_T devID;           //设置ID
    CHAR_T devName[16];      //设备名称
    INT32_T imgWidth;        //设备图像宽
    INT32_T imgHeight;       //设备图像高
    CHAR_T serialNum[64];    //设备序列号
    CHAR_T macAddr[32];      //设备mac地址
    CHAR_T ipAddr[16];       //设备ip
    CHAR_T subNetMask[16];   //子网掩码
    CHAR_T gateway[16];      //网关
    CHAR_T dnsAddr[16];      //dns
    UINT16_T armPort;        //arm通讯端口号
    UINT16_T fpgaPort;       //fpga通讯端口号
    UINT16_T y16Port;        //y16数据通讯端口号
    CHAR_T model[16];        //测温模型名称
    BOOL_T isConnected;      //本机是否已连接到设备。如果已连接不能重复再次连接同一台设备。
    WORKING_MODE workingMode;//本机连接到设备时设置的工作方式，0 NONE_MODE表示未连接。
public:
    DEVICE_INFO() {
        memset(this, 0, sizeof(DEVICE_INFO));
    }
};

struct NETWORK_INFO {
    CHAR_T serialNum[64]; //设备序列号
    CHAR_T macAddr[32];   //设备mac地址
    CHAR_T ipAddr[16];    //设备ip
    CHAR_T subNetMask[16];//子网掩码
    CHAR_T gateway[16];   //网关
    CHAR_T dnsAddr[16];   //dns
public:
    NETWORK_INFO() {
        memset(this, 0, sizeof(NETWORK_INFO));
    }
};

// Y16数据结构
struct GD_Y16OutputInfo {
    float fCurrentShutterTemp;// 实时快门温, 单位摄氏度
    float fPreShutterTemp;    //上一次打快门温度
    float fJpmTemp;           //焦平面温度
    float fLenTemp;           //实时镜筒温
    short sY16_Center;        //Y16中间值CenterAD
    BYTE_T *paramLine;        //参数行
    INT32_T paramLineLength;  //参数行长度
};

// RGB视频回调参数数据结构
struct GD_RGB_INFO {
    BYTE_T *rgbData;  // RGB数据
    INT32_T imgWidth; // 图像宽
    INT32_T imgHeight;// 图像高
    INT32_T devID;    // rgbData对应的设备ID
public:
    GD_RGB_INFO() {
        memset(this, 0, sizeof(GD_RGB_INFO));
    }
};

// Y16回调参数数据结构
struct GD_Y16_INFO {
    INT16_T *y16Data; // Y16数据
    INT32_T imgWidth; // 图像宽
    INT32_T imgHeight;// 图像高
    INT32_T devID;    // y16Data对应的设备ID
    GD_Y16OutputInfo y16OutputInfo;

public:
    GD_Y16_INFO() {
        memset(this, 0, sizeof(GD_Y16_INFO));
    }
};

typedef enum {
    STREAM_DISCONNECT = 0,// 已断开
    STREAM_CONNECT = 1,   // 已连接
} CONNECT_STATE;

// 网络状态回调参数数据结构
struct GD_STATE_INFO {
    CONNECT_STATE state;
    INT32_T devID;

public:
    GD_STATE_INFO() {
        memset(this, 0, sizeof(GD_STATE_INFO));
    }
};

struct POINT_T {
    INT32_T x;
    INT32_T y;

public:
    POINT_T() {
        memset(this, 0, sizeof(POINT_T));
    }
};

struct LINE_T {
    INT32_T x1;
    INT32_T y1;
    INT32_T x2;
    INT32_T y2;

public:
    LINE_T() {
        memset(this, 0, sizeof(LINE_T));
    }
};

// 矩形区域数据结构
struct RECT_T {
    INT16_T x;// 矩形左上角X坐标
    INT16_T y;// 矩形左上角Y坐标
    INT32_T w;// 矩形宽度
    INT32_T h;// 矩形高度
public:
    RECT_T() {
        memset(this, 0, sizeof(RECT_T));
    }
};

// 温度点数据结构
struct TEMP_POINT {
    INT16_T x;   // 温度点X坐标
    INT16_T y;   // 温度点Y坐标
    FLOAT_T temp;// 温度点温度
public:
    TEMP_POINT() {
        memset(this, 0, sizeof(TEMP_POINT));
    }
};

// 温度回调参数数据结构
struct GD_TEMP_INFO {
    TEMP_POINT highTemp;// 高温
    TEMP_POINT lowTemp; // 低温
    TEMP_POINT avgTemp; // 平均温
    TEMP_POINT centTemp;// 中心温
    INT32_T devID;

public:
    GD_TEMP_INFO() {
        memset(this, 0, sizeof(GD_TEMP_INFO));
    }
};

typedef enum {
    CALC_TEMP_HIGH = 1,  //只计算最高温
    CALC_TEMP_LOW = 2,   //只计算最低温
    CALC_TEMP_AVG = 3,   //只计算平均温
    CALC_TEMP_ALL = 4,   //同时计算最高温、最低温、平均温度
    CALC_TEMP_CENTRE = 5,//只计算中心温
} CALC_TEMP_TYPE;

typedef enum {
    SHUTTER_NOW = 1,         //即时打快门
    SHUTTER_CLOSE = 2,       //关闭快门
    SHUTTER_OPEN = 3,        //打开快门
    AUTO_SHUTTER_ENABLE = 4, //设备端自动快门机制开启
    AUTO_SHUTTER_DISABLE = 5,//设备端自动打快门机制关闭
    SET_SHUTTER_TIME = 6,    //设置自动打快门时间间隔	单位：分钟。
    GET_SHUTTER_TIME = 7     //获取自动打快门时间间隔	单位：分钟。
} CMD_SHUTTER_TYPE;

typedef enum {
    NEAR_FOCUS = 1,        //近焦		电机位置为最大值
    FAR_FOCUS = 2,         //远焦		电机位置为0
    STOP_FOCUS = 3,        //停止调焦
    AUTO_FOCUS = 4,        //自动调焦
    NEAR_FOCUS_FINE = 5,   //近焦微调
    FAR_FOCUS_FINE = 6,    //远焦微调
    SET_MOTOR_POSITION = 7,//设置电机位置
    GET_MOTOR_POSITION = 8 //获取电机位置
} CMD_FOCUS_TYPE;

typedef enum {
    JPG_WITH_TEMP = 1,//图片+温度信息
    ONLY_TEMP = 2,    //只有温度信息
    ONLY_JPG = 3,     //只有图片
    JPG_TEMP_GW = 4,  //国网格式信息
    JPG_TEMP_UVH = 5, //特高压变电站系统格式
} IMG_TYPE;

typedef enum {
    MP4_MEDIA = 1,
    AVI_MEDIA = 2,
} GD_MEDIA_TYPE;

typedef enum {
    RGB24_PIXEL_FORMAT = 1,
    BGR24_PIXEL_FORMAT = 2,
} GD_PIXEL_FORMAT;

typedef VOID (*RGBDataCB)(GD_RGB_INFO rgbInfo, VOID *param);
typedef VOID (*Y16DataCB)(GD_Y16_INFO y16Info, VOID *param);
typedef VOID (*StateCB)(GD_STATE_INFO stateInfo, VOID *param);
typedef VOID (*TempCB)(GD_TEMP_INFO tempInfo, VOID *param);

// 电子变焦倍数，对于fpga或asic程序是0（1倍）、1（2倍）、2（4倍）
typedef enum {
    GD_EZ_1,//电子变倍为1
    GD_EZ_2,//电子变倍为2
    GD_EZ_4,//电子变倍为4
} GD_EZ_TIMES;

// 电子变焦信息
struct GD_EZ_INFO {
    GD_EZ_TIMES nExLevel;
    INT32_T nCenterX;
    INT32_T nCenterY;

public:
    GD_EZ_INFO() {
        memset(this, 0, sizeof(GD_EZ_INFO));
    }
};

// 电子变焦倍数，对ARM应用程序就是设置1、2、4
typedef enum {
    GD_ZOOM_SCALE_1 = 1,//电子变倍为1
    GD_ZOOM_SCALE_2 = 2,//电子变倍为2
    GD_ZOOM_SCALE_4 = 4,//电子变倍为4
} GD_ZOOM_SCALE;

typedef enum {
    ADD_RECT_ANALYSIS = 1,   //(废弃 不生效)				添加矩形分析对象
    DELETE_TEMP_ANALYSIS = 2,//(废弃 不生效)				删除分析对象
    ADD_TEMP_DIS = 3,        //显示温度分析		需要给ANALYSIS_PARAM_INFO.combinaType赋值
    TEMP_WITH_CURSOR = 4,    //显示光标			需要给ANALYSIS_PARAM_INFO.cursorMode赋值
    GET_RECT_ANALYSIS = 5,   //(废弃 不生效)				获取矩形分析对象信息
} CMD_ANALYSIS_TYPE;

struct ANALYSIS_PARAM_INFO {
    INT32_T combinaType;//ARM软件温度值类型：0 none 不显示温度值。1 MAX  2 MIN   3 AVG   4 MAX +MIN    5 MAX +AVG   6 MIN + AVG   7 MAX + MIN + AVG。   8 Center
    RECT_T rect;
    BOOL_T enableTempWithCursor;//(废弃 不生效)				使能数字温跟随光标，1启用，0禁用。
    INT32_T analyzeMode;        //(废弃 不生效)				分析模式 0-关闭分析 1-全屏分析 2-区域分析
    INT32_T cursorMode;         //光标显示方式  0-不显示 1-最高温 2-最低温  3-最低+最高   4-中心
public:
    ANALYSIS_PARAM_INFO() {
        memset(this, 0, sizeof(ANALYSIS_PARAM_INFO));
    }
};

typedef enum {
    SET_TEMP_DISPLAY_MODE = 1,//设置实时画面显示温度标识		0 none 不显示温度值。1 MAX  2 MIN   3 AVG   4 MAX +MIN    5 MAX +AVG   6 MIN + AVG   7 MAX + MIN + AVG   8 Center
    GET_TEMP_DISPLAY_MODE = 2,//获取实时画面显示温度标识	0 none 不显示温度值。1 MAX  2 MIN   3 AVG   4 MAX +MIN    5 MAX +AVG   6 MIN + AVG   7 MAX + MIN + AVG   8 Center
    SET_TEMP_CURSOR_MODE = 3, //设置实时画面显示光标模式		0-不显示 1-最高温 2-最低温  3-最低+最高   4-Center
    GET_TEMP_CURSOR_MODE = 4, //获取实时画面显示光标模式		0-不显示 1-最高温 2-最低温  3-最低+最高   4-Center
} CMD_TRMPLABEL_TYPE;

// 显示色带信息方式
enum SHOW_PALETTE_TYPE {
    PALETTE_HIDE = 0, //不显示
    PALETTE_LEFT = 1, //显示左边
    PALETTE_RIGHT = 2,//显示右边
};

enum CMD_MODE {
    FPGA_MODE = 0,//发送FPGA命令
    ARM_MODE = 1, //发送ARM命令
};

struct VERSION_INFO {
    CHAR_T serialNum[64];  //设置序列号
    CHAR_T macAddr[32];    //设备mac地址
    CHAR_T armVersion[32]; //arm版本号
    CHAR_T fpgaVersion[32];//fpga版本号
    CHAR_T sdkVersion[32]; //sdk版本号
public:
    VERSION_INFO() {
        memset(this, 0, sizeof(VERSION_INFO));
    }
};

struct STRING_INFO {
    INT32_T status;//使能状态，1 显示字符串（右上角固定的位置），0 不显示字符串, 5 可自定义显示字符串位置。
    INT32_T x;
    INT32_T y;
    INT32_T contentLen;     //限定contentLenlen < 30字符（除数字和字母外，其他字符算两个字符）
    CHAR_T content[1280];   //Unicode, UTF16，添加长字符串
    DOUBLE_T contentExtents;//获取字符串尺寸
public:
    STRING_INFO() {
        memset(this, 0, sizeof(STRING_INFO));
    }
};

typedef enum {
    ADD_STRING = 1,    //添加字符串
    GET_STRING = 2,    //获取字符串
    ENABLE_STRING = 3, //使能字符串
    DISABLE_STRING = 4,//禁用字符串
} CMD_STRING_TYPE;

struct ALARM_INFO {
    INT32_T state;//1 高温报警；	2 低温报警； 3 高低温同时报警。0，取消报警。
    INT32_T highLimit;
    INT32_T lowLimit;
    INT32_T mode;//0 持续报警； 1 自动停止
public:
    ALARM_INFO() {
        memset(this, 0, sizeof(ALARM_INFO));
    }
};

typedef enum {
    ALARM_SWITCH = 1,
    ALARM_STATE = 2,
    ALARM_HIGH = 3,
    ALARM_LOW = 4,
    ALARM_MODE = 5,
    ALARM_ALL_PARAM = 6,//此命令一次完成以上5个参数一起设置。使用上面5个命令可逐个参数分别设置。
} CMD_ALARM_TYPE;

/*取值范围说明：
发射率（0.01~1.00）
距离（0.4m~25m）
湿度(0 % ~100 % )
背景温度(0.1℃~650℃)
B参数（ - 100℃~100℃）
KF参数（1~100）
coef0(80~120)
coef1(-10000~10000)*/
struct CALC_PARAM_INFO {
    FLOAT_T emiss;        //发射率 0.01-1
    FLOAT_T distance;     //距离	0.4-25
    INT32_T humidity;     //湿度	0-100
    FLOAT_T backTemp;     //背景温度 0.1-650
    INT32_T backFlag;     //背温开关
    FLOAT_T B;            //CorrectionTemp -100-100
    INT32_T KF;           // 0-255
    FLOAT_T transmittance;//透过率 0.00-100.00
    INT32_T coef0;        //两点校正参数0
    INT32_T coef1;        //两点校正参数1
public:
    CALC_PARAM_INFO() {
        memset(this, 0, sizeof(CALC_PARAM_INFO));
    }
};

enum CALC_PARAM_TYPE {
    CALC_PARAM_EMISS = 1,   //发射率
    CALC_PARAM_DISTANCE = 2,//距离
    CALC_PARAM_HUMIDITY = 3,//湿度
    CALC_PARAM_BACKTEMP = 4,//背景温度
    CALC_PARAM_BACKFLAG = 5,//背温开关
    CALC_PARAM_B = 6,       //B2
    CALC_PARAM_KF = 7,      //KF
    CALC_PARAM_TRANSMIT = 8,//透过率
    CALC_PARAM_ALL = 9,     //以上8个测温参数一起set或者get，一条命令可以完成。
    CALC_PARAM_SAVE = 10,   //保存前面操作设置的参数，掉电后再开机仍然有效。
    CALC_PARAM_COEF0 = 11,  //coef0
    CALC_PARAM_COEF1 = 12,  //coef1
};

enum DEVICE_PARAM_TYPE {
    DEVICE_PARAM_RANGE = 1,    //切换测温范围，INT16_T。
    DEVICE_PARAM_RSADDR = 2,   //UART校验，INT32_T。
    DEVICE_PARAM_UARTSPEED = 3,//UART速率，INT32_T。
    BLACK_BODY_DIAMETER = 4,   //黑体直径，浮点参数。
    AUTO_SWITCH_RANGE = 5,     //是否启用自动切换测温范围，INT32_T。1，自动切换。0，不会自动切换。
};

enum DEVICE_PORT_TYPE {
    DEVICE_Y16_PORT = 1,
    DEVICE_ARM_PORT = 2,
    DEVICE_FPGA_PORT = 3,
    DEVICE_ALL_PORT = 4,//以上3个端口信息一起set或者get，一条命令可以完成。
    DEVICE_HTTP_PORT = 5,
};

// 画面调光模式
enum ADJUST_LIGHT_MODE {
    LIGHT_BRIGHTNESS_CONTRAST = 1,//自动调光(亮度、对比度）
    LIGHT_TEMPERATURE_MANUAL = 2, //手动调光(温度、高低值)
    LIGHT_TEMPERATURE_AUTO = 3,   //仅Y16模式不支持		(此模式不建议使用)
};

struct LIGHT_PARAM_INFO {
    ADJUST_LIGHT_MODE mode;//调光模式，设备端会存储
    INT32_T brightness;    //在自动调光支持设置亮度，设备端会存储			0~255
    INT32_T contrast;      //在自动调光支持设置对比度，设备端会存储		0~512
    FLOAT_T maxT;          //仅Y16模式手动调光支持设置，设备端不会存储
    FLOAT_T minT;          //仅Y16模式手动调光支持设置，设备端不会存储
public:
    LIGHT_PARAM_INFO() {
        memset(this, 0, sizeof(LIGHT_PARAM_INFO));
    }
};

struct MODULATE_PARAM_INFO {
    BOOL_T auto_moudulate;//自动调光开关  对于Y16模式设置不生效
    INT32_T luminance;    //亮度		0~255
    INT32_T contrast;     //对比度	0~512
public:
    MODULATE_PARAM_INFO() {
        memset(this, 0, sizeof(MODULATE_PARAM_INFO));
    }
};

typedef enum {
    LIGHT_MODE = 1,
    LIGHT_BRIGHT = 2,
    LIGHT_CONTRAST = 3,
    LIGHT_MAX_TEMP = 4,
    LIGHT_MIN_TEMP = 5,
    LIGHT_ALL_PARAM = 6,//此命令一次完成以上5个参数一起设置。使用上面5个命令可逐个参数分别设置。
} CMD_LIGHT_TYPE;

typedef enum {
    PTZ_GET_ADDR = 0x01,
    PTZ_SET_ADDR,
    PTZ_MOVE_UP,
    PTZ_MOVE_DOWN,
    PTZ_MOVE_LEFT,
    PTZ_MOVE_RIGHT,
    PTZ_MOVE_STOP,
    PTZ_MOVE_LEFT_UP,
    PTZ_MOVE_RIGHT_UP,
    PTZ_MOVE_LEFT_DOWN,
    PTZ_MOVE_RIGHT_DOWN,
    PTZ_ZOOM_IN,
    PTZ_ZOOM_OUT,
    PTZ_ZOOM_STOP,
    PTZ_FOCUS_NEAR,
    PTZ_FOCUS_FAR,
    PTZ_FOCUS_STOP,
    PTZ_APERTURE_OPEN,
    PTZ_APERTURE_CLOSE,
    PTZ_SET_HORI_ANGLE,
    PTZ_GET_HORI_ANGLE,
    PTZ_SET_VERT_ANGLE,
    PTZ_GET_VERT_ANGLE,
    PTZ_SET_LOCA_SPEED,
    PTZ_SET_SCAN_SPEED,
    PTZ_SET_CRUI_INTERVAL,
    PTZ_PRESET_SET,
    PTZ_PRESET_CALL,
    PTZ_PRESET_DELETE,
    PTZ_SET_CRUI_SPEED,
    PTZ_CRUI_START,
    PTZ_CRUI_STOP,
    PTZ_CHECK_POWERON,
    PTZ_FACTORY_SETTINGS,
} PTZ_COMMAND_TYPE;

typedef enum {
    PLP_GET_POINTS = 0x01,//获取点分析对象
    PLP_GET_LINES,        //获取线分析对象
    PLP_GET_RECTS,        //获取面分析对象
    PLP_ADD_POINTS,       //添加点分析对象
    PLP_ADD_LINES,        //添加线分析对象
    PLP_ADD_RECTS,        //添加面分析对象
    PLP_UPDATE_POINTS,    //更新点分析对象
    PLP_UPDATE_LINES,     //更新线分析对象
    PLP_UPDATE_RECTS,     //更新面分析对象
    PLP_DELETE_OBJ,       //通过id删除分析对象
    PLP_DELETE_ALL_OBJ,   //删除所有分析对象
} PLP_COMMAND_TYPE;

struct PLP_OBJ_INFO {
    INT32_T id;         //内部已设置值，无需设置
    CHAR_T name[32];    //内部已定义值，无需设置
    INT32_T type;       //分析对象类型：1 ：点； 2：线； 3：面；
    INT32_T combinaType;//5种温度信息组合方式：0：不显示；1：显示最高温；2：显示最低温；3：显示平均温；4：仅名称
    BOOL_T isHide;      //此字段失效
    union {
        POINT_T point;
        LINE_T line;
        RECT_T rect;
    };

public:
    PLP_OBJ_INFO() {
        memset(this, 0, sizeof(PLP_OBJ_INFO));
    }
};

typedef enum {
    ANA_GET = 0x01,    //获取分析对象
    ANA_ADD,           //添加分析对象
    ANA_UPDATE,        //更新分析对象
    ANA_DELETE_OBJ,    //通过id删除分析对象
    ANA_DELETE_ALL_OBJ,//删除所有分析对象
} ANALYZE_OBJ_COMMAND_TYPE;

struct ANALYZE_OBJ_INFO {
    INT32_T id;               //内部已设置值，无需设置
    CHAR_T name[32];          //内部已定义值，无需设置
    INT32_T type;             //分析对象类型：1 ：点； 2：线； 3：面； 5:圆；
    POINT_T position[2];      //如果对象类型为1：第二个元素赋值为空即可   2：2个数组元素标明线的两个端点  3：2个数组元素标明矩形的左上角和右下角
                              //5：2个数组元素标明圆所在矩形的左上角和右下角
    INT32_T temperature_label;//5种温度信息组合方式：0：不显示；1：显示最高温；2：显示最低温；3：显示平均温；4：仅名称
public:
    ANALYZE_OBJ_INFO() {
        memset(this, 0, sizeof(ANALYZE_OBJ_INFO));
    }
};

struct IPT_SHIELDAREA {
    int shield_area_id;//只能添加2个屏蔽区域  ID为0或1
    int x1;            //矩形区域左上角x坐标
    int y1;            //矩形区域左上角y坐标
    int x2;            //矩形区域右下角x坐标
    int y2;            //矩形区域右下角y坐标
public:
    IPT_SHIELDAREA() {
        memset(this, 0, sizeof(IPT_SHIELDAREA));
    }
};

struct DEVICE_TEMP_INFO {
    int temp_mode;         //0 全屏  1 分析对象
    int analyze_object_id; //0为全屏   其余为分析对象id
    float max_temp;        //最高温
    float min_temp;        //最低温
    float avg_temp;        //平均温
    UINT64_T current_times;//当前时间
public:
    DEVICE_TEMP_INFO() {
        memset(this, 0, sizeof(DEVICE_TEMP_INFO));
    }
};

struct IptPictureFrame {
    char *IRImage;                 //红外视频截图数据文件
    unsigned char FileVersion[2];  //文件版本
    unsigned short Width;          //温度点阵宽度
    unsigned short Height;         //温度点阵高度
    unsigned char DateTime[14];    //拍摄时间
    float *IRData;                 //红外温度值点阵数据
    float Emiss;                   //辐射率
    float AmbientTemperature;      //环境温度
    unsigned char Len;             //镜头度数
    unsigned int Distance;         //拍摄距离
    unsigned char RelativeHumidity;//相对湿度
    float ReflectiveTemperature;   //反射温度
    unsigned char Productor[32];   //生产厂家
    unsigned char Type[32];        //产品型号
    unsigned char SerialNO[32];    //产品序列号
    double Longitude;              //经度
    double Latitude;               //纬度
    int Altitude;                  //海拔
    unsigned int DescriptionLength;//备注信息长度
    unsigned char *DescriptionData;//备注信息,分析对象等信息
    unsigned int IRDataOffset;     //红外数据的起始偏移地址
    unsigned char FileEndType[16]; //文件末尾标识
public:
    IptPictureFrame() {
        memset(this, 0, sizeof(IptPictureFrame));
    }
};
#pragma pack(1)
struct UVH_PICTURE_FRAME {
    BYTE_T fileVersion[4];//文件版本
    FLOAT_T transmittance;//透过率 0.00-100.00
    FLOAT_T emiss;        //发射率 0.01-1
    FLOAT_T distance;     //距离	0.4-25
    FLOAT_T ambientTemp;  //环境温度 0.1-650
    FLOAT_T humidity;     //环境湿度	0-100

    UINT16_T width;    //温度点阵宽度
    UINT16_T height;   //温度点阵高度
    CHAR_T reserve[36];//保留位
public:
    UVH_PICTURE_FRAME() {
        memset(this, 0, sizeof(UVH_PICTURE_FRAME));
    }
};
#pragma pack()

struct TWO_POINT_CORRECT_INFO {
    float blackbody_first_temp;
    POINT_T blackbody_first_point;
    float blackbody_seconed_temp;
    POINT_T blackbody_seconed_point;

public:
    TWO_POINT_CORRECT_INFO() {
        memset(this, 0, sizeof(TWO_POINT_CORRECT_INFO));
    }
};

typedef enum {
    WHITEHOT = 0,  //白热
    BLACKHOT,      //黑热
    IRONRED,       //铁红
    FULGURITE,     //熔岩
    HOTIRON,       //热铁
    MEDICAL,       //医疗
    MEDICAL0,      //医疗0
    MEDICAL1,      //医疗1
    MEDICAL2,      //医疗2
    ARCTIC,        //北极
    BODYDRT,       //人体筛查
    RAINBOW1,      //彩虹1
    RAINBOW2,      //彩虹2
    RAINBOW3,      //彩虹3
    TINT1,         //描红1
    TINT2,         //描红2
    TINT3,         //描红3
    ICEFIRE,       //冰火
    RECERSEICEFIRE,//反冰火
    STEPS,         //分层
    SEPIA,         //深褐
    GREENHOT,      //绿热
    BLUEHOT,       //蓝热
    WINTER,        //冬季
    HIGHLIGHT,     //高亮
    AMBER,         //琥珀

} PALETTE_INTO;


typedef enum {
    UP_DOWN = 0,       //垂直轴线180度翻转
    LEFT_RIGHT,        //水平轴线180度翻转
    UP_DOWN_LEFT_RIGHT,//360度翻转
    ROTATE90,          //90度翻转
    ROTATE270,         //270度翻转
    NORMAL,            //不翻转
} ROTATE_TYPE;

//细节增强参数
struct FIXED_POINT_IEE {
    BOOL_T auto_IEE = FALSE_T;        //是否开启细节增强
    INT32_T threshold = 20;           //细节阈值					1~50    ss:5
    INT32_T pos_weight_table_std = 15;//权重表  空域滤波 1~50
    INT32_T restrainRangeThre = 128;  //均匀面抑制阈值		0~512   ss:512
    INT32_T mixRange = 230;           //混合调光范围				0~512
    INT32_T midValue = 110;           //映射中值					0~255
    INT32_T platThresh = 15;          //平台阈值					1~1000
    INT32_T upDiscardRatio = 5;       //上抛点					0~100
    INT32_T downDiscardRatio = 5;     //下抛点				0~100
    INT32_T iie_detail_gain = 32;     //增益系数			0~128   ss:64
};

struct IEE_PARAMS {
    BOOL_T auto_iee = FALSE_T;   //是否开启细节增强
    INT32_T iie_detail_gain = 32;//增益系数					0~128
};

//ARM设备状态码
#define ARM_NO_CURVE_FILE_ERROR 0x00000001
#define ARM_Y16_ABNORMAL_ERROR 0x00000002
#define ARM_NO_MEASURE_PARAM_ERROR 0x00000004
#define ARM_FONT_MISSING_ERROR 0x00000008
//FPGA设备状态码
#define FPGA_INVALID_SENSOR_CONFIG_ERROR 0x00000010
#define FPGA_LOAD_FLASH_PARAM_FAILED_ERROR 0x00000020
#define FPGA_DEVICE_WORK_TEMP_OVER_RANGE_ERROR 0x00000040

#endif// !SDK_PARAMS_H