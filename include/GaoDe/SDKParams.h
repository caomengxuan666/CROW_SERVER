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
    Y16_MODE = 1,//���������󣬲�����ʹ��
    H264_MODE = 2,
    Y16_AND_H264 = 3//���������󣬲�����ʹ��
} WORKING_MODE;

struct URL_INFO {
    CHAR_T userName[16];//�û���
    CHAR_T passWord[16];//����
};

struct DEVICE_INFO {
    INT32_T devID;           //����ID
    CHAR_T devName[16];      //�豸����
    INT32_T imgWidth;        //�豸ͼ���
    INT32_T imgHeight;       //�豸ͼ���
    CHAR_T serialNum[64];    //�豸���к�
    CHAR_T macAddr[32];      //�豸mac��ַ
    CHAR_T ipAddr[16];       //�豸ip
    CHAR_T subNetMask[16];   //��������
    CHAR_T gateway[16];      //����
    CHAR_T dnsAddr[16];      //dns
    UINT16_T armPort;        //armͨѶ�˿ں�
    UINT16_T fpgaPort;       //fpgaͨѶ�˿ں�
    UINT16_T y16Port;        //y16����ͨѶ�˿ں�
    CHAR_T model[16];        //����ģ������
    BOOL_T isConnected;      //�����Ƿ������ӵ��豸����������Ӳ����ظ��ٴ�����ͬһ̨�豸��
    WORKING_MODE workingMode;//�������ӵ��豸ʱ���õĹ�����ʽ��0 NONE_MODE��ʾδ���ӡ�
public:
    DEVICE_INFO() {
        memset(this, 0, sizeof(DEVICE_INFO));
    }
};

struct NETWORK_INFO {
    CHAR_T serialNum[64]; //�豸���к�
    CHAR_T macAddr[32];   //�豸mac��ַ
    CHAR_T ipAddr[16];    //�豸ip
    CHAR_T subNetMask[16];//��������
    CHAR_T gateway[16];   //����
    CHAR_T dnsAddr[16];   //dns
public:
    NETWORK_INFO() {
        memset(this, 0, sizeof(NETWORK_INFO));
    }
};

// Y16���ݽṹ
struct GD_Y16OutputInfo {
    float fCurrentShutterTemp;// ʵʱ������, ��λ���϶�
    float fPreShutterTemp;    //��һ�δ�����¶�
    float fJpmTemp;           //��ƽ���¶�
    float fLenTemp;           //ʵʱ��Ͳ��
    short sY16_Center;        //Y16�м�ֵCenterAD
    BYTE_T *paramLine;        //������
    INT32_T paramLineLength;  //�����г���
};

// RGB��Ƶ�ص��������ݽṹ
struct GD_RGB_INFO {
    BYTE_T *rgbData;  // RGB����
    INT32_T imgWidth; // ͼ���
    INT32_T imgHeight;// ͼ���
    INT32_T devID;    // rgbData��Ӧ���豸ID
public:
    GD_RGB_INFO() {
        memset(this, 0, sizeof(GD_RGB_INFO));
    }
};

// Y16�ص��������ݽṹ
struct GD_Y16_INFO {
    INT16_T *y16Data; // Y16����
    INT32_T imgWidth; // ͼ���
    INT32_T imgHeight;// ͼ���
    INT32_T devID;    // y16Data��Ӧ���豸ID
    GD_Y16OutputInfo y16OutputInfo;

public:
    GD_Y16_INFO() {
        memset(this, 0, sizeof(GD_Y16_INFO));
    }
};

typedef enum {
    STREAM_DISCONNECT = 0,// �ѶϿ�
    STREAM_CONNECT = 1,   // ������
} CONNECT_STATE;

// ����״̬�ص��������ݽṹ
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

// �����������ݽṹ
struct RECT_T {
    INT16_T x;// �������Ͻ�X����
    INT16_T y;// �������Ͻ�Y����
    INT32_T w;// ���ο��
    INT32_T h;// ���θ߶�
public:
    RECT_T() {
        memset(this, 0, sizeof(RECT_T));
    }
};

// �¶ȵ����ݽṹ
struct TEMP_POINT {
    INT16_T x;   // �¶ȵ�X����
    INT16_T y;   // �¶ȵ�Y����
    FLOAT_T temp;// �¶ȵ��¶�
public:
    TEMP_POINT() {
        memset(this, 0, sizeof(TEMP_POINT));
    }
};

