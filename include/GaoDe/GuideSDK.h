/*************************************************
Copyright (C), 2019-2029, GuideIR Tech. Co., Ltd.
File name	: GuideSDK.h
Author		: Guide Sensmart RD
Version		: 1.0
Date		: 2019/7/6
Description	:
*************************************************/
#ifndef GUIDE_SDK_H
#define GUIDE_SDK_H

#include "SDKParams.h"

GUIDESDK_STDC_START


/**
* @brief	搜索网络中的设备，返回已接入设备数量。如果已打开一个设备，则返回已存在的设备个数。
* @param    无
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note     用户根据GetDeviceNum的返回值设置devID。设备序号取值范围 >=1 且 <= GetDeviceNum()返回值。
*			在已open stream任一路视频的情况下调用GetDeviceNum不会搜索网络，将返回已存在的设备个数，
*			由于用户可能重复连接同一设备，所以可能包含重复设备，但devID不会重复。
*           在配置网络时改成dhcp后应该调用GetDeviceNum更新设备信息。
*/
GUIDESDKAPI INT32_T GetDeviceNum();

/**
* @brief	根据IP查询设备ID，返回的设备可能处于连接或者未连接状态。
* @param
*  ip       设备IP。
* @return	成功返回设备ID，大于0。失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetDeviceID(CONST CHAR_T *ip);

/**
* @brief	根据IP查询设备ID，返回一个处于未连接状态的设备ID给用户。
*           如果该设备已连接，将虚拟一个设备ID返回，保证每路连接的devID不同。支持同时多路连接同一设备。
*           如果搜索不到该设备，但检测到网络中存在，将分配一个设备ID返回。
*           如果网络中不存在该设备，返回失败。
* @param
*  ip       设备IP。
* @return	成功返回设备ID，大于0。失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetDeviceIDNotConnected(CONST CHAR_T *ip);

/**
* @brief	设置设备rtsp的用户名和密码。
* @param
*  devID	设备ID，>=1有效。
*  info		输入参数，rtsp信息。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SetDeviceURLInfo(INT32_T devID, URL_INFO info);

/**
* @brief	查询设备rtsp的用户名和密码。
* @param
*  devID	设备ID，>=1有效。
*  info		输出参数，输出rtsp信息。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetDeviceURLInfo(INT32_T devID, URL_INFO *info);

/**
* @brief	查询设备信息。
* @param
*  devID	设备ID，>=1有效。
*  devInfo	输出参数，输出设备信息。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetDeviceInfo(INT32_T devID, DEVICE_INFO *devInfo);

/**
* @brief	连接设备打开一路视频流。如果此devID设备已经连接，再连接将返回失败。
*			如果需要重复连接同一个设备，两种方式可实现：
*			1、使用OpenStreamEx。
*			2、使用GetDeviceIDNotConnected得到devID，再调用OpenStream。
* @param
*  devID	设备序号，取值范围 >=1 且 <= GetDeviceNum()返回值。
*  rgbCB	RGB数据回调函数。如果回调函数参数为空，不影响SDK打开一路视频，仅不回调。
*  y16CB	Y16数据回调函数。
*  stateCB	网络状态回调函数，通知网络断开或已连接。SDK内部支持断线重连功能。用户也可以根据网络状态实现断线重连。
*  param	回调函数参数。
*  mode	    此路视频的工作模式，支持三种。多路视频情况下每路有各自的工作模式。
*  url		视频完整url。可以传0. 为空时用默认url。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		
*/
GUIDESDKAPI INT32_T OpenStream(INT32_T devID, RGBDataCB rgbCB, Y16DataCB y16CB,
							StateCB stateCB, VOID *param, WORKING_MODE mode, CONST CHAR_T *url);
/**
* @brief	另一种方式打开设备，连接成功将分配设备ID。
* @param
*  ip   	设备IP。
*  rgbCB	RGB数据回调函数。如果回调函数参数为空，不影响SDK打开一路视频，仅不回调。
*  y16CB	Y16数据回调函数。
*  stateCB	网络状态回调函数，通知网络断开或已连接。SDK内部支持断线重连功能。用户也可以根据网络状态实现断线重连。
*  param	回调函数参数。
*  mode	    此路视频的工作模式，支持三种。多路视频情况下每路有各自的工作模式。
*  url		视频完整url。可以传0. 为空时用默认url。
* @return	成功返回分配的devID，失败返回GUIDEIR_ERR。
* @note		支持重复连接同一个设备IP，成功连接后虚拟一个设备ID返回，保证每路视频devID不同。
*/
GUIDESDKAPI INT32_T OpenStreamEx(CONST CHAR_T *ip, RGBDataCB rgbCB, Y16DataCB y16CB,
							StateCB stateCB, VOID *param, WORKING_MODE mode, CONST CHAR_T *url);

