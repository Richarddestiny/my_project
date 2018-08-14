/*
struct fb_var_screeninfo 和 struct fb_fix_screeninfo 两个数据结构是在/usr/include/linux/fb.h中定义的，里面有些有趣的值：（都是无符号32位的整数）

在fb_fix_screeninfo中有
__u32 smem_len 是这个/dev/fb0的大小，也就是内存大小。
__u32 line_length 是屏幕上一行的点在内存中占有的空间，不是一行上的点数。
在fb_var_screeninfo 中有
__u32 xres ，__u32 yres 是x和y方向的分辨率，就是两个方向上的点数。
__u32 bits_per_pixel 是每一点占有的内存空间。
*/


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

int main () {
    int fp=0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long screensize=0;
    char *fbp = 0, *fbbuf = 0;
    int x = 0, y = 0;
    long location = 0;
    int color, idx;

    fp = open ("/dev/fb0",O_RDWR);

    if (fp < 0){
        printf("Error : Can not open framebuffer device\n");
        exit(1);
    }

    if (ioctl(fp,FBIOGET_FSCREENINFO,&finfo)){
        printf("Error reading fixed information\n");
        exit(2);
    }

    if (ioctl(fp,FBIOGET_VSCREENINFO,&vinfo)){
        printf("Error reading variable information\n");
        exit(3);
    }

    printf("The mem is :%d\n",finfo.smem_len);
    printf("The line_length is :%d\n",finfo.line_length);
    printf("The xres is :%d\n",vinfo.xres);
    printf("The yres is :%d\n",vinfo.yres);
    printf("bits_per_pixel is :%d\n",vinfo.bits_per_pixel);
    printf("vinfo.yoffset:%d\n",vinfo.yoffset);
    printf("vinfo.xoffset:%d\n",vinfo.xoffset);
    printf("finfo.smem_len:%d\n",finfo.smem_len);

    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    /*这就是把fp所指的文件中从开始到screensize大小的内容给映射出来，得到一个指向这块空间的指针*/
    fbbuf =(char *) mmap (0, 1*screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp,0);
    if ((int) fbp == -1)
    {
        printf ("Error: failed to map framebuffer device to memory.\n");
        exit (4);
    }
    fbp = fbbuf;
    printf("framebuf pointer : %p\n", fbp);
    idx = 0;
    memset(fbp,5, 1 * screensize);
        vinfo.yoffset = vinfo.yres;
        vinfo.yoffset = 0;
        if(ioctl(fp, FBIOPAN_DISPLAY,&vinfo) < 0)
          printf("ioctl FBIOPAN_DISPLAY failed!\n");

int y_roll = 0, x_roll = 0;
int roll_long = 80, tmp = 0;
    printf("11111111111111111111\n");
while(1) {
    usleep(300000);
    x_roll > vinfo.xres?x_roll = 0 :(x_roll+=10);
    for (x=0; x<vinfo.xres ; x++) 
    {
#if 1        
        if(x%2 != 0) {
            vinfo.yoffset = vinfo.yres;
//            vinfo.xoffset = vinfo.xres;
          //  fbp = fbbuf + screensize;
        }else {
            vinfo.yoffset = 0;
            vinfo.xoffset = 0;
            fbp = fbbuf;
        }
#endif
            
        for (y=0;y<vinfo.yres;y++)
        {
            location = x * (vinfo.bits_per_pixel / 8) + y  *  finfo.line_length;
            /*直接赋值来改变屏幕上某点的颜色，little endian，先放低字节
            本例子为 16bbp，所以占2个字节一个点 */
            // 纯色
            if( x >= x_roll && x <= (x_roll + roll_long)  && y > 100 && y <= 180) {
//                *(fbp + location) = 0x00;   
                *(fbp + location + 1) = 0xff;
  //              *(fbp + location + 2) = 0x00;

            }else {
                *(fbp + location) = 0xff;   
                *(fbp + location + 1) = 0x00;
      //          *(fbp + location + 2) = 0x00;
            }
            // 图像点阵数据
            //*(fbp + location) = pic[idx];   
            //*(fbp + location + 1) = pic[idx+1];
            idx += 2;

        }
//        if(ioctl(fp, FBIOPAN_DISPLAY,&vinfo) < 0)
  //          printf("ioctl FBIOPAN_DISPLAY failed!\n");

    }

    }
    munmap (fbp, screensize); /*解除映射*/
    close (fp);    /*关闭文件*/

    return 0;
}

