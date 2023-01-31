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

void FileBrowser::SetLineChartDrawingArea(int x1, int y1, int x2, int y2)
{	
	line_chart.point1.x = x1;
	line_chart.point1.y = y1;
	line_chart.point2.x = x2;
	line_chart.point2.y = y2;
}

void FileBrowser::SetDataInfoDrawingArea(int x1, int y1, int x2, int y2)
{
	data_info.point1.x = x1;
	data_info.point1.y = y1;
	data_info.point2.x = x2;
	data_info.point2.y = y2;
}

void FileBrowser::FlushDataIndex() { data_index = 0; }


void FileBrowser::ClearDataDrawingZone(hiex::Canvas& canvas)
{
	canvas.SolidRectangle(WINDOW_WID * MID_LEFT + 2, WINDOW_WID * EX_LEFT, WINDOW_WID, WINDOW_HEI - 30, true, 0xDDDDDD);	// 30为底部安全边距
}

bool FileBrowser::IsHomePage()
{
	if (data_page == 0)
		return true;
	else
		return false;
}

bool FileBrowser::IsEndPage()
{
	if (data_page == page_num - 1)
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
			data_len = data_index + 1;
			page_num = data_len / row_num + 1;
			last_page_row_num = data_len - (page_num - 1) * row_num;
			break;
		}
		data_index++;
	}
}

void FileBrowser::RenderFileBrowser(hiex::Canvas& canvas)
{
	canvas.ClearRectangle(WINDOW_WID * EX_LEFT + 1, WINDOW_WID * EX_LEFT, WINDOW_WID * MID_LEFT - 2, WINDOW_HEI - 50);   ///注意在其他分辨率下此处安全边距的设置
	
	canvas.SetTextStyle(txt_height, txt_width, L"微软雅黑");  //文件资源管理器（数据名及按钮绘制）
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
		if (y >= WINDOW_HEI - 100 || data_index >= data_len - 1)		///<-100为安全边距
		{
			break;
		}
		data_index++;
		y += data_btn_height;
	}

}

int FileBrowser::InWhichButton(ExMessage msg)
{
	if (!IsEndPage())
	{
		for (int i = 0; i < row_num; i++)
		{
			if (file_buttons[i].isIn(msg))
				return i;
		}
	}
	else
	{
		for (int i = 0; i < last_page_row_num; i++)
		{
			if (file_buttons[i].isIn(msg))
				return i;
		}
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
	char mean_suffix[DATA_WIDTH + 10] = "均值：\n";
	sprintf(mean, "%f", info.mean);
	strcat(mean_suffix, mean);
	char var[DATA_WIDTH];
	char var_suffix[DATA_WIDTH + 10] = "方差：\n";
	sprintf(var, "%f", info.variance);
	strcat(var_suffix, var);
	const char* pmean = mean_suffix;
	const char* pvar = var_suffix;

	SetLineChartDrawingArea(WINDOW_WID * MID_LEFT + 300, WINDOW_WID * EX_LEFT + 100, WINDOW_WID - 120, WINDOW_HEI - 150);

	float x1 = line_chart.point1.x;					// 左上角x坐标
	int y1 = line_chart.point1.y;					// 左上角y坐标
	int x2 = line_chart.point2.x;					// 右下角x坐标
	int y2 = line_chart.point2.y;					// 右下角y坐标

	const float xval = (x2 - x1) / info.count;		// 每两点间的横坐标之差
	const float hratio = (y2 - y1) / info.scale;	// 高度拉伸的比例
	ClearDataDrawingZone(canvas);	// 清除整个绘画区域

	// 绘制坐标轴
	const int margin = 30;
	const int extent = 20;
	canvas.SetLineStyle(PS_SOLID | PS_JOIN_ROUND, 3);
	canvas.Line(x1 - margin, y1 - margin - extent, x1 - margin, y2 + margin, true, BLACK);	// y轴
	canvas.Line(x1 - margin, y2 + margin, x2 + margin + extent, y2 + margin, true, BLACK);	// x轴
	imageAlign_alpha(canvas, L"sprites/next_page.png", 25, 25, x2 + margin + extent - 2, y2 + margin, 0, 0);
	imageAlign_alpha(canvas, L"sprites/up_arrow.png", 25, 25, x1 - margin, y1 - margin - extent + 2, 0, 0);
	//canvas.Draw_Text();




	// 绘制折线图
	canvas.SetLineStyle(PS_SOLID | PS_JOIN_BEVEL, 1);	
	float x0 = x1;
	for (int i = 0; i < info.count - 1; i++)
	{
		canvas.Line(x0, y1 + (info.max - info.data[i]) * hratio, x0 + xval, y1 + (info.max - info.data[i + 1]) * hratio, true, BLUE);
		x0 += xval;
	}

	// 均值
	canvas.SetLineColor(YELLOW);
	canvas.SetLineStyle(PS_DASH | PS_JOIN_BEVEL, 3);
	canvas.Line(x1, y1 + (info.max - info.mean) * hratio, x2, y1 + (info.max - info.mean) * hratio);


	textAlign(canvas, char2wchar(pname), 24, 0, L"微软雅黑", WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * (1 - MID_LEFT), WINDOW_HEI - WINDOW_WID * EX_LEFT - 30, TOP);
	textAlign(canvas, char2wchar(pmean), 24, 0, L"微软雅黑", WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * (1 - MID_LEFT), WINDOW_HEI - WINDOW_WID * EX_LEFT - 30, BOTTOM_LEFT);
	textAlign(canvas, char2wchar(pvar), 24, 0, L"微软雅黑", WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * (1 - MID_LEFT), WINDOW_HEI - WINDOW_WID * EX_LEFT - 30, TOP_LEFT);
	//canvas.Draw_Text();
}

FileBrowser::~FileBrowser()
{
}
