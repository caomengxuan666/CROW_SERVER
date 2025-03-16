/*************************************************
Copyright (C), 2019-2029, GuideIR Tech. Co., Ltd.
File name	: porting_file.h
Author		: Guide Sensmart RD
Version		: 1.0
Date		: 2019/7/6
Description	:
*************************************************/

#ifndef PORTING_FILE_H
#define PORTING_FILE_H

#include "common_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NAME_LENGTH 256

typedef struct
{
	UINT32_T flag; 				//0 ��ʾ�ļ��ڵ㣬1��ʾĿ¼�ڵ�
	CHAR_T 	 name[NAME_LENGTH]; //�ڵ����ַ������������ϼ�·��
	ULONG_T  size;				//�ļ���С�����ļ�ʱ�����塣
	UINT64_T time;				//�޸����ڣ���1970��1��1��0ʱ0��0�뿪ʼ��ʱ��������
}DIR_T;

/**
* @brief	���ļ�
* @param
* filename	�ļ�·��+����
* mode		ʹ���ļ���ʽ�����ͺͲ���Ҫ�󣬲ο�fopen��
* @return	�ļ������NULL��ʾ���ļ�ʧ�ܡ�
*/
HANDLE_T porting_file_open(CONST CHAR_T *filename, CONST CHAR_T *mode);

/**
* @brief	�ر��ļ�
* @param
* fd		�ļ����
* @return	�ļ������NULL��ʾ���ļ�ʧ�ܡ�
*/
INT32_T porting_file_close(HANDLE_T fd);

/**
* @brief	���ļ�
* @param
* fd		�ļ����
* buffer	�����ݻ���
* nbytes	��ȡ��С
* @return	ʵ�ʶ�ȡ��С
*/
INT32_T porting_file_read(HANDLE_T fd, BYTE_T *buffer, INT32_T nbytes);

/**
* @brief	д�ļ�
* @param
* fd		�ļ����
* buffer	д���ݻ���
* nbytes	д���С
* @return	ʵ��д���С
*/
INT32_T porting_file_write(HANDLE_T fd, CONST BYTE_T *buffer, INT32_T nbytes);

/**
* @brief	������������д���ļ�
* @param
* fd		�ļ����
*/
INT32_T porting_file_flush(HANDLE_T fd);

/**
* @brief	�õ��ļ���ǰ��дλ��
* @param
* fd		�ļ����
* @return	��ǰ��дλ��ƫ���ļ�ͷ�����ֽ���
*/
INT32_T porting_file_tell(HANDLE_T fd);

/**
* @brief	���ļ���дָ���Ƶ�ָ��λ��
* @param
* fd		�ļ����
* offset	ƫ��λ��
* seek		��ʼ�㣬ȡֵ��0 1 2�������ļ���ͬ��λ�á�
* SEEK_SET 0   �ļ���ͷ
* SEEK_CUR 1   �ļ���ǰλ��
* SEEK_END 2   �ļ�ĩβ
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_file_seek(HANDLE_T fd, INT32_T offset, INT32_T seek);

/**
* @brief	���ļ���дָ������ָ���ļ���ͷ
* @param
* fd		�ļ����
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_file_rewind(HANDLE_T fd);

/**
* @brief	ɾ���ļ�
* @param
* name		�ļ�·��+����
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_file_delete(CONST CHAR_T *name);

/**
* @brief	�½�Ŀ¼
* @param
* dirname	Ŀ¼��
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_dir_create(CONST CHAR_T *dirname);

/**
* @brief	ɾ��Ŀ¼����֧��ɾ�ǿ�Ŀ¼��
* @param
* dirname	Ŀ¼��
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_dir_remove(CONST CHAR_T *dirname);

/**
* @brief	��Ŀ¼��readĿ¼֮ǰ��open��
* @param
* dirname	Ŀ¼��
* @return	����Ŀ¼���
*/
HANDLE_T porting_dir_open(CONST CHAR_T *dirname);

/**
* @brief	�ر�Ŀ¼
* @param
* dd		Ŀ¼���
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_dir_close(HANDLE_T dd);

/**
* @brief	��ȡĿ¼�µ�һ���ӽڵ㣬���readֱ����ȡ���ӽڵ�Ϊ�ձ�������Ŀ¼��ɡ�
* @param
* dd		Ŀ¼���
* pdir		�������ӽڵ���Ϣ�����������
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_dir_read(HANDLE_T dd, DIR_T *pdir);

/**
* @brief	���Ŀ¼�µ������ļ���Ϣ����¼����־�ļ���
* @param
* dirname	Ŀ¼����Ҫ��ͨ���"*.*"������
* @return
* 0			�ɹ�
* -1		ʧ��
*/
INT32_T porting_dir_list(CONST CHAR_T *dirname);

#ifdef __cplusplus
}
#endif

#endif // !PORTING_FILE_H
