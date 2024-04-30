#include "main.h"


/***********************************************************
 *   函数名称：TouchScreenInit
 *   函数作用：初始化触摸屏
 *   函数参数：NULL
 *   返回结果：ts_fd
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：作打开文件失败的错误处理
 *************************************************************/
int TouchScreenInit()
{
    /*打开触摸屏并进行错误处理*/
    int ts_fd = open("/dev/input/event0", O_RDWR);
    if (-1 == ts_fd)
    {
        perror("Open touch screen error");
        exit(0);
    }

    printf("Open touch screen successful.\n");

    return ts_fd;
}

/***********************************************************
 *   函数名称： click
 *   函数作用：获取点击事件
 *   函数参数：
 *            @ tp: 触摸屏文件描述符
 *            @ x: 触摸屏x坐标
 *            @ y: 触摸屏y坐标
 *   返回结果：ture或者false
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：读取触摸时会阻塞
 *************************************************************/
bool click(int tp, int *x, int *y)
{
    int x1, y1;
    int x2, y2;

    bool x1done = false;
    bool y1done = false;

    struct input_event buf;
    while (1)
    {

        bzero(&buf, sizeof(buf));
        read(tp, &buf, sizeof(buf));

        // get first pos
        if (buf.type == EV_ABS && buf.code == ABS_X && !x1done)
        {
            x2 = x1 = buf.value;
            x1done = true;
        }

        if (buf.type == EV_ABS && buf.code == ABS_Y && !y1done)
        {
            y2 = y1 = buf.value;
            y1done = true;
        }

        if (buf.type == EV_ABS && buf.code == ABS_X)
            x2 = buf.value;
        if (buf.type == EV_ABS && buf.code == ABS_Y)
            y2 = buf.value;

        if (buf.type == EV_KEY && buf.code == BTN_TOUCH && buf.value == 0)
        {
            if (abs(x1 - x2) <= 20 && abs(y1 - y2) <= 20)
            {
                *x = x1 * 800 / 1024;
                *y = y1 * 480 / 600;
                // printf("click x1=%d\tx2=%d\n", x1 * 800 / 1024, x2 * 800 / 1024); // 输出X轴坐标
                // printf("click y1=%d\ty2=%d\n", y1 * 480 / 600, y2 * 480 / 600);   // 输出Y轴坐标
                return true;
            }
            else
            {
                x1done = false;
                y1done = false;
                continue;
            }
        }
    }
}

void down_button(int tp, int *x, int *y)
{
    int x1, y1;
    struct input_event buf;
    while (1)
    {
        bzero(&buf, sizeof(buf));
        read(tp, &buf, sizeof(buf));

        if (buf.type == EV_ABS && buf.code == ABS_X)
            x1 = buf.value;
        if (buf.type == EV_ABS && buf.code == ABS_Y)
            y1 = buf.value;
        *x = x1 * 800 / 1024;
        *y = y1 * 480 / 600;
        if (buf.code == BTN_TOUCH && buf.type == EV_KEY && buf.value > 0)
            break;
    }
}

void up_button(int tp)
{

    struct input_event buf;
    while (1)
    {
        bzero(&buf, sizeof(buf));
        read(tp, &buf, sizeof(buf));

        if (buf.code == BTN_TOUCH && buf.type == EV_KEY && buf.value == 0)
            break;
    }
}

void release_ts(int ts_fd)
{
    close(ts_fd);
}

int GetNumber(int x, int y)
{
    if (x > 0 && x < 265 && y > 289 && y < 336)
        return 1;
    if (x > 265 && x < 535 && y > 289 && y < 336)
        return 2;
    if (x > 535 && x < 800 && y > 289 && y < 336)
        return 3;
    if (x > 0 && x < 265 && y > 336 && y < 384)
        return 4;
    if (x > 265 && x < 535 && y > 336 && y < 384)
        return 5;
    if (x > 535 && x < 800 && y > 336 && y < 384)
        return 6;
    if (x > 0 && x < 265 && y > 384 && y < 433)
        return 7;
    if (x > 265 && x < 535 && y > 384 && y < 433)
        return 8;
    if (x > 535 && x < 800 && y > 384 && y < 433)
        return 9;
    if (x > 535 && x < 800 && y > 433 && y < 480)
        return BACK;
    if (x > 265 && x < 535 && y > 433 && y < 480)
        return 0;
    if (x > 0 && x < 265 && y > 433 && y < 480)
        return POINT;
    return -1;
}