/**
* @brief	获取设备网络属性信息。
* @param
*  devID	设备ID，>=1有效。
*  info		设备网络属性参数。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetDeviceNetInfo(INT32_T devID, NETWORK_INFO *info);

/**
* @brief	关闭设备。
* @param
*  devID	设备ID，>=1有效。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T CloseStream(INT32_T devID);

/**
* @brief	点测温。
* @param
*  devID	设备ID，>=1有效。
*  point	point.x：横坐标，范围在0到imgWidth-1之间。point.y：纵坐标，范围在0到imgHeight-1之间。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note	    在实时画面中显示当前帧点温,只支持H264模式
*/
GUIDESDKAPI INT32_T ShowPointTemp(INT32_T devID, POINT_T point);

/**
* @brief		获取当前帧温度矩阵。
* @param
*  devID		设备ID，>=1有效。
*  tempMatrix	矩阵首地址。
*  matrixW		矩阵宽，等于图像宽。
*  matrixH		矩阵高，等于图像高。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			从设备端获取温度矩阵,只支持H264模式
*/
GUIDESDKAPI INT32_T GetTempMatrixEx(INT32_T devID, FLOAT_T *tempMatrix, INT32_T matrixW, INT32_T matrixH);

/**
* @brief		快门操作(Json形式)。
* @param
*  devID		设备ID，>=1有效。
*  shutterType	具体操作命令。  
*  param		由具体命令决定是否带参数。参数类型可以是int或其它，传地址。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			目前此接口不支持SET_SHUTTER_TIME，合并到AUTO_SHUTTER_ENABLE，启用快门的同时设置快门时间
*/
GUIDESDKAPI INT32_T ShutterControlEx(INT32_T devID, CMD_SHUTTER_TYPE shutterType, VOID *param);

/**
* @brief		调焦操作(Json形式)。
* @param
*  devID		设备ID，>=1有效。
*  focusType	具体操作命令。
*  param		由具体命令决定是否带参数。参数类型可以是int或其它，传地址。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T FocusControlEx(INT32_T devID, CMD_FOCUS_TYPE focusType, VOID *param);

/**
* @brief		设置回调图像的像素格式。
* @param
*  devID		设备ID，>=1有效。
*  pixelFormat	像素格式，默认RGB24。可以根据需要设置为BGR24。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SetPixelFormatEx(INT32_T devID, GD_PIXEL_FORMAT pixelFormat);

/**
* @brief		设置图像的翻转方式。
* @param
*  devID		设备ID，>=1有效。
*  type			翻转角度，支持5种。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			目前此接口仅支持Y16模式
*/
GUIDESDKAPI INT32_T SetRotateType(INT32_T devID, ROTATE_TYPE type);

/**
* @brief		设置色带(Json形式)。
* @param
*  devID		设备ID，>=1有效。
*  paletteIndex	色带号。范围：0-25。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SetPaletteEx(INT32_T devID, INT32_T paletteIndex);

/**
* @brief		设置色带。
* @param
*  devID		设备ID，>=1有效。
*  paletteIndex	色带号。范围：0-25。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			对SetPaletteEx接口封装，使参数类型规范化
*/
GUIDESDKAPI INT32_T SetPalettePlus(INT32_T devID, PALETTE_INTO paletteIndex);

/**
* @brief		获取色带号(从设备端获取)。
* @param
*  devID		设备ID，>=1有效。
*  paletteIndex	输出参数，色带号。范围：0-25。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetPaletteEx(INT32_T devID, INT32_T *paletteIndex);

/**
* @brief		设置电子变焦(Json形式)。
* @param
*  devID		设备ID，>=1有效。
*  exLevel		电子变焦倍数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SetElecZoomPlus(INT32_T devID, GD_ZOOM_SCALE  exLevel);

/**
* @brief		获取电子变焦信息(Json形式)。
* @param
*  devID		设备ID，>=1有效。
*  ezInfo		输出参数，电子变焦信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			从设备端获取
*/
GUIDESDKAPI INT32_T GetElecZoomPlus(INT32_T devID, GD_ZOOM_SCALE *exLevel);

