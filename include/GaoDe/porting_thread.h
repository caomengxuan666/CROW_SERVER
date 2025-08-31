/*************************************************
Copyright (C), 2019-2029, GuideIR Tech. Co., Ltd.
File name	: porting_thread.h
Author		: Guide Sensmart RD
Version		: 1.0
Date		: 2019/7/6
Description	:
*************************************************/

#ifndef PORTING_THREAD_H
#define PORTING_THREAD_H

#include "common_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    UINT16_T year;
    UINT16_T month;
    UINT16_T day;
    UINT16_T hour;
    UINT16_T minute;
    UINT16_T second;
    UINT16_T milliseconds;
} TIME_T;

typedef VOID (*GUIDEIR_THREAD_PROC)(VOID *param);

/**
* @brief		�����߳�
* @param
* func:			������ڵ�ַ:typedef VOID(*IPANEL_THREAD_PROC)(VOID *);
* param:		�����б�
* stack_size:	ջ��С�����Բ�����
* priority:		���ȼ��𣬿��Բ�����
* @return		�߳̾��
*/
HANDLE_T porting_thread_create(GUIDEIR_THREAD_PROC func, VOID *param, INT32_T priority, UINT32_T stack_size);

/**
* @brief		�����̡߳��ȴ�Ŀ���߳̽��������Ŀ���̶߳�����Դ����һ�ַ�ʽ��Ŀ���̷߳��룬�����Լ����������õȴ���
*				���õ�һ�ַ�ʽʵ�������̡߳��������ַ�ʽ��Ҫ���̺߳�����֤���Զ��˳���
* @param
* handle:		�߳̾��
* @return
* 0				�ɹ�
* -1			ʧ��
*/
INT32_T porting_thread_destroy(HANDLE_T handle);

/**
* @brief		����һ��ʱ�䣬�ó�CPU
* @param
* ms			����ʱ�䣬��λ����
* @return		��
*/
VOID porting_thread_sleep(INT32_T ms);

/**
* @brief		��ȡ�߳��ڲ���ϵͳ�е�ID
* @param
* handle:		�߳̾��
* @return		ID
*/
UINT64_T porting_thread_identify(HANDLE_T handle);

/**
* @brief		������������������ERRORCHECK_MUTEX��ͬһ�̲߳����ظ����������ϵ���ֻ���ɱ��߳̽�����
* @param		��
* @return		mutex���
*/
HANDLE_T porting_mutex_create();

/**
* @brief		���ٻ�����
* @param		mutex���
* @return
* 0				�ɹ�
* -1			ʧ��
*/
INT32_T porting_mutex_destroy(HANDLE_T handle);

/**
* @brief		����������
* @param		mutex���
* @return
* 0				�ɹ�
* -1			ʧ��
*/
INT32_T porting_mutex_lock(HANDLE_T handle);

/**
* @brief		����������
* @param		mutex���
* @return
* 0				�ɹ�
* -1			ʧ��
*/
INT32_T porting_mutex_unlock(HANDLE_T handle);

/**
* @brief		��ȡ��ǰ����ʱ�䣬��ȷ�����롣
* @param		time�������ǰ����ʱ�䡣
* @return
* 0				�ɹ�
* -1			ʧ��
*/
INT32_T porting_get_time(TIME_T *time);

/**
* @brief		��ȡ��ǰʱ��ͳ�������ʱ��֮�侭���ĺ�������
* @param		��
* @return		���ص�ǰʱ��ͳ�������ʱ��֮�侭���ĺ�������
* @note			ʹ�øýӿڿ��Լ���ĳ�����̵ĺ�ʱ�����̿�ʼʱ����һ�κ���������ʱ����һ�κ���������������������ĵĺ�������
*/
UINT32_T porting_get_ms(VOID);

#ifdef __cplusplus
}
#endif

#endif// !PORTING_THREAD_H
