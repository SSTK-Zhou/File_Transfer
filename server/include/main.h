#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdbool.h>
#include <errno.h>
#include <poll.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <netdb.h>
/* See NOTES */
#include <netinet/ip.h> /* superset of previous */
#include "font.h"
#include "jconfig.h"
#include "jerror.h"
#include "jpeglib.h"

#define HTONS 8888                 // 网络字节序转换宏
#define HTONS1 5432                // 网络字节序转换宏
#define HTONS2 1234                // 网络字节序转换宏
#define HTONS3 1245                // 网络字节序转换宏
#define SERVER_IP "192.168.171.6"  // 服务器IP地址
#define CLIENT_IP "192.168.171.11" // 客户端IP地址

#define USERPASSWORDDISSHOWUP "./Data/PictureForThis/KeyBoard/unshow/Frame0.jpg" // 主界面密码不可见且未按下确认
#define USERPASSWORDSHOWUP "./Data/PictureForThis/KeyBoard/show/Frame18.jpg"     // 主界面密码可见且未按下确认
#define USERPASSWORDDISSHOWDOWN "./Data/PictureForThis/loginunshow.jpg"          // 主界面密码不可见且按下确认
#define USERPASSWORDSHOWDOWN "./Data/PictureForThis/loginshow.jpg"               // 主界面密码可见且按下确认
#define UPKEYBOARD "./Data/PictureForThis/KeyBoard/unshow/Frame17.jpg"           // 未被按下的键盘
#define DOWN_0 "./Data/PictureForThis/KeyBoard/0.jpg"                            // 键盘按下数字0
#define DOWN_1 "./Data/PictureForThis/KeyBoard/1.jpg"                            // 键盘按下数字1
#define DOWN_2 "./Data/PictureForThis/KeyBoard/2.jpg"                            // 键盘按下数字2
#define DOWN_3 "./Data/PictureForThis/KeyBoard/3.jpg"                            // 键盘按下数字3
#define DOWN_4 "./Data/PictureForThis/KeyBoard/4.jpg"                            // 键盘按下数字4
#define DOWN_5 "./Data/PictureForThis/KeyBoard/5.jpg"                            // 键盘按下数字5
#define DOWN_6 "./Data/PictureForThis/KeyBoard/6.jpg"                            // 键盘按下数字6
#define DOWN_7 "./Data/PictureForThis/KeyBoard/7.jpg"                            // 键盘按下数字7
#define DOWN_8 "./Data/PictureForThis/KeyBoard/8.jpg"                            // 键盘按下数字8
#define DOWN_9 "./Data/PictureForThis/KeyBoard/9.jpg"                            // 键盘按下数字9
#define DOWN_P "./Data/PictureForThis/KeyBoard/point.jpg"                        // 键盘按下小数点
#define DOWN_BACK "./Data/PictureForThis/KeyBoard/Back.jpg"                      // 键盘按下退格键
#define SHINTER "./Data/PictureForThis/ShowInterface/default.jpg"                // 显示界面
#define SHINTERAR "./Data/PictureForThis/ShowInterface/article.jpg"              // 显示界面点击文章按钮
#define SHINTERBA "./Data/PictureForThis/ShowInterface/Back.jpg"                 // 显示界面点击返回按钮
#define SHINTERPH "./Data/PictureForThis/ShowInterface/photograph.jpg"           // 显示界面点击照片按钮
#define SHINTERVI "./Data/PictureForThis/ShowInterface/video.jpg"                // 显示界面点击视频按钮
#define SUSERERROR_UP "./Data/PictureForThis/Error/Frame17.jpg"                  // 密码可见时账号错误处理动画(未按下确认)
#define SUSERERROR_DOWN "./Data/PictureForThis/Error/Frame18.jpg"                // 密码可见时账号错误处理动画(按下确认)
#define SPWDERROR_UP "./Data/PictureForThis/Error/Frame35.jpg"                   // 密码可见时密码错误处理动画(未按下确认)
#define SPWDERROR_DOWN "./Data/PictureForThis/Error/Frame36.jpg"                 // 密码可见时密码错误处理动画(按下确认)
#define UNSUSERERROR_UP "./Data/PictureForThis/Error/Frame54.jpg"                // 密码不可见时账号错误处理动画(未按下确认)
#define UNSUSERERROR_DOWN "./Data/PictureForThis/Error/Frame55.jpg"              // 密码不可见时账号错误处理动画(按下确认)
#define UNSPWDERROR_UP "./Data/PictureForThis/Error/Frame73.jpg"                 // 密码不可见时密码错误处理动画(未按下确认)
#define UNSPWDERROR_DOWN "./Data/PictureForThis/Error/Frame74.jpg"               // 密码不可见时密码错误处理动画(按下确认)
#define AUD_BACK "./Data/PictureForThis/AUD/back.jpg"                            // 文章界面返回按钮
#define AUD_DEFAULT "./Data/PictureForThis/AUD/default.jpg"                      // 文章界面默认显示
#define AUD_UPLOAD "./Data/PictureForThis/AUD/upload.jpg"                        // 文章界面上传按钮
#define AUD_DOWNLOAD "./Data/PictureForThis/AUD/download.jpg"                    // 文章界面下载按钮
#define PUD_BACK "./Data/PictureForThis/PUD/back.jpg"                            // 照片界面返回按钮
#define PUD_DEFAULT "./Data/PictureForThis/PUD/default.jpg"                      // 照片界面默认显示
#define PUD_UPLOAD "./Data/PictureForThis/PUD/upload.jpg"                        // 照片界面上传按钮
#define PUD_DOWNLOAD "./Data/PictureForThis/PUD/download.jpg"                    // 照片界面下载按钮
#define VUD_BACK "./Data/PictureForThis/VUD/back.jpg"                            // 视频界面返回按钮
#define VUD_DEFAULT "./Data/PictureForThis/VUD/default.jpg"                      // 视频界面默认显示
#define VUD_UPLOAD "./Data/PictureForThis/VUD/upload.jpg"                        // 视频界面上传按钮
#define VUD_DOWNLOAD "./Data/PictureForThis/VUD/download.jpg"                    // 视频界面下载按钮

