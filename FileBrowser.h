#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "my_Button.h"

class FileBrowser
{
/// <summary>
/// 该自定义类中，全部变量变量设为私有，所有get函数获取到的是变量的内容，而非指针。
/// </summary>
public:
	FileBrowser();
	unsigned int GetDataIndex();
	unsigned int GetDataPage();
	unsigned int GetRowNum();
	unsigned int GetTotalPages();
	void SetDataIndex(int index);
	void SetDataPage(int page);
	bool IsHomePage();
	bool IsEndPage();
	void FlushDataIndex();

	void LoadDataFileName(const char* filename);
	void RenderFileBrowser(hiex::Canvas& canvas);
	int InWhichButton(ExMessage msg);

	void LoadData(ExMessage msg);
	void DrawDataInfo(hiex::Canvas& canvas);

	~FileBrowser();

public:
	static const unsigned short txt_height = 24;			///<-文字高度
	static const unsigned short txt_width = 9;				///<-文字宽度，与文字高度和字体有关
	static const unsigned short data_btn_height = 40;		///<-数据文件按钮显示的高度

private:
	static const unsigned int row_num = (WINDOW_HEI * (1 - EX_LEFT) - 140) / data_btn_height;		///<-每页可显示的行数，140为安全边距
	bool isStartToLoad = true;																		///<-是否开始加载
	static const int max_len = (WINDOW_WID * (MID_LEFT - EX_LEFT) - 30) / txt_width;				///<-每行可显示的字数，30为安全边距（仍有设计上的bug）
	unsigned int data_page = 0;																		///<-当前页数
	unsigned int data_index = data_page * row_num;													///<-当前数据文件的索引
	unsigned int data_len;																			///<-文件总个数
	unsigned int page_num;																			///<-总页数
	dataInfo info;																					///<-数据信息

	char buf1[MAX_LEN];					///<-一级缓冲区，加载数据时使用。通过 WinAPI 从 Windows 资源管理器中读取文件名称。
	char* data_names[DATA_NUM];			///<-存放所有文件名的区域（可能需要通过动态分配内存优化）
	char buf2[max_len + 10];			///<-二级缓冲区，绘制文件名称时使用，从存放所有文件名的区域取应显示的部分渲染到画布上。
	const char suffix[5] = { " ..." };


public:
	my_Button file_buttons[row_num];


};

