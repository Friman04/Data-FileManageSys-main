#include "FileBrowser.h"

FileBrowser::FileBrowser()
{
}

int FileBrowser::GetDataIndex() { return data_index; }

int FileBrowser::GetDataPage() { return data_page; }

int FileBrowser::GetRowNum() { return row_num; }

void FileBrowser::SetDataIndex(int index) { data_index = index; }

void FileBrowser::SetDataPage(int page) { data_page = page; }

void FileBrowser::FlushDataIndex() { data_index = 0; }

bool FileBrowser::IsHomePage()
{
	if (data_page == 0)
		return true;
	else
		return false;
}

bool FileBrowser::IsEndPage()
{
	if (data_page == data_index / row_num)
		return true;
	else
		return false;
}

void FileBrowser::LoadDataFileName()
{
	struct _finddata_t file;
	intptr_t hFile;
	hFile = _findfirst("data/*.txt", &file);
	if (hFile == -1)
	{
		printf("û���ҵ��ļ���\n");
		isStartToLoad = false;
	}
	while (isStartToLoad)
	{
		if (strlen(file.name) >= MAX_LEN)	///<-���ǵ���ȫ�ԣ��벻Ҫ�������ļ������ù������������ᱨ��
		{
			printf("�����ļ����д������ƹ������ļ���");
			exit(0);
		}
		sprintf_s(buf1, MAX_LEN, "%s", file.name);    ///<-�ļ������ʾ����
		char* data = (char*)malloc(MAX_LEN);
		strcpy(data, buf1);
		data_names[data_index] = data;
		if (_findnext(hFile, &file))
		{
			data_len = data_index;
			page_num = data_len / row_num + 1;
			break;
		}
		data_index++;
	}
}

void FileBrowser::RenderFileBrowser(hiex::Canvas& canvas)
{
	canvas.ClearRectangle(WINDOW_WID * EX_LEFT + 1, WINDOW_WID * EX_LEFT, WINDOW_WID * MID_LEFT - 2, WINDOW_HEI - 50);   ///ע���������ֱ����´˴���ȫ�߾������
	canvas.SetTextStyle(txt_height, txt_width, L"΢���ź�");  //�ļ���Դ�����������ּ���ť���ƣ�
	canvas.SetBkMode(TRANSPARENT);
	canvas.SetTextColor(BLACK); 
	int x = WINDOW_WID * EX_LEFT + 10, y = WINDOW_WID * EX_LEFT + 40;		///<-10��40Ϊ��ȫ�߾�
	data_index = data_page * row_num;
	while (true)
	{
		if (strlen(data_names[data_index]) > max_len)
		{	
			strncpy(buf2, data_names[data_index], max_len);
			buf2[max_len - 2] = '\0';
			strcat(buf2, suffix);
			canvas.OutTextXY(x, y, char2wchar(buf2));
		}
		else
		{
			strncpy(buf2, data_names[data_index], max_len);
			buf2[max_len - 1] = '\0';
			canvas.OutTextXY(x, y, char2wchar(buf2));
		}
		canvas.Line(x - 10, y - (data_btn_height - txt_height) / 2, WINDOW_WID * MID_LEFT, y - (data_btn_height - txt_height) / 2);
		canvas.Line(x - 10, y + (data_btn_height + txt_height) / 2, WINDOW_WID * MID_LEFT, y + (data_btn_height + txt_height) / 2);
		file_buttons[data_index](x - 10, y - (data_btn_height - txt_height) / 2, WINDOW_WID * (MID_LEFT - EX_LEFT), data_btn_height);
		if (y >= WINDOW_HEI - 100 || data_index >= data_len)		///<-100Ϊ��ȫ�߾�
		{
			break;
		}
		data_index++;
		y += data_btn_height;
	}

}

int FileBrowser::InWhichButton(ExMessage msg)
{
	for (int i = 0; i <= row_num; i++)
	{
		if (file_buttons[i].isIn(msg))
			return i;
	}
	return -1;
}

void FileBrowser::DrawButton()
{
}

FileBrowser::~FileBrowser()
{
}
