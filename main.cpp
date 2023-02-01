/*******************************************
 * @note		该版本仅供提交大作业使用！
 * @author		电创2202-吴玮彤-20221072060
 * @email		272316212@qq.com
 * @site		https://github.com/Friman04/Data-FileManageSys-main
 * @date		2023.01.12
 * @envir		Windows 11 dev_Build 25272.rs_prerelease.221216-1237 | Visual Studio 2022 | EasyX_20220901 | HiEasyX Ver 0.3.0
 * @hardware	CPU:	12th Gen Intel(R) Core(TM) i7-12700H   2.30 GHz
 *				GPU:	NVIDIA GeForce RTX 3060 Laptop GPU GDDR6 @ 6GB (192 bit)
 *				
 * @version     0.1Beta5b
 *
 * @note		本项目使用了基于 EasyX 的扩展 HiEasyX，请确保环境中安装了 EasyX
 *				程序只能在 Windows 环境下运行，应该在 Windows 10/11 和 Visual Studio 下编译程序，暂不支持 MinGW 编译器，其它环境未测试，不保证程序能正常运行
 *				本程序依赖CPU单核性能和GPU性能，若出现轻微卡顿和延迟渲染现象为正常
 *				第一次编译需要较长时间，请耐心等待
 * 
 * @file
	├── management system.sln       // 项目解决方案
	├── main.cpp					// 主函数
	├── Configuration.h				// 配置文件
	├── Core.h						// 核心函数
	├── Core.cpp
	├── my_Button.h					// 按钮类
	├── my_Button.cpp
	├── FileBrowser.h				// 文件浏览器类
	├── FileBrowser.cpp
	├── HiEasyX
	│   ├── HiEasyX.h				// HieasyX头文件
	│   └── ...						// HieasyX其它库文件
	├── data						// 数据文件夹
	│   ├── mine.txt
	│   ├── randn.txt
	│   └── ...
	├── sprites						// 资源文件夹
	│   ├── drawing_bg.png
	│   ├── last_page.png
	│   ├── last_page_disabled.png
	│   ├── login.png
	│   ├── logo.png
	│   ├── logo_144px.png
	│   ├── logo_alpha_light.png
	│   ├── logo_light.png
	│   ├── next_page.png
	│   ├── next_page_disabled.png
	│   ├── up_arrow.png
	│   └── white.png
	├── VerChange.log				// 更新日志（不再维护）
	├── 工业数据分析与文件信息管理系统0.1Beta5a-release20230201.exe		// 生成的程序
	└── ...
 * 
 * @note		目前已知存在的bug（更多已修复bug可移步更新日志）
 * @note		如果您发现了其它bug，可以通过邮箱联系我或者在 GitHub 上提交 Issue
 * @bug			0.渲染精度低
 * @bug			1.文件浏览器第二页无法使用
 * @bug			2.性能问题
 * @bug			4.偶见的系统崩溃
 * @bug			5.文件资源管理器中文件名若存在非英语字符可能会使得末尾显示过短或过长
 * 
 * @bug			6.数据分析按钮未开发完全
 * @bug			7.系统启动初期不稳定，容易闪退
 * 
 * @develop		1.登录系统
 * @develop		2.切换按钮
 * @develop		3.去除离群值
 *******************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _SYS_VER_STR_	L"Ver 0.1Beta5b"

#include "my_Button.h"
#include "FileBrowser.h"

 //
 // 自变量声明区
 //

char token; // 未使用



/*创建储存用户账号密码的文件*/
void createFile()
{
	FILE* fp;
	if ((fopen("users.txt", "rb")) == NULL)                 // 如果此文件不存在
	{
		if ((fopen("users.txt", "wb+")) == NULL)
		{
			printf("无法建立文件！\n");
			exit(0);
		}
	}
}

/*创建菜单*/
int index()
{
	printf("___________________________________\n");
	printf("Welcome!\n");
	printf("在进一步的使用前，你需要进行登录：\n");
	printf("【1】注册\n");
	printf("【2】登录\n");
	printf("___________________________________\n");
	printf("请输入对应序号：");

	int kbhit = getchar();
	getchar();
	return kbhit;
}