/**
* @brief		获取设备序列号、MAC地址、ARM版本号、FPGA版本号、SDK版本号。
* @param
*  devID		设备ID，>=1有效。
*  verInfo		输出参数，版本信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetVersionInfo(INT32_T devID, VERSION_INFO *verInfo);

/**
* @brief		配置网络信息。
* @param
*  devID		设备ID，>=1有效。
*  newIP		新IP
*  netMask		子网掩码
*  newGateWay	网关
*  newDNS		DNS
*  dhcp			是否dhcp
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			在当前设备open stream的情况下调用NetworkSettings无效。
*				网络配置成功后将自动更新本地设备信息。修改成dhcp方式例外，需要使用者调用GetDeviceNum自行更新信息。
*/
GUIDESDKAPI INT32_T NetworkSettings(INT32_T devID, CONST CHAR_T *newIP, CONST CHAR_T *netMask,
	CONST CHAR_T *newGateWay, CONST CHAR_T *newDNS, BOOL_T dhcp);

/*@brief	搜索设备并返回接入设备信息和数量。
*			在有无open stream的情况下均可调用searchDevice查询已接入的设备信息。
*           与其它接口中的参数devID无关，不能根据SearchDevice的返回值设置devID。
* @param
*  devInfo	输出参数，逐一保存搜索到的多个设备信息。
*  size		输入参数，devInfo个数。
* @return	成功，返回搜索到的设备个数。失败，返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SearchDevice(DEVICE_INFO *devInfo, INT32_T size);

/*@brief	获取设备端口号。
* @param
*  devID	设备ID，>=1有效。
*  portType	端口类型，标识获取哪个端口号。
*  port		输出参数，端口信息。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetDevicePort(INT32_T devID, DEVICE_PORT_TYPE portType, UINT16_T *port);

/*@brief	设置设备端口号。
* @param
*  devID	设备ID，>=1有效。
*  portType	端口类型，标识修改哪个端口号。
*  port		端口值。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		在open设备的情况下不能修改该设备的端口信息。修改多个端口号时注意最后修改ARM端口号。
*/
GUIDESDKAPI INT32_T SetDevicePort(INT32_T devID, DEVICE_PORT_TYPE portType, UINT16_T port);

/**
* @brief		操控字符串对象。
* @param
*  devID		设备ID，>=1有效。
*  type			操作类型。
*  info			字符串对象参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			设备底层决定坐标不能为奇数，如果输入为奇数，则返回错误。
*/
GUIDESDKAPI INT32_T StringControl(INT32_T devID, CMD_STRING_TYPE type, STRING_INFO *info);

/**
* @brief		设置色带叠加(Json形式)。
* @param
*  devID		设备ID，>=1有效。
*  type			色带叠加类型。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			分别在左右两侧显示色带信息或者不显示。
*/
GUIDESDKAPI INT32_T ShowPaletteEx(INT32_T devID, SHOW_PALETTE_TYPE type);

/**
* @brief		设置调光参数(Json形式指令)。
* @param
*  devID		设备ID，>=1有效。
*  info			调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅支持H264模式。
*/
GUIDESDKAPI INT32_T SetAdjustLightParameterEx(INT32_T devID, MODULATE_PARAM_INFO info);

/**
* @brief		获取调光参数。
* @param
*  devID		设备ID，>=1有效。
*  info			输出参数，调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅支持H264模式。
*/
GUIDESDKAPI INT32_T GetAdjustLightParameterEx(INT32_T devID, MODULATE_PARAM_INFO *info);

/**
* @brief		设置细节增加参数。
* @param
*  devID		设备ID，>=1有效。
*  info			输入参数，调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅在Y16模式，自动调光时设置图像生效。
*/
GUIDESDKAPI INT32_T SetIEEParameter(INT32_T devID, IEE_PARAMS info);

/**
* @brief		获取细节增加参数。
* @param
*  devID		设备ID，>=1有效。
*  info			输出参数，调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			从设备端返回Json形式字符串。
*/
GUIDESDKAPI INT32_T GetIEEParameter(INT32_T devID, IEE_PARAMS *info);

