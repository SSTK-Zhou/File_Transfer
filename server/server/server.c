#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <stdbool.h>

#define HTONS 8888                 // 网络字节序转换宏
#define HTONS1 5432                // 网络字节序转换宏
#define HTONS2 1234                // 网络字节序转换宏
#define HTONS3 1245                // 网络字节序转换宏
#define SERVER_IP "192.168.171.6"  // 服务器IP地址
#define CLIENT_IP "192.168.171.11" // 客户端IP地址

pthread_t tidr; // 接收数据的线程
pthread_t txt;  // 接收文本的线程
pthread_t pic;  // 接收图片的线程
pthread_t vid;  // 接收视频的线程

int tcp_socket = -1; // 服务器socket
int client_fd = -1;  // 客户端socket

int tcp_txt_socket = -1; // 文本服务器socket
int client_txt_fd = -1;  // 文本客户端socket

int tcp_pic_socket = -1; // 图片服务器socket
int client_pic_fd = -1;  // 图片客户端socket

int tcp_vid_socket = -1; // 视频服务器socket
int client_vid_fd = -1;  // 视频客户端socket

bool flag_txt = false; // 文本线程标志位
bool flag_pic = false; // 图片线程标志位
bool flag_vid = false; // 视频线程标志位

int recv_Cmd(); // 声明接受命令的服务器，以便main函数调用
int recv_Txt(); // 声明接受文本的服务器，以便main函数调用
int recv_Pic(); // 声明接受图片的服务器，以便main函数调用
int recv_Vid(); // 声明接受视频的服务器，以便main函数调用

void test_send()
{
    FILE *fp = fopen("./send_file.txt", "r");
    if (NULL == fp)
    {
        perror("Open File Error");
        exit(1);
    }
    printf("Open File Successfully !\n");
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 分配足够内存存储整个文件内容
    char *file_buf = calloc(file_size + 1, sizeof(char));
    if (file_buf == NULL)
    {
        perror("Calloc Error Or End of File");
        fclose(fp);
        return;
    }

    // 一次性读取整个文件内容到缓冲区
    size_t byteRead = fread(file_buf, sizeof(char), file_size, fp);
    if (byteRead != file_size)
    {
        perror("Read File Error");
        free(file_buf);
        fclose(fp);
        return;
    }
    // 发送文件内容给客户端
    file_buf[file_size] = '\0';
    if (write(client_txt_fd, file_buf, file_size) > 0)
    {
        printf("Send File Success\n");
    }
    else
    {
        perror("Send File Error");
    }

    // 释放资源
    free(file_buf);
    fclose(fp);
    return;
}

void picture_send()
{
    FILE *fp = fopen("./downdemo.jpg", "rb");
    if (NULL == fp)
    {
        perror("Open Picture Error");
        exit(1);
    }
    printf("Open Picture Successfully !\n");
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 分配足够内存存储整个文件内容
    char *file_buf = calloc(file_size + 1, sizeof(char));
    if (file_buf == NULL)
    {
        perror("Calloc Error Or End of Picture");
        fclose(fp);
        return;
    }

    // 一次性读取整个文件内容到缓冲区
    size_t byteRead = fread(file_buf, sizeof(char), file_size, fp);
    if (byteRead != file_size)
    {
        perror("Read Picture Error");
        free(file_buf);
        fclose(fp);
        return;
    }
    // 发送文件内容给客户端
    file_buf[file_size] = '\0';
    if (write(client_pic_fd, file_buf, file_size) > 0)
    {
        printf("Send Picture Success\n");
    }
    else
    {
        perror("Send Picture Error");
    }

    // 释放资源
    free(file_buf);
    fclose(fp);
    return;
}

void video_send()
{
    FILE *fp = fopen("./../data/video/downdemo.mp4", "rb");
    if (NULL == fp)
    {
        perror("Open Video Error");
        exit(1);
    }
    printf("Open Video Successfully !\n");
    fseek(fp, 0, SEEK_END);
    long long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // 分配足够内存存储整个文件内容
    char *file_buf = calloc(file_size + 1, sizeof(char));
    if (file_buf == NULL)
    {
        perror("Calloc Error Or End of Video");
        fclose(fp);
        return;
    }
    // 一次性读取整个文件内容到缓冲区
    size_t byteRead = fread(file_buf, sizeof(char), file_size, fp);
    if (byteRead != file_size)
    {
        perror("Read Picture Error");
        free(file_buf);
        fclose(fp);
        return;
    }
    // 发送文件内容给客户端
    file_buf[file_size] = '\0';
    if (write(client_vid_fd, file_buf, file_size) > 0)
    {
        printf("Send Picture Success\n");
    }
    else
    {
        perror("Send Picture Error");
    }

    // 释放资源
    free(file_buf);
    fclose(fp);
    return;
}

