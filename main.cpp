/*******************************************
 * @note		�ð汾�����ύ����ҵʹ�ã�
 * @author		�紴2202-����ͮ-20221072060
 * @email		272316212@qq.com
 * @site		https://github.com/Friman04/Data-FileManageSys-main
 * @date		2023.01.12
 * @envir		Windows 11 dev_Build 25272.rs_prerelease.221216-1237 | Visual Studio 2022 | EasyX_20220901 | HiEasyX Ver 0.3.0
 * @version     0.1Beta3d
 *
 * @note		����Ŀʹ���˻��� EasyX ����չ HiEasyX����ȷ�������а�װ�� EasyX
 *				����ֻ���� Windows ���������У�Ӧ���� Windows 10/11 �� Visual Studio �±�������ݲ�֧�� MinGW ����������������δ���ԣ�����֤��������������
 *
 * @note		д�����ʱ�� Windows Defence �������Ʋ�����Ц����
 * @note		Ŀǰ��֪���ڵ�bug���������޸�bug���Ʋ�������־��
 *				1.���޷��ա�[2023-01-12]���ڴ�С����������ƺ����йصĳߴ����ʵ�ʾ�Ϊ�����õ�1.5��
 *					[���ܵ�ԭ��]δ֪��
 *					[�������]�ޡ�
 *				2.���޷��ա�[2023-01-13]��Ⱦ���ȵ�
 *					[���ܵ�ԭ��]δ֪��
 *					[�������]�ޡ�
 *				1.���޷��ա�[2023-01-27]�ļ���Դ���������ļ��������ڷ�Ӣ���ַ����ܻ�ʹ��ĩβ��ʾ���̻����
 *					[����ԭ��]ͨ�������ַ�����ȷ����ʾ�ַ�������
 *					[���еĽ������]ͨ��get�ı����ܿ����������ʾ�ַ������������ܼ���΢��Ӱ�����ܣ�
 *				2.�����ء����ѽ����[2023-01-26]ʹ��HiEasyX�ṩ��Canvas��չImageBlock��Layer��Scene�µ�Render()��Redraw()�������´��������Ϣ����
 *					[���ܵ�ԭ��]δ֪��
 *					[���еĽ������]��д�ײ㣬��ʹ��Canvas��չ��
 * 
 * @bug			1.�ļ�������ڶ�ҳ�޷�ʹ��
 * @bug			2.��������
 * @bug			3.��ѡ���ļ�ʱż���ļ���������зָ�����ȾΪ�;�ֵ��һ���Ļ�ɫ
 * @bug			4.ż����ϵͳ����
 * @bug			5.�ļ���Դ���������ļ��������ڷ�Ӣ���ַ����ܻ�ʹ��ĩβ��ʾ���̻����
 *******************************************/

#define _CRT_SECURE_NO_WARNINGS

#define _SYS_VER_STR_	L"Ver 0.1Beta3d"

#include "my_Button.h"
#include "FileBrowser.h"

 //
 // �Ա���������
 //

char token; // δʹ��



/*���������û��˺�������ļ�*/
void createFile()
{
	FILE* fp;
	if ((fopen("users.txt", "rb")) == NULL)                 // ������ļ�������
	{
		if ((fopen("users.txt", "wb+")) == NULL)
		{
			printf("�޷������ļ���\n");
			exit(0);
		}
	}
}

int index()
{
	printf("___________________________________\n");
	printf("Welcome!\n");
	printf("�ڽ�һ����ʹ��ǰ������Ҫ���е�¼��\n");
	printf("��1��ע��\n");
	printf("��2����¼\n");
	printf("___________________________________\n");
	printf("�������Ӧ��ţ�");

	int kbhit = getchar();
	getchar();
	return kbhit;
}

int indexInter()
{
	switch (index())
	{
	case 1:
		break;
	case 2:
		break;
	default:
		printf("��Ч�����룬���������룡");
	}

	return 0;
}