/**
* @brief		设置细节增加参数。
* @param
*  devID		设备ID，>=1有效。
*  info			输入参数，调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			从设备端返回Json形式字符串。
*/
GUIDESDKAPI INT32_T SetDetailEnhanceParameter(INT32_T devID, FIXED_POINT_IEE info);

/**
* @brief		获取细节增加参数。
* @param
*  devID		设备ID，>=1有效。
*  info			输出参数，调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			从设备端返回Json形式字符串。
*/
GUIDESDKAPI INT32_T GetDetailEnhanceParameter(INT32_T devID, FIXED_POINT_IEE *info);

/**
* @brief		导入细节增加参数。
* @param
*  devID		设备ID，>=1有效。
*  dataPath		数据包路径。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			从本地生成IEE.data文件导入数据并设置参数。
*/
GUIDESDKAPI INT32_T ImportDetailEnhanceParameter(INT32_T devID, CONST CHAR_T * dataPath);

/**
* @brief		导出细节增加参数。
* @param
*  devID		设备ID，>=1有效。
*  dataPath		数据包路径。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			在本地生成IEE.data文件存储数据。
*/
GUIDESDKAPI INT32_T ExportDetailEnhanceParameter(INT32_T devID, CONST CHAR_T * dataPath);

/**
* @brief		设置测温参数或其它参数。
* @param
*  devID		设备ID，>=1有效。
*  info			参数信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SetCalcParameter(INT32_T devID, CALC_PARAM_TYPE paramType, CALC_PARAM_INFO info);

/**
* @brief		获取测温参数或其它参数。
* @param
*  devID		设备ID，>=1有效。
*  info			输出参数，参数信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			Get测温参数时，使用CALC_PARAM_ALL同时获取7个参数效率更高，机芯在一个响应中返回7个参数。
*/
GUIDESDKAPI INT32_T GetCalcParameter(INT32_T devID, CALC_PARAM_TYPE paramType, CALC_PARAM_INFO *info);

/**
* @brief:  SetDeviceParameter 设置测温档位、串口比特率、地址等参数。
* @access: public 
* @param:  INT32_T devID
* @param:  DEVICE_PARAM_TYPE paramType
* @param:  VOID * param
* @return: 成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note:  
**/
GUIDESDKAPI INT32_T SetDeviceParameter(INT32_T devID, DEVICE_PARAM_TYPE paramType, VOID *param);

/**
* @brief:  GetDeviceParameter	获取测温档位、串口比特率、地址等参数。
* @access: public 
* @param:  INT32_T devID
* @param:  DEVICE_PARAM_TYPE paramType
* @param:  VOID * param
* @return: 成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note:  
**/
GUIDESDKAPI INT32_T GetDeviceParameter(INT32_T devID, DEVICE_PARAM_TYPE paramType, VOID *param);

/**
* @brief		设置高低温报警信息。
* @param
*  devID		设备ID，>=1有效。
*  alarmInfo	报警信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SetAlarm(INT32_T devID, ALARM_INFO alarmInfo);

/**
* @brief		获取高低温报警信息。
* @param
*  devID		设备ID，>=1有效。
*  alarmInfo	输出参数，报警信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetAlarm(INT32_T devID, ALARM_INFO *alarmInfo);

/**
* @brief		获取设备状态。
* @param
*  devID		设备ID，>=1有效。
*  state		输出参数，设备状态码。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetDeviceState(INT32_T devID, INT32_T *state);

/**
* @brief		两点校正。
* @param
*  devID		设备ID，>=1有效。
*  point		输出参数，两个黑体的中心坐标。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T CorrectDeviceByTwoPoint(INT32_T devID, TWO_POINT_CORRECT_INFO info);

/**
* @brief		拍照。
* @param
*  devID		设备ID，>=1有效。
*  imgPath		图片保存目录。路径中统一使用/，例如/myprojects/Demo/。
*  imgType		图片类型，此接口只支持ONLY_JPG和JPG_TEMP_GW。
* @return		失败返回GUIDEIR_ERR，成功返回GUIDEIR_OK或1。
* @note			只支持H264模式。
*/
GUIDESDKAPI INT32_T TakeScreenshotEx(INT32_T devID, CONST CHAR_T *imgPath, IMG_TYPE imgType);