/*菜单交互*/
int indexInter()
{
	switch (index())
	{
	case 1:
		break;
	case 2:
		break;
	default:
		printf("无效的输入，请重新输入！");
	}

	return 0;
}

/*注册*/
void reg()  // 按结构体的大小，一次写入或者读入1个结构体大小
{
	user a, b;
	FILE* fp = NULL;
	errno_t err = 0;
	char temp[20];
	int count = 0;
	fp = fopen("users.txt", "r");
	fread(&b, sizeof(user), 1, fp);   // 用b遍历users

	printf("___________________________________\n");
	printf("欢迎来到注册界面！\n");
	Sleep(1000);
	printf("【info】用户名不可超过16个字符\n");
	printf("【info】输入q可返回\n");
	printf("请输入用户名:\n");
	scanf("%s", &a.id);
	if (*a.id == 'q')
		return;
	while (1)
	{
		if (strcmp(a.id, b.id)) // 如果ab不同
		{
			if (!feof(fp))    // 如果未到文件尾
			{
				fread(&b, sizeof(user), 1, fp);
			}
			else
				break;
		}
		else

		{
			printf("此用户名已存在！请重新注册！\n");
			Sleep(1000);
			fclose(fp);
			return;
		}
	}



	printf("请输入性别(1（女）/2（男）/3（机器人）)：\n");
	scanf("%d", &a.sex);
	while (a.sex != 1 && a.sex != 2 && a.sex != 3)
	{
		printf("如果是机器人的话请输入3哦-ω-\n");
		scanf("%d", &a.sex);
	}
	getchar();
	while (1)
	{
		printf("请输入密码\n");
		scanf(" %s", &a.pwd);
		printf("请确认密码\n");
		scanf(" %s", &temp);

		if (!strcmp(a.pwd, temp))
		{
			fp = fopen("users.txt", "a");
			fwrite(&a, sizeof(user), 1, fp);
			printf("账号注册成功，请登录！\n");
			Sleep(500);
			fclose(fp);
			return;
		}
		else
		{
			printf("两次密码不匹配！请重新输入！\n");
		}
	}
}

/*登录系统*/
void login()
{
	user a, b;
	FILE* fp;
	fp = fopen("users.txt", "r");
	fread(&b, sizeof(user), 1, fp);
	printf("___________________________________\n");
	printf("欢迎来到登录界面！\n");
	Sleep(500);
	printf("【info】输入q可返回\n");
	printf("请输入账号\n");

	scanf("%s", &a.id);
	if (*a.id == 'q')
		return;
	while (1)
	{
		if (strcmp(a.id, b.id) == 0)         // 如果有此用户名
		{
			break;
		}
		else
		{
			if (!feof(fp))  // 如果文件没有读完                            

			{
				fread(&b, sizeof(user), 1, fp);
			}

			else
			{
				printf("此用户名不存在，请重新输入！\n");
				Sleep(500);
				fclose(fp);
				return;
			}
		}
	}
	printf("请输入密码\n");
	scanf("%s", &a.pwd);
	while (1)
	{

		if (strcmp(a.pwd, b.pwd) == 0)
		{
			fclose(fp);
			printf("登录成功,欢迎使用!");
			//token = &a.id;  /*bug*/
			Sleep(500);
			return;
		}
		else
		{
			printf("密码不正确!请重新输入密码\n");
			scanf("%s", &a.pwd);
		}

	}
}


