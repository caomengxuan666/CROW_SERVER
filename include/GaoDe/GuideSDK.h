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
* @brief	���������е��豸�������ѽ����豸����������Ѵ�һ���豸���򷵻��Ѵ��ڵ��豸������
* @param    ��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note     �û�����GetDeviceNum�ķ���ֵ����devID���豸���ȡֵ��Χ >=1 �� <= GetDeviceNum()����ֵ��
*			����open stream��һ·��Ƶ������µ���GetDeviceNum�����������磬�������Ѵ��ڵ��豸������
*			�����û������ظ�����ͬһ�豸�����Կ��ܰ����ظ��豸����devID�����ظ���
*           ����������ʱ�ĳ�dhcp��Ӧ�õ���GetDeviceNum�����豸��Ϣ��
*/
GUIDESDKAPI INT32_T GetDeviceNum();

/**
* @brief	����IP��ѯ�豸ID�����ص��豸���ܴ������ӻ���δ����״̬��
* @param
*  ip       �豸IP��
* @return	�ɹ������豸ID������0��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetDeviceID(CONST CHAR_T *ip);

/**
* @brief	����IP��ѯ�豸ID������һ������δ����״̬���豸ID���û���
*           ������豸�����ӣ�������һ���豸ID���أ���֤ÿ·���ӵ�devID��ͬ��֧��ͬʱ��·����ͬһ�豸��
*           ��������������豸������⵽�����д��ڣ�������һ���豸ID���ء�
*           ��������в����ڸ��豸������ʧ�ܡ�
* @param
*  ip       �豸IP��
* @return	�ɹ������豸ID������0��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetDeviceIDNotConnected(CONST CHAR_T *ip);

/**
* @brief	�����豸rtsp���û��������롣
* @param
*  devID	�豸ID��>=1��Ч��
*  info		���������rtsp��Ϣ��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SetDeviceURLInfo(INT32_T devID, URL_INFO info);

/**
* @brief	��ѯ�豸rtsp���û��������롣
* @param
*  devID	�豸ID��>=1��Ч��
*  info		������������rtsp��Ϣ��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetDeviceURLInfo(INT32_T devID, URL_INFO *info);

/**
* @brief	��ѯ�豸��Ϣ��
* @param
*  devID	�豸ID��>=1��Ч��
*  devInfo	�������������豸��Ϣ��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetDeviceInfo(INT32_T devID, DEVICE_INFO *devInfo);

/**
* @brief	�����豸��һ·��Ƶ���������devID�豸�Ѿ����ӣ������ӽ�����ʧ�ܡ�
*			�����Ҫ�ظ�����ͬһ���豸�����ַ�ʽ��ʵ�֣�
*			1��ʹ��OpenStreamEx��
*			2��ʹ��GetDeviceIDNotConnected�õ�devID���ٵ���OpenStream��
* @param
*  devID	�豸��ţ�ȡֵ��Χ >=1 �� <= GetDeviceNum()����ֵ��
*  rgbCB	RGB���ݻص�����������ص���������Ϊ�գ���Ӱ��SDK��һ·��Ƶ�������ص���
*  y16CB	Y16���ݻص�������
*  stateCB	����״̬�ص�������֪ͨ����Ͽ��������ӡ�SDK�ڲ�֧�ֶ����������ܡ��û�Ҳ���Ը�������״̬ʵ�ֶ���������
*  param	�ص�����������
*  mode	    ��·��Ƶ�Ĺ���ģʽ��֧�����֡���·��Ƶ�����ÿ·�и��ԵĹ���ģʽ��
*  url		��Ƶ����url�����Դ�0. Ϊ��ʱ��Ĭ��url��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		
*/
GUIDESDKAPI INT32_T OpenStream(INT32_T devID, RGBDataCB rgbCB, Y16DataCB y16CB,
							StateCB stateCB, VOID *param, WORKING_MODE mode, CONST CHAR_T *url);