void *recv_txt(void *arg)
{
    int socket_fd = *(int *)arg;

    for (;;)
    {
        pthread_testcancel(); // 检查取消请求
        char *recv_buf = calloc(1024 * 1024, sizeof(char));
        ssize_t bytes_read2 = read(socket_fd, recv_buf, 1024 * 1024);
        if (recv_buf == NULL)
        {
            perror("Calloc Error");
        }

        if (bytes_read2 > 0)
        {
            /*将读取到的数据创建一个文件存入(相当于粘贴文档)*/
            FILE *fp = fopen("./../data/article/test_client.txt", "w+");
            if (fp == NULL)
            {
                perror("Open File Error");
                exit(1);
            }
            fwrite(recv_buf, sizeof(char), bytes_read2, fp); // 将数据写入文件
            fclose(fp);                                      // 关闭文件
            memset(recv_buf, 0, sizeof(recv_buf));           // 清空接收缓冲区
            free(recv_buf);                                  // 释放接收缓冲区
        }
        else if (bytes_read2 == 0)
        {
            printf("Client Close\n");
        }
        else
        {
            perror("Read File Error");
            free(recv_buf);
        }
    }
    return NULL;
}

void *recv_pic(void *arg)
{
    int socket_fd = *(int *)arg;
    for (;;)
    {
        pthread_testcancel(); // 检查取消请求
        char *recv_buf = calloc(1024 * 1024, sizeof(char));
        if (recv_buf == NULL)
        {
            perror("Calloc Error");
            close(socket_fd);
            close(client_vid_fd);
            return NULL;
        }
        ssize_t bytes_read2 = read(socket_fd, recv_buf, 1024 * 1024);
        if (bytes_read2 > 0)
        {
            /*将读取到的数据创建一个文件存入(相当于粘贴文档)*/
            FILE *fp = fopen("./../data/picture/updemo.jpg", "ab"); // 以追加二进制模式的方式传输图片
            if (fp == NULL)
            {
                perror("Open File Error");
                exit(1);
            }
            fwrite(recv_buf, sizeof(char), bytes_read2, fp); // 将数据写入文件
            fclose(fp);                                      // 关闭文件
            memset(recv_buf, 0, sizeof(recv_buf));           // 清空接收缓冲区
            free(recv_buf);                                  // 释放接收缓冲区
        }
        else if (bytes_read2 == 0)
        {
            printf("Client Close\n");
        }
        else
        {
            perror("Read Picture Error");
            free(recv_buf);
        }
    }
    return NULL;
}

void *recv_vid(void *arg)
{
    int socket_fd = *(int *)arg;
    for (;;)
    {
        pthread_testcancel(); // 检查取消请求
        char *recv_buf = calloc(1024 * 1024, sizeof(char));
        if (recv_buf == NULL)
        {
            perror("Calloc Error");
            close(socket_fd);
            close(client_vid_fd);
            return NULL;
        }
        ssize_t bytes_read2 = read(socket_fd, recv_buf, 1024 * 1024);
        if (bytes_read2 > 0)
        {
            /*将读取到的数据创建一个文件存入(相当于粘贴文档)*/
            FILE *fp = fopen("./../data/video/updemo.mp4", "ab"); // 以追加二进制模式的方式传输图片
            if (fp == NULL)
            {
                perror("Open File Error");
                exit(1);
            }
            fwrite(recv_buf, sizeof(char), bytes_read2, fp); // 将数据写入文件
            fclose(fp);                                      // 关闭文件
            memset(recv_buf, 0, sizeof(recv_buf));           // 清空接收缓冲区
            free(recv_buf);                                  // 释放接收缓冲区
        }
        else if (bytes_read2 == 0)
        {
            printf("Client Close\n");
        }
        else
        {
            perror("Read Picture Error");
            free(recv_buf);
        }
    }
    return NULL;
}