/*
void home_deprecated()
{
	hiex::Canvas canvas_main;
	hiex::Window wnd(WINDOW_WID, WINDOW_HEI);
	wnd.BindCanvas(&canvas_main);
	hiex::AutoExit();
	HWND hwnd = wnd.GetHandle();

	// 背景1
	canvas_main.Clear(true, WHITE);  //设置背景颜色

	// 线条
	hiex::ImageBlock dividing_line;
	dividing_line.CreateCanvas(10, WINDOW_HEI);
	dividing_line.GetCanvas()->SetLineStyle(PS_SOLID, 2);
	dividing_line.GetCanvas()->SetLineColor(0xEEEEEE);
	dividing_line.GetCanvas()->Line(WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * MID_LEFT, WINDOW_HEI); // 分隔资源管理器和绘图区
	dividing_line.bUseSrcAlpha = true;
	ReverseAlpha(dividing_line.GetCanvas()->GetBuffer(), dividing_line.GetCanvas()->GetBufferSize());

	// 背景2
	hiex::ImageBlock bg_left;
	hiex::ImageBlock bg_top;

	bg_left.CreateCanvas(WINDOW_WID * EX_LEFT, WINDOW_HEI);
	bg_left.GetCanvas()->SetFillColor(0x662015);
	bg_left.GetCanvas()->FillRectangle(0, 0, WINDOW_WID * EX_LEFT, WINDOW_HEI); // 左侧深蓝色背景

	bg_top.CreateCanvas(WINDOW_WID, WINDOW_WID * EX_LEFT);
	bg_top.GetCanvas()->SetFillColor(0xEFE1CF);
	bg_top.GetCanvas()->FillRectangle(0, 0, WINDOW_WID, WINDOW_WID * EX_LEFT); // 顶侧浅蓝色背景

	//logo
	hiex::ImageBlock logo;
	logo.CreateCanvas(WINDOW_WID * EX_LEFT - 1, WINDOW_WID * EX_LEFT - 1);
	logo.GetCanvas()->Load_Image_Alpha(L"sprites/logo_light.png", 0, 0, false, WINDOW_WID * EX_LEFT - 1, WINDOW_WID * EX_LEFT - 1, 255U, true);

	// 文字
	hiex::ImageBlock title;
	hiex::ImageBlock info;

	title.CreateCanvas(WINDOW_WID, WINDOW_HEI);
	textAlign(title, L"工业数据分析与文件信息管理系统", 36, 0, L"微软雅黑", WINDOW_WID * EX_LEFT, 0, WINDOW_WID * (1 - EX_LEFT), WINDOW_WID * EX_LEFT); // 标题
	title.bUseSrcAlpha = true;
	ReverseAlpha(title.GetCanvas()->GetBuffer(), title.GetCanvas()->GetBufferSize());

	info.CreateCanvas(WINDOW_WID, WINDOW_HEI);
	textAlign(info, L"Created by Friman " _SYS_VER_STR_, 16, 0, L"Arial", 0, 0, WINDOW_WID, WINDOW_HEI, BOTTOM_RIGHT, GRAY); // 信息
	info.bUseSrcAlpha = true;
	ReverseAlpha(info.GetCanvas()->GetBuffer(), info.GetCanvas()->GetBufferSize());

	// 按钮
	my_Button btn_login(WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
	btn_login.setImage(L"sprites/login.png");
	btn_login.setIconSize(32, 32);
	btn_login.createIconCanvas();
	btn_login.createHoverCanvas();
	btn_login.createPushCanvas();

	hiex::ImageBlock login_icon;
	hiex::ImageBlock login_bg;

	btn_login.draw_default_img();
	login_icon = btn_login.getIcon();





	hiex::Scene s;
	hiex::Layer BG; // 静态背景图层
	hiex::Layer inter; // 动态交互图层

	BG.push_back(&bg_left);
	BG.push_back(&bg_top);
	BG.push_back(&dividing_line);
	BG.push_back(&logo);
	BG.push_back(&title);
	BG.push_back(&info);

	inter.push_back(&login_icon);

	s.push_back(&BG);
	s.push_back(&inter);


	// 初始化绘制
	if (wnd.BeginTask())
	{
		hiex::SetDrawMode(hiex::DM_Fastest);
		s.Render(canvas_main.GetImagePointer());
		wnd.Redraw();
		wnd.EndTask();
	}

	btn_login.eventloop(getmessage(EX_MOUSE));
	bool isDown = false;
	while (1)
	{



		printf("%d", isDown);
		if (btn_login.isIn())
		{
			btn_login.draw_hover();
			login_bg = btn_login.getHoveringImage();
			inter.push_back(&login_bg);
			printf("in\n");

			if (btn_login.isLCD())
			{
				btn_login.draw_push();
				login_bg = btn_login.getPushingImage();
				inter.push_back(&login_bg);
				isDown = true;
				printf("in and down\n");

			}
			else if (btn_login.isLCU())
			{
				btn_login.draw_hover();
				login_bg = btn_login.getHoveringImage();
				inter.push_back(&login_bg);
				isDown = false;
				printf("in and up\n");

			}
		}
		else if (!btn_login.isIn())
		{
			if (isDown)
			{
				btn_login.draw_hover();
				login_bg = btn_login.getHoveringImage();
				inter.push_back(&login_bg);
			}
			else if (!isDown)
			{
				btn_login.draw_default_img();
				btn_login.draw_default_img();
				login_icon = btn_login.getIcon();
			}

			printf("not in\n");
		}

		if (wnd.BeginTask())
		{
			s.Render(canvas_main.GetImagePointer());
			wnd.FlushDrawing();
			wnd.EndTask();
		}

	}
	hiex::init_end(hwnd);

}
*/



