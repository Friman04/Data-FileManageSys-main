#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "my_Button.h"

class FileBrowser
{
public:
	FileBrowser();
	int GetDataIndex();
	int GetDataPage();
	int GetRowNum();
	void SetDataIndex(int index);
	void SetDataPage(int page);
	bool IsHomePage();
	bool IsEndPage();
	void FlushDataIndex();

	void LoadDataFileName();
	void RenderFileBrowser(hiex::Canvas& canvas);
	int InWhichButton(ExMessage msg);
	void DrawButton();
	~FileBrowser();
public:
	static const unsigned short txt_height = 24;			///<-���ָ߶�
	static const unsigned short txt_width = 9;				///<-���ֿ��ȣ������ָ߶Ⱥ������й�
	static const unsigned short data_btn_height = 40;		///<-�����ļ���ť��ʾ�ĸ߶�

private:
	static const int row_num = (WINDOW_HEI * (1 - EX_LEFT) - 140) / data_btn_height;		///<-ÿҳ����ʾ��������140Ϊ��ȫ�߾�
	bool isStartToLoad = true;																///<-�Ƿ�ʼ����
	static const int max_len = (WINDOW_WID * (MID_LEFT - EX_LEFT) - 30) / txt_width;		///<-ÿ�п���ʾ��������30Ϊ��ȫ�߾ࣨ��������ϵ�bug��
	unsigned int data_page = 0;																///<-��ǰҳ��
	unsigned int data_index = data_page * row_num;											///<-��ǰ�����ļ�������
	unsigned int data_len;																	///<-�ļ��ܸ���

	char buf1[MAX_LEN];					///<-һ������������������ʱʹ�á�ͨ�� WinAPI �� Windows ��Դ�������ж�ȡ�ļ����ơ�
	char* data_names[DATA_NUM];			///<-��������ļ��������򣨿�����Ҫͨ����̬�����ڴ��Ż���
	char buf2[max_len + 10];			///<-�����������������ļ�����ʱʹ�ã��Ӵ�������ļ���������ȡӦ��ʾ�Ĳ�����Ⱦ�������ϡ�
	const char suffix[5] = { " ..." };


public:
	my_Button file_buttons[row_num];


};