/**
* @brief		国网图片解析。
* @param
*  devID		设备ID，>=1有效。
*  imgPath		图片保存目录。路径中统一使用/，例如/myprojects/Demo/。
*  imgType		图片类型，此接口只支持ONLY_JPG和JPG_TEMP_GW。
* @return		失败返回GUIDEIR_ERR，成功返回GUIDEIR_OK或1。
*/
GUIDESDKAPI INT32_T GetImgTempFromGW(CONST CHAR_T * imgPath, FLOAT_T * temp);

/**
* @brief		开始录制视频。
* @param
*  devID		设备ID，>=1有效。
*  videoPath	视频录像保存目录。路径中统一使用/，例如/myprojects/Demo/。
*  mediaType	媒体文件类型。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T StartRecordVideo(INT32_T devID, CONST CHAR_T *videoPath, GD_MEDIA_TYPE mediaType);

/**
* @brief		停止录制视频。
* @param
*  devID		设备ID，>=1有效。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T StopRecordVideo(INT32_T devID);

/**
* @brief		设置视频画面温度标签（高低温数值与光标）。
* @param
*  devID		设备ID，>=1有效。
*  labelType	温度标签模式。
*  param		参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T TempLabelControl(INT32_T devID, CMD_TRMPLABEL_TYPE labelType, VOID *param);

/**
* @brief	分析对象(json形式)。
* @param
*  devID	设备ID，>=1有效。
*  cmd		操作命令
*  plpArray	输入和输出参数，PLP对象列表。
*  size		输入和输出参数，输入参数表示plpArray长度，输出参数表示获取到的PLP对象个数。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		仅支持H264模式，对于获取分析对象命令，通过给plpArray空指针，size的初始值需赋值为40，接口会返回实际的分析对象个数。
对于添加、更新分析对象命令，size为1，内部已定义点10个，ID为101~110，线10条，ID为201~210，面10个，ID为301~210,圆2个，ID为501~502。
*/
GUIDESDKAPI INT32_T PlpControlEx(INT32_T devID, ANALYZE_OBJ_COMMAND_TYPE cmd, ANALYZE_OBJ_INFO *plpArray, INT32_T *size);

/**
* @brief	设置阴影。
* @param
*  devID	设备ID，>=1有效。
*  Array	输入参数（shield_area_id只能是0,1）。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note     仅H264模式支持设置
*/
GUIDESDKAPI INT32_T SetShieldArea(INT32_T devID, IPT_SHIELDAREA Array);

/**
* @brief	删除阴影。
* @param
*  devID	设备ID，>=1有效。
*  Array	输入参数（只能是0,1）。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note     仅H264模式支持设置
*/
GUIDESDKAPI INT32_T DeleteShieldArea(INT32_T devID, INT32_T Array);

/**
* @brief	获取阴影个数。
* @param
*  devID	设备ID，>=1有效。
*  size		输出参数，表示获取到的阴影对象个数。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note     仅H264模式支持设置
*/
GUIDESDKAPI INT32_T GetShieldAreaSize(INT32_T devID, INT32_T *size);

/**
* @brief	获取阴影。
* @param
*  devID	设备ID，>=1有效。
*  Array	输出参数，返回结构体数组指针。
*  size		输出参数，表示获取到的阴影对象个数。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note     仅H264模式支持设置
*/
GUIDESDKAPI INT32_T GetShieldArea(INT32_T devID, IPT_SHIELDAREA *Array, INT32_T *size);

/**
* @brief	获取全部温度。
* @param
*  devID	设备ID，>=1有效。
*  cmd		操作命令
*  Array	输出参数，返回结构体数组指针。
*  size		输出参数，表示获取到的温度对象个数。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note     仅H264模式支持设置
*/
GUIDESDKAPI INT32_T GetGlobalTemp(INT32_T devID, DEVICE_TEMP_INFO *Array, INT32_T *size);

//以下接口对Y8设备操作，无ARM FPGA命令交互和Y16数据。
/**
* @brief:  ConnectDevice
* @access: public 
* @param:  DEVICE_INFO devInfo
* @param:  RGBDataCB rgbCB
* @param:  StateCB stateCB
* @param:  VOID * param
* @param:  CONST CHAR_T * url
* @return: GUIDESDKAPI HANDLE_T
* @note:  
**/
GUIDESDKAPI HANDLE_T ConnectDevice(DEVICE_INFO devInfo, RGBDataCB rgbCB, StateCB stateCB, VOID *param, CONST CHAR_T *url);

