/******************************************************************************

                  ��Ȩ���� (C), 2016-2026, ���ڽ�����������Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : mcu.h
  �� �� ��   : ����
  ��    ��   : ����ȫ
  ��������   : 2016��4��18��
  ����޸�   :
  ��������   : mcu.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��4��18��
    ��    ��   : ����ȫ
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MCU_H__
#define __MCU_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <sys/socket.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/* sock_mmĬ��IP��ַ����ȡ eth0 IP��ַʧ��ʱʹ�� */
#define SOCK_MM_IP_ADDR             "192.168.0.178"
#define SOCK_MM_PORT                5555

#define MCU_MAX_MAGIC_LEN           6

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define MCU_CMD_KEEP_ALIVE          0   /* ����MCUͨ������������ */
#define MCU_ACK_VOLT_QUERY          1   /* ������ѯ�����ӦDock�� */
#define MCU_OP_MODE_CHANG           2   /* ģʽ�л�����֪ͨDock�� */
#define MCU_OP_SHOOT_OPERA          3   /* �������֪ͨDock�� */
#define MCU_CMD_QUERY_VOLT          4   /* ��ѯ�������� */
#define MCU_CMD_CHANG_MODE_LIGHT    5   /* �л�ģʽ������ */
#define MCU_CMD_CHANG_POWER_LIGHT   6   /* �л���Դ������ */

#define MCU_DEBUG_SWITCH            0   /* MCU���Կ��� */

/*----------------------------------------------*
 * ö�����Ͷ���                                 *
 *----------------------------------------------*/
typedef enum {
	LED_STATUS_GS   = 0,
	LED_STATUS_OS   = 1,
	LED_STATUS_RS   = 2,
	LED_STATUS_GB_1 = 3,
	LED_STATUS_OB_1 = 4,
	LED_STATUS_RB_1 = 5,
	LED_STATUS_GB_4 = 6,
	LED_STATUS_RB_4 = 7,
	LED_STATUS_OB_4 = 8,
} PowerStatusVaule;

/*----------------------------------------------*
 * �ṹ�����Ͷ���                               *
 *----------------------------------------------*/
/* MCUͨ�ñ��ĸ�ʽ */
struct mcu_packet
{
    u8 magic[MCU_MAX_MAGIC_LEN];    /* ʶ��key�����Mcmd����Ӧ��Mack */
    u8 type;                        /* ����ͻ�Ӧ������ */
    u8 data;                        /* ����ͻ�Ӧ������ */
};

/*****************************************************************************
 �� �� ��  : send_mcu_cmd_pkt
 ��������  : ����MCU�����ʵ�ֺ���
*****************************************************************************/
extern void send_mcu_cmd_pkt(u8 ucCmd, u8 ucData);

/*****************************************************************************
 �� �� ��  : mcu_init
 ��������  : MCU��ʼ��ʵ�ֺ���
*****************************************************************************/
extern void mcu_init(stDock *pstDock);

/*****************************************************************************
 �� �� ��  : set_power_status
 ��������  : ���õ�Դ��״̬ʵ�ֺ���
*****************************************************************************/
extern void set_power_status(stDock *pstDock);

/*****************************************************************************
 �� �� ��  : set_power_status
 ��������  : ����ģʽ��״̬ʵ�ֺ���
*****************************************************************************/
extern void set_mode_status(stDock *pstDock);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __MCU_H__ */