void home()
{
	hiex::Canvas canvas_main;
	hiex::Window wnd(int(WINDOW_WID), WINDOW_HEI);
	FileBrowser file_browser;
	wnd.BindCanvas(&canvas_main);
	hiex::AutoExit();
	HWND hwnd = wnd.GetHandle();
	EnableResizing(GetHWnd(), false);

	const int out_r = 8;

	while (1)
	{
		/*绘制GUI框架*/


		/*
		edit.PreSetStyle(true, false, true);
		edit.Create(hwnd, WINDOW_WID * EX_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * (MID_LEFT - EX_LEFT), WINDOW_HEI - WINDOW_WID * EX_LEFT,
			L"Welcome to HiEasyX !\r\n"
			L"\r\n"
			L"Here you will experience the overall upgrade of EasyX.\r\n"
			L"Let's start HiEasyX from the simple sample.\r\n"
			L"\r\n"
			L"What's new in HiEasyX\r\n"
			L"\r\n"
			L">> You could create multi-window application with HiEasyX easily.\r\n"
			L">> You could use HiCanvas, which is a C++ canvas wrapper of EasyX, in the similar way of EasyX.\r\n"
			L">> The best support of Windows system controls integrated in HiEasyX is avalible.\r\n"
			L">> The most easy method to create a tray.\r\n"
			L"etc.\r\n"
		);
		edit.SetFont(26, 0, L"微软雅黑");
		*/


		// 背景1
		canvas_main.Clear(true, WHITE);  //设置背景颜色

		// 线条
		canvas_main.SetLineStyle(PS_SOLID, 2);
		canvas_main.Line(WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * MID_LEFT, WINDOW_HEI, true, BLACK); // 分隔资源管理器和绘图区

		// 背景2
		canvas_main.SetFillColor(0x662015);
		canvas_main.SolidRectangle(0, 0, WINDOW_WID * EX_LEFT, WINDOW_HEI); // 左侧深蓝色背景
		canvas_main.SetFillColor(0xEFE1CF);
		canvas_main.SolidRectangle(0, 0, WINDOW_WID, WINDOW_WID * EX_LEFT); // 顶侧浅蓝色背景
		file_browser.ClearDataDrawingZone(canvas_main);
		//logo
		canvas_main.Load_Image_Alpha(L"sprites/logo_light.png", 0, 0, false, WINDOW_WID * EX_LEFT + 1, WINDOW_WID * EX_LEFT + 1, 255U, true);

		// 文字
		textAlign(canvas_main, L"工业数据分析与文件信息管理系统", 36, 0, L"黑体", WINDOW_WID * EX_LEFT, 0, WINDOW_WID * (1 - EX_LEFT), WINDOW_WID * EX_LEFT); // 标题
		textAlign(canvas_main, L"Created by Friman " _SYS_VER_STR_, 16, 0, L"Arial", 0, 0, WINDOW_WID, WINDOW_HEI, BOTTOM_RIGHT, GRAY); // 信息


		// 其它按钮绘制
		imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
		imageAlign_alpha(canvas_main, L"sprites/last_page_disabled.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
		imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);


		// 按钮控件逻辑

		// 资源管理器
		file_browser.LoadDataFileName("data/*.txt");
		file_browser.FlushDataIndex();
		canvas_main.SetLineColor(BLACK);
		file_browser.RenderFileBrowser(canvas_main);  //初始化绘制

		char page_txt[32];
		sprintf(page_txt, "%d / %d", file_browser.GetDataPage() + 1, file_browser.GetTotalPages());
		const char* ppage_txt = page_txt;
		textAlign(canvas_main, char2wchar(ppage_txt), 20, 0, L"等线", WINDOW_WID * EX_LEFT, WINDOW_HEI - 45, WINDOW_WID * (MID_LEFT - EX_LEFT) - 10, 32, RIGHT);		/// 10为安全边距

		REDRAW_WINDOW();
		// 按钮是否可用
		bool isLastEnable = false;
		bool isNextEnable = true;

		ExMessage m_msg;


		while (1)
		{
			m_msg = getmessage(EX_MOUSE);

			my_Button btn;

			if (m_msg.x > WINDOW_WID * (1 - EX_LEFT * 3 / 4) && m_msg.y > WINDOW_WID * EX_LEFT / 4 && m_msg.x < WINDOW_WID * (1 - EX_LEFT / 4) && m_msg.y < WINDOW_WID * EX_LEFT * 3 / 4) // 如果鼠标在这个区间内
			{
				/// LOGIN
				switch (m_msg.message)
				{
					case WM_LBUTTONDOWN:
					{
						canvas_main.SetFillColor(0x999999);
						canvas_main.SolidRoundRect(WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * (1 - EX_LEFT / 4), WINDOW_WID * EX_LEFT * 3 / 4, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
						REDRAW_WINDOW();
						break;
					}
					case WM_LBUTTONUP:
					{
						textAlign(canvas_main, _T("登录注册系统前端正在开发中..."), 18, 0, _T("微软雅黑"), 0, 0, WINDOW_WID - 30, WINDOW_WID * EX_LEFT + 30, BOTTOM_RIGHT); //do somthing

						canvas_main.SetFillColor(0xCCCCCC);
						canvas_main.SolidRoundRect(WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * (1 - EX_LEFT / 4), WINDOW_WID * EX_LEFT * 3 / 4, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
						REDRAW_WINDOW();
						break;
					}
					default:
					{
						// 鼠标指针经过按钮
						canvas_main.SetFillColor(0xDDDDDD);
						canvas_main.SolidRoundRect(WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * (1 - EX_LEFT / 4), WINDOW_WID * EX_LEFT * 3 / 4, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
						REDRAW_WINDOW();
						break;
					}
				}
			}
			else if (isLastEnable && m_msg.x > WINDOW_WID * EX_LEFT + 10 && m_msg.y > WINDOW_HEI - 45 && m_msg.x < WINDOW_WID * EX_LEFT + 42 && m_msg.y < WINDOW_HEI - 13) // 如果鼠标在这个区间内
			{
				/// LastPage
				switch (m_msg.message)
				{
					case WM_LBUTTONDOWN:
					{
						canvas_main.SetFillColor(0x999999);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/last_page.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
					case WM_LBUTTONUP:
					{
						textAlign(canvas_main, _T("Last"), 36, 0, _T("微软雅黑"), 0, 0, WINDOW_WID, WINDOW_WID); //do somthing
						file_browser.SetDataPage(file_browser.GetDataPage() - 1);
						file_browser.RenderFileBrowser(canvas_main);

						if (file_browser.IsHomePage())
						{
							isLastEnable = false;
							canvas_main.SetFillColor(WHITE);
							canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * MID_LEFT - 10, WINDOW_HEI - 13, 20, 20);
							imageAlign_alpha(canvas_main, L"sprites/last_page_disabled.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
						}
						else
						{
							canvas_main.SetFillColor(WHITE);
							canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * MID_LEFT - 10, WINDOW_HEI - 13, 20, 20);
							canvas_main.SetFillColor(0xCCCCCC);
							canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
							imageAlign_alpha(canvas_main, L"sprites/last_page.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
						}

						sprintf(page_txt, "%d / %d", file_browser.GetDataPage() + 1, file_browser.GetTotalPages());
						const char* ppage_txt = page_txt;
						textAlign(canvas_main, char2wchar(ppage_txt), 20, 0, L"等线", WINDOW_WID * EX_LEFT, WINDOW_HEI - 45, WINDOW_WID * (MID_LEFT - EX_LEFT) - 10, 32, RIGHT);		/// 10为安全边距

						canvas_main.SetFillColor(WHITE);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
					default:
					{
						// 鼠标指针经过按钮
						canvas_main.SetFillColor(0xDDDDDD);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/last_page.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
				}

			}
			else if (isNextEnable && m_msg.x > WINDOW_WID * EX_LEFT + 50 && m_msg.y > WINDOW_HEI - 45 && m_msg.x < WINDOW_WID * EX_LEFT + 82 && m_msg.y < WINDOW_HEI - 13) // 如果鼠标在这个区间内
			{
				/// NextPage
				switch (m_msg.message)
				{
					case WM_LBUTTONDOWN:
					{
						canvas_main.SetFillColor(0x999999);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 82, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
					case WM_LBUTTONUP:
					{
						textAlign(canvas_main, _T("Next"), 36, 0, _T("微软雅黑"), 0, 0, WINDOW_WID, WINDOW_WID); //do somthing
						file_browser.SetDataPage(file_browser.GetDataPage() + 1);
						file_browser.RenderFileBrowser(canvas_main);

						if (file_browser.IsEndPage())
						{
							isNextEnable = false;
							canvas_main.SetFillColor(WHITE);
							canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * MID_LEFT - 10, WINDOW_HEI - 13, 20, 20);
							imageAlign_alpha(canvas_main, L"sprites/next_page_disabled.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
						}
						else
						{
							canvas_main.SetFillColor(WHITE);
							canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * MID_LEFT - 10, WINDOW_HEI - 13, 20, 20);
							canvas_main.SetFillColor(0xCCCCCC);
							canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 82, WINDOW_HEI - 13, 20, 20);
							imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
						}
						sprintf(page_txt, "%d / %d", file_browser.GetDataPage() + 1, file_browser.GetTotalPages());
						const char* ppage_txt = page_txt;
						textAlign(canvas_main, char2wchar(ppage_txt), 20, 0, L"等线", WINDOW_WID * EX_LEFT, WINDOW_HEI - 45, WINDOW_WID * (MID_LEFT - EX_LEFT) - 10, 32, RIGHT);		/// 10为安全边距

						canvas_main.SetFillColor(WHITE);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/last_page.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
					default:
					{
						// 鼠标指针经过按钮
						canvas_main.SetFillColor(0xDDDDDD);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 82, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
				}

			}

			else if (m_msg.x > WINDOW_WID * EX_LEFT && m_msg.y > WINDOW_WID * EX_LEFT && m_msg.x < WINDOW_WID * MID_LEFT && m_msg.y < WINDOW_HEI - 45)
			{
				int btn_index = file_browser.InWhichButton(m_msg);
				if (btn_index != -1) 
				{
					btn = file_browser.file_buttons[btn_index];
					file_browser.RenderFileBrowser(canvas_main);
					btn.draw_hover(canvas_main);
					if (btn.isIn(m_msg))
					{
						if (btn.isLCD(m_msg))
						{

						}
						else if (btn.isLCU(m_msg))
						{
							file_browser.LoadData(m_msg);
							file_browser.DrawDataInfo(canvas_main);
							REDRAW_WINDOW();
						}
					}
				}
			}
			else if (file_browser.IsInFuncArea(m_msg))
			{
				int btn_index = file_browser.InWhichFuncBtn(m_msg);
				if (btn_index == -1);
				else if (file_browser.filters[btn_index].isIn(m_msg))
				{
					file_browser.filters[btn_index].draw_detailed_hover(canvas_main, true);
					file_browser.filters[btn_index].draw_default_txt(canvas_main);
					REDRAW_WINDOW();
					if (file_browser.filters[btn_index].isLCD(m_msg))
					{
						file_browser.filters[btn_index].draw_detailed_push(canvas_main, true);
						file_browser.filters[btn_index].draw_default_txt(canvas_main);
						REDRAW_WINDOW();
					}
					if (file_browser.filters[btn_index].isLCU(m_msg))
					{
						file_browser.FilterData(btn_index);
						file_browser.DrawDataChart(canvas_main, file_browser.info.data, BLUE);
						file_browser.ClearChartDrawingZone(canvas_main);
						file_browser.DrawDataChart(canvas_main, file_browser.info.processed_data, RED);
						REDRAW_WINDOW();
					}
				}
				else
				{
					if (file_browser.filters[btn_index].isPressed())
					{
						file_browser.filters[btn_index].draw_detailed_hover(canvas_main, true);
						file_browser.filters[btn_index].draw_default_txt(canvas_main);
						REDRAW_WINDOW();
					}
					else
					{
						file_browser.filters[btn_index].draw_detailed_default(canvas_main, true);
						file_browser.filters[btn_index].draw_default_txt(canvas_main);
						REDRAW_WINDOW();
					}
				}
			}


			else if (
			// FileBrowser
			(m_msg.x > WINDOW_WID * EX_LEFT - out_r &&	// 文件浏览器左端
			m_msg.x < WINDOW_WID * EX_LEFT) ||
			(m_msg.y > WINDOW_WID * EX_LEFT - out_r &&	// 文件浏览器上端
			m_msg.y < WINDOW_WID * EX_LEFT) ||
			(m_msg.x > WINDOW_WID * MID_LEFT &&			// 文件浏览器右端
			m_msg.x < WINDOW_WID * MID_LEFT + out_r) ||

			// 登录按钮
			(m_msg.x > WINDOW_WID * (1 - EX_LEFT * 3 / 4) - out_r &&
			m_msg.x < WINDOW_WID * (1 - EX_LEFT * 3 / 4)) ||
			(m_msg.x > WINDOW_WID * (1 - EX_LEFT / 4) &&
			m_msg.x < WINDOW_WID * (1 - EX_LEFT / 4) + out_r) ||
			(m_msg.y > WINDOW_WID * (1 - EX_LEFT / 4) - out_r &&
			m_msg.y < WINDOW_WID * EX_LEFT * 3 / 4) ||
			(m_msg.y > WINDOW_WID * EX_LEFT * 3 / 4 &&
			m_msg.y < WINDOW_WID * EX_LEFT * 3 / 4 + out_r))

			// 默认状态（伪退出事件）
			{
				/// LOGIN
				canvas_main.SetFillColor(0xEFE1CF);
				canvas_main.SolidRoundRect(WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * (1 - EX_LEFT / 4), WINDOW_WID * EX_LEFT * 3 / 4, 20, 20);
				imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);

				/// LastPage
				if (isLastEnable)
				{
					canvas_main.SetFillColor(WHITE);
					canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
					imageAlign_alpha(canvas_main, L"sprites/last_page.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
				}
				else
				{
					canvas_main.SetFillColor(WHITE);
					canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
					imageAlign_alpha(canvas_main, L"sprites/last_page_disabled.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);

				}

				/// NextPage
				if (isNextEnable)
				{
					canvas_main.SetFillColor(WHITE);
					canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 82, WINDOW_HEI - 13, 20, 20);
					imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
				}
				else
				{
					canvas_main.SetFillColor(WHITE);
					canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 82, WINDOW_HEI - 13, 20, 20);
					imageAlign_alpha(canvas_main, L"sprites/next_page_disabled.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
				}

				file_browser.RenderFileBrowser(canvas_main);
				REDRAW_WINDOW();
			}


			// 处理其它事件
			if (file_browser.IsHomePage())
				isLastEnable = false;
			else
				isLastEnable = true;
			if (file_browser.IsEndPage())
				isNextEnable = false;
			else
				isNextEnable = true;

		}


		hiex::init_end(hwnd);
		break;
	}
}


void menu()
{
	int username = 0, statu = 0;
	printf("___________________________________\n");
	if (token != -1)
	{

		printf("Welcome!%s\n", username);
		printf("【1】Module A\n");
		printf("【2】Module B\n");
		printf("【3】退出登录\n");
	}
	else
	{
		printf("您还未登录，请先登录！");
		printf("【1】登录");
		printf("【2】注册");
	}
	printf("___________________________________\n");



	char option = getchar();
	switch (option)
	{
	case '1':
		while (1)
		{
			system("cls");
			//Menu();
			//Operate();
		}break;
	case 50:
		while (1)
		{
			system("cls");
			//Menu1();
			//Operate1();
		}break; break;
	case 48:exit(0);
	}
}

int main()
{

	home();

	getchar();
	return 0;
}