// �¶Ȼص��������ݽṹ
struct GD_TEMP_INFO {
    TEMP_POINT highTemp;// ����
    TEMP_POINT lowTemp; // ����
    TEMP_POINT avgTemp; // ƽ����
    TEMP_POINT centTemp;// ������
    INT32_T devID;

public:
    GD_TEMP_INFO() {
        memset(this, 0, sizeof(GD_TEMP_INFO));
    }
};

typedef enum {
    CALC_TEMP_HIGH = 1,  //ֻ���������
    CALC_TEMP_LOW = 2,   //ֻ���������
    CALC_TEMP_AVG = 3,   //ֻ����ƽ����
    CALC_TEMP_ALL = 4,   //ͬʱ��������¡�����¡�ƽ���¶�
    CALC_TEMP_CENTRE = 5,//ֻ����������
} CALC_TEMP_TYPE;

typedef enum {
    SHUTTER_NOW = 1,         //��ʱ�����
    SHUTTER_CLOSE = 2,       //�رտ���
    SHUTTER_OPEN = 3,        //�򿪿���
    AUTO_SHUTTER_ENABLE = 4, //�豸���Զ����Ż��ƿ���
    AUTO_SHUTTER_DISABLE = 5,//�豸���Զ�����Ż��ƹر�
    SET_SHUTTER_TIME = 6,    //�����Զ������ʱ����	��λ�����ӡ�
    GET_SHUTTER_TIME = 7     //��ȡ�Զ������ʱ����	��λ�����ӡ�
} CMD_SHUTTER_TYPE;

typedef enum {
    NEAR_FOCUS = 1,        //����		���λ��Ϊ���ֵ
    FAR_FOCUS = 2,         //Զ��		���λ��Ϊ0
    STOP_FOCUS = 3,        //ֹͣ����
    AUTO_FOCUS = 4,        //�Զ�����
    NEAR_FOCUS_FINE = 5,   //����΢��
    FAR_FOCUS_FINE = 6,    //Զ��΢��
    SET_MOTOR_POSITION = 7,//���õ��λ��
    GET_MOTOR_POSITION = 8 //��ȡ���λ��
} CMD_FOCUS_TYPE;