/**
* @brief	��һ�ַ�ʽ���豸�����ӳɹ��������豸ID��
* @param
*  ip   	�豸IP��
*  rgbCB	RGB���ݻص�����������ص���������Ϊ�գ���Ӱ��SDK��һ·��Ƶ�������ص���
*  y16CB	Y16���ݻص�������
*  stateCB	����״̬�ص�������֪ͨ����Ͽ��������ӡ�SDK�ڲ�֧�ֶ����������ܡ��û�Ҳ���Ը�������״̬ʵ�ֶ���������
*  param	�ص�����������
*  mode	    ��·��Ƶ�Ĺ���ģʽ��֧�����֡���·��Ƶ�����ÿ·�и��ԵĹ���ģʽ��
*  url		��Ƶ����url�����Դ�0. Ϊ��ʱ��Ĭ��url��
* @return	�ɹ����ط����devID��ʧ�ܷ���GUIDEIR_ERR��
* @note		֧���ظ�����ͬһ���豸IP���ɹ����Ӻ�����һ���豸ID���أ���֤ÿ·��ƵdevID��ͬ��
*/
GUIDESDKAPI INT32_T OpenStreamEx(CONST CHAR_T *ip, RGBDataCB rgbCB, Y16DataCB y16CB,
							StateCB stateCB, VOID *param, WORKING_MODE mode, CONST CHAR_T *url);

/**
* @brief	��ȡ�豸����������Ϣ��
* @param
*  devID	�豸ID��>=1��Ч��
*  info		�豸�������Բ�����
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetDeviceNetInfo(INT32_T devID, NETWORK_INFO *info);

/**
* @brief	�ر��豸��
* @param
*  devID	�豸ID��>=1��Ч��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T CloseStream(INT32_T devID);

/**
* @brief	����¡�
* @param
*  devID	�豸ID��>=1��Ч��
*  point	point.x�������꣬��Χ��0��imgWidth-1֮�䡣point.y�������꣬��Χ��0��imgHeight-1֮�䡣
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note	    ��ʵʱ��������ʾ��ǰ֡����,ֻ֧��H264ģʽ
*/
GUIDESDKAPI INT32_T ShowPointTemp(INT32_T devID, POINT_T point);

/**
* @brief		��ȡ��ǰ֡�¶Ⱦ���
* @param
*  devID		�豸ID��>=1��Ч��
*  tempMatrix	�����׵�ַ��
*  matrixW		���������ͼ���
*  matrixH		����ߣ�����ͼ��ߡ�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			���豸�˻�ȡ�¶Ⱦ���,ֻ֧��H264ģʽ
*/
GUIDESDKAPI INT32_T GetTempMatrixEx(INT32_T devID, FLOAT_T *tempMatrix, INT32_T matrixW, INT32_T matrixH);

/**
* @brief		���Ų���(Json��ʽ)��
* @param
*  devID		�豸ID��>=1��Ч��
*  shutterType	����������  
*  param		�ɾ�����������Ƿ���������������Ϳ�����int������������ַ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			Ŀǰ�˽ӿڲ�֧��SET_SHUTTER_TIME���ϲ���AUTO_SHUTTER_ENABLE�����ÿ��ŵ�ͬʱ���ÿ���ʱ��
*/
GUIDESDKAPI INT32_T ShutterControlEx(INT32_T devID, CMD_SHUTTER_TYPE shutterType, VOID *param);

/**
* @brief		��������(Json��ʽ)��
* @param
*  devID		�豸ID��>=1��Ч��
*  focusType	����������
*  param		�ɾ�����������Ƿ���������������Ϳ�����int������������ַ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T FocusControlEx(INT32_T devID, CMD_FOCUS_TYPE focusType, VOID *param);

/**
* @brief		���ûص�ͼ������ظ�ʽ��
* @param
*  devID		�豸ID��>=1��Ч��
*  pixelFormat	���ظ�ʽ��Ĭ��RGB24�����Ը�����Ҫ����ΪBGR24��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SetPixelFormatEx(INT32_T devID, GD_PIXEL_FORMAT pixelFormat);

/**
* @brief		����ͼ��ķ�ת��ʽ��
* @param
*  devID		�豸ID��>=1��Ч��
*  type			��ת�Ƕȣ�֧��5�֡�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			Ŀǰ�˽ӿڽ�֧��Y16ģʽ
*/
GUIDESDKAPI INT32_T SetRotateType(INT32_T devID, ROTATE_TYPE type);

/**
* @brief		����ɫ��(Json��ʽ)��
* @param
*  devID		�豸ID��>=1��Ч��
*  paletteIndex	ɫ���š���Χ��0-25��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SetPaletteEx(INT32_T devID, INT32_T paletteIndex);

/**
* @brief		����ɫ����
* @param
*  devID		�豸ID��>=1��Ч��
*  paletteIndex	ɫ���š���Χ��0-25��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��SetPaletteEx�ӿڷ�װ��ʹ�������͹淶��
*/
GUIDESDKAPI INT32_T SetPalettePlus(INT32_T devID, PALETTE_INTO paletteIndex);

