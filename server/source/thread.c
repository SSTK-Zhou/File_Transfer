#include "main.h"

void *tcp_client_receive_thread(void *arg)
{
    // 1.创建TCP套接字 通信对象
    int socket_fd = *(int *)arg;

    // 3.下载数据
    for (;;)
    {
        pthread_testcancel(); // 检查取消请求
        char *recvbuf = calloc(1024 * 1024, sizeof(char)); // 分配一个接收缓冲区
        if(recvbuf == NULL)
        {
            perror("Memory Allocation Failed!");
            exit(-1);
        }
        if (read(socket_fd, recvbuf, 1024 * 1024) > 0)    // 读取数据
        {
            /*将读取到的数据创建一个文件存入*/
            FILE *fp = fopen("./Data/Article/recv_file.txt", "w+"); // 创建一个文件
            if (fp == NULL)
            {
                perror("File open error");
                exit(-1);
            }
            fwrite(recvbuf, sizeof(char), strlen(recvbuf), fp); // 将数据写入文件
            fclose(fp);                                         // 关闭文件
            memset(recvbuf, 0, sizeof(recvbuf));                // 清空接收缓冲区
            free(recvbuf);                                      // 释放接收缓冲区
        }
    }
    printf("Download TXT File Success!\n");
    return NULL;
}

void *picture_receive_thread(void *arg)
{
    // 1.创建TCP套接字 通信对象
    int socket_fd = *(int *)arg;

    // 3.下载数据
    for (;;)
    {
        pthread_testcancel(); // 检查取消请求
        char *recvbuf = calloc(1024 * 1024, sizeof(char)); // 分配一个接收缓冲区
        if(recvbuf == NULL)
        {
            perror("Memory Allocation Failed!");
            exit(-1);
        }
        if (read(socket_fd, recvbuf, 1024 * 1024) > 0)    // 读取数据
        {
            /*将读取到的数据创建一个文件存入*/
            FILE *fp = fopen("./Data/Picture/downdemo.jpg", "ab"); // 创建一个文件
            if (fp == NULL)
            {
                perror("File open error");
                exit(-1);
            }
            fwrite(recvbuf, sizeof(char), strlen(recvbuf), fp); // 将数据写入文件
            fclose(fp);                                         // 关闭文件
            memset(recvbuf, 0, sizeof(recvbuf));                // 清空接收缓冲区
            free(recvbuf);                                      // 释放接收缓冲区
        }
    }
    printf("Download Picture Success!\n");
    return NULL;
}

void *video_receive_thread(void *arg)
{
       // 1.创建TCP套接字 通信对象
    int socket_fd = *(int *)arg;

    // 3.下载数据
    for (;;)
    {
        pthread_testcancel(); // 检查取消请求
        char *recvbuf = calloc(1024 * 1024, sizeof(char)); // 分配一个接收缓冲区
        if(recvbuf == NULL)
        {
            perror("Memory Allocation Failed!");
            exit(-1);
        }
        if (read(socket_fd, recvbuf, 1024 * 1024) > 0)    // 读取数据
        {
            /*将读取到的数据创建一个文件存入*/
            FILE *fp = fopen("./Data/Video/downdemo.mp4", "ab"); // 以追加二进制形式创建一个文件
            if (fp == NULL)
            {
                perror("File open error");
                exit(-1);
            }
            fwrite(recvbuf, sizeof(char), strlen(recvbuf), fp); // 将数据写入文件
            fclose(fp);                                         // 关闭文件
            memset(recvbuf, 0, sizeof(recvbuf));                // 清空接收缓冲区
            free(recvbuf);                                      // 释放接收缓冲区
        }
    }
    printf("Download Picture Success!\n");
    return NULL;
}