/*ע��*/
void reg()  // ���ṹ��Ĵ�С��һ��д����߶���1���ṹ���С
{
	user a, b;
	FILE* fp = NULL;
	errno_t err = 0;
	char temp[20];
	int count = 0;
	fp = fopen("users.txt", "r");
	fread(&b, sizeof(user), 1, fp);   // ��b����users

	printf("___________________________________\n");
	printf("��ӭ����ע����棡\n");
	Sleep(1000);
	printf("��info���û������ɳ���16���ַ�\n");
	printf("��info������q�ɷ���\n");
	printf("�������û���:\n");
	scanf("%s", &a.id);
	if (*a.id == 'q')
		return;
	while (1)
	{
		if (strcmp(a.id, b.id)) // ���ab��ͬ
		{
			if (!feof(fp))    // ���δ���ļ�β
			{
				fread(&b, sizeof(user), 1, fp);
			}
			else
				break;
		}
		else

		{
			printf("���û����Ѵ��ڣ�������ע�ᣡ\n");
			Sleep(1000);
			fclose(fp);
			return;
		}
	}



	printf("�������Ա�(1��Ů��/2���У�/3�������ˣ�)��\n");
	scanf("%d", &a.sex);
	while (a.sex != 1 && a.sex != 2 && a.sex != 3)
	{
		printf("����ǻ����˵Ļ�������3Ŷ-��-\n");
		scanf("%d", &a.sex);
	}
	getchar();
	while (1)
	{
		printf("����������\n");
		scanf(" %s", &a.pwd);
		printf("��ȷ������\n");
		scanf(" %s", &temp);

		if (!strcmp(a.pwd, temp))
		{
			fp = fopen("users.txt", "a");
			fwrite(&a, sizeof(user), 1, fp);
			printf("�˺�ע��ɹ������¼��\n");
			Sleep(500);
			fclose(fp);
			return;
		}
		else
		{
			printf("�������벻ƥ�䣡���������룡\n");
		}
	}
}

/*��¼ϵͳ*/
void login()
{
	user a, b;
	FILE* fp;
	fp = fopen("users.txt", "r");
	fread(&b, sizeof(user), 1, fp);
	printf("___________________________________\n");
	printf("��ӭ������¼���棡\n");
	Sleep(500);
	printf("��info������q�ɷ���\n");
	printf("�������˺�\n");

	scanf("%s", &a.id);
	if (*a.id == 'q')
		return;
	while (1)
	{
		if (strcmp(a.id, b.id) == 0)         // ����д��û���
		{
			break;
		}
		else
		{
			if (!feof(fp))  // ����ļ�û�ж���                            

			{
				fread(&b, sizeof(user), 1, fp);
			}

			else
			{
				printf("���û��������ڣ����������룡\n");
				Sleep(500);
				fclose(fp);
				return;
			}
		}
	}
	printf("����������\n");
	scanf("%s", &a.pwd);
	while (1)
	{

		if (strcmp(a.pwd, b.pwd) == 0)
		{
			fclose(fp);
			printf("��¼�ɹ�,��ӭʹ��!");
			//token = &a.id;  /*bug*/
			Sleep(500);
			return;
		}
		else
		{
			printf("���벻��ȷ!��������������\n");
			scanf("%s", &a.pwd);
		}

	}
}