/**
* @brief:  DisconnectDevice
* @access: public 
* @param:  HANDLE_T device
* @return: GUIDESDKAPI INT32_T
* @note:  
**/
GUIDESDKAPI INT32_T DisconnectDevice(HANDLE_T device);

/**
* @brief:  DeviceSnapshot
* @access: public 
* @param:  HANDLE_T device
* @param:  CONST CHAR_T * imgPath
* @return: GUIDESDKAPI INT32_T
* @note:  
**/
GUIDESDKAPI INT32_T DeviceSnapshot(HANDLE_T device, CONST CHAR_T * imgPath);

/**
* @brief:  DeviceStartRecord
* @access: public 
* @param:  HANDLE_T device
* @param:  CONST CHAR_T * videoPath
* @param:  GD_MEDIA_TYPE mediaType
* @return: GUIDESDKAPI INT32_T
* @note:  
**/
GUIDESDKAPI INT32_T DeviceStartRecord(HANDLE_T device, CONST CHAR_T * videoPath, GD_MEDIA_TYPE mediaType);

/**
* @brief:  DeviceStopRecord
* @access: public 
* @param:  HANDLE_T device
* @return: GUIDESDKAPI INT32_T
* @note:  
**/
GUIDESDKAPI INT32_T DeviceStopRecord(HANDLE_T device);



//************************************之前版本的接口，不建议使用，只为兼容之前版本而存在***************************************************//

//************************************之前版本的接口，不建议使用，只为兼容之前版本而存在***************************************************//

//************************************之前版本的接口，不建议使用，只为兼容之前版本而存在***************************************************//

/**
* @brief		快门操作。
* @param
*  devID		设备ID，>=1有效。
*  shutterType	具体操作命令。
*  param		由具体命令决定是否带参数。参数类型可以是int或其它，传地址。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			透传二进制指令。
*/
GUIDESDKAPI INT32_T ShutterControl(INT32_T devID, CMD_SHUTTER_TYPE shutterType, VOID *param);

/**
* @brief		调焦操作。
* @param
*  devID		设备ID，>=1有效。
*  focusType	具体操作命令。
*  param		由具体命令决定是否带参数。参数类型可以是int或其它，传地址。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			透传二进制指令。
*/
GUIDESDKAPI INT32_T FocusControl(INT32_T devID, CMD_FOCUS_TYPE focusType, VOID *param);

/**
* @brief	获取当前帧点温。
* @param
*  devID	设备ID，>=1有效。
*  point	point.x：横坐标，范围在0到imgWidth-1之间。point.y：纵坐标，范围在0到imgHeight-1之间。
*  temp	输出参数，温度。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		由SDK进行Y16计算所得。
*/
GUIDESDKAPI INT32_T GetPointTemp(INT32_T devID, POINT_T point, FLOAT_T *temp);

/**
* @brief	获取当前帧矩形温。
* @param
*  devID	设备ID，>=1有效。
*  rect		矩形区域。
*  calcType	温度类型。
*  temp		输出参数，一种或多种温度信息。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		如果同时需要最高温、最低温、平均温，推荐使用CALC_TEMP_ALL，效率高于分别调用三次接口计算。
* @note		由SDK进行Y16计算所得。
*/
GUIDESDKAPI INT32_T GetRectTemp(INT32_T devID, RECT_T rect, CALC_TEMP_TYPE calcType, GD_TEMP_INFO *temp);

/**
* @brief		获取当前帧温度矩阵。
* @param
*  devID		设备ID，>=1有效。
*  tempMatrix	矩阵首地址。
*  matrixW		矩阵宽，大于等于图像宽。
*  matrixH		矩阵高，大于等于图像高。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		    由SDK进行Y16计算所得。
*/
GUIDESDKAPI INT32_T GetTempMatrix(INT32_T devID, FLOAT_T *tempMatrix, INT32_T matrixW, INT32_T matrixH);

/**
* @brief	获取点温。
* @param
*  devID	设备ID，>=1有效。
*  y16Value	Y16数据。
*  temp		输出参数，温度。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		由SDK进行Y16计算所得。
*/
GUIDESDKAPI INT32_T GetY16Temp(INT32_T devID, INT16_T y16Value, FLOAT_T *temp);