#define OPANPRE "./Data/PictureForThis/LogIn/Frame" // 开场动画文件名前半部分
#define OPANBEGIN 0                                 // 开场动画文件图片起始值
#define OPANEND 22                                  // 开场动画文件图片结束值
#define OPANLAST ".jpg"                             // 开场动画文件名后缀

#define LOGINPRE "./Data/PictureForThis/LogIn/Frame" // 主界面动画文件名前半部分
#define LOGINBEGIN 23                                // 主界面动画文件图片起始值
#define LOGINEND 171                                 // 主界面动画文件图片结束值
#define LOGINLAST ".jpg"                             // 主界面动画文件名后缀

#define DSKBPRE "./Data/PictureForThis/KeyBoard/unshow/Frame" // 键盘在密码不可见时出现动画文件名前半部分
#define DSKBBEGIN 0                                           // 键盘在密码不可见时出现动画文件图片起始值
#define DSKBEND 17                                            // 键盘在密码不可见时出现动画文件图片结束值
#define DSKBLAST ".jpg"                                       // 键盘在密码不可见时出现动画文件名后半部分

#define SKBPRE "./Data/PictureForThis/KeyBoard/show/Frame" // 键盘在密码可见时出现动画文件名前半部分
#define SKBBEGIN 18                                        // 键盘在密码可见时出现动画文件图片起始值
#define SKBEND 34                                          // 键盘在密码可见时出现动画文件图片结束值
#define SKBLAST ".jpg"                                     // 键盘在密码可见时出现动画文件名后半部分

#define SUSERERRORPRE "./Data/PictureForThis/Error/Frame" // 密码可见时账号错误处理动画文件名前半部分
#define SUSERERRORBEGIN 0                                 // 密码可见时账号错误处理动画文件图片起始值
#define SUSERERROREND 17                                  // 密码可见时账号错误处理动画文件图片结束值
#define SUSERERRORLAST ".jpg"                             // 密码可见时账号错误处理动画文件名后半部分

#define SPWDERRORPRE "./Data/PictureForThis/Error/Frame" // 密码可见时密码错误处理动画文件名前半部分
#define SPWDERRORBEGIN 19                                // 密码可见时密码错误处理动画文件图片起始值
#define SPWDERROREND 35                                  // 密码可见时密码错误处理动画文件图片结束值
#define SPWDERRORLAST ".jpg"                             // 密码可见时密码错误处理动画文件名后半部分

#define UNSUSERERRORPRE "./Data/PictureForThis/Error/Frame" // 密码不可见时账号错误处理动画文件名前半部分
#define UNSUSERERRORBEGIN 37                                // 密码不可见时账号错误处理动画文件图片起始值
#define UNSUSERERROREND 54                                  // 密码不可见时账号错误处理动画文件图片结束值
#define UNSUSERERRORLAST ".jpg"                             // 密码不可见时账号错误处理动画文件名后半部分