/**
* @brief		��ȡɫ����(���豸�˻�ȡ)��
* @param
*  devID		�豸ID��>=1��Ч��
*  paletteIndex	���������ɫ���š���Χ��0-25��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetPaletteEx(INT32_T devID, INT32_T *paletteIndex);

/**
* @brief		���õ��ӱ佹(Json��ʽ)��
* @param
*  devID		�豸ID��>=1��Ч��
*  exLevel		���ӱ佹������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SetElecZoomPlus(INT32_T devID, GD_ZOOM_SCALE  exLevel);

/**
* @brief		��ȡ���ӱ佹��Ϣ(Json��ʽ)��
* @param
*  devID		�豸ID��>=1��Ч��
*  ezInfo		������������ӱ佹��Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			���豸�˻�ȡ
*/
GUIDESDKAPI INT32_T GetElecZoomPlus(INT32_T devID, GD_ZOOM_SCALE *exLevel);

/**
* @brief		��ȡ�豸���кš�MAC��ַ��ARM�汾�š�FPGA�汾�š�SDK�汾�š�
* @param
*  devID		�豸ID��>=1��Ч��
*  verInfo		����������汾��Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetVersionInfo(INT32_T devID, VERSION_INFO *verInfo);

/**
* @brief		����������Ϣ��
* @param
*  devID		�豸ID��>=1��Ч��
*  newIP		��IP
*  netMask		��������
*  newGateWay	����
*  newDNS		DNS
*  dhcp			�Ƿ�dhcp
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			�ڵ�ǰ�豸open stream������µ���NetworkSettings��Ч��
*				�������óɹ����Զ����±����豸��Ϣ���޸ĳ�dhcp��ʽ���⣬��Ҫʹ���ߵ���GetDeviceNum���и�����Ϣ��
*/
GUIDESDKAPI INT32_T NetworkSettings(INT32_T devID, CONST CHAR_T *newIP, CONST CHAR_T *netMask,
	CONST CHAR_T *newGateWay, CONST CHAR_T *newDNS, BOOL_T dhcp);

/*@brief	�����豸�����ؽ����豸��Ϣ��������
*			������open stream������¾��ɵ���searchDevice��ѯ�ѽ�����豸��Ϣ��
*           �������ӿ��еĲ���devID�޹أ����ܸ���SearchDevice�ķ���ֵ����devID��
* @param
*  devInfo	�����������һ�����������Ķ���豸��Ϣ��
*  size		���������devInfo������
* @return	�ɹ����������������豸������ʧ�ܣ�����GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SearchDevice(DEVICE_INFO *devInfo, INT32_T size);

/*@brief	��ȡ�豸�˿ںš�
* @param
*  devID	�豸ID��>=1��Ч��
*  portType	�˿����ͣ���ʶ��ȡ�ĸ��˿ںš�
*  port		����������˿���Ϣ��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetDevicePort(INT32_T devID, DEVICE_PORT_TYPE portType, UINT16_T *port);

/*@brief	�����豸�˿ںš�
* @param
*  devID	�豸ID��>=1��Ч��
*  portType	�˿����ͣ���ʶ�޸��ĸ��˿ںš�
*  port		�˿�ֵ��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		��open�豸������²����޸ĸ��豸�Ķ˿���Ϣ���޸Ķ���˿ں�ʱע������޸�ARM�˿ںš�
*/
GUIDESDKAPI INT32_T SetDevicePort(INT32_T devID, DEVICE_PORT_TYPE portType, UINT16_T port);

/**
* @brief		�ٿ��ַ�������
* @param
*  devID		�豸ID��>=1��Ч��
*  type			�������͡�
*  info			�ַ������������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			�豸�ײ�������겻��Ϊ�������������Ϊ�������򷵻ش���
*/
GUIDESDKAPI INT32_T StringControl(INT32_T devID, CMD_STRING_TYPE type, STRING_INFO *info);

/**
* @brief		����ɫ������(Json��ʽ)��
* @param
*  devID		�豸ID��>=1��Ч��
*  type			ɫ���������͡�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			�ֱ�������������ʾɫ����Ϣ���߲���ʾ��
*/
GUIDESDKAPI INT32_T ShowPaletteEx(INT32_T devID, SHOW_PALETTE_TYPE type);

/**
* @brief		���õ������(Json��ʽָ��)��
* @param
*  devID		�豸ID��>=1��Ч��
*  info			���������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��֧��H264ģʽ��
*/
GUIDESDKAPI INT32_T SetAdjustLightParameterEx(INT32_T devID, MODULATE_PARAM_INFO info);

/**
* @brief		��ȡ���������
* @param
*  devID		�豸ID��>=1��Ч��
*  info			������������������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��֧��H264ģʽ��
*/
GUIDESDKAPI INT32_T GetAdjustLightParameterEx(INT32_T devID, MODULATE_PARAM_INFO *info);