typedef enum {
    JPG_WITH_TEMP = 1,//ͼƬ+�¶���Ϣ
    ONLY_TEMP = 2,    //ֻ���¶���Ϣ
    ONLY_JPG = 3,     //ֻ��ͼƬ
    JPG_TEMP_GW = 4,  //������ʽ��Ϣ
    JPG_TEMP_UVH = 5, //�ظ�ѹ���վϵͳ��ʽ
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

// ���ӱ佹����������fpga��asic������0��1������1��2������2��4����
typedef enum {
    GD_EZ_1,//���ӱ䱶Ϊ1
    GD_EZ_2,//���ӱ䱶Ϊ2
    GD_EZ_4,//���ӱ䱶Ϊ4
} GD_EZ_TIMES;

// ���ӱ佹��Ϣ
struct GD_EZ_INFO {
    GD_EZ_TIMES nExLevel;
    INT32_T nCenterX;
    INT32_T nCenterY;

public:
    GD_EZ_INFO() {
        memset(this, 0, sizeof(GD_EZ_INFO));
    }
};

// ���ӱ佹��������ARMӦ�ó����������1��2��4
typedef enum {
    GD_ZOOM_SCALE_1 = 1,//���ӱ䱶Ϊ1
    GD_ZOOM_SCALE_2 = 2,//���ӱ䱶Ϊ2
    GD_ZOOM_SCALE_4 = 4,//���ӱ䱶Ϊ4
} GD_ZOOM_SCALE;

typedef enum {
    ADD_RECT_ANALYSIS = 1,   //(���� ����Ч)				��Ӿ��η�������
    DELETE_TEMP_ANALYSIS = 2,//(���� ����Ч)				ɾ����������
    ADD_TEMP_DIS = 3,        //��ʾ�¶ȷ���		��Ҫ��ANALYSIS_PARAM_INFO.combinaType��ֵ
    TEMP_WITH_CURSOR = 4,    //��ʾ���			��Ҫ��ANALYSIS_PARAM_INFO.cursorMode��ֵ
    GET_RECT_ANALYSIS = 5,   //(���� ����Ч)				��ȡ���η���������Ϣ
} CMD_ANALYSIS_TYPE;

struct ANALYSIS_PARAM_INFO {
    INT32_T combinaType;//ARM����¶�ֵ���ͣ�0 none ����ʾ�¶�ֵ��1 MAX  2 MIN   3 AVG   4 MAX +MIN    5 MAX +AVG   6 MIN + AVG   7 MAX + MIN + AVG��   8 Center
    RECT_T rect;
    BOOL_T enableTempWithCursor;//(���� ����Ч)				ʹ�������¸����꣬1���ã�0���á�
    INT32_T analyzeMode;        //(���� ����Ч)				����ģʽ 0-�رշ��� 1-ȫ������ 2-�������
    INT32_T cursorMode;         //�����ʾ��ʽ  0-����ʾ 1-����� 2-�����  3-���+���   4-����
public:
    ANALYSIS_PARAM_INFO() {
        memset(this, 0, sizeof(ANALYSIS_PARAM_INFO));
    }
};

typedef enum {
    SET_TEMP_DISPLAY_MODE = 1,//����ʵʱ������ʾ�¶ȱ�ʶ		0 none ����ʾ�¶�ֵ��1 MAX  2 MIN   3 AVG   4 MAX +MIN    5 MAX +AVG   6 MIN + AVG   7 MAX + MIN + AVG   8 Center
    GET_TEMP_DISPLAY_MODE = 2,//��ȡʵʱ������ʾ�¶ȱ�ʶ	0 none ����ʾ�¶�ֵ��1 MAX  2 MIN   3 AVG   4 MAX +MIN    5 MAX +AVG   6 MIN + AVG   7 MAX + MIN + AVG   8 Center
    SET_TEMP_CURSOR_MODE = 3, //����ʵʱ������ʾ���ģʽ		0-����ʾ 1-����� 2-�����  3-���+���   4-Center
    GET_TEMP_CURSOR_MODE = 4, //��ȡʵʱ������ʾ���ģʽ		0-����ʾ 1-����� 2-�����  3-���+���   4-Center
} CMD_TRMPLABEL_TYPE;

// ��ʾɫ����Ϣ��ʽ
enum SHOW_PALETTE_TYPE {
    PALETTE_HIDE = 0, //����ʾ
    PALETTE_LEFT = 1, //��ʾ���
    PALETTE_RIGHT = 2,//��ʾ�ұ�
};

enum CMD_MODE {
    FPGA_MODE = 0,//����FPGA����
    ARM_MODE = 1, //����ARM����
};

struct VERSION_INFO {
    CHAR_T serialNum[64];  //�������к�
    CHAR_T macAddr[32];    //�豸mac��ַ
    CHAR_T armVersion[32]; //arm�汾��
    CHAR_T fpgaVersion[32];//fpga�汾��
    CHAR_T sdkVersion[32]; //sdk�汾��
public:
    VERSION_INFO() {
        memset(this, 0, sizeof(VERSION_INFO));
    }
};

struct STRING_INFO {
    INT32_T status;//ʹ��״̬��1 ��ʾ�ַ��������Ͻǹ̶���λ�ã���0 ����ʾ�ַ���, 5 ���Զ�����ʾ�ַ���λ�á�
    INT32_T x;
    INT32_T y;
    INT32_T contentLen;     //�޶�contentLenlen < 30�ַ��������ֺ���ĸ�⣬�����ַ��������ַ���
    CHAR_T content[1280];   //Unicode, UTF16����ӳ��ַ���
    DOUBLE_T contentExtents;//��ȡ�ַ����ߴ�
public:
    STRING_INFO() {
        memset(this, 0, sizeof(STRING_INFO));
    }
};

typedef enum {
    ADD_STRING = 1,    //����ַ���
    GET_STRING = 2,    //��ȡ�ַ���
    ENABLE_STRING = 3, //ʹ���ַ���
    DISABLE_STRING = 4,//�����ַ���
} CMD_STRING_TYPE;

struct ALARM_INFO {
    INT32_T state;//1 ���±�����	2 ���±����� 3 �ߵ���ͬʱ������0��ȡ��������
    INT32_T highLimit;
    INT32_T lowLimit;
    INT32_T mode;//0 ���������� 1 �Զ�ֹͣ
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
    ALARM_ALL_PARAM = 6,//������һ���������5������һ�����á�ʹ������5���������������ֱ����á�
} CMD_ALARM_TYPE;

/*ȡֵ��Χ˵����
�����ʣ�0.01~1.00��
���루0.4m~25m��
ʪ��(0 % ~100 % )
�����¶�(0.1��~650��)
B������ - 100��~100�棩
KF������1~100��
coef0(80~120)
coef1(-10000~10000)*/
struct CALC_PARAM_INFO {
    FLOAT_T emiss;        //������ 0.01-1
    FLOAT_T distance;     //����	0.4-25
    INT32_T humidity;     //ʪ��	0-100
    FLOAT_T backTemp;     //�����¶� 0.1-650
    INT32_T backFlag;     //���¿���
    FLOAT_T B;            //CorrectionTemp -100-100
    INT32_T KF;           // 0-255
    FLOAT_T transmittance;//͸���� 0.00-100.00
    INT32_T coef0;        //����У������0
    INT32_T coef1;        //����У������1
public:
    CALC_PARAM_INFO() {
        memset(this, 0, sizeof(CALC_PARAM_INFO));
    }
};

enum CALC_PARAM_TYPE {
    CALC_PARAM_EMISS = 1,   //������
    CALC_PARAM_DISTANCE = 2,//����
    CALC_PARAM_HUMIDITY = 3,//ʪ��
    CALC_PARAM_BACKTEMP = 4,//�����¶�
    CALC_PARAM_BACKFLAG = 5,//���¿���
    CALC_PARAM_B = 6,       //B2
    CALC_PARAM_KF = 7,      //KF
    CALC_PARAM_TRANSMIT = 8,//͸����
    CALC_PARAM_ALL = 9,     //����8�����²���һ��set����get��һ�����������ɡ�
    CALC_PARAM_SAVE = 10,   //����ǰ��������õĲ�����������ٿ�����Ȼ��Ч��
    CALC_PARAM_COEF0 = 11,  //coef0
    CALC_PARAM_COEF1 = 12,  //coef1
};

enum DEVICE_PARAM_TYPE {
    DEVICE_PARAM_RANGE = 1,    //�л����·�Χ��INT16_T��
    DEVICE_PARAM_RSADDR = 2,   //UARTУ�飬INT32_T��
    DEVICE_PARAM_UARTSPEED = 3,//UART���ʣ�INT32_T��
    BLACK_BODY_DIAMETER = 4,   //����ֱ�������������
    AUTO_SWITCH_RANGE = 5,     //�Ƿ������Զ��л����·�Χ��INT32_T��1���Զ��л���0�������Զ��л���
};

enum DEVICE_PORT_TYPE {
    DEVICE_Y16_PORT = 1,
    DEVICE_ARM_PORT = 2,
    DEVICE_FPGA_PORT = 3,
    DEVICE_ALL_PORT = 4,//����3���˿���Ϣһ��set����get��һ�����������ɡ�
    DEVICE_HTTP_PORT = 5,
};

// �������ģʽ
enum ADJUST_LIGHT_MODE {
    LIGHT_BRIGHTNESS_CONTRAST = 1,//�Զ�����(���ȡ��Աȶȣ�
    LIGHT_TEMPERATURE_MANUAL = 2, //�ֶ�����(�¶ȡ��ߵ�ֵ)
    LIGHT_TEMPERATURE_AUTO = 3,   //��Y16ģʽ��֧��		(��ģʽ������ʹ��)
};

struct LIGHT_PARAM_INFO {
    ADJUST_LIGHT_MODE mode;//����ģʽ���豸�˻�洢
    INT32_T brightness;    //���Զ�����֧���������ȣ��豸�˻�洢			0~255
    INT32_T contrast;      //���Զ�����֧�����öԱȶȣ��豸�˻�洢		0~512
    FLOAT_T maxT;          //��Y16ģʽ�ֶ�����֧�����ã��豸�˲���洢
    FLOAT_T minT;          //��Y16ģʽ�ֶ�����֧�����ã��豸�˲���洢
public:
    LIGHT_PARAM_INFO() {
        memset(this, 0, sizeof(LIGHT_PARAM_INFO));
    }
};

struct MODULATE_PARAM_INFO {
    BOOL_T auto_moudulate;//�Զ����⿪��  ����Y16ģʽ���ò���Ч
    INT32_T luminance;    //����		0~255
    INT32_T contrast;     //�Աȶ�	0~512
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
    LIGHT_ALL_PARAM = 6,//������һ���������5������һ�����á�ʹ������5���������������ֱ����á�
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
    PLP_GET_POINTS = 0x01,//��ȡ���������
    PLP_GET_LINES,        //��ȡ�߷�������
    PLP_GET_RECTS,        //��ȡ���������
    PLP_ADD_POINTS,       //��ӵ��������
    PLP_ADD_LINES,        //����߷�������
    PLP_ADD_RECTS,        //������������
    PLP_UPDATE_POINTS,    //���µ��������
    PLP_UPDATE_LINES,     //�����߷�������
    PLP_UPDATE_RECTS,     //�������������
    PLP_DELETE_OBJ,       //ͨ��idɾ����������
    PLP_DELETE_ALL_OBJ,   //ɾ�����з�������
} PLP_COMMAND_TYPE;

struct PLP_OBJ_INFO {
    INT32_T id;         //�ڲ�������ֵ����������
    CHAR_T name[32];    //�ڲ��Ѷ���ֵ����������
    INT32_T type;       //�����������ͣ�1 ���㣻 2���ߣ� 3���棻
    INT32_T combinaType;//5���¶���Ϣ��Ϸ�ʽ��0������ʾ��1����ʾ����£�2����ʾ����£�3����ʾƽ���£�4��������
    BOOL_T isHide;      //���ֶ�ʧЧ
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
    ANA_GET = 0x01,    //��ȡ��������
    ANA_ADD,           //��ӷ�������
    ANA_UPDATE,        //���·�������
    ANA_DELETE_OBJ,    //ͨ��idɾ����������
    ANA_DELETE_ALL_OBJ,//ɾ�����з�������
} ANALYZE_OBJ_COMMAND_TYPE;

struct ANALYZE_OBJ_INFO {
    INT32_T id;               //�ڲ�������ֵ����������
    CHAR_T name[32];          //�ڲ��Ѷ���ֵ����������
    INT32_T type;             //�����������ͣ�1 ���㣻 2���ߣ� 3���棻 5:Բ��
    POINT_T position[2];      //�����������Ϊ1���ڶ���Ԫ�ظ�ֵΪ�ռ���   2��2������Ԫ�ر����ߵ������˵�  3��2������Ԫ�ر������ε����ϽǺ����½�
                              //5��2������Ԫ�ر���Բ���ھ��ε����ϽǺ����½�
    INT32_T temperature_label;//5���¶���Ϣ��Ϸ�ʽ��0������ʾ��1����ʾ����£�2����ʾ����£�3����ʾƽ���£�4��������
public:
    ANALYZE_OBJ_INFO() {
        memset(this, 0, sizeof(ANALYZE_OBJ_INFO));
    }
};

struct IPT_SHIELDAREA {
    int shield_area_id;//ֻ�����2����������  IDΪ0��1
    int x1;            //�����������Ͻ�x����
    int y1;            //�����������Ͻ�y����
    int x2;            //�����������½�x����
    int y2;            //�����������½�y����
public:
    IPT_SHIELDAREA() {
        memset(this, 0, sizeof(IPT_SHIELDAREA));
    }
};

struct DEVICE_TEMP_INFO {
    int temp_mode;         //0 ȫ��  1 ��������
    int analyze_object_id; //0Ϊȫ��   ����Ϊ��������id
    float max_temp;        //�����
    float min_temp;        //�����
    float avg_temp;        //ƽ����
    UINT64_T current_times;//��ǰʱ��
public:
    DEVICE_TEMP_INFO() {
        memset(this, 0, sizeof(DEVICE_TEMP_INFO));
    }
};

struct IptPictureFrame {
    char *IRImage;                 //������Ƶ��ͼ�����ļ�
    unsigned char FileVersion[2];  //�ļ��汾
    unsigned short Width;          //�¶ȵ�����
    unsigned short Height;         //�¶ȵ���߶�
    unsigned char DateTime[14];    //����ʱ��
    float *IRData;                 //�����¶�ֵ��������
    float Emiss;                   //������
    float AmbientTemperature;      //�����¶�
    unsigned char Len;             //��ͷ����
    unsigned int Distance;         //�������
    unsigned char RelativeHumidity;//���ʪ��
    float ReflectiveTemperature;   //�����¶�
    unsigned char Productor[32];   //��������
    unsigned char Type[32];        //��Ʒ�ͺ�
    unsigned char SerialNO[32];    //��Ʒ���к�
    double Longitude;              //����
    double Latitude;               //γ��
    int Altitude;                  //����
    unsigned int DescriptionLength;//��ע��Ϣ����
    unsigned char *DescriptionData;//��ע��Ϣ,�����������Ϣ
    unsigned int IRDataOffset;     //�������ݵ���ʼƫ�Ƶ�ַ
    unsigned char FileEndType[16]; //�ļ�ĩβ��ʶ
public:
    IptPictureFrame() {
        memset(this, 0, sizeof(IptPictureFrame));
    }
};
#pragma pack(1)
struct UVH_PICTURE_FRAME {
    BYTE_T fileVersion[4];//�ļ��汾
    FLOAT_T transmittance;//͸���� 0.00-100.00
    FLOAT_T emiss;        //������ 0.01-1
    FLOAT_T distance;     //����	0.4-25
    FLOAT_T ambientTemp;  //�����¶� 0.1-650
    FLOAT_T humidity;     //����ʪ��	0-100

    UINT16_T width;    //�¶ȵ�����
    UINT16_T height;   //�¶ȵ���߶�
    CHAR_T reserve[36];//����λ
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
    WHITEHOT = 0,  //����
    BLACKHOT,      //����
    IRONRED,       //����
    FULGURITE,     //����
    HOTIRON,       //����
    MEDICAL,       //ҽ��
    MEDICAL0,      //ҽ��0
    MEDICAL1,      //ҽ��1
    MEDICAL2,      //ҽ��2
    ARCTIC,        //����
    BODYDRT,       //����ɸ��
    RAINBOW1,      //�ʺ�1
    RAINBOW2,      //�ʺ�2
    RAINBOW3,      //�ʺ�3
    TINT1,         //���1
    TINT2,         //���2
    TINT3,         //���3
    ICEFIRE,       //����
    RECERSEICEFIRE,//������
    STEPS,         //�ֲ�
    SEPIA,         //���
    GREENHOT,      //����
    BLUEHOT,       //����
    WINTER,        //����
    HIGHLIGHT,     //����
    AMBER,         //����

} PALETTE_INTO;


typedef enum {
    UP_DOWN = 0,       //��ֱ����180�ȷ�ת
    LEFT_RIGHT,        //ˮƽ����180�ȷ�ת
    UP_DOWN_LEFT_RIGHT,//360�ȷ�ת
    ROTATE90,          //90�ȷ�ת
    ROTATE270,         //270�ȷ�ת
    NORMAL,            //����ת
} ROTATE_TYPE;

//ϸ����ǿ����
struct FIXED_POINT_IEE {
    BOOL_T auto_IEE = FALSE_T;        //�Ƿ���ϸ����ǿ
    INT32_T threshold = 20;           //ϸ����ֵ					1~50    ss:5
    INT32_T pos_weight_table_std = 15;//Ȩ�ر�  �����˲� 1~50
    INT32_T restrainRangeThre = 128;  //������������ֵ		0~512   ss:512
    INT32_T mixRange = 230;           //��ϵ��ⷶΧ				0~512
    INT32_T midValue = 110;           //ӳ����ֵ					0~255
    INT32_T platThresh = 15;          //ƽ̨��ֵ					1~1000
    INT32_T upDiscardRatio = 5;       //���׵�					0~100
    INT32_T downDiscardRatio = 5;     //���׵�				0~100
    INT32_T iie_detail_gain = 32;     //����ϵ��			0~128   ss:64
};

struct IEE_PARAMS {
    BOOL_T auto_iee = FALSE_T;   //�Ƿ���ϸ����ǿ
    INT32_T iie_detail_gain = 32;//����ϵ��					0~128
};

//ARM�豸״̬��
#define ARM_NO_CURVE_FILE_ERROR 0x00000001
#define ARM_Y16_ABNORMAL_ERROR 0x00000002
#define ARM_NO_MEASURE_PARAM_ERROR 0x00000004
#define ARM_FONT_MISSING_ERROR 0x00000008
//FPGA�豸״̬��
#define FPGA_INVALID_SENSOR_CONFIG_ERROR 0x00000010
#define FPGA_LOAD_FLASH_PARAM_FAILED_ERROR 0x00000020
#define FPGA_DEVICE_WORK_TEMP_OVER_RANGE_ERROR 0x00000040

#endif// !SDK_PARAMS_H