/*
void home_test()
{
	hiex::Canvas canvas_main;
	hiex::Window wnd(WINDOW_WID, WINDOW_HEI);
	wnd.BindCanvas(&canvas_main);
	hiex::AutoExit();
	HWND hwnd = wnd.GetHandle();

	// ����1
	canvas_main.Clear(true, WHITE);  //���ñ�����ɫ

	// ����
	hiex::ImageBlock dividing_line;
	dividing_line.CreateCanvas(10, WINDOW_HEI);
	dividing_line.GetCanvas()->SetLineStyle(PS_SOLID, 2);
	dividing_line.GetCanvas()->SetLineColor(0xEEEEEE);
	dividing_line.GetCanvas()->Line(WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * MID_LEFT, WINDOW_HEI); // �ָ���Դ�������ͻ�ͼ��
	dividing_line.bUseSrcAlpha = true;
	ReverseAlpha(dividing_line.GetCanvas()->GetBuffer(), dividing_line.GetCanvas()->GetBufferSize());

	// ����2
	hiex::ImageBlock bg_left;
	hiex::ImageBlock bg_top;

	bg_left.CreateCanvas(WINDOW_WID * EX_LEFT, WINDOW_HEI);
	bg_left.GetCanvas()->SetFillColor(0x662015);
	bg_left.GetCanvas()->FillRectangle(0, 0, WINDOW_WID * EX_LEFT, WINDOW_HEI); // �������ɫ����

	bg_top.CreateCanvas(WINDOW_WID, WINDOW_WID * EX_LEFT);
	bg_top.GetCanvas()->SetFillColor(0xEFE1CF);
	bg_top.GetCanvas()->FillRectangle(0, 0, WINDOW_WID, WINDOW_WID * EX_LEFT); // ����ǳ��ɫ����

	//logo
	hiex::ImageBlock logo;
	logo.CreateCanvas(WINDOW_WID * EX_LEFT - 1, WINDOW_WID * EX_LEFT - 1);
	logo.GetCanvas()->Load_Image_Alpha(L"sprites/logo_light.png", 0, 0, false, WINDOW_WID * EX_LEFT - 1, WINDOW_WID * EX_LEFT - 1, 255U, true);

	// ����
	hiex::ImageBlock title;
	hiex::ImageBlock info;

	title.CreateCanvas(WINDOW_WID, WINDOW_HEI);
	textAlign(title, L"��ҵ���ݷ������ļ���Ϣ����ϵͳ", 36, 0, L"΢���ź�", WINDOW_WID * EX_LEFT, 0, WINDOW_WID * (1 - EX_LEFT), WINDOW_WID * EX_LEFT); // ����
	title.bUseSrcAlpha = true;
	ReverseAlpha(title.GetCanvas()->GetBuffer(), title.GetCanvas()->GetBufferSize());

	info.CreateCanvas(WINDOW_WID, WINDOW_HEI);
	textAlign(info, L"Created by Friman " _SYS_VER_STR_, 16, 0, L"Arial", 0, 0, WINDOW_WID, WINDOW_HEI, BOTTOM_RIGHT, GRAY); // ��Ϣ
	info.bUseSrcAlpha = true;
	ReverseAlpha(info.GetCanvas()->GetBuffer(), info.GetCanvas()->GetBufferSize());

	// ��ť
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
	hiex::Layer BG; // ��̬����ͼ��
	hiex::Layer inter; // ��̬����ͼ��

	BG.push_back(&bg_left);
	BG.push_back(&bg_top);
	BG.push_back(&dividing_line);
	BG.push_back(&logo);
	BG.push_back(&title);
	BG.push_back(&info);

	inter.push_back(&login_icon);

	s.push_back(&BG);
	s.push_back(&inter);


	// ��ʼ������
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

	while (1)
	{
		/*����GUI���*/


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
		edit.SetFont(26, 0, L"΢���ź�");
		*/


		// ����1
		canvas_main.Clear(true, WHITE);  //���ñ�����ɫ

		// ����
		canvas_main.SetLineStyle(PS_SOLID, 2);
		canvas_main.Line(WINDOW_WID * MID_LEFT, WINDOW_WID * EX_LEFT, WINDOW_WID * MID_LEFT, WINDOW_HEI, true, BLACK); // �ָ���Դ�������ͻ�ͼ��

		// ����2
		canvas_main.SetFillColor(0x662015);
		canvas_main.SolidRectangle(0, 0, WINDOW_WID * EX_LEFT, WINDOW_HEI); // �������ɫ����
		canvas_main.SetFillColor(0xEFE1CF);
		canvas_main.SolidRectangle(0, 0, WINDOW_WID, WINDOW_WID * EX_LEFT); // ����ǳ��ɫ����
		file_browser.ClearDataDrawingZone(canvas_main);
		//logo
		canvas_main.Load_Image_Alpha(L"sprites/logo_light.png", 0, 0, false, WINDOW_WID * EX_LEFT + 1, WINDOW_WID * EX_LEFT + 1, 255U, true);

		// ����
		textAlign(canvas_main, L"��ҵ���ݷ������ļ���Ϣ����ϵͳ", 36, 0, L"����", WINDOW_WID * EX_LEFT, 0, WINDOW_WID * (1 - EX_LEFT), WINDOW_WID * EX_LEFT); // ����
		textAlign(canvas_main, L"Created by Friman " _SYS_VER_STR_, 16, 0, L"Arial", 0, 0, WINDOW_WID, WINDOW_HEI, BOTTOM_RIGHT, GRAY); // ��Ϣ


		// ������ť����

		imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
		imageAlign_alpha(canvas_main, L"sprites/last_page_disabled.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
		imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);



		// ��ť�ؼ��߼�

		// ��Դ������
		file_browser.LoadDataFileName("data/*.txt");
		file_browser.FlushDataIndex();
		canvas_main.SetLineColor(0xAAAAAA);
		file_browser.RenderFileBrowser(canvas_main);  //��ʼ������

		char page_txt[32];
		sprintf(page_txt, "%d / %d", file_browser.GetDataPage() + 1, file_browser.GetTotalPages());
		const char* ppage_txt = page_txt;
		textAlign(canvas_main, char2wchar(ppage_txt), 20, 0, L"����", WINDOW_WID * EX_LEFT, WINDOW_HEI - 45, WINDOW_WID * (MID_LEFT - EX_LEFT) - 10, 32, RIGHT);		/// 10Ϊ��ȫ�߾�

		REDRAW_WINDOW();
		// ��ť�Ƿ����
		bool isLastEnable = false;
		bool isNextEnable = true;

		ExMessage m_msg;


		int count = 0;
		while (1)
		{
			count++;


			m_msg = getmessage(EX_MOUSE);

			my_Button btn;

			if (m_msg.x > WINDOW_WID * (1 - EX_LEFT * 3 / 4) && m_msg.y > WINDOW_WID * EX_LEFT / 4 && m_msg.x < WINDOW_WID * (1 - EX_LEFT / 4) && m_msg.y < WINDOW_WID * EX_LEFT * 3 / 4) // �����������������
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
						textAlign(canvas_main, _T("LOGIN"), 36, 0, _T("΢���ź�"), 0, 0, WINDOW_WID, WINDOW_WID); //do somthing

						canvas_main.SetFillColor(0xCCCCCC);
						canvas_main.SolidRoundRect(WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * (1 - EX_LEFT / 4), WINDOW_WID * EX_LEFT * 3 / 4, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
						REDRAW_WINDOW();
						break;
					}
					default:
					{
						// ���ָ�뾭����ť
						canvas_main.SetFillColor(0xDDDDDD);
						canvas_main.SolidRoundRect(WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * (1 - EX_LEFT / 4), WINDOW_WID * EX_LEFT * 3 / 4, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/login.png", 32, 32, WINDOW_WID * (1 - EX_LEFT * 3 / 4), WINDOW_WID * EX_LEFT / 4, WINDOW_WID * EX_LEFT / 2, WINDOW_WID * EX_LEFT / 2);
						REDRAW_WINDOW();
						break;
					}
				}
			}
			else if (isLastEnable && m_msg.x > WINDOW_WID * EX_LEFT + 10 && m_msg.y > WINDOW_HEI - 45 && m_msg.x < WINDOW_WID * EX_LEFT + 42 && m_msg.y < WINDOW_HEI - 13) // �����������������
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
						textAlign(canvas_main, _T("Last"), 36, 0, _T("΢���ź�"), 0, 0, WINDOW_WID, WINDOW_WID); //do somthing
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
						textAlign(canvas_main, char2wchar(ppage_txt), 20, 0, L"����", WINDOW_WID * EX_LEFT, WINDOW_HEI - 45, WINDOW_WID * (MID_LEFT - EX_LEFT) - 10, 32, RIGHT);		/// 10Ϊ��ȫ�߾�

						canvas_main.SetFillColor(WHITE);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/next_page.png", 32, 32, WINDOW_WID * EX_LEFT + 50, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
					default:
					{
						// ���ָ�뾭����ť
						canvas_main.SetFillColor(0xDDDDDD);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/last_page.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
				}

			}
			else if (isNextEnable && m_msg.x > WINDOW_WID * EX_LEFT + 50 && m_msg.y > WINDOW_HEI - 45 && m_msg.x < WINDOW_WID * EX_LEFT + 82 && m_msg.y < WINDOW_HEI - 13) // �����������������
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
						textAlign(canvas_main, _T("Next"), 36, 0, _T("΢���ź�"), 0, 0, WINDOW_WID, WINDOW_WID); //do somthing
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
						textAlign(canvas_main, char2wchar(ppage_txt), 20, 0, L"����", WINDOW_WID * EX_LEFT, WINDOW_HEI - 45, WINDOW_WID * (MID_LEFT - EX_LEFT) - 10, 32, RIGHT);		/// 10Ϊ��ȫ�߾�

						canvas_main.SetFillColor(WHITE);
						canvas_main.SolidRoundRect(WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, WINDOW_WID * EX_LEFT + 42, WINDOW_HEI - 13, 20, 20);
						imageAlign_alpha(canvas_main, L"sprites/last_page.png", 32, 32, WINDOW_WID * EX_LEFT + 10, WINDOW_HEI - 45, 32, 32);
						REDRAW_WINDOW();
						break;
					}
					default:
					{
						// ���ָ�뾭����ť
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



			else    // Ĭ��״̬
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


			// ���������¼�
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
		printf("��1��Module A\n");
		printf("��2��Module B\n");
		printf("��3���˳���¼\n");
	}
	else
	{
		printf("����δ��¼�����ȵ�¼��");
		printf("��1����¼");
		printf("��2��ע��");
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