/**
* @brief		����ϸ�����Ӳ�����
* @param
*  devID		�豸ID��>=1��Ч��
*  info			������������������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			����Y16ģʽ���Զ�����ʱ����ͼ����Ч��
*/
GUIDESDKAPI INT32_T SetIEEParameter(INT32_T devID, IEE_PARAMS info);

/**
* @brief		��ȡϸ�����Ӳ�����
* @param
*  devID		�豸ID��>=1��Ч��
*  info			������������������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			���豸�˷���Json��ʽ�ַ�����
*/
GUIDESDKAPI INT32_T GetIEEParameter(INT32_T devID, IEE_PARAMS *info);

/**
* @brief		����ϸ�����Ӳ�����
* @param
*  devID		�豸ID��>=1��Ч��
*  info			������������������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			���豸�˷���Json��ʽ�ַ�����
*/
GUIDESDKAPI INT32_T SetDetailEnhanceParameter(INT32_T devID, FIXED_POINT_IEE info);

/**
* @brief		��ȡϸ�����Ӳ�����
* @param
*  devID		�豸ID��>=1��Ч��
*  info			������������������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			���豸�˷���Json��ʽ�ַ�����
*/
GUIDESDKAPI INT32_T GetDetailEnhanceParameter(INT32_T devID, FIXED_POINT_IEE *info);

/**
* @brief		����ϸ�����Ӳ�����
* @param
*  devID		�豸ID��>=1��Ч��
*  dataPath		���ݰ�·����
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			�ӱ�������IEE.data�ļ��������ݲ����ò�����
*/
GUIDESDKAPI INT32_T ImportDetailEnhanceParameter(INT32_T devID, CONST CHAR_T * dataPath);

/**
* @brief		����ϸ�����Ӳ�����
* @param
*  devID		�豸ID��>=1��Ч��
*  dataPath		���ݰ�·����
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			�ڱ�������IEE.data�ļ��洢���ݡ�
*/
GUIDESDKAPI INT32_T ExportDetailEnhanceParameter(INT32_T devID, CONST CHAR_T * dataPath);

/**
* @brief		���ò��²���������������
* @param
*  devID		�豸ID��>=1��Ч��
*  info			������Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SetCalcParameter(INT32_T devID, CALC_PARAM_TYPE paramType, CALC_PARAM_INFO info);

/**
* @brief		��ȡ���²���������������
* @param
*  devID		�豸ID��>=1��Ч��
*  info			���������������Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			Get���²���ʱ��ʹ��CALC_PARAM_ALLͬʱ��ȡ7������Ч�ʸ��ߣ���о��һ����Ӧ�з���7��������
*/
GUIDESDKAPI INT32_T GetCalcParameter(INT32_T devID, CALC_PARAM_TYPE paramType, CALC_PARAM_INFO *info);

/**
* @brief:  SetDeviceParameter ���ò��µ�λ�����ڱ����ʡ���ַ�Ȳ�����
* @access: public 
* @param:  INT32_T devID
* @param:  DEVICE_PARAM_TYPE paramType
* @param:  VOID * param
* @return: �ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note:  
**/
GUIDESDKAPI INT32_T SetDeviceParameter(INT32_T devID, DEVICE_PARAM_TYPE paramType, VOID *param);

/**
* @brief:  GetDeviceParameter	��ȡ���µ�λ�����ڱ����ʡ���ַ�Ȳ�����
* @access: public 
* @param:  INT32_T devID
* @param:  DEVICE_PARAM_TYPE paramType
* @param:  VOID * param
* @return: �ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note:  
**/
GUIDESDKAPI INT32_T GetDeviceParameter(INT32_T devID, DEVICE_PARAM_TYPE paramType, VOID *param);

