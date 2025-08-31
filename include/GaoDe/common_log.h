/*************************************************
Copyright (C), 2019-2029, GuideIR Tech. Co., Ltd.
File name	: common_log.h
Author		: Guide Sensmart RD
Version		: 1.0
Date		: 2019/7/6
Description	:
*************************************************/

#ifndef COMMON_LOG_H
#define COMMON_LOG_H

#include "common_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LOG_DEBUG = 1,// ��� Debug ������Ϣ
    LOG_INFO = 2, // ��� Info ������Ϣ
    LOG_WARN = 3, // ��� Warning ������Ϣ
    LOG_ERROR = 4,// ��� Error ������Ϣ
    LOG_FATAL = 5,// ��� Fatal Error ������Ϣ
} LOG_LEVEL_T;

typedef enum {
    MODULE_LOG = 0,    // ��־ģ��
    MODULE_VIDEO = 1,  // ��Ƶ����ģ��
    MODULE_PORTING = 2,// ƽ̨��ֲģ��
    MODULE_RECORDE = 3,// ¼������ģ��
    MODULE_Y16 = 4,    // Y16����
    MODULE_IMAGE = 5,  // ͼ����
    MODULE_TEMPE = 6,  // ����ģ��
    MODULE_STATE = 7,  // ��о״̬����
    MODULE_DEVICE = 8, // �豸����ģ��
    MODULE_CONTROL = 9,// ���ȣ����ͼ���
    MODULE_UTIL = 10,  // ���߼�
} MODULE_T;

typedef enum {
    DBG_OUTPUT_FILE = 1,    //��־������ļ���Ĭ�������ʽ
    DBG_OUTPUT_CONSOLE = 2, //���������̨
    DBG_OUTPUT_ETHERNET = 3,//ʹ�����������Ŀǰ��֧��
} DBG_MODE_T;

/**
* @brief ��־ģ���ʼ�������ظ���ε��á�
* @param ��
* @return
* GUIDEIR_OK : ��ʼ���ɹ�
* GUIDEIR_ERR : ��ʼ��ʧ��
*/
INT32_T log_init();

/**
* @brief ��־ģ��ȥ��ʼ��
* @param ��
* @return
* GUIDEIR_OK : ȥ��ʼ���ɹ�
* GUIDEIR_ERR : ȥ��ʼ��ʧ��
*/
INT32_T log_uninit();

/**
* @brief ��ģ����Եȼ������־��֧�ֶ��̵߳��á�
* @param module ģ��ID
* @param level ��־�ȼ�
* @param fmt ��ʽ���ַ���������˵�����ձ�׼��printf������
* @return
* > 0, ʵ��������ַ�����
* = 0, GUIDEIR_OK��������ȼ������������
* < 0��GUIDEIR_ERR�������Ƿ�������־����ļ�д��ʧ�ܡ�
* @note Ĭ����־����ȼ���INFO������INFO��������������ļ��п��Էֱ����ø�ģ�����־�ȼ���
* ���磺MODULE_VIDEO=1  VIDEOģ��DEBUG�ȼ�������־�������MODULE_PORTING=3 PORTINGģ��WARN�ȼ�������־�������
* ÿ�δ�ӡһ����־������8KB��
*/
INT32_T log_output(MODULE_T module, LOG_LEVEL_T level, CONST CHAR_T *fmt, ...);

/**
* @brief �����Եȼ������־��֧�ֶ��̵߳��á�
* @param level ��־�ȼ�
* @param fmt ��ʽ���ַ���������˵�����ձ�׼��printf������
* @return
* > 0, ʵ��������ַ�����
* = 0, GUIDEIR_OK��������ȼ������������
* < 0��GUIDEIR_ERR�������Ƿ�������־����ļ�д��ʧ�ܡ�
* @note ÿ�δ�ӡһ����־������8KB��
*/
INT32_T log_output_ex(LOG_LEVEL_T level, CONST CHAR_T *fmt, ...);

/**
* @brief ������־�ļ�����·������������ã���־�����ڳ���ͬ��Ŀ¼�¡�
* @param 
*  path	�ļ�·��
* @return
* GUIDEIR_OK : ���óɹ�
* GUIDEIR_ERR : ����ʧ��
*/
INT32_T log_set_path(CONST CHAR_T *path);

#ifdef __cplusplus
}
#endif

#endif// !COMMON_LOG_H