void *recv_data(void *arg)
{
    int socket_fd = *(int *)arg;

    for (;;)
    {
        // 客户端套接字有数据可读
        char *recv_buf = calloc(1024 * 1024, sizeof(char));
        if (recv_buf == NULL)
        {
            perror("Calloc Error");
        }
        ssize_t bytes_read1 = read(socket_fd, recv_buf, 1024 * 1024);
        if (bytes_read1 == -1)
        {
            perror("Read File Error");
            free(recv_buf);
            close(socket_fd);
            close(client_fd);
            return NULL;
        }
        else if (bytes_read1 == 0)
        {
            printf("Client Close\n");
            free(recv_buf);
            close(socket_fd);
            close(client_fd);
            return NULL;
        }
        if (!strcmp(recv_buf, "GetTXT1")) // 从服务器下载文本文件
        {
            printf("Download .txt\n");
            memset(recv_buf, 0, sizeof(recv_buf)); // 清空接收缓冲区
            test_send();
        }
        if (!strcmp(recv_buf, "GetPIC1")) // 从服务器下载图片文件
        {
            printf("Download .jpg\n");
            memset(recv_buf, 0, sizeof(recv_buf)); // 清空接收缓冲区
            picture_send();
        }
        if (!strcmp(recv_buf, "GetVID1")) // 从服务器下载视频文件
        {
            printf("Download .mp4\n");
            memset(recv_buf, 0, sizeof(recv_buf)); // 清空接收缓冲区
            video_send();
        }
        if (!strcmp(recv_buf, "SetTXT1")) // 从开发板上传文本文件
        {
            if (flag_txt)
            {
                pthread_cancel(txt);
                flag_txt = false;
            }
            printf("Upload .txt\n");
            memset(recv_buf, 0, sizeof(recv_buf)); // 清空接收缓冲区
            /**************************************************/
            // 创建一个线程用于接收数据
            if (pthread_create(&txt, NULL, recv_txt, (void *)&client_txt_fd) != 0)
            {
                perror("Create Thread Error");
                close(socket_fd);
                close(client_txt_fd);
                return NULL;
            }
            pthread_detach(txt); // 分离线程，避免资源泄漏
            flag_txt = true;
            /**************************************************/
            continue;
        }
        if (!strcmp(recv_buf, "SetPIC1")) // 从开发板上传图片文件
        {
            if (flag_pic)
            {
                pthread_cancel(pic);
                flag_pic = false;
            }
            printf("Upload .jpg\n");
            memset(recv_buf, 0, sizeof(recv_buf)); // 清空接收缓冲区
            /**************************************************/
            // 创建一个线程用于接收数据
            if (pthread_create(&pic, NULL, recv_pic, (void *)&client_pic_fd) != 0)
            {
                perror("Create Thread Error");
                close(socket_fd);
                close(client_pic_fd);
                return NULL;
            }
            pthread_detach(pic); // 分离线程，避免资源泄漏
            flag_pic = true;
            /**************************************************/
            continue;
        }
        if (!strcmp(recv_buf, "SetVID1")) // 从开发板上传视频文件
        {
            if (flag_vid)
            {
                pthread_cancel(vid);
                flag_vid = false;
            }
            printf("Upload .mp4\n");
            memset(recv_buf, 0, sizeof(recv_buf)); // 清空接收缓冲区
            /**************************************************/
            // 创建一个线程用于接收数据
            if (pthread_create(&pic, NULL, recv_vid, (void *)&client_vid_fd) != 0)
            {
                perror("Create Thread Error");
                close(socket_fd);
                close(client_vid_fd);
                return NULL;
            }
            pthread_detach(vid); // 分离线程，避免资源泄漏
            flag_pic = true;
            /**************************************************/
            continue;
        }
    }
    printf("Recv Data Over\n");
    return NULL;
}

int main()
{

    if (-1 == recv_Cmd())
    {
        printf("Error For recv_cmd\n");
        return -1;
    }
    if (-1 == recv_Txt())
    {
        printf("Error For recv_txt\n");
        return -1;
    }
    if (-1 == recv_Pic())
    {
        printf("Error For recv_pic\n");
        return -1;
    }
    if (-1 == recv_Vid())
    {
        printf("Error For recv_vid\n");
        return -1;
    }

    /**************************************************/
    // 创建一个线程用于接收数据
    if (pthread_create(&tidr, NULL, recv_data, (void *)&client_fd) != 0)
    {
        perror("Create Thread Error");
        close(tcp_socket);
        close(client_fd);
        return -1;
    }
    pthread_detach(tidr); // 分离线程，避免资源泄漏
    /**************************************************/

    for (;;)
    {
    }

    close(tcp_socket);
    return 0;
}

