#include "main.h"

int tcp_client_fd = -1;         // tcp客户端套接字
int tcp_client_txt_fd = -1;     // tcp客户端文本套接字
int tcp_client_picture_fd = -1; // tcp客户端图片套接字
int tcp_client_video_fd = -1;   // tcp客户端视频套接字

struct sockaddr_in server_address;

void client_cmd() // 专门发送命令的客户端
{
    sleep(1); // 延时以确保服务器代码运行至有效处
    /*创建TCP客户端发送数据*/
    // 1. 创建TCP套接字
    tcp_client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client_fd < 0)
    {
        perror("Create socket error");
        exit(1);
    }
    printf("Create Socket For Client -> Server Success !\n");
    printf("tcp_client_fd = %d\n", tcp_client_fd);

    // 使用套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_client_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("setsockopt default");
        exit(1);
    }

    // 2.连接TCP 服务器
    server_address.sin_family = AF_INET;                   // 网络通信
    server_address.sin_port = htons(HTONS);                // 服务器端口
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP); // 服务器IP
    int ret = connect(tcp_client_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret < 0)
    {
        perror("Connect Server_cmd Failed!");
        exit(-1);
    }
    else
        printf("Connect Server_cmd Success!\n");
}

void client_txt() // 专门发送文本的客户端
{
    sleep(1); // 延时以确保服务器代码运行至有效处
    /*创建TCP客户端发送数据*/
    // 1. 创建TCP套接字
    tcp_client_txt_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client_txt_fd < 0)
    {
        perror("Create socket error");
        exit(1);
    }
    printf("Create Socket For Client -> Server Success !\n");
    printf("tcp_client_txt_fd = %d\n", tcp_client_txt_fd);

    // 使用套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_client_txt_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("setsockopt default");
        exit(1);
    }

    // 2.连接TCP 服务器
    server_address.sin_family = AF_INET;                   // 网络通信
    server_address.sin_port = htons(HTONS1);               // 服务器端口
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP); // 服务器IP
    int ret = connect(tcp_client_txt_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret < 0)
    {
        perror("Connect Server_txt Failed!");
        exit(-1);
    }
    else
        printf("Connect Server_txt Success!\n");
}

void client_picture() // 专门发送图片的客户端
{
    sleep(1); // 延时以确保服务器代码运行至有效处
    /*创建TCP客户端发送数据*/
    // 1. 创建TCP套接字
    tcp_client_picture_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client_picture_fd < 0)
    {
        perror("Create socket error");
        exit(1);
    }
    printf("Create Socket For Client -> Server Success !\n");
    printf("tcp_client_picture_fd = %d\n", tcp_client_picture_fd);

    // 使用套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_client_picture_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("setsockopt default");
        exit(1);
    }

    // 2.连接TCP 服务器
    server_address.sin_family = AF_INET;                   // 网络通信
    server_address.sin_port = htons(HTONS2);               // 服务器端口
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP); // 服务器IP
    int ret = connect(tcp_client_picture_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret < 0)
    {
        perror("Connect Server_pic Failed!");
        exit(-1);
    }
    else
        printf("Connect Server_pic Success!\n");
}

void client_video() // 专门发送视频的客户端
{
    sleep(1); // 延时以确保服务器代码运行至有效处
    /*创建TCP客户端发送数据*/
    // 1. 创建TCP套接字
    tcp_client_video_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_client_video_fd < 0)
    {
        perror("Create socket error");
        exit(1);
    }
    printf("Create Socket For Client -> Server Success !\n");
    printf("tcp_client_video_fd = %d\n", tcp_client_video_fd);

    // 使用套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_client_video_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("setsockopt default");
        exit(1);
    }

    // 2.连接TCP 服务器
    server_address.sin_family = AF_INET;                   // 网络通信
    server_address.sin_port = htons(HTONS3);               // 服务器端口
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP); // 服务器IP
    int ret = connect(tcp_client_video_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret < 0)
    {
        perror("Connect Server_pic Failed!");
        exit(-1);
    }
    else
        printf("Connect Server_pic Success!\n");
}