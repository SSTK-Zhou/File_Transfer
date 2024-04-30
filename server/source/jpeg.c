#include "main.h"

/***********************************************************
 *   函数名称：get_information_jpeg
 *   函数作用：获取jpeg图片信息
 *   函数参数：
 *           @road : 指的是jpeg图片路径
 *           @jpeginfo : 指的是JPEG图片的结构体
 *   返回结果：jpegdata字符型数组，即整张JPEG的信息
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：使用该函数需要在外解压JPEG数据解码包
 *************************************************************/
char *get_information_jpeg(const char *road, jpeginformation *jpeginfo)
{
    if (-1 == fseek(jpeginfo->fp, 0, SEEK_END))
    {
        perror("Fseek End Of Picture Error");
        exit(1);
    }
    jpeginfo->jpgsize = ftell(jpeginfo->fp); /*告知当前文件位置指示器的偏移量*/
    if (-1 == jpeginfo->jpgsize)
    {
        perror("Ftell For jpegsize Error");
        exit(1);
    }
    if (-1 == fseek(jpeginfo->fp, 0, SEEK_SET))
    {
        perror("Fseek Set Of Picture Error");
        exit(1);
    }
    //printf("该图片的大小为：%d\n", jpeginfo->jpgsize);

    char *jpegdata = malloc(jpeginfo->jpgsize);

    while (1)
    {
        int n_read = fread(jpegdata, jpeginfo->jpgsize, 1, jpeginfo->fp);
        if (n_read == 1)
            continue;
        else if (n_read < 1)
        {
            if (feof)
                break;
            else if (ferror)
            {
                perror("图片读取失败");
                fclose(jpeginfo->fp);
                free(jpegdata);
                exit(1);
            }
        }
    }

    return jpegdata;
}

/************************************************************
 *   函数名称：jpg2rgb
 *   函数作用：JPEG图片解码
 *   函数参数：
 *           @jpgdata：从get_information_jpeg返回的JPEG数据
 *           @jpgsize：JPEG图片的尺寸
 *           @ p：搭载JPEG结构体信息的指针
 *   返回结果：NULL
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：暂无
 ************************************************************/
void jpg2rgb(const char *jpgdata, size_t jpgsize, jpeginformation *p)
{
    // 1，声明解码结构体，以及错误管理结构体
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // 2，使用缺省的出错处理来初始化解码结构体
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 3，配置该cinfo，使其从 jpgdata 中读取jpgsize个字节
    //    这些数据必须是完整的JPEG数据
    jpeg_mem_src(&cinfo, jpgdata, jpgsize);

    // 4，读取JPEG文件的头，并判断其格式是否合法
    if (!jpeg_read_header(&cinfo, true))
    {
        fprintf(stderr, "jpeg_read_header failed: "
                        "%s\n",
                strerror(errno));
        return;
    }

    // 5，开始解码
    jpeg_start_decompress(&cinfo);

    // 6，获取图片的尺寸信息
    p->width = cinfo.output_width;
    p->height = cinfo.output_height;
    p->bpp = cinfo.output_components * 8;

    // 7，根据图片的尺寸大小，分配一块相应的内存rgbdata
    //    用来存放从jpgdata解码出来的图像数据
    unsigned long linesize = cinfo.output_width * cinfo.output_components;
    unsigned long rgbsize = linesize * cinfo.output_height;
    p->RGB = calloc(1, rgbsize);

    // 8，循环地将图片的每一行读出并解码到rgb_buffer中
    int line = 0;
    while (cinfo.output_scanline < cinfo.output_height)
    {
        unsigned char *buffer_array[1];
        buffer_array[0] = p->RGB + cinfo.output_scanline * linesize;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    // 9，解码完了，将jpeg相关的资源释放掉
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return;
}

/************************************************************
 *   函数名称：show_jpeg
 *   函数作用：在开发板上展示JPEG图片
 *   函数参数：
 *           @road：图片路径
 *           @x：图片起始位置所在的x坐标轴
 *           @y：图片起始位置所在的y坐标轴
 *           @lcdinfo：
 *   返回结果：NULL
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：图片大小以及图片偏移位置不宜超过lcd显示屏
 ************************************************************/
void show_jpeg(const char *road, int x, int y, lcdinformation *lcdinfo)
{
    jpeginformation jpeginfo;

    jpeginfo.fp = fopen(road, "r"); // fopen(文件名，读取文件方式)

    if(lcdinfo == NULL)
    {
        perror("Lcd Open error");
        return;
    }

    if (jpeginfo.fp == NULL)
    {
        perror("图片打开失败");
        fclose(jpeginfo.fp);
        exit(1);
    }
    char *jpegdata = get_information_jpeg(road, &jpeginfo);
    jpg2rgb(jpegdata, jpeginfo.jpgsize, &jpeginfo);
    //printf("图片的高度为：%d\n图片的宽度为：%d\n", jpeginfo.height, jpeginfo.width);

    char *input_image = lcdinfo->fbm + lcdinfo->width * (lcdinfo->bpp / 8) * y + x * lcdinfo->bpp / 8;
    int i, j;

    for (j = 0; j < jpeginfo.height && j < lcdinfo->height; j++)
    {
        int jpegoffset = j * jpeginfo.width * jpeginfo.bpp / 8;
        int lcdoffset = j * lcdinfo->width * lcdinfo->bpp / 8;
        for (i = 0; i < jpeginfo.width && i < lcdinfo->width; i++)
        {
            memcpy(input_image + i * 4 + lcdoffset + 0, jpeginfo.RGB + i * 3 + jpegoffset + 2, 1);
            memcpy(input_image + i * 4 + lcdoffset + 1, jpeginfo.RGB + i * 3 + jpegoffset + 1, 1);
            memcpy(input_image + i * 4 + lcdoffset + 2, jpeginfo.RGB + i * 3 + jpegoffset + 0, 1);
        }
    }
    fclose(jpeginfo.fp);
    free(jpegdata);
    free(jpeginfo.RGB);
}