// 创建接收命令的服务器
int recv_Cmd()
{
    // 1. 创建TCP 服务器
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0)
    {
        perror("Socket Creation Error");
        return -1;
    }
    else
        printf("Socket Created Successfully !\n");

    // 使套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("Setsockopt Default");
        close(tcp_socket);
        return -1;
    }
    printf("Setsockopt Default Successfully !\n");

    // 2. 绑定IP和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(HTONS);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(tcp_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("Bind Error");
        close(tcp_socket);
        return -1;
    }
    printf("Bind Successfully !\n");

    // 3. 设置为监听模式
    if (listen(tcp_socket, 10) < 0)
    {
        perror("Listen Error");
        close(tcp_socket);
        return -1;
    }
    printf("Listen Successfully !\n");

    // 4. 接收客户端连接
    client_fd = accept(tcp_socket, NULL, NULL);
    if (client_fd < 0)
    {
        perror("Accept Error");
        close(tcp_socket);
        return -1;
    }
    else
    {
        printf("Accept Success\n");
    }
}

// 专门处理文章的服务器
int recv_Txt()
{
    // 1. 创建TCP 服务器
    tcp_txt_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_txt_socket < 0)
    {
        perror("Socket Creation Error");
        return -1;
    }
    else
        printf("Socket Created Successfully !\n");

    // 使套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_txt_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("Setsockopt Default");
        close(tcp_txt_socket);
        return -1;
    }
    printf("Setsockopt Default Successfully !\n");

    // 2. 绑定IP和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(HTONS1);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(tcp_txt_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("Bind Error");
        close(tcp_txt_socket);
        return -1;
    }
    printf("Bind Successfully !\n");

    // 3. 设置为监听模式
    if (listen(tcp_txt_socket, 10) < 0)
    {
        perror("Listen Error");
        close(tcp_txt_socket);
        return -1;
    }
    printf("Listen Successfully !\n");

    // 4. 接收客户端连接
    client_txt_fd = accept(tcp_txt_socket, NULL, NULL);
    if (client_txt_fd < 0)
    {
        perror("Accept Error");
        close(tcp_txt_socket);
        return -1;
    }
    else
    {
        printf("Accept Success\n");
    }
}

int recv_Pic() // 处理图片的服务器
{
    // 1. 创建TCP 服务器
    tcp_pic_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_pic_socket < 0)
    {
        perror("Socket Creation Error");
        return -1;
    }
    else
        printf("Socket Created Successfully !\n");

    // 使套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_pic_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("Setsockopt Default");
        close(tcp_pic_socket);
        return -1;
    }
    printf("Setsockopt Default Successfully !\n");

    // 2. 绑定IP和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(HTONS2);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(tcp_pic_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("Bind Error");
        close(tcp_pic_socket);
        return -1;
    }
    printf("Bind Successfully !\n");

    // 3. 设置为监听模式
    if (listen(tcp_pic_socket, 10) < 0)
    {
        perror("Listen Error");
        close(tcp_pic_socket);
        return -1;
    }
    printf("Listen Successfully !\n");

    // 4. 接收客户端连接
    client_pic_fd = accept(tcp_pic_socket, NULL, NULL);
    if (client_pic_fd < 0)
    {
        perror("Accept Error");
        close(tcp_pic_socket);
        return -1;
    }
    else
    {
        printf("Accept Success\n");
    }
}

int recv_Vid() // 处理视频的服务器
{
    // 1. 创建TCP 服务器
    tcp_vid_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_vid_socket < 0)
    {
        perror("Socket Creation Error");
        return -1;
    }
    else
        printf("Socket Created Successfully !\n");

    // 使套接字sockfd关联的地址在套接字关闭后立即释放
    int on = 1;
    if (setsockopt(tcp_vid_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("Setsockopt Default");
        close(tcp_vid_socket);
        return -1;
    }
    printf("Setsockopt Default Successfully !\n");

    // 2. 绑定IP和端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(HTONS3);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(tcp_vid_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("Bind Error");
        close(tcp_vid_socket);
        return -1;
    }
    printf("Bind Successfully !\n");

    // 3. 设置为监听模式
    if (listen(tcp_vid_socket, 10) < 0)
    {
        perror("Listen Error");
        close(tcp_vid_socket);
        return -1;
    }
    printf("Listen Successfully !\n");

    // 4. 接收客户端连接
    client_vid_fd = accept(tcp_vid_socket, NULL, NULL);
    if (client_vid_fd < 0)
    {
        perror("Accept Error");
        close(tcp_vid_socket);
        return -1;
    }
    else
    {
        printf("Accept Success\n");
    }
}