/**
* @brief	体表体内映射。
* @param
*  devID	设备ID，>=1有效。
*  enviTemp	环温。
*  surfaceTemp	体表温度。
*  mapTemp		输出参数，映射后的体内温度。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetMapTemperature(INT32_T devID, FLOAT_T enviTemp, FLOAT_T surfaceTemp, FLOAT_T * mapTemp);

/**
* @brief		设置色带。
* @param
*  devID		设备ID，>=1有效。
*  paletteIndex	色带号。范围：0-7。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			透传二进制指令。
*/
GUIDESDKAPI INT32_T SetPalette(INT32_T devID, INT32_T paletteIndex);

/**
* @brief		获取色带号(从参数行解析)。
* @param
*  devID		设备ID，>=1有效。
*  paletteIndex	输出参数，色带号。范围：0-25。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetPalette(INT32_T devID, INT32_T *paletteIndex);

/**
* @brief		设置帧率。
* @param
*  devID		设备ID，>=1有效。
*  frameRate	帧率。范围：1-25。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T SetFrameRate(INT32_T devID, INT32_T frameRate);

/**
* @brief		获取帧率。
* @param
*  devID		设备ID，>=1有效。
*  frameRate	输出参数，帧率。范围：1-25。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			从设备端获取。
*/
GUIDESDKAPI INT32_T GetFrameRate(INT32_T devID, INT32_T *frameRate);

/**
* @brief		设置色带叠加。分别在左右两侧显示色带信息或者不显示。
* @param
*  devID		设备ID，>=1有效。
*  type			色带叠加类型。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			透传二进制指令。
*/
GUIDESDKAPI INT32_T ShowPalette(INT32_T devID, SHOW_PALETTE_TYPE type);

/**
* @brief		设置电子变焦。
* @param
*  devID		设备ID，>=1有效。
*  ezInfo		电子变焦信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			透传二进制指令。
*/
GUIDESDKAPI INT32_T SetElecZoom(INT32_T devID, GD_EZ_INFO ezInfo);


/**
* @brief		设置电子变焦。
* @param
*  devID		设备ID，>=1有效。
*  exLevel		电子变焦倍数，设置值为1、2、4倍。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		    对SetElecZoom接口参数进行简化。
*/
GUIDESDKAPI INT32_T SetElecZoomEx(INT32_T devID, INT32_T exLevel);

/**
* @brief		获取电子变焦信息。
* @param
*  devID		设备ID，>=1有效。
*  ezInfo		输出参数，电子变焦信息。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		    从参数行获取。
*/
GUIDESDKAPI INT32_T GetElecZoom(INT32_T devID, GD_EZ_INFO *ezInfo);

/**
* @brief		设置调光参数。
* @param
*  devID		设备ID，>=1有效。
*  info			调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅支持Y16模式。
*/
GUIDESDKAPI INT32_T SetAdjustLightParameter(INT32_T devID, LIGHT_PARAM_INFO info);

/**
* @brief		获取调光参数。
* @param
*  devID		设备ID，>=1有效。
*  info			输出参数，调光参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅支持Y16模式。
*/
GUIDESDKAPI INT32_T GetAdjustLightParameter(INT32_T devID, LIGHT_PARAM_INFO *info);

/**
* @brief		设置温度分析对象。
* @param
*  devID		设备ID，>=1有效。
*  analysisType	分析类型。
*  info			参数。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			部分命令不生效，请查看注释,推荐使用TempLabelControl接口替换此接口。
*/
GUIDESDKAPI INT32_T TempAnalysisControl(INT32_T devID, CMD_ANALYSIS_TYPE analysisType, ANALYSIS_PARAM_INFO *info);

/**
* @brief		获取图像尺寸。
* @param
*  imgPath		图像文件路径。路径中统一使用/，例如/myprojects/Demo/。
*  w			输出参数，图像宽
*  h			输出参数，图像高
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetImgDemension(CONST CHAR_T *imgPath, INT32_T *w, INT32_T *h);

/**
* @brief		拍照。
* @param
*  devID		设备ID，>=1有效。
*  imgPath		图片保存目录。路径中统一使用/，例如/myprojects/Demo/。
*  imgType		图片类型。
* @return		失败返回GUIDEIR_ERR，成功返回GUIDEIR_OK或1。
*/
GUIDESDKAPI INT32_T TakeScreenshot(INT32_T devID, CONST CHAR_T *imgPath, IMG_TYPE imgType);

