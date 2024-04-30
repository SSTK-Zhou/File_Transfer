#include "main.h"

int main(int argc, char const *argv[])
{
    /*获取lcd屏幕的信息并初始化lcd屏*/
    lcdinformation *lcdinfo = GetInfoLcd();
    /*初始化触摸屏*/
    int ts_fd = TouchScreenInit();
    int x, y;

    /*开机动画*/
    OpenInterface(lcdinfo);
    LogInInterface(lcdinfo);
    if (click(ts_fd, &x, &y))
        InterfaceInit(ts_fd, lcdinfo);

    /*释放资源*/
    release_lcd(lcdinfo);
    release_ts(ts_fd);
    return 0;
}