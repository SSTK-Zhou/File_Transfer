#include "main.h"

/***********************************************************
 *   函数名称：LcdInit
 *   函数作用：初始化lcd屏幕
 *   函数参数：NULL
 *   返回结果：LCD的文件描述符
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：一定要写对LCD屏幕所在的地址，并作错误处理
 *************************************************************/
int LcdInit()
{
    printf("Initializing LCD dev : \n");

    /*以读写的方式打开屏幕路径下的文件*/
    int lcd_fb = open("/dev/fb0", O_RDWR);
    if (-1 == lcd_fb)
    {
        perror("open LCD dev error");
        exit(0);
    }
    else
        printf("Open LCD dev successful.\n");

    return lcd_fb;
}

/***********************************************************
 *   函数名称：GetInfoLcd
 *   函数作用：获取LCD屏幕的参数信息并将其存放进相应的结构体中
 *   函数参数：NULL
 *   返回结果：lcd的屏幕参数信息
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：最后要对显存入口进行清零操作
 *************************************************************/
lcdinformation *GetInfoLcd()
{
    /*创建一个lcd信息结构体*/
    lcdinformation *lcdinfo = malloc(sizeof(lcdinformation));
    lcdinfo->lcd = LcdInit(); /*初始化并获取文件描述符*/

    /*定义一个用来描述各种于显示相关的参数（坐标、颜色等等）的结构体*/
    struct fb_var_screeninfo devinfo;

    if (-1 == ioctl(lcdinfo->lcd, FBIOGET_VSCREENINFO, &devinfo))
    {
        perror("Get LCD devinfo error");
        exit(0);
    }

    /*输出lcd液晶屏的各种信息*/
    lcdinfo->width = devinfo.xres;         /*屏幕的水平分辨率（像素数）*/
    lcdinfo->height = devinfo.yres;        /*屏幕的垂直分辨率（像素数）*/
    lcdinfo->bpp = devinfo.bits_per_pixel; /*每个像素的位深度*/

    printf("The width for LCD is : %d\n", lcdinfo->width);
    printf("The height for LCD is : %d\n", lcdinfo->height);
    printf("The bpp for LCD is : %d\n", lcdinfo->bpp);

    /*申请虚拟区800*480大小的内存并映射到LCD设备中，利用mmap内存映射技术*/
    lcdinfo->fbm = mmap(
        NULL,
        lcdinfo->width * lcdinfo->height * lcdinfo->bpp / 8,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        lcdinfo->lcd,
        0);
    /*内存映射错误处理*/
    if (MAP_FAILED == lcdinfo->fbm) /*若成功，则返回映射区的存储地址*/
    {
        perror("mmap for lcd error");
        exit(0);
    }

    memset(lcdinfo->fbm, 0, sizeof(lcdinfo->fbm));

    return lcdinfo;
}

/***********************************************************
 *   函数名称：release_lcd
 *   函数作用：释放申请的LCD屏幕内存
 *   函数参数：
 *            @ p : 搭载LCD屏幕信息结构体的指针
 *   返回结果：NULL
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：主函数末尾要调用该函数以释放LCD信息屏空间
 *************************************************************/
void release_lcd(lcdinformation *p)
{
    if (NULL == p)
        return;
    if (-1 == munmap(p->fbm, p->width * p->height * p->bpp / 8))
    {
        perror("munmap error");
        exit(0);
    }
    close(p->lcd);
    free(p);
    printf("Successfully released memory.\n");
}