#define UNSPWDERRORPRE "./Data/PictureForThis/Error/Frame" // 密码不可见时密码错误处理动画文件名前半部分
#define UNSPWDERRORBEGIN 56                                // 密码不可见时密码错误处理动画文件图片起始值
#define UNSPWDERROREND 73                                  // 密码不可见时密码错误处理动画文件图片结束值
#define UNSPWDERRORLAST ".jpg"                             // 密码不可见时密码错误处理动画文件名后半部分

#define CHANGEINTERFACEPRE "./Data/PictureForThis/Change/Frame" // 初始转内部界面动画文件名前半部分
#define CHANGEINTERFACEBEGIN 0                                  // 初始转内部界面动画文件图片起始值
#define CHANGEINTERFACEEND 70                                   // 初始转内部界面动画文件图片结束值
#define CHANGEINTERFACELAST ".jpg"                              // 初始转内部界面动画文件名后半部分

#define MTPPRE "./Data/PictureForThis/MTP/Frame" //  主界面跳转到图片界面动画文件名前半部分
#define MTPBEGIN 21                              //  主界面跳转到图片界面动画文件图片起始值
#define MTPEND 30                                //  主界面跳转到图片界面动画文件图片结束值
#define MTPLAST ".jpg"                           //  主界面跳转到图片界面动画文件名后半部分

#define MTVPRE "./Data/PictureForThis/MTV/Frame" //  主界面跳转到视频界面动画文件名前半部分
#define MTVBEGIN 21                              //  主界面跳转到视频界面动画文件图片起始值
#define MTVEND 30                                //  主界面跳转到视频界面动画文件图片结束值
#define MTVLAST ".jpg"                           //  主界面跳转到视频界面动画文件名后半部分

#define MTAPRE "./Data/PictureForThis/MTA/Frame" //  主界面跳转到文本界面动画文件名前半部分
#define MTABEGIN 21                              //  主界面跳转到文本界面动画文件图片起始值
#define MTAEND 30                                //  主界面跳转到文本界面动画文件图片结束值
#define MTALAST ".jpg"                           //  主界面跳转到文本界面动画文件名后半部分

#define USERNAMELEN 12 // 用户名长度
#define PASSWORDLEN 7  // 密码长度
#define NODISPSW 0     // 密码不可见
#define DISPSW 1       // 密码可见

#define BACK 'b'  // 定义退格为“b”
#define POINT '.' // 定义.为“.”

extern pthread_t tcp_client_thread_recv;   // 文本文件线程
extern pthread_t picture_thread_recv;      // 图片文件线程
extern int tcp_client_fd;                  // tcp客户端套接字
extern int tcp_client_txt_fd;              // tcp客户端文本套接字
extern int tcp_client_picture_fd;          // tcp客户端图片套接字
extern int tcp_client_video_fd;            // tcp客户端视频套接字
extern int tcp_client_thread_recv_running; // 控制文本线程是否继续运行的标志
extern int picture_thread_recv_running;    // 控制图片线程是否继续运行的标志

/*结构体*/
typedef struct
{
    int lcd;    /*文件描述符*/
    int width;  /*LCD屏幕的宽度*/
    int height; /*/LCD屏幕的高度*/
    int bpp;    /*每位像素的位深度*/

    unsigned int *fbm; /*显存入口，指向LCD区域*/
} lcdinformation;      // LCD屏幕信息结构体

typedef struct
{
    FILE *fp;       // 图片文件指针
    size_t jpgsize; // JPEG图片文件大小
    int width;      // JPEG图片宽度
    int height;     // JPEG图片高度
    int bpp;        // JPEG图片位深度

    char *RGB;     // JPEG图片解压后存放的数组
} jpeginformation; // JPEG图片信息结构体

typedef struct
{
    void *thread_main;       // 线程主体
    int socket_fd;           // 套接字文件描述符
    lcdinformation *lcdinfo; // 屏幕信息
    int ts_fd;               // 触屏文件描述符
} Thread_Args;               // 线程结构体

/*********************************************字体区********************************************/
void ShowFont(lcdinformation *lcd, char buf[], int size, int width, int height, int x, int y); // 字体显示

/*********************************************JPEG区********************************************/
char *get_information_jpeg(const char *road, jpeginformation *jpeginfo); // 获取jpeg图片信息
void jpg2rgb(const char *jpgdata, size_t jpgsize, jpeginformation *p);   // JPEG图片解压
void show_jpeg(const char *road, int x, int y, lcdinformation *lcdinfo); // 在开发板上展示JPEG图片

/*********************************************LCD区********************************************/
int LcdInit();                       // 初始化lcd屏幕
lcdinformation *GetInfoLcd();        // 获取LCD屏幕的参数信息并将其存放进相应的结构体中
void release_lcd(lcdinformation *p); // 釋放屏幕信息

