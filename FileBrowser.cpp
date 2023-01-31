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
	canvas.SetLineColor(BLACK);
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
		canvas.SetLineColor(0xAAAAAA);
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
	/*绘图常数*/
	const int margin = 30;				// 与折线图的边距
	const int extension = 20;			// 坐标轴正半轴延伸长度
	const int interval = 50;			// 标记线间距
	const int mark_len = 5;				// 标记线长度
	const int info_margin = 10;			// 信息到信息框的边距
	const int info_margin_top = 5;		// 信息到文件名的边距
	const int info_txt_height = 24;		// 信息文字大小
	const float txt_line_space = 1.25;	// 行间距（倍数）
	SetLineChartDrawingArea(WINDOW_WID * MID_LEFT + 350, WINDOW_WID * EX_LEFT + 100, WINDOW_WID - 100, WINDOW_HEI - 150);
	SetDataInfoDrawingArea(WINDOW_WID * MID_LEFT + 50, WINDOW_WID * EX_LEFT + 100 - margin - extension, WINDOW_WID * MID_LEFT + 250, WINDOW_WID * EX_LEFT + 400);

	char mean[DATA_WIDTH];
	char mean_suffix[DATA_WIDTH + 10] = "均值：\n";
	sprintf(mean, "%f", info.mean);
	strcat(mean_suffix, mean);

	char var[DATA_WIDTH];
	char var_suffix[DATA_WIDTH + 10] = "方差：\n";
	sprintf(var, "%f", info.variance);
	strcat(var_suffix, var);

	char max[DATA_WIDTH];
	char max_suffix[DATA_WIDTH + 10] = "最大值：\n";
	sprintf(max, "%f", info.max);
	strcat(max_suffix, max);

	char min[DATA_WIDTH];
	char min_suffix[DATA_WIDTH + 10] = "最小值：\n";
	sprintf(min, "%f", info.min);
	strcat(min_suffix, min);

	const char* pname = info.filename;
	const char* pmean = mean_suffix;
	const char* pvar = var_suffix;
	const char* pmax = max_suffix;
	const char* pmin = min_suffix;

	float x1 = line_chart.point1.x;					// 左上角x坐标
	int y1 = line_chart.point1.y;					// 左上角y坐标
	int x2 = line_chart.point2.x;					// 右下角x坐标
	int y2 = line_chart.point2.y;					// 右下角y坐标

	const float xval = (x2 - x1) / info.count;		// 每两点间的横坐标之差
	const float hratio = (y2 - y1) / info.scale;	// 高度拉伸的比例
	ClearDataDrawingZone(canvas);	// 清除整个绘画区域

	// 绘制数据信息
	canvas.FillRoundRect(data_info.point1.x, data_info.point1.y, data_info.point2.x, data_info.point2.y, 30, 30, true, 0x999999, RGB(200, 215, 230));

	//* 其实这段代码可以优化成
	//* 需要展示的信息放在一个队列里，用for遍历这个队列然后绘制出来
	textAlign
		(canvas,
		char2wchar(pname),
		info_txt_height,
		0,
		L"黑体",
		data_info.point1.x + info_margin, 
		data_info.point1.y + info_margin,
		data_info.point2.x - data_info.point1.x - 2 * info_margin, 
		data_info.point2.y - data_info.point1.y - 2 * info_margin, 
		TOP);
	textAlign
		(canvas,
		char2wchar(pmean),
		info_txt_height,
		0,
		L"微软雅黑",
		data_info.point1.x + info_margin,
		data_info.point1.y + info_margin + info_txt_height * txt_line_space + info_margin_top,
		data_info.point2.x - data_info.point1.x - 2 * info_margin,
		data_info.point2.y - data_info.point1.y - 2 * info_margin - info_txt_height * txt_line_space,
		TOP_LEFT);
	textAlign
		(canvas,
		char2wchar(pvar),
		info_txt_height,
		0,
		L"微软雅黑",
		data_info.point1.x + info_margin,
		data_info.point1.y + info_margin + 2 * info_txt_height * txt_line_space + info_margin_top,
		data_info.point2.x - data_info.point1.x - 2 * info_margin,
		data_info.point2.y - data_info.point1.y - 2 * info_margin - 2 * info_txt_height * txt_line_space,
		TOP_LEFT);
	textAlign
		(canvas,
		char2wchar(pmax),
		info_txt_height,
		0,
		L"微软雅黑",
		data_info.point1.x + info_margin,
		data_info.point1.y + info_margin + 3 * info_txt_height * txt_line_space + info_margin_top,
		data_info.point2.x - data_info.point1.x - 2 * info_margin,
		data_info.point2.y - data_info.point1.y - 2 * info_margin - 3 * info_txt_height * txt_line_space,
		TOP_LEFT);
	textAlign
		(canvas,
		char2wchar(pmin),
		info_txt_height,
		0,
		L"微软雅黑",
		data_info.point1.x + info_margin,
		data_info.point1.y + info_margin + 4 * info_txt_height * txt_line_space + info_margin_top,
		data_info.point2.x - data_info.point1.x - 2 * info_margin,
		data_info.point2.y - data_info.point1.y - 2 * info_margin - 4 * info_txt_height * txt_line_space,
		TOP_LEFT);


	// 绘制坐标轴
	canvas.SetLineStyle(PS_SOLID | PS_JOIN_ROUND, 3);
	canvas.Line(x1 - margin, y1 - margin - extension, x1 - margin, y2 + margin, true, BLACK);	// y轴
	canvas.Line(x1 - margin, y2 + margin, x2 + margin + extension, y2 + margin, true, BLACK);	// x轴
	imageAlign_alpha(canvas, L"sprites/next_page.png", 25, 25, x2 + margin + extension - 2, y2 + margin, 0, 0);
	imageAlign_alpha(canvas, L"sprites/up_arrow.png", 25, 25, x1 - margin, y1 - margin - extension + 2, 0, 0);

	for (int i = x1; i < x2 + margin + extension; i += interval)
	{	// x轴
		canvas.Line(i, y2 + margin, i, y2 + margin - mark_len);
	}
	float y = info.min;
	for (int i = y2; i > y1 - margin - extension; i -= interval, y += interval / hratio)
	{	// y轴
		canvas.Line(x1 - margin, i, x1 - margin + mark_len, i);
		char buffer[DATA_WIDTH];
		sprintf(buffer, "%.2f", y);
		textAlign(canvas, char2wchar(buffer), 22, 0, L"微软雅黑", x1 - margin - 5, i, 0, 0, RIGHT);
	}

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

	// 按钮
	my_Button mean_filter_btn(WINDOW_WID * MID_LEFT + 50, 500, 100, 30);
	mean_filter_btn.draw_detailed_default(canvas);
	mean_filter_btn.setText(L"均值滤波", 23, 0, L"微软雅黑", BLACK);
	mean_filter_btn.draw_default_txt(canvas);

	filter[1] = mean_filter_btn;

}

void FileBrowser::FilterData()
{
	mean_filter(info.processed_data, info.data, info.count, 5);
}

void FileBrowser::DrawProcessedDataChart(hiex::Canvas& canvas)
{
	float x1 = line_chart.point1.x;					// 左上角x坐标
	int y1 = line_chart.point1.y;					// 左上角y坐标
	int x2 = line_chart.point2.x;					// 右下角x坐标
	int y2 = line_chart.point2.y;					// 右下角y坐标

	const float xval = (x2 - x1) / info.count;		// 每两点间的横坐标之差
	const float hratio = (y2 - y1) / info.scale;	// 高度拉伸的比例

	canvas.SetLineStyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	float x0 = x1;
	for (int i = 0; i < info.count - 1; i++)
	{
		canvas.Line(x0, y1 + (info.max - info.processed_data[i]) * hratio, x0 + xval, y1 + (info.max - info.processed_data[i + 1]) * hratio, true, RED);
		x0 += xval;
	}

}

FileBrowser::~FileBrowser()
{
}
