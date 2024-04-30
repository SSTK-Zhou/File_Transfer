#include "main.h"

pthread_t tcp_client_thread_recv; // 文本文件线程
pthread_t picture_thread_recv;    // 图片文件线程
pthread_t video_thread_recv;      // 视频文件线程

int tcp_client_thread_recv_running = 0; // 控制文本线程是否继续运行的标志
int picture_thread_recv_running = 0;    // 控制图片线程是否继续运行的标志
int video_thread_recv_running = 0;      // 控制视频线程是否继续运行的标志

// 回调函数
void Callback_InitalInterface(int ts_fd, lcdinformation *lcdinfo, void (*p)(int, lcdinformation *))
{
    (*p)(ts_fd, lcdinfo);
}

void InterfaceInit(int ts_fd, lcdinformation *lcdinfo)
{
    bool click_flag = false; // 判断是否第一次点击屏幕的标志
    int x, y;                // 存储点击位置的坐标
    int flagp = NODISPSW;    // 密码默认不可见
    int temp = 0;            // 用于存储点击的小键盘的位置所对应的按钮的功能
    /**************************************************************************************************************/
    client_cmd();     // 专门发送命令的客户端
    client_txt();     // 专门发送文本的客户端
    client_picture(); // 专门发送图片的客户端
    client_video();   // 专门发送视频的客户端
    /**************************************************************************************************************/

    /*存储输入的用户名密码*/
    char username[USERNAMELEN] = {0};    // 存储输入的用户名
    char password[PASSWORDLEN] = {0};    // 存储输入的密码
    char dispassword[PASSWORDLEN] = {0}; // 存儲輸入的不可見密碼
    int usernameposition = 0;            // 用于记录当前用户名输入到的位置
    int passwordposition = 0;            // 用于记录当前密码输入到的位置

    for (;;)
    {
        if (click_flag)
        {
            if (flagp == NODISPSW)
            {
                show_jpeg(USERPASSWORDDISSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
            }
            else if (flagp == DISPSW)
            {
                show_jpeg(USERPASSWORDSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中表中
            }
        }
        down_button(ts_fd, &x, &y);
        if (x > 190 && x < 605 && y > 143 && y < 214) // 点击输入账号框
        {
            if (flagp == NODISPSW)
            {
                show_jpeg(USERPASSWORDDISSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                ShowKeyBoardUS(lcdinfo);
                ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                for (;;)                                          // 在键盘上输入数字
                {
                    down_button(ts_fd, &x, &y);
                    temp = GetNumber(x, y);
                    if ((temp >= 0 && temp <= 9) || temp == POINT)
                    {
                        switch (temp) // 获取数字并输入到键盘的输入框中
                        {
                        case 0:
                            show_jpeg(DOWN_0, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 1:
                            show_jpeg(DOWN_1, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 2:
                            show_jpeg(DOWN_2, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 3:
                            show_jpeg(DOWN_3, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 4:
                            show_jpeg(DOWN_4, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 5:
                            show_jpeg(DOWN_5, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 6:
                            show_jpeg(DOWN_6, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 7:
                            show_jpeg(DOWN_7, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 8:
                            show_jpeg(DOWN_8, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 9:
                            show_jpeg(DOWN_9, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case POINT:
                            show_jpeg(DOWN_P, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        default:
                            break;
                        }
                        if (usernameposition < USERNAMELEN - 1)
                        {
                            username[usernameposition++] = 48 + temp;
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                        if (usernameposition == USERNAMELEN - 1)
                        {
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                    }
                    if (temp == BACK)
                    {
                        show_jpeg(DOWN_BACK, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        up_button(ts_fd);

                        if (usernameposition > 0)
                            username[--usernameposition] = '\0';
                        show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        continue;
                    }
                    if (y > 0 && y < 240)
                    {
                        DisShowKeyBoardUS(lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中表中
                        show_jpeg(USERPASSWORDDISSHOWUP, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中表中
                        break;
                    }
                }
            }
            else if (flagp == DISPSW)
            {
                show_jpeg(USERPASSWORDSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                ShowKeyBoardS(lcdinfo);
                ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                for (;;)                                          // 在键盘上输入数字
                {
                    down_button(ts_fd, &x, &y);
                    temp = GetNumber(x, y);
                    if ((temp >= 0 && temp <= 9) || temp == POINT)
                    {
                        switch (temp) // 获取数字并输入到键盘的输入框中
                        {
                        case 0:
                            show_jpeg(DOWN_0, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 1:
                            show_jpeg(DOWN_1, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 2:
                            show_jpeg(DOWN_2, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 3:
                            show_jpeg(DOWN_3, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 4:
                            show_jpeg(DOWN_4, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 5:
                            show_jpeg(DOWN_5, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 6:
                            show_jpeg(DOWN_6, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 7:
                            show_jpeg(DOWN_7, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 8:
                            show_jpeg(DOWN_8, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 9:
                            show_jpeg(DOWN_9, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case POINT:
                            show_jpeg(DOWN_P, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        default:
                            break;
                        }
                        if (usernameposition < USERNAMELEN - 1)
                        {
                            username[usernameposition++] = 48 + temp;
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                        if (usernameposition == USERNAMELEN - 1)
                        {
                            ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                    }
                    if (temp == BACK)
                    {
                        show_jpeg(DOWN_BACK, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        up_button(ts_fd);

                        if (usernameposition > 0)
                            username[--usernameposition] = '\0';
                        show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        continue;
                    }
                    if (y > 0 && y < 240)
                    {
                        DisShowKeyBoardS(lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                        show_jpeg(USERPASSWORDSHOWUP, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                        break;
                    }
                }
            }
        }
        if (x > 190 && x < 562 && y > 247 && y < 319) // 密碼輸入
        {
            if (flagp == NODISPSW)
            {
                show_jpeg(USERPASSWORDDISSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                ShowKeyBoardUS(lcdinfo);
                ShowFont(lcdinfo, username, 36, 800, 40, 0, 244);    // 将获取到的賬號显示在键盘输入框中
                ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的密碼显示在键盘输入框中
                for (;;)                                             // 在键盘上输入数字
                {
                    down_button(ts_fd, &x, &y);
                    temp = GetNumber(x, y);
                    if ((temp >= 0 && temp <= 9) || temp == POINT)
                    {
                        switch (temp) // 获取数字并输入到键盘的输入框中
                        {
                        case 0:
                            show_jpeg(DOWN_0, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 1:
                            show_jpeg(DOWN_1, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 2:
                            show_jpeg(DOWN_2, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 3:
                            show_jpeg(DOWN_3, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 4:
                            show_jpeg(DOWN_4, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 5:
                            show_jpeg(DOWN_5, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 6:
                            show_jpeg(DOWN_6, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 7:
                            show_jpeg(DOWN_7, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 8:
                            show_jpeg(DOWN_8, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 9:
                            show_jpeg(DOWN_9, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case POINT:
                            show_jpeg(DOWN_P, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        default:
                            break;
                        }
                        if (passwordposition < PASSWORDLEN - 1)
                        {
                            dispassword[passwordposition] = '*';
                            password[passwordposition++] = 48 + temp;
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                        if (passwordposition == PASSWORDLEN - 1)
                        {
                            ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                    }
                    if (temp == BACK)
                    {
                        show_jpeg(DOWN_BACK, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        up_button(ts_fd);

                        if (passwordposition > 0)
                        {
                            dispassword[--passwordposition] = '\0';
                            password[passwordposition] = '\0';
                        }
                        show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, dispassword, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        continue;
                    }
                    if (y > 0 && y < 240)
                    {
                        DisShowKeyBoardUS(lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                        show_jpeg(USERPASSWORDDISSHOWUP, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                        break;
                    }
                }
            }
            else if (flagp == DISPSW)
            {
                show_jpeg(USERPASSWORDSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                ShowKeyBoardS(lcdinfo);
                ShowFont(lcdinfo, username, 36, 800, 40, 0, 244); // 将获取到的賬號显示在键盘输入框中
                ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的密碼显示在键盘输入框中
                for (;;)                                          // 在键盘上输入数字
                {
                    down_button(ts_fd, &x, &y);
                    temp = GetNumber(x, y);
                    if ((temp >= 0 && temp <= 9) || temp == POINT)
                    {
                        switch (temp) // 获取数字并输入到键盘的输入框中
                        {
                        case 0:
                            show_jpeg(DOWN_0, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 1:
                            show_jpeg(DOWN_1, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 2:
                            show_jpeg(DOWN_2, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 3:
                            show_jpeg(DOWN_3, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 4:
                            show_jpeg(DOWN_4, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 5:
                            show_jpeg(DOWN_5, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 6:
                            show_jpeg(DOWN_6, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 7:
                            show_jpeg(DOWN_7, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 8:
                            show_jpeg(DOWN_8, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case 9:
                            show_jpeg(DOWN_9, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        case POINT:
                            show_jpeg(DOWN_P, 0, 0, lcdinfo);
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                            up_button(ts_fd);
                            show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                            break;
                        default:
                            break;
                        }
                        if (passwordposition < PASSWORDLEN - 1)
                        {
                            dispassword[passwordposition] = '*';
                            password[passwordposition++] = 48 + temp;
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                        if (passwordposition == PASSWORDLEN - 1)
                        {
                            ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        }
                    }
                    if (temp == BACK)
                    {
                        show_jpeg(DOWN_BACK, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        up_button(ts_fd);

                        if (passwordposition > 0)
                        {
                            dispassword[--passwordposition] == '\0';
                            password[passwordposition] = '\0';
                        }
                        show_jpeg(UPKEYBOARD, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, password, 36, 800, 40, 0, 244); // 将获取到的字符显示在键盘输入框中
                        continue;
                    }
                    if (y > 0 && y < 240)
                    {
                        DisShowKeyBoardS(lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                        show_jpeg(USERPASSWORDSHOWUP, 0, 0, lcdinfo);
                        ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                        ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                        break;
                    }
                }
            }
        }
        if (x > 562 && x < 604 && y > 270 && y < 299) // 按下密码是否可见
        {
            flagp = !flagp;
        }
        if (x > 192 && x < 607 && y > 355 && y < 427) // 点击登录
        {
            if (flagp == NODISPSW)
            {
                show_jpeg(USERPASSWORDDISSHOWDOWN, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                up_button(ts_fd);
                show_jpeg(USERPASSWORDDISSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                if (strcmp(username, "1234567890"))
                {
                    unshow_UserError(lcdinfo);
                    // 错误处理
                    for (;;)
                    {
                        down_button(ts_fd, &x, &y);
                        if (x > 216 && x < 546 && y > 335 && y < 415)
                        {
                            show_jpeg(UNSUSERERROR_DOWN, 0, 0, lcdinfo);
                            up_button(ts_fd);
                            Disunshow_UserError(lcdinfo);
                            ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                            ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                            break;
                        }
                    }
                    continue;
                }
                if (strcmp(password, "123456"))
                {
                    unshow_PasswordError(lcdinfo);
                    for (;;)
                    {
                        down_button(ts_fd, &x, &y);
                        if (x > 216 && x < 546 && y > 335 && y < 415)
                        {
                            show_jpeg(UNSPWDERROR_DOWN, 0, 0, lcdinfo);
                            up_button(ts_fd);
                            Disunshow_PasswordError(lcdinfo);
                            ShowFont(lcdinfo, username, 36, 290, 60, 255, 145);    // 將獲取的字符顯示在賬戶列表中
                            ShowFont(lcdinfo, dispassword, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                            break;
                        }
                    }
                    continue;
                }
                ChangeInterface(lcdinfo);
                Callback_InitalInterface(ts_fd, lcdinfo, MainInterface);
            }
            else
            {
                show_jpeg(USERPASSWORDSHOWDOWN, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                up_button(ts_fd);
                show_jpeg(USERPASSWORDSHOWUP, 0, 0, lcdinfo);
                ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                if (strcmp(username, "1234567890"))
                {
                    unshow_UserError(lcdinfo);
                    // 错误处理
                    for (;;)
                    {
                        down_button(ts_fd, &x, &y);
                        if (x > 216 && x < 546 && y > 335 && y < 415)
                        {
                            show_jpeg(SUSERERROR_DOWN, 0, 0, lcdinfo);
                            up_button(ts_fd);
                            Disunshow_UserError(lcdinfo);
                            ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                            ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                            break;
                        }
                    }
                    continue;
                }
                if (strcmp(password, "123456"))
                {
                    unshow_PasswordError(lcdinfo);
                    for (;;)
                    {
                        down_button(ts_fd, &x, &y);
                        if (x > 216 && x < 546 && y > 335 && y < 415)
                        {
                            show_jpeg(SPWDERROR_DOWN, 0, 0, lcdinfo);
                            up_button(ts_fd);
                            Disunshow_PasswordError(lcdinfo);
                            ShowFont(lcdinfo, username, 36, 290, 60, 255, 145); // 將獲取的字符顯示在賬戶列表中
                            ShowFont(lcdinfo, password, 36, 290, 60, 255, 249); // 將獲取的字符顯示在密碼列表中
                            break;
                        }
                    }
                    continue;
                }
                ChangeInterface(lcdinfo);
                Callback_InitalInterface(ts_fd, lcdinfo, MainInterface);
            }
        }
        click_flag = true;
    }

    close(tcp_client_fd); // 关闭套接字
    return;
}

void MainInterface(int ts_fd, lcdinformation *lcdinfo)
{
    int x, y; // 存储点击位置的坐标
    for (;;)
    {
        down_button(ts_fd, &x, &y);
        if (x > 0 && x < 104 && y > 0 && y < 112) // 点击返回
        {
            show_jpeg(SHINTERBA, 0, 0, lcdinfo);
            up_button(ts_fd);
            DisChangeInterface(lcdinfo);
            Callback_InitalInterface(ts_fd, lcdinfo, InterfaceInit);
        }
        if (x > 72 && x < 280 && y > 186 && y < 392) // 点击视频
        {
            show_jpeg(SHINTERVI, 0, 0, lcdinfo);
            up_button(ts_fd);
            MTV(lcdinfo);
            Callback_InitalInterface(ts_fd, lcdinfo, FileForVideo);
        }
        if (x > 401 && x < 729 && y > 183 && y < 266) // 点击图片
        {
            show_jpeg(SHINTERPH, 0, 0, lcdinfo);
            up_button(ts_fd);
            MTP(lcdinfo);
            Callback_InitalInterface(ts_fd, lcdinfo, FileForPicture);
        }
        if (x > 401 && x < 729 && y > 308 && y < 393) // 点击文本文件
        {
            show_jpeg(SHINTERAR, 0, 0, lcdinfo);
            up_button(ts_fd);
            MTA(lcdinfo);
            Callback_InitalInterface(ts_fd, lcdinfo, FileForTXT);
        }
    }
}

void FileForPicture(int ts_fd, lcdinformation *lcdinfo) // 图片界面
{
    cancel_thread();
    int x, y; // 存储点击位置的坐标
    /*****************************************************/
    /*创建TCP客户端接收数据(图片文件)线程*/
    pthread_create(&picture_thread_recv, NULL, picture_receive_thread, (void *)&tcp_client_picture_fd);
    pthread_detach(picture_thread_recv); // 分离线程
    picture_thread_recv_running = 1;
    /*****************************************************/
    for (;;)
    {
        down_button(ts_fd, &x, &y);
        if (x > 0 && x < 104 && y > 0 && y < 112) // 点击返回
        {
            show_jpeg(PUD_BACK, 0, 0, lcdinfo);
            up_button(ts_fd);
            DisMTP(lcdinfo);
            Callback_InitalInterface(ts_fd, lcdinfo, MainInterface);
        }
        if (x > 102 && x < 227 && y > 366 && y < 414) // 点击上传
        {
            show_jpeg(PUD_UPLOAD, 0, 0, lcdinfo);
            up_button(ts_fd);
            show_jpeg(PUD_DEFAULT, 0, 0, lcdinfo);
            ssize_t bytesSent = write(tcp_client_fd, "SetPIC1", sizeof("SetPIC1"));
            if (bytesSent > 0)
            {
                printf("Send Words Success !\n");
            }
            else if (bytesSent == -1)
            {
                perror("Send Words Error !");
            }
            sleep(1);
            picture_send();
        }
        if (x > 541 && x < 669 && y > 366 && y < 414) // 点击下载
        {
            show_jpeg(PUD_DOWNLOAD, 0, 0, lcdinfo);
            up_button(ts_fd);
            show_jpeg(PUD_DEFAULT, 0, 0, lcdinfo);

            ssize_t bytesSent = write(tcp_client_fd, "GetPIC1", sizeof("GetPIC1"));
            if (bytesSent > 0)
            {
                printf("Send Words Success !\n");
            }
            else if (bytesSent == -1)
            {
                perror("Send Words Error !");
            }
        }
    }
}

void FileForVideo(int ts_fd, lcdinformation *lcdinfo) // 视频界面
{
    cancel_thread();
    int x, y; // 存储点击位置的坐标
    /*****************************************************/
    /*创建TCP客户端接收数据(视频文件)线程*/
    pthread_create(&video_thread_recv, NULL, video_receive_thread, (void *)&tcp_client_video_fd);
    pthread_detach(video_thread_recv); // 分离线程
    video_thread_recv_running = 1;
    /*****************************************************/
    for (;;)
    {
        down_button(ts_fd, &x, &y);
        if (x > 0 && x < 104 && y > 0 && y < 112) // 点击返回
        {
            show_jpeg(VUD_BACK, 0, 0, lcdinfo);
            up_button(ts_fd);
            DisMTV(lcdinfo);
            Callback_InitalInterface(ts_fd, lcdinfo, MainInterface);
        }
        if (x > 111 && x < 240 && y > 407 && y < 455) // 点击上传
        {
            show_jpeg(VUD_UPLOAD, 0, 0, lcdinfo);
            up_button(ts_fd);
            show_jpeg(VUD_DEFAULT, 0, 0, lcdinfo);
            ssize_t bytesSent = write(tcp_client_fd, "SetVID1", sizeof("SetVID1"));
            if (bytesSent > 0)
            {
                printf("Send Words Success !\n");
            }
            else if (bytesSent == -1)
            {
                perror("Send Words Error !");
            }
            sleep(1);
            video_send();
        }
        if (x > 552 && x < 680 && y > 407 && y < 455) // 点击下载
        {
            show_jpeg(VUD_DOWNLOAD, 0, 0, lcdinfo);
            up_button(ts_fd);
            show_jpeg(VUD_DEFAULT, 0, 0, lcdinfo);
            ssize_t bytesSent = write(tcp_client_fd, "GetVID1", sizeof("GetVID1"));
            if (bytesSent > 0)
            {
                printf("Send Words Success !\n");
            }
            else if (bytesSent == -1)
            {
                perror("Send Words Error !");
            }
        }
    }
}

void FileForTXT(int ts_fd, lcdinformation *lcdinfo) // 文本界面
{
    cancel_thread();
    int x, y; // 存储点击位置的坐标
    /*****************************************************/
    /*创建TCP客户端接收数据(文本文件)线程*/
    pthread_create(&tcp_client_thread_recv, NULL, tcp_client_receive_thread, (void *)&tcp_client_txt_fd);
    pthread_detach(tcp_client_thread_recv); // 分离线程
    tcp_client_thread_recv_running = 1;
    /*****************************************************/

    for (;;)
    {
        down_button(ts_fd, &x, &y);
        if (x > 0 && x < 104 && y > 0 && y < 112) // 点击返回
        {
            pthread_cancel(tcp_client_thread_recv); // 取消文本线程
            show_jpeg(AUD_BACK, 0, 0, lcdinfo);
            up_button(ts_fd);
            DisMTA(lcdinfo);
            Callback_InitalInterface(ts_fd, lcdinfo, MainInterface);
        }
        if (x > 113 && x < 239 && y > 383 && y < 431) // 点击上传
        {
            show_jpeg(AUD_UPLOAD, 0, 0, lcdinfo);
            up_button(ts_fd);
            show_jpeg(AUD_DEFAULT, 0, 0, lcdinfo);
            ssize_t bytesSent = write(tcp_client_fd, "SetTXT1", sizeof("SetTXT1"));
            if (bytesSent > 0)
            {
                printf("Send Words Success !\n");
            }
            else if (bytesSent == -1)
            {
                perror("Send Words Error !");
            }
            sleep(1);
            test_send();
        }
        if (x > 571 && x < 698 && y > 383 && y < 431) // 点击下载
        {
            show_jpeg(AUD_DOWNLOAD, 0, 0, lcdinfo);
            up_button(ts_fd);
            show_jpeg(AUD_DEFAULT, 0, 0, lcdinfo);

            ssize_t bytesSent = write(tcp_client_fd, "GetTXT1", sizeof("GetTXT1"));
            if (bytesSent > 0)
            {
                printf("Send Words Success !\n");
            }
            else if (bytesSent == -1)
            {
                perror("Send Words Error !");
            }
        }
    }
}

void test_send()
{
    FILE *fp = fopen("./test_client.txt", "r");
    if (fp == NULL)
    {
        perror("Open file error");
        return;
    }
    printf("Open file success !\n");

    // 获取源文件的大小
    fseek(fp, 0L, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // 分配足够内存存储整个文件内容
    char *buffer = calloc(file_size + 1, sizeof(char));
    if (buffer == NULL)
    {
        perror("Memory allocation error Or file is empty");
        fclose(fp);
        return;
    }
    printf("Memory allocation success !\n");

    // 一次性读取整个文件内容到缓冲区中
    size_t bytesRead = fread(buffer, sizeof(char), file_size, fp);
    if (bytesRead != file_size)
    {
        perror("Read file error");
        free(buffer);
        fclose(fp);
        return;
    }
    printf("Read file success !\n");

    if (tcp_client_fd < 0)
    {
        perror("Invalid socket file descriptor !");
        return;
    }
    printf("Valid socket file descriptor !\n");

    // 发送文件内容给服务器
    buffer[file_size] = '\0';
    ssize_t bytesSent = write(tcp_client_txt_fd, buffer, file_size);

    if (bytesSent > 0 && (size_t)bytesSent == file_size)
    {
        printf("Send file success !\n");
    }
    else if (bytesSent == -1)
    {
        perror("Send file error !");
    }
    else
    {
        printf("Incomplete file sent: %ld bytes out of %ld\n", bytesSent, file_size);
    }
    printf("File sent: %ld bytes out of %ld\n", bytesSent, file_size);

    // 释放内存
    free(buffer);
    fclose(fp);
    return;
}

void picture_send()
{
    FILE *fp = fopen("./Data/Picture/updemo.jpg", "rb");
    if (fp == NULL)
    {
        perror("Open file error");
        return;
    }
    printf("Open file success !\n");

    // 获取源文件的大小
    fseek(fp, 0L, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // 分配足够内存存储整个文件内容
    char *buffer = calloc(file_size + 1, sizeof(char));
    if (buffer == NULL)
    {
        perror("Memory allocation error Or file is empty");
        fclose(fp);
        return;
    }
    printf("Memory allocation success !\n");

    // 一次性读取整个文件内容到缓冲区中
    size_t bytesRead = fread(buffer, sizeof(char), file_size, fp);
    if (bytesRead != file_size)
    {
        perror("Read file error");
        free(buffer);
        fclose(fp);
        return;
    }
    printf("Read file success !\n");

    if (tcp_client_picture_fd < 0)
    {
        perror("Invalid socket file descriptor !");
        return;
    }
    printf("Valid socket file descriptor !\n");

    // 发送文件内容给服务器
    buffer[file_size] = '\0';
    if (write(tcp_client_picture_fd, buffer, file_size) > 0)
    {
        printf("Send Picture Success !\n");
    }
    else
    {
        perror("Send Picture Error !");
    }

    // 释放内存
    free(buffer);
    fclose(fp);
    return;
}

void video_send()
{
    FILE *fp = fopen("./Data/Video/updemo.mp4", "rb");
    if (fp == NULL)
    {
        perror("Open file error");
        return;
    }
    printf("Open file success !\n");

    // 获取源文件的大小
    fseek(fp, 0L, SEEK_END);
    long long file_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // 分配足够内存存储整个文件内容
    char *buffer = calloc(file_size + 1, sizeof(char));
    if (buffer == NULL)
    {
        perror("Memory allocation error Or file is empty");
        fclose(fp);
        return;
    }
    printf("Memory allocation success !\n");

    // 一次性读取整个文件内容到缓冲区中
    size_t bytesRead = fread(buffer, sizeof(char), file_size, fp);
    if (bytesRead != file_size)
    {
        perror("Read file error");
        free(buffer);
        fclose(fp);
        return;
    }
    printf("Read file success !\n");

    if (tcp_client_video_fd < 0)
    {
        perror("Invalid socket file descriptor !");
        return;
    }
    printf("Valid socket file descriptor !\n");

    // 发送文件内容给服务器
    buffer[file_size] = '\0';
    if (write(tcp_client_video_fd, buffer, file_size) > 0)
    {
        printf("Send Video Success !\n");
    }
    else
    {
        perror("Send Video Error !");
    }

    // 释放内存
    free(buffer);
    fclose(fp);
    return;
}

void cancel_thread()
{
    if (tcp_client_thread_recv_running)
    {
        pthread_cancel(tcp_client_thread_recv);
        tcp_client_thread_recv_running = 0;
    }
    if (picture_thread_recv_running)
    {
        pthread_cancel(picture_thread_recv);
        picture_thread_recv_running = 0;
    }
    if(video_thread_recv_running)
    {
        pthread_cancel(video_thread_recv);
        video_thread_recv_running = 0;
    }
}