/*********************************************触屏区********************************************/
int TouchScreenInit();                    // 初始化觸摸屏信息
bool click(int tp, int *x, int *y);       // 點擊獲取屏幕坐標
void down_button(int tp, int *x, int *y); // 獲取按下屏幕的坐標，并獲取按下狀態
void up_button(int tp);                   // 獲取鬆開屏幕狀態
void release_ts(int ts_fd);               // 釋放觸摸屏信息
int GetNumber(int x, int y);              // 获取点击的数字

/********************************************动画区********************************************/
void GifShow(lcdinformation *lcdinfo, char *prename, int begin, int end, char *lastname, int time);
void DisGifShow(lcdinformation *lcdinfo, char *prename, int begin, int end, char *lastname, int time);
void OpenInterface(lcdinformation *lcdinfo);           // 开场动画
void DisOpenInterface(lcdinformation *lcdinfo);        // 开场动画(逆序)
void LogInInterface(lcdinformation *lcdinfo);          // 登录界面动画
void DisLogInInterface(lcdinformation *lcdinfo);       // 登录界面动画(逆序)
void ShowKeyBoardUS(lcdinformation *lcdinfo);          // 密码不可见键盘上浮
void DisShowKeyBoardUS(lcdinformation *lcdinfo);       // 密码不可见键盘下沉
void ShowKeyBoardS(lcdinformation *lcdinfo);           // 密码可见键盘上浮
void DisShowKeyBoardS(lcdinformation *lcdinfo);        // 密码可见键盘下沉
void show_UserError(lcdinformation *lcdinfo);          // 密码可见时账号错误处理动画
void Disshow_UserError(lcdinformation *lcdinfo);       // 密码可见时账号错误处理动画(逆序)
void show_PasswordError(lcdinformation *lcdinfo);      // 密码可见时密码错误处理动画
void Disshow_PasswordError(lcdinformation *lcdinfo);   // 密码可见时密码错误处理动画(逆序)
void unshow_UserError(lcdinformation *lcdinfo);        // 密码不可见时账号错误处理动画
void Disunshow_UserError(lcdinformation *lcdinfo);     // 密码不可见时账号错误处理动画(逆序)
void unshow_PasswordError(lcdinformation *lcdinfo);    // 密码不可见时密码错误处理动画
void Disunshow_PasswordError(lcdinformation *lcdinfo); // 密码不可见时密码错误处理动画(逆序)
void ChangeInterface(lcdinformation *lcdinfo);         // 界面跳转动画
void DisChangeInterface(lcdinformation *lcdinfo);      // 界面跳转动画(逆序)
void MTP(lcdinformation *lcdinfo);                     // 主界面跳转到图片界面
void DisMTP(lcdinformation *lcdinfo);                  // 主界面跳转到图片界面(逆序)
void MTV(lcdinformation *lcdinfo);                     // 主界面跳转到视频界面
void DisMTV(lcdinformation *lcdinfo);                  // 主界面跳转到视频界面
void MTA(lcdinformation *lcdinfo);                     // 主界面跳转到文本文件界面
void DisMTA(lcdinformation *lcdinfo);                  // 主界面跳转到文本文件界面(逆序)

/********************************************界面区********************************************/
void Callback_InitalInterface(int ts_fd, lcdinformation *lcdinfo, void (*p)(int, lcdinformation *));
void InterfaceInit(int ts_fd, lcdinformation *lcdinfo);  // 初始化主界面
void MainInterface(int ts_fd, lcdinformation *lcdinfo);  // 主界面 (选择传输文件类型)
void FileForPicture(int ts_fd, lcdinformation *lcdinfo); // 图片界面
void FileForVideo(int ts_fd, lcdinformation *lcdinfo);   // 视频界面
void FileForTXT(int ts_fd, lcdinformation *lcdinfo);     // 文本文件界面 (传输与下载)
void test_send();                                        // 上传测试数据(文本文件)
void picture_send();                                     // 上传图片
void video_send();                                       // 上传视频
void cancel_thread();                                    // 取消线程

/********************************************线程区********************************************/
void *tcp_client_receive_thread(void *arg); // 创建TCP客户端接收线程(下载文本文件)
void *picture_receive_thread(void *arg);    // 创建TCP客户端接收线程(下载图片文件)
void *video_receive_thread(void *arg);      // 创建TCP客户端接收线程(下载视频文件)

/********************************************网络区********************************************/
void client_cmd();     // 专门发送命令的客户端
void client_txt();     // 专门发送文本的客户端
void client_picture(); // 专门发送图片的客户端
void client_video();   // 专门发送视频的客户端
#endif