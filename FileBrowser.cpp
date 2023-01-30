#include "FileBrowser.h"

FileBrowser::FileBrowser()
{
}

unsigned int FileBrowser::GetDataIndex() { return data_index; }

unsigned int FileBrowser::GetDataPage() { return data_page; }

unsigned int FileBrowser::GetRowNum() { return row_num; }

unsigned int FileBrowser::GetTotalPages() { return page_num; }

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

void FileBrowser::LoadDataFileName(const char* filename)
{
	struct _finddata_t file;
	intptr_t hFile;
	hFile = _findfirst(filename, &file);
	if (hFile == -1)
	{
		printf("没有找到文件！\n");
		isStartToLoad = false;
	}
	while (isStartToLoad)
	{
		if (strlen(file.name) >= MAX_LEN)	///<-考虑到安全性，请不要将数据文件命名得过长，否则程序会报错
		{
			printf("数据文件夹中存在名称过长的文件！");
			exit(0);
		}
		sprintf_s(buf1, MAX_LEN, "%s", file.name);    ///<-文件名最长显示长度
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
	canvas.ClearRectangle(WINDOW_WID * EX_LEFT + 1, WINDOW_WID * EX_LEFT, WINDOW_WID * MID_LEFT - 2, WINDOW_HEI - 50);   ///注意在其他分辨率下此处安全边距的设置
	canvas.SetTextStyle(txt_height, txt_width, L"微软雅黑");  //文件资源管理器（文字及按钮绘制）
	canvas.SetBkMode(TRANSPARENT);
	canvas.SetTextColor(BLACK);
	canvas.SetLineStyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	int x = WINDOW_WID * EX_LEFT + 10, y = WINDOW_WID * EX_LEFT + 40;		///<-10和40为安全边距
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
		file_buttons[data_index](x - 10, y - (data_btn_height - txt_height) / 2, WINDOW_WID* (MID_LEFT - EX_LEFT), data_btn_height);
		if (y >= WINDOW_HEI - 100 || data_index >= data_len)		///<-100为安全边距
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

void FileBrowser::LoadData(ExMessage msg)
{
	char filename[MAX_LEN];
	strcpy(filename, "data/");
	strcat(filename, data_names[data_page * row_num + InWhichButton(msg)]);
	FILE* fp;
	if ((fp = fopen(filename, "r+")) == NULL)
	{
		printf("Can not open file\n");
		exit(0);
	}
	for (int i = 0; i < N; i++)
	{
		if (fscanf(fp, "%f", &info.data[i]) == EOF)
		{
			info.count = i;
			break;
		}
	}
	fclose(fp);
	strcpy(info.filename, data_names[data_page * row_num + InWhichButton(msg)]);
	info.mean = mean(info.data, info.count);
	info.variance = variance(info.data, info.count);
	info.max = arraymax(info.data, info.count);
	info.min = arraymin(info.data, info.count);
	info.scale = info.max - info.min;
}

void FileBrowser::DrawDataInfo(hiex::Canvas& canvas)
{
	const char* pname = info.filename;
	char mean[DATA_WIDTH];
	char mean_suffix[DATA_WIDTH + 10] = "均值为：";
	sprintf(mean, "%f", info.mean);
	strcat(mean_suffix, mean);
	char var[DATA_WIDTH];
	char var_suffix[DATA_WIDTH + 10] = "方差为：";
	sprintf(var, "%f", info.variance);
	strcat(var_suffix, var);
	const char* pmean = mean_suffix;
	const char* pvar = var_suffix;


	float x1 = WINDOW_WID * MID_LEFT + 50;			// 左上角x坐标
	int y1 = WINDOW_WID * EX_LEFT + 50;			// 左上角y坐标
	int x2 = WINDOW_WID - 50;						// 右下角x坐标
	int y2 = WINDOW_HEI - 50;						// 右下角y坐标
	const float xval = (x2 - x1) / info.count;		// 每两点间的横坐标之差
	const float hratio = (y2 - y1) / info.scale;	// 高度拉伸的比例
	canvas.SolidRectangle(WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID, WINDOW_HEI - 30, true, RGB(204, 204, 204));	// 30为底部安全边距
	textAlign(canvas, char2wchar(pname), 24, 0, L"微软雅黑", WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * (1 - MID_LEFT), WINDOW_HEI - WINDOW_WID * EX_LEFT - 30, TOP);
	textAlign(canvas, char2wchar(pmean), 24, 0, L"微软雅黑", WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * (1 - MID_LEFT), WINDOW_HEI - WINDOW_WID * EX_LEFT - 30, BOTTOM_LEFT);
	textAlign(canvas, char2wchar(pvar), 24, 0, L"微软雅黑", WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * (1 - MID_LEFT), WINDOW_HEI - WINDOW_WID * EX_LEFT - 30, TOP_LEFT);
	canvas.SetLineColor(BLUE);
	canvas.SetLineStyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	float x0 = x1;
	for (int i = 0; i < info.count - 1; i++)
	{
		canvas.Line(x0, y1 + (info.max - info.data[i]) * hratio, x0 + xval, y1 + (info.max - info.data[i + 1]) * hratio);
		x0 += xval;
	}
	// 均值
	canvas.SetLineColor(YELLOW);
	canvas.SetLineStyle(PS_DASH | PS_JOIN_BEVEL, 3);

	canvas.Line(x1, y1 + (info.max - info.mean) * hratio, x2, y1 + (info.max - info.mean) * hratio);

}

FileBrowser::~FileBrowser()
{
}
