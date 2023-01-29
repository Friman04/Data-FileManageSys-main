#pragma once
#include <io.h>
#include <time.h>
#include <string.h>
#include "HiEasyX.h"

#define MAX_LEN 4096	// �ַ���������
#define DATA_NUM 10000	// �����ļ�������
#define FPS 60
#define N 1000			//���ݸ���
//#include<graphics.h>

#ifdef UNICODE  //���ö��ֽ��ַ���
#undef UNICODE
#endif

//
// ��������
//

// �����С
#define ASPECT_RATIO 1.7777777777777778       // ��߱ȣ�16��9��
#define WINDOW_HEI 720                       // ����߶ȴ�С
#define WINDOW_WID WINDOW_HEI*ASPECT_RATIO    // �����ȴ�С

// ƽ������еĳ���
#define PHI 0.618
#define EX_LEFT (PHI - 0.5) / 2
#define MID_LEFT (1 - PHI) / 2

// �������
#define TOP_LEFT     1
#define TOP          2
#define TOP_RIGHT    3
#define LEFT         4
#define CENTER       5
#define RIGHT        6
#define BOTTOM_LEFT  7
#define BOTTOM       8
#define BOTTOM_RIGHT 9