/**
* @brief		开始录制Y16数据。
* @param
*  devID		设备ID，>=1有效。
*  y16Path		Y16录像保存目录。路径中统一使用/，例如/myprojects/Demo/。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T StartRecordY16(INT32_T devID, CONST CHAR_T *y16Path);

/**
* @brief		停止录制Y16数据。
* @param
*  devID		设备ID，>=1有效。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T StopRecordY16(INT32_T devID);

/**
* @brief		开始录制原始y16数据，不加参数行的。
* @param
*  devID		设备ID，>=1有效。
*  y16Path		Y16录像保存目录。路径中统一使用/，例如/myprojects/Demo/。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T StartRecordRawY16(INT32_T devID, CONST CHAR_T *y16Path);

/**
* @brief		停止录制原始y16数据，不加参数行的。
* @param
*  devID		设备ID，>=1有效。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T StopRecordRawY16(INT32_T devID);

/**
* @brief		获取图像矩形温度。
* @param
*  imgPath		图像文件路径。路径中统一使用/，例如/myprojects/Demo/。
*  rect			矩形区域
*  info			输出参数，温度。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅支持JPG_WITH_TEMP = 1和 ONLY_TEMP = 2两种格式的图片
*/
GUIDESDKAPI INT32_T GetImgRectTemp(CONST CHAR_T *imgPath, RECT_T rect, GD_TEMP_INFO *info);

/**
* @brief		获得整张图片的温度矩阵（不支持国网格式的图片，需自己解析）。
* @param
*  imgPath		图像文件路径。路径中统一使用/，例如/myprojects/Demo/。
*  temp			输出参数，温度矩阵，指向温度数组首地址。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅支持JPG_WITH_TEMP = 1和 ONLY_TEMP = 2两种格式的图片
*/
GUIDESDKAPI INT32_T GetImgTemp(CONST CHAR_T *imgPath, FLOAT_T *temp);

/**
* @brief		获得图片点温。
* @param
*  imgPath		图像文件路径。路径中统一使用/，例如/myprojects/Demo/。
*  point		点坐标
*  temp			输出参数，温度。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note			仅支持JPG_WITH_TEMP = 1和 ONLY_TEMP = 2两种格式的图片
*/
GUIDESDKAPI INT32_T GetImgPointTemp(CONST CHAR_T *imgPath, POINT_T point, FLOAT_T *temp);


/**
* @brief	云台控制。
* @param
*  devID	设备ID，>=1有效。
*  cmd		PTZ命令
*  paramIn	对于set类命令，作为输入参数，类型可能是int或其它，传地址。
*  paramOut	输出参数，对于get类命令，返回应答内容。
*  timeout	超时时间，超出此时间无应答将返回失败。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T PtzControl(INT32_T devID, PTZ_COMMAND_TYPE cmd, VOID * paramIn, VOID * paramOut, INT32_T timeout);


/**
* @brief	PLP点线面分析。
* @param
*  devID	设备ID，>=1有效。
*  cmd		操作命令
*  plpArray	输入和输出参数，PLP对象列表。
*  size		输入和输出参数，输入参数表示plpArray长度，输出参数表示获取到的PLP对象个数。
* @return	成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
* @note		仅支持H264模式，对于获取分析对象命令，通过给plpArray空指针，size的初始值需赋值为40，接口会返回实际的分析对象个数。
对于添加、更新分析对象命令，size为1，内部已定义点10个，ID为101~110，线10条，ID为201~210，面10个，ID为301~210。
*/
GUIDESDKAPI INT32_T PlpControl(INT32_T devID, PLP_COMMAND_TYPE cmd, PLP_OBJ_INFO *plpArray, INT32_T *size);



//以下接口不开放。

/**
* @brief		获得帧中心点温度。   此接口废弃不用，意义不大
* @param
*  vidPath		文件路径。路径中统一使用/，例如/myprojects/Demo/。
*  frameIndex	帧序号，从0开始表示第一帧。
*  w			输出参数，帧图像宽度。
*  h			输出参数，帧图像高度。
*  temp			输出参数，温度。
* @return		成功返回GUIDEIR_OK，失败返回GUIDEIR_ERR。
*/
GUIDESDKAPI INT32_T GetFrameCentraTemp(CONST CHAR_T *vidPath, INT32_T frameIndex,
	INT32_T *w, INT32_T *h, FLOAT_T *temp);

GUIDESDK_STDC_END

#endif // !GUIDE_SDK_H

