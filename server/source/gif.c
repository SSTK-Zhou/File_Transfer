#include "main.h"

void GifShow(lcdinformation *lcdinfo, char *prename, int begin, int end, char *lastname, int time)
{
    char gifpath[256] = {0};
    int i;
    for (i = begin; i <= end; i++)
    {
        sprintf(gifpath, "%s%d%s", prename, i, lastname);
        show_jpeg(gifpath, 0, 0, lcdinfo);
        usleep(time);
    }
}

void DisGifShow(lcdinformation *lcdinfo, char *prename, int begin, int end, char *lastname, int time)
{
    char gifpath[256] = {0};
    int i;
    for (i = end; i >= begin; i--)
    {
        sprintf(gifpath, "%s%d%s", prename, i, lastname);
        show_jpeg(gifpath, 0, 0, lcdinfo);
        usleep(time);
    }
}

void OpenInterface(lcdinformation *lcdinfo)
{
    GifShow(lcdinfo, OPANPRE, OPANBEGIN, OPANEND, OPANLAST, 30);
}

void DisOpenInterface(lcdinformation *lcdinfo)
{
    DisGifShow(lcdinfo, OPANPRE, OPANBEGIN, OPANEND, OPANLAST, 30);
}

void LogInInterface(lcdinformation *lcdinfo)
{
    GifShow(lcdinfo, LOGINPRE, LOGINBEGIN, LOGINEND, LOGINLAST, 30);
}

void DisLogInInterface(lcdinformation *lcdinfo)
{
    DisGifShow(lcdinfo, LOGINPRE, LOGINBEGIN, LOGINEND, LOGINLAST, 30);
}

void ShowKeyBoardUS(lcdinformation *lcdinfo) // 密码不可见键盘上浮
{
    GifShow(lcdinfo, DSKBPRE, DSKBBEGIN, DSKBEND, DSKBLAST, 30);
}

void DisShowKeyBoardUS(lcdinformation *lcdinfo) // 密码不可见键盘下沉
{
    DisGifShow(lcdinfo, DSKBPRE, DSKBBEGIN, DSKBEND, DSKBLAST, 30);
}

void ShowKeyBoardS(lcdinformation *lcdinfo) // 密码可见键盘上浮
{
    GifShow(lcdinfo, SKBPRE, SKBBEGIN, SKBEND, SKBLAST, 30);
}

void DisShowKeyBoardS(lcdinformation *lcdinfo) // 密码可见键盘下沉
{
    DisGifShow(lcdinfo, SKBPRE, SKBBEGIN, SKBEND, SKBLAST, 30);
}

void show_UserError(lcdinformation *lcdinfo) // 密码可见时账号错误处理动画
{
    GifShow(lcdinfo, SUSERERRORPRE, SUSERERRORBEGIN, SUSERERROREND, SUSERERRORLAST, 5);
}

void Disshow_UserError(lcdinformation *lcdinfo) // 密码可见时账号错误处理动画(逆序)
{
    DisGifShow(lcdinfo, SUSERERRORPRE, SUSERERRORBEGIN, SUSERERROREND, SUSERERRORLAST, 5);
}

void show_PasswordError(lcdinformation *lcdinfo) // 密码可见时密码错误处理动画
{
    GifShow(lcdinfo, SPWDERRORPRE, SPWDERRORBEGIN, SPWDERROREND, SPWDERRORLAST, 5);
}

void Disshow_PasswordError(lcdinformation *lcdinfo) // 密码可见时密码错误处理动画(逆序)
{
    DisGifShow(lcdinfo, SPWDERRORPRE, SPWDERRORBEGIN, SPWDERROREND, SPWDERRORLAST, 5);
}

void unshow_UserError(lcdinformation *lcdinfo) // 密码不可见时账号错误处理动画
{
    GifShow(lcdinfo, UNSUSERERRORPRE, UNSUSERERRORBEGIN, UNSUSERERROREND, UNSUSERERRORLAST, 5);
}

void Disunshow_UserError(lcdinformation *lcdinfo) // 密码不可见时账号错误处理动画(逆序)
{
    DisGifShow(lcdinfo, UNSUSERERRORPRE, UNSUSERERRORBEGIN, UNSUSERERROREND, UNSUSERERRORLAST, 5);
}

void unshow_PasswordError(lcdinformation *lcdinfo) // 密码不可见时密码错误处理动画
{
    GifShow(lcdinfo, UNSPWDERRORPRE, UNSPWDERRORBEGIN, UNSPWDERROREND, UNSPWDERRORLAST, 5);
}

void Disunshow_PasswordError(lcdinformation *lcdinfo) // 密码不可见时密码错误处理动画(逆序)
{
    DisGifShow(lcdinfo, UNSPWDERRORPRE, UNSPWDERRORBEGIN, UNSPWDERROREND, UNSPWDERRORLAST, 5);
}

void ChangeInterface(lcdinformation *lcdinfo) // 界面跳转动画
{
    GifShow(lcdinfo, CHANGEINTERFACEPRE, CHANGEINTERFACEBEGIN, CHANGEINTERFACEEND, CHANGEINTERFACELAST, 30);
}

void DisChangeInterface(lcdinformation *lcdinfo) // 界面跳转动画(逆序)
{
    DisGifShow(lcdinfo, CHANGEINTERFACEPRE, CHANGEINTERFACEBEGIN, CHANGEINTERFACEEND, CHANGEINTERFACELAST, 30);
}

void MTP(lcdinformation *lcdinfo) // 主界面跳转到图片界面
{
    GifShow(lcdinfo, MTPPRE, MTPBEGIN, MTPEND, MTPLAST, 30);
}

void DisMTP(lcdinformation *lcdinfo) // 主界面跳转到图片界面(逆序)
{
    DisGifShow(lcdinfo, MTPPRE, MTPBEGIN, MTPEND, MTPLAST, 30);
}

void MTV(lcdinformation *lcdinfo) // 主界面跳转到视频界面
{
    GifShow(lcdinfo, MTVPRE, MTVBEGIN, MTVEND, MTVLAST, 30);
}

void DisMTV(lcdinformation *lcdinfo) // 主界面跳转到视频界面(逆序)
{
    DisGifShow(lcdinfo, MTVPRE, MTVBEGIN, MTVEND, MTVLAST, 30);
}

void MTA(lcdinformation *lcdinfo) // 主界面跳转到文本文件界面
{
    GifShow(lcdinfo, MTAPRE, MTABEGIN, MTAEND, MTALAST, 30);
}

void DisMTA(lcdinformation *lcdinfo) // 主界面跳转到文本文件界面(逆序)
{
    DisGifShow(lcdinfo, MTAPRE, MTABEGIN, MTAEND, MTALAST, 30);
}