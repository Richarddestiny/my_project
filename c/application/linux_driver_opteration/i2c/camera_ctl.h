#ifndef __CAMERA_CTL_H__
#define __CAMERA_CTL_H__


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

#define I2C_DEV "/dev/i2c-4"
#define PCIE_DEV "/dev/gpio_pcie"
#define SLAVE_ADDR 0x27

#define DEBUG

/*
* REG
*/
#define SOFTWARE_TRIGGER_MODE  0x01
#define IO_TRIGGER_MODE        0x02
#define VIDEO_TRIGGER_MODE  0x03
#define SOTFWARE_TRIGGER_SET   0x0a

#define GET_MODE_SETREG 0x02
#define HIGH_EXPOSURE_SETREG  0x04
#define LOW_EXPOSURE_SETREG 0x06

#define FLASH_LIGHT_CTL_1 0x0c
#define FLASH_LIGHT_CTL_2 0x0e

#define SHARPEN_CAPTURE_SET 0x10
#define CONTRAST_SET 0x12

#define TEST_REG 0xf0

/*
* RGB CTRL
*/
#define CPU_GPIO1 25
#define CPU_GPIO2 24
#define CPU_GPIO3 27
#define CPU_RESET 8

#define FLASH_LIGHT_MODE_0 0
#define FLASH_LIGHT_MODE_1 1
#define FLASH_LIGHT_MODE_2 2
#define FLASH_LIGHT_MODE_3 3


extern  int init_camera_i2c(void); //open i2c device and init i2c
extern  void gpio_set(int pin,int value);//RGB CTRL and reset
extern  int set_contrast(int mode);//  0 < mode < 16
extern  int set_sharpen(int mode);//  0 < mode < 9
extern  int enable_flashlight(int mode);// FLASH_LIGHT_MODE_?
extern  int camera_capture(void);//capture  set trigger mode first
extern  int set_exposure_time(int nshutter); // us unit
extern  int set_trigger_mode(int mode);//suport sotrware mode,video mode


extern int set_green1_gain(int ngain);//设置绿色通道 1 的增益函数  范围为 0~511  一般情况下绿色通道 1和通道 2 设置相同的值
extern int get_green1_gain(void);  //获取绿色通道 1 的增益函数 
extern int set_green2_gain(int ngain); //设置绿色通道 2 的增益函数  范围为 0~511 
extern int get_green2_gain(void);  //获取绿色通道 2 的增益函数
extern int set_red_gain(int ngain);  //设置红色通道的增益函数  范围为 0~511 
extern int get_red_gain(void); //获取红色通道的增益函数 
extern int setbluegain(int ngain);   //设置蓝色通道的增益函数，范围为 0~511 
extern int get_blue_gain(void); //获取蓝色通道的增益函数 
extern int set_global_gain(int ngain); //设置全局增益函数，最大不超过 800 



#endif


