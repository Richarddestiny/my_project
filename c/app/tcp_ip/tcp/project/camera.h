#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <errno.h>  
#include <time.h>  
  
#define PORT 3311  
#define LISTENQ 10  
#define BUFFSIZE 1024  
#define FILE_NAME_MAX_SIZE 512

#define DATA_SIZE 256

#define HOST_ASK_VERSION 0x01
#define HOST_ASK_VERSION_OK 0x81
#define HOST_ASK_VERSION_ERR 0xc1

#define HOST_ASK_CAPTURE 0x04
#define HOST_ASK_CAPTURE_OK 0x84
#define HOST_ASK_CAPTURE_ERR 0xc4

#define HOST_ASK_SETWIFI  0X0a
#define HOST_ASK_SETWIFI_OK 0x8a
#define HOST_ASK_SETWIFI_ERR 0xca

#define HOST_ASK_CHECKTIME   0x0f
#define HOST_ASK_CHECKTIME_OK 0x8f
#define HOST_ASK_CHECKTIME_ERR 0xcf


#define SAFE_SAPCE 20


static int sockfd,connfd;
static int client_count = 0;

typedef   struct camera_msg_str {
        int head_head;
        int address;
        int head;
        int ctr_code;
        int data_length;
        char data[DATA_SIZE];
        int ack;
        int end;    
    }camera_msg;
/*
 D7=0：由主站发出的命令帧
       D7=1：由从站发出的应答帧
       D6=0：从站正确应答
       D6=1：从站对异常信息的应答
       D5=0：保留
       D5=1：保留
       D4∽D0：请求及应答功能码
               00000：保留
               00001：读数据
               00010：保留
               00011：保留
               00100：写数据
               01000：保留
               01010：写设备地址
               01100：保留
               01111：修改密码
*/



extern camera_msg cmd_resolve(char *);