/**
* @brief		���øߵ��±�����Ϣ��
* @param
*  devID		�豸ID��>=1��Ч��
*  alarmInfo	������Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SetAlarm(INT32_T devID, ALARM_INFO alarmInfo);

/**
* @brief		��ȡ�ߵ��±�����Ϣ��
* @param
*  devID		�豸ID��>=1��Ч��
*  alarmInfo	���������������Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetAlarm(INT32_T devID, ALARM_INFO *alarmInfo);

/**
* @brief		��ȡ�豸״̬��
* @param
*  devID		�豸ID��>=1��Ч��
*  state		����������豸״̬�롣
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetDeviceState(INT32_T devID, INT32_T *state);

/**
* @brief		����У����
* @param
*  devID		�豸ID��>=1��Ч��
*  point		�������������������������ꡣ
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T CorrectDeviceByTwoPoint(INT32_T devID, TWO_POINT_CORRECT_INFO info);

/**
* @brief		���ա�
* @param
*  devID		�豸ID��>=1��Ч��
*  imgPath		ͼƬ����Ŀ¼��·����ͳһʹ��/������/myprojects/Demo/��
*  imgType		ͼƬ���ͣ��˽ӿ�ֻ֧��ONLY_JPG��JPG_TEMP_GW��
* @return		ʧ�ܷ���GUIDEIR_ERR���ɹ�����GUIDEIR_OK��1��
* @note			ֻ֧��H264ģʽ��
*/
GUIDESDKAPI INT32_T TakeScreenshotEx(INT32_T devID, CONST CHAR_T *imgPath, IMG_TYPE imgType);

/**
* @brief		����ͼƬ������
* @param
*  devID		�豸ID��>=1��Ч��
*  imgPath		ͼƬ����Ŀ¼��·����ͳһʹ��/������/myprojects/Demo/��
*  imgType		ͼƬ���ͣ��˽ӿ�ֻ֧��ONLY_JPG��JPG_TEMP_GW��
* @return		ʧ�ܷ���GUIDEIR_ERR���ɹ�����GUIDEIR_OK��1��
*/
GUIDESDKAPI INT32_T GetImgTempFromGW(CONST CHAR_T * imgPath, FLOAT_T * temp);

/**
* @brief		��ʼ¼����Ƶ��
* @param
*  devID		�豸ID��>=1��Ч��
*  videoPath	��Ƶ¼�񱣴�Ŀ¼��·����ͳһʹ��/������/myprojects/Demo/��
*  mediaType	ý���ļ����͡�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T StartRecordVideo(INT32_T devID, CONST CHAR_T *videoPath, GD_MEDIA_TYPE mediaType);

/**
* @brief		ֹͣ¼����Ƶ��
* @param
*  devID		�豸ID��>=1��Ч��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T StopRecordVideo(INT32_T devID);

/**
* @brief		������Ƶ�����¶ȱ�ǩ���ߵ�����ֵ���꣩��
* @param
*  devID		�豸ID��>=1��Ч��
*  labelType	�¶ȱ�ǩģʽ��
*  param		������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T TempLabelControl(INT32_T devID, CMD_TRMPLABEL_TYPE labelType, VOID *param);

/**
* @brief	��������(json��ʽ)��
* @param
*  devID	�豸ID��>=1��Ч��
*  cmd		��������
*  plpArray	��������������PLP�����б�
*  size		�����������������������ʾplpArray���ȣ����������ʾ��ȡ����PLP���������
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		��֧��H264ģʽ�����ڻ�ȡ�����������ͨ����plpArray��ָ�룬size�ĳ�ʼֵ�踳ֵΪ40���ӿڻ᷵��ʵ�ʵķ������������
������ӡ����·����������sizeΪ1���ڲ��Ѷ����10����IDΪ101~110����10����IDΪ201~210����10����IDΪ301~210,Բ2����IDΪ501~502��
*/
GUIDESDKAPI INT32_T PlpControlEx(INT32_T devID, ANALYZE_OBJ_COMMAND_TYPE cmd, ANALYZE_OBJ_INFO *plpArray, INT32_T *size);

/**
* @brief	������Ӱ��
* @param
*  devID	�豸ID��>=1��Ч��
*  Array	���������shield_area_idֻ����0,1����
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note     ��H264ģʽ֧������
*/
GUIDESDKAPI INT32_T SetShieldArea(INT32_T devID, IPT_SHIELDAREA Array);

/**
* @brief	ɾ����Ӱ��
* @param
*  devID	�豸ID��>=1��Ч��
*  Array	���������ֻ����0,1����
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note     ��H264ģʽ֧������
*/
GUIDESDKAPI INT32_T DeleteShieldArea(INT32_T devID, INT32_T Array);

/**
* @brief	��ȡ��Ӱ������
* @param
*  devID	�豸ID��>=1��Ч��
*  size		�����������ʾ��ȡ������Ӱ���������
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note     ��H264ģʽ֧������
*/
GUIDESDKAPI INT32_T GetShieldAreaSize(INT32_T devID, INT32_T *size);

/**
* @brief	��ȡ��Ӱ��
* @param
*  devID	�豸ID��>=1��Ч��
*  Array	������������ؽṹ������ָ�롣
*  size		�����������ʾ��ȡ������Ӱ���������
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note     ��H264ģʽ֧������
*/
GUIDESDKAPI INT32_T GetShieldArea(INT32_T devID, IPT_SHIELDAREA *Array, INT32_T *size);

