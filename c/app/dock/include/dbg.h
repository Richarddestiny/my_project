/******************************************************************************

                  ��Ȩ���� (C), 2016-2026, ���ڽ�����������Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : dbg.h
  �� �� ��   : ����
  ��    ��   : ����ȫ
  ��������   : 2016��4��15��
  ����޸�   :
  ��������   : dbg.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��4��15��
    ��    ��   : ����ȫ
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DBG_H__
#define __DBG_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <syslog.h>
#include <sys/statfs.h>
#include "main.h"
#include "app.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/
extern u8 g_hdmi_debug_switch;
extern u8 g_app_preview_debug_switch;
extern u8 g_init_debug_switch;

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
extern u8 g_debug_switch;

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define DEBUG_OFF   0
#define DEBUG_ON    1

/*----------------------------------------------*
 * �꺯������                                   *
 *----------------------------------------------*/

/* ����򿪵��Կ��أ���¼DEBUG����ϵͳ��־��ͬʱ������� */
#define dbg(fmt, arg...) \
        do { \
                if (DEBUG_ON == g_debug_switch) { \
                        syslog(LOG_DEBUG, "[dock] "fmt, ##arg);\
                        printf("[dock] "fmt, ##arg);\
                }\
        } while (0)

/*  ��¼INFO����ϵͳ��־��ͬʱ������� */
#define msg(fmt, arg...) \
        do { \
                syslog(LOG_INFO, "[dock] "fmt, ##arg);\
                printf("[dock] "fmt, ##arg);\
        } while (0)

/*----------------------------------------------*
 * ���⺯��ԭ��˵��                             *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��  : set_system_log
 ��������  : ����ϵͳ��־
*****************************************************************************/
extern void set_system_log(void);

/*****************************************************************************
 �� �� ��  : dbg_console
 ��������  : ���Կ���̨ʵ�ֺ���
*****************************************************************************/
extern void dbg_console(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __DBG_H__ */
