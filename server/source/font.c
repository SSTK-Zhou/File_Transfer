#include "main.h"

/***********************************************************
 *   函数名称：ShowFont
 *   函数作用：在开发板上显示字体
 *   函数参数：
 *           @lcd : lcd显示屏信息
 *           @buf : 要显示的字符
 * 			 @size : 要显示的字体大小
 * 			 @width : 画板的宽度
 * 			 @height : 画板的高度
 * 			 @x : 画板起始位置的x轴
 * 			 @y : 画板起始位置的y轴
 *   返回结果：NULL
 *   函数作者：
 *   修改日期：2024/02/24
 *   修改版本：V1.0
 *   注意事项：画板的位置不可以超出屏幕外，字体也应该在画板内
 *************************************************************/
void ShowFont(lcdinformation *lcd, char buf[], int size, int width, int height, int x, int y)
{
	// 打开字体
	font *f = fontLoad("/usr/share/fonts/DroidSansFallback.ttf");
	
	// 字体大小的设置
	fontSetSize(f, size);
	
	// 创建一个画板（点阵图）
	bitmap *bm = createBitmapWithInit(width, height, 4, getColor(0, 255, 255, 255)); // 也可使用createBitmapWithInit函数，改变画板颜色
	// bitmap *bm = createBitmap(288, 100, 4);
	
	// 将字体写到点阵图上
	fontPrint(f, bm, 0, 0, buf, getColor(0, 255, 0, 0), 0);
	
	// 把字体框输出到LCD屏幕上
	show_font_to_lcd(lcd->fbm, x, y, bm);

	// 关闭字体，关闭画板
	fontUnload(f);
	destroyBitmap(bm);
}