/**
* @brief	��ȡȫ���¶ȡ�
* @param
*  devID	�豸ID��>=1��Ч��
*  cmd		��������
*  Array	������������ؽṹ������ָ�롣
*  size		�����������ʾ��ȡ�����¶ȶ��������
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note     ��H264ģʽ֧������
*/
GUIDESDKAPI INT32_T GetGlobalTemp(INT32_T devID, DEVICE_TEMP_INFO *Array, INT32_T *size);

//���½ӿڶ�Y8�豸��������ARM FPGA�������Y16���ݡ�
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



//************************************֮ǰ�汾�Ľӿڣ�������ʹ�ã�ֻΪ����֮ǰ�汾������***************************************************//

//************************************֮ǰ�汾�Ľӿڣ�������ʹ�ã�ֻΪ����֮ǰ�汾������***************************************************//

//************************************֮ǰ�汾�Ľӿڣ�������ʹ�ã�ֻΪ����֮ǰ�汾������***************************************************//

/**
* @brief		���Ų�����
* @param
*  devID		�豸ID��>=1��Ч��
*  shutterType	����������
*  param		�ɾ�����������Ƿ���������������Ϳ�����int������������ַ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			͸��������ָ�
*/
GUIDESDKAPI INT32_T ShutterControl(INT32_T devID, CMD_SHUTTER_TYPE shutterType, VOID *param);

/**
* @brief		����������
* @param
*  devID		�豸ID��>=1��Ч��
*  focusType	����������
*  param		�ɾ�����������Ƿ���������������Ϳ�����int������������ַ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			͸��������ָ�
*/
GUIDESDKAPI INT32_T FocusControl(INT32_T devID, CMD_FOCUS_TYPE focusType, VOID *param);

/**
* @brief	��ȡ��ǰ֡���¡�
* @param
*  devID	�豸ID��>=1��Ч��
*  point	point.x�������꣬��Χ��0��imgWidth-1֮�䡣point.y�������꣬��Χ��0��imgHeight-1֮�䡣
*  temp	����������¶ȡ�
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		��SDK����Y16�������á�
*/
GUIDESDKAPI INT32_T GetPointTemp(INT32_T devID, POINT_T point, FLOAT_T *temp);

/**
* @brief	��ȡ��ǰ֡�����¡�
* @param
*  devID	�豸ID��>=1��Ч��
*  rect		��������
*  calcType	�¶����͡�
*  temp		���������һ�ֻ�����¶���Ϣ��
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		���ͬʱ��Ҫ����¡�����¡�ƽ���£��Ƽ�ʹ��CALC_TEMP_ALL��Ч�ʸ��ڷֱ�������νӿڼ��㡣
* @note		��SDK����Y16�������á�
*/
GUIDESDKAPI INT32_T GetRectTemp(INT32_T devID, RECT_T rect, CALC_TEMP_TYPE calcType, GD_TEMP_INFO *temp);

/**
* @brief		��ȡ��ǰ֡�¶Ⱦ���
* @param
*  devID		�豸ID��>=1��Ч��
*  tempMatrix	�����׵�ַ��
*  matrixW		��������ڵ���ͼ���
*  matrixH		����ߣ����ڵ���ͼ��ߡ�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		    ��SDK����Y16�������á�
*/
GUIDESDKAPI INT32_T GetTempMatrix(INT32_T devID, FLOAT_T *tempMatrix, INT32_T matrixW, INT32_T matrixH);

/**
* @brief	��ȡ���¡�
* @param
*  devID	�豸ID��>=1��Ч��
*  y16Value	Y16���ݡ�
*  temp		����������¶ȡ�
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		��SDK����Y16�������á�
*/
GUIDESDKAPI INT32_T GetY16Temp(INT32_T devID, INT16_T y16Value, FLOAT_T *temp);

/**
* @brief	�������ӳ�䡣
* @param
*  devID	�豸ID��>=1��Ч��
*  enviTemp	���¡�
*  surfaceTemp	����¶ȡ�
*  mapTemp		���������ӳ���������¶ȡ�
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetMapTemperature(INT32_T devID, FLOAT_T enviTemp, FLOAT_T surfaceTemp, FLOAT_T * mapTemp);

/**
* @brief		����ɫ����
* @param
*  devID		�豸ID��>=1��Ч��
*  paletteIndex	ɫ���š���Χ��0-7��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			͸��������ָ�
*/
GUIDESDKAPI INT32_T SetPalette(INT32_T devID, INT32_T paletteIndex);

