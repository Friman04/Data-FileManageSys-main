#pragma once
#include <io.h>
#include <time.h>
#include <string.h>
#include "HiEasyX.h"

#ifdef UNICODE  //设置多字节字符集
#undef UNICODE
#endif

#define MAX_LEN 4096							// 字符串缓冲区
#define DATA_NUM 10000							// 数据文件最大个数
#define FPS 60									// 帧率
#define N INT16_MAX								// 数据最长个数
#define DATA_WIDTH 32							// 数据显示位宽
//#include<graphics.h>


//
// 超参数区
//

// 窗体大小
#define ASPECT_RATIO 1.77777777777778			// 宽高比（16：9）
#define WINDOW_HEI 720							// 窗体高度大小
#define WINDOW_WID WINDOW_HEI*ASPECT_RATIO		// 窗体宽度大小

// 平面设计中的常数
#define PHI 0.618
#define EX_LEFT (PHI - 0.5) / 2
#define MID_LEFT (1 - PHI) / 2

// 字体居中
#define TOP_LEFT     1
#define TOP          2
#define TOP_RIGHT    3
#define LEFT         4
#define CENTER       5
#define RIGHT        6
#define BOTTOM_LEFT  7
#define BOTTOM       8
#define BOTTOM_RIGHT 9