/**
* @brief		��ȡɫ����(�Ӳ����н���)��
* @param
*  devID		�豸ID��>=1��Ч��
*  paletteIndex	���������ɫ���š���Χ��0-25��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetPalette(INT32_T devID, INT32_T *paletteIndex);

/**
* @brief		����֡�ʡ�
* @param
*  devID		�豸ID��>=1��Ч��
*  frameRate	֡�ʡ���Χ��1-25��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T SetFrameRate(INT32_T devID, INT32_T frameRate);

/**
* @brief		��ȡ֡�ʡ�
* @param
*  devID		�豸ID��>=1��Ч��
*  frameRate	���������֡�ʡ���Χ��1-25��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			���豸�˻�ȡ��
*/
GUIDESDKAPI INT32_T GetFrameRate(INT32_T devID, INT32_T *frameRate);

/**
* @brief		����ɫ�����ӡ��ֱ�������������ʾɫ����Ϣ���߲���ʾ��
* @param
*  devID		�豸ID��>=1��Ч��
*  type			ɫ���������͡�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			͸��������ָ�
*/
GUIDESDKAPI INT32_T ShowPalette(INT32_T devID, SHOW_PALETTE_TYPE type);

/**
* @brief		���õ��ӱ佹��
* @param
*  devID		�豸ID��>=1��Ч��
*  ezInfo		���ӱ佹��Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			͸��������ָ�
*/
GUIDESDKAPI INT32_T SetElecZoom(INT32_T devID, GD_EZ_INFO ezInfo);


/**
* @brief		���õ��ӱ佹��
* @param
*  devID		�豸ID��>=1��Ч��
*  exLevel		���ӱ佹����������ֵΪ1��2��4����
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		    ��SetElecZoom�ӿڲ������м򻯡�
*/
GUIDESDKAPI INT32_T SetElecZoomEx(INT32_T devID, INT32_T exLevel);

/**
* @brief		��ȡ���ӱ佹��Ϣ��
* @param
*  devID		�豸ID��>=1��Ч��
*  ezInfo		������������ӱ佹��Ϣ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		    �Ӳ����л�ȡ��
*/
GUIDESDKAPI INT32_T GetElecZoom(INT32_T devID, GD_EZ_INFO *ezInfo);

/**
* @brief		���õ��������
* @param
*  devID		�豸ID��>=1��Ч��
*  info			���������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��֧��Y16ģʽ��
*/
GUIDESDKAPI INT32_T SetAdjustLightParameter(INT32_T devID, LIGHT_PARAM_INFO info);

/**
* @brief		��ȡ���������
* @param
*  devID		�豸ID��>=1��Ч��
*  info			������������������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��֧��Y16ģʽ��
*/
GUIDESDKAPI INT32_T GetAdjustLightParameter(INT32_T devID, LIGHT_PARAM_INFO *info);

/**
* @brief		�����¶ȷ�������
* @param
*  devID		�豸ID��>=1��Ч��
*  analysisType	�������͡�
*  info			������
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			���������Ч����鿴ע��,�Ƽ�ʹ��TempLabelControl�ӿ��滻�˽ӿڡ�
*/
GUIDESDKAPI INT32_T TempAnalysisControl(INT32_T devID, CMD_ANALYSIS_TYPE analysisType, ANALYSIS_PARAM_INFO *info);

/**
* @brief		��ȡͼ��ߴ硣
* @param
*  imgPath		ͼ���ļ�·����·����ͳһʹ��/������/myprojects/Demo/��
*  w			���������ͼ���
*  h			���������ͼ���
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetImgDemension(CONST CHAR_T *imgPath, INT32_T *w, INT32_T *h);

/**
* @brief		���ա�
* @param
*  devID		�豸ID��>=1��Ч��
*  imgPath		ͼƬ����Ŀ¼��·����ͳһʹ��/������/myprojects/Demo/��
*  imgType		ͼƬ���͡�
* @return		ʧ�ܷ���GUIDEIR_ERR���ɹ�����GUIDEIR_OK��1��
*/
GUIDESDKAPI INT32_T TakeScreenshot(INT32_T devID, CONST CHAR_T *imgPath, IMG_TYPE imgType);

/**
* @brief		��ʼ¼��Y16���ݡ�
* @param
*  devID		�豸ID��>=1��Ч��
*  y16Path		Y16¼�񱣴�Ŀ¼��·����ͳһʹ��/������/myprojects/Demo/��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T StartRecordY16(INT32_T devID, CONST CHAR_T *y16Path);

/**
* @brief		ֹͣ¼��Y16���ݡ�
* @param
*  devID		�豸ID��>=1��Ч��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T StopRecordY16(INT32_T devID);

/**
* @brief		��ʼ¼��ԭʼy16���ݣ����Ӳ����еġ�
* @param
*  devID		�豸ID��>=1��Ч��
*  y16Path		Y16¼�񱣴�Ŀ¼��·����ͳһʹ��/������/myprojects/Demo/��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T StartRecordRawY16(INT32_T devID, CONST CHAR_T *y16Path);

/**
* @brief		ֹͣ¼��ԭʼy16���ݣ����Ӳ����еġ�
* @param
*  devID		�豸ID��>=1��Ч��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T StopRecordRawY16(INT32_T devID);

/**
* @brief		��ȡͼ������¶ȡ�
* @param
*  imgPath		ͼ���ļ�·����·����ͳһʹ��/������/myprojects/Demo/��
*  rect			��������
*  info			����������¶ȡ�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��֧��JPG_WITH_TEMP = 1�� ONLY_TEMP = 2���ָ�ʽ��ͼƬ
*/
GUIDESDKAPI INT32_T GetImgRectTemp(CONST CHAR_T *imgPath, RECT_T rect, GD_TEMP_INFO *info);

/**
* @brief		�������ͼƬ���¶Ⱦ��󣨲�֧�ֹ�����ʽ��ͼƬ�����Լ���������
* @param
*  imgPath		ͼ���ļ�·����·����ͳһʹ��/������/myprojects/Demo/��
*  temp			����������¶Ⱦ���ָ���¶������׵�ַ��
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��֧��JPG_WITH_TEMP = 1�� ONLY_TEMP = 2���ָ�ʽ��ͼƬ
*/
GUIDESDKAPI INT32_T GetImgTemp(CONST CHAR_T *imgPath, FLOAT_T *temp);

/**
* @brief		���ͼƬ���¡�
* @param
*  imgPath		ͼ���ļ�·����·����ͳһʹ��/������/myprojects/Demo/��
*  point		������
*  temp			����������¶ȡ�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note			��֧��JPG_WITH_TEMP = 1�� ONLY_TEMP = 2���ָ�ʽ��ͼƬ
*/
GUIDESDKAPI INT32_T GetImgPointTemp(CONST CHAR_T *imgPath, POINT_T point, FLOAT_T *temp);


/**
* @brief	��̨���ơ�
* @param
*  devID	�豸ID��>=1��Ч��
*  cmd		PTZ����
*  paramIn	����set�������Ϊ������������Ϳ�����int������������ַ��
*  paramOut	�������������get���������Ӧ�����ݡ�
*  timeout	��ʱʱ�䣬������ʱ����Ӧ�𽫷���ʧ�ܡ�
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T PtzControl(INT32_T devID, PTZ_COMMAND_TYPE cmd, VOID * paramIn, VOID * paramOut, INT32_T timeout);


/**
* @brief	PLP�����������
* @param
*  devID	�豸ID��>=1��Ч��
*  cmd		��������
*  plpArray	��������������PLP�����б�
*  size		�����������������������ʾplpArray���ȣ����������ʾ��ȡ����PLP���������
* @return	�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
* @note		��֧��H264ģʽ�����ڻ�ȡ�����������ͨ����plpArray��ָ�룬size�ĳ�ʼֵ�踳ֵΪ40���ӿڻ᷵��ʵ�ʵķ������������
������ӡ����·����������sizeΪ1���ڲ��Ѷ����10����IDΪ101~110����10����IDΪ201~210����10����IDΪ301~210��
*/
GUIDESDKAPI INT32_T PlpControl(INT32_T devID, PLP_COMMAND_TYPE cmd, PLP_OBJ_INFO *plpArray, INT32_T *size);



//���½ӿڲ����š�

/**
* @brief		���֡���ĵ��¶ȡ�   �˽ӿڷ������ã����岻��
* @param
*  vidPath		�ļ�·����·����ͳһʹ��/������/myprojects/Demo/��
*  frameIndex	֡��ţ���0��ʼ��ʾ��һ֡��
*  w			���������֡ͼ���ȡ�
*  h			���������֡ͼ��߶ȡ�
*  temp			����������¶ȡ�
* @return		�ɹ�����GUIDEIR_OK��ʧ�ܷ���GUIDEIR_ERR��
*/
GUIDESDKAPI INT32_T GetFrameCentraTemp(CONST CHAR_T *vidPath, INT32_T frameIndex,
	INT32_T *w, INT32_T *h, FLOAT_T *temp);

GUIDESDK_STDC_END

#endif // !GUIDE_SDK_H

