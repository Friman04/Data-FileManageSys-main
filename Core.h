#pragma once
#include "Configuration.h"


/*结构体*/

/*
* @brief 用于存放用户的数据
* @note 两个value为待开发的值
*/
typedef struct
{
    char id[16];        ///<-用户名
    long long uid;      ///<-用户唯一标识
    char pwd[20];       ///<-密码
    int value1;
    int value2;
    int sex;            ///<-性别
    tm reg_date;        ///<-注册日期
}user;

/*
* @brief 文本信息
*/
typedef struct Text  ///<-[?]C++20标准中typerdef名称中使用的未命名的类不能声明非静态数据成员、成员枚举或成员类以外的成员。而该结构体中不包含类的实例化，这个bug的解决方式是命名改结构体。
{
    LPCTSTR str;    ///<-文本内容
    int nHeight;    ///<-文字高度
    int nWidth;     ///<-文字宽度
    LPCTSTR font;   ///<-字体
    COLORREF c;     ///<-颜色
    LONG esc = 0;   ///<-字符串书写角度
    LONG ori = 0;   ///<-每个字符的倾斜角
    int mode = TRANSPARENT;     ///<-文字绘制模式（默认为透明背景）
}Text;

/*
* @brief 数据信息
*/
typedef struct
{
    char filename[MAX_LEN];     ///<-文件名
    tm create_time;             ///<-创建时间
    tm recent_edited_time;      ///<-最近修改时间
    float data[N];              ///<-数据
    float processed_data[N];    ///<-处理后的数据
    int count;                  ///<-数据个数
    float mean;                 ///<-均值
    float variance;             ///<-方差
    float max;                  ///<-最大值
    float min;                  ///<-最小值
    float scale;                ///<-极差
    char status;                ///<-文件状态
    bool is_valid;              ///<-数据文件是否合法
    long long uid;              ///<-最后一次修改者的uid
}dataInfo;

/*
* @brief 两个int
* @note 用于存放坐标
*/
typedef struct
{
    int x, y;
}intPair;

/*
* @brief 两个intPair
* @note 用于存放矩形区域
*/
typedef struct
{
    intPair point1;     ///<- 左上角点
    intPair point2;     ///<- 右下角点
}squaredArea;


/*数组处理方法*/

/**
 * @brief 拷贝数组
 * @param[in] destination       目标数组
 * @param[in] source            源数组
 * @param[in] n 	            数组长度
*/
void arraycopy(float destination[], float source[], int n);

/**
 * @brief 数组相减
 * @param[in] x                 被减数组
 * @param[in] y                 减数组
 * @param[in] z 	            差数组
 * @param[in] n 	            数组长度
*/
void arraysub(float x[], float y[], float z[], int n);

/**
 * @brief 求数组最大值
 * @param[in] a                 一维数组
 * @param[in] n 	            数组长度
*/
float arraymax(float a[], int n);

/**
 * @brief 求数组最小值
 * @param[in] a                 一维数组
 * @param[in] n 	            数组长度
*/
float arraymin(float a[], int n);

/**
 * @brief 求数组范围
 * @param[in] a                 一维数组
 * @param[in] n 	            数组长度
*/
float arrayscale(float a[], int n);


/*数据统计方法*/

/**
 * @brief 求数据均值
 * @param[in] a                 一维数组
 * @param[in] n 	            数组长度
*/
float mean(float a[], int n);

/**
 * @brief 求数据方差
 * @param[in] a                 一维数组
 * @param[in] n 	            数组长度
*/
float variance(float a[], int n);


/*数据分析方法*/

/**
 * @brief 均值滤波1(向右偏移)
 * @param[in] destination       一维目标数组
 * @param[in] source            一维源数组
 * @param[in] n 	            数组长度
 * @param[in] kernel_size       窗口大小（必须为奇数）
*/
int mean_filter1(float destination[], float a[], int n, int kernel_size);

/**
 * @brief 均值滤波2（向左偏移）
 * @param[in] destination       一维目标数组
 * @param[in] source            一维源数组
 * @param[in] n 	            数组长度
 * @param[in] kernel_size       窗口大小（必须为奇数）
*/
int mean_filter2(float destination[], float a[], int n, int kernel_size);


/*对齐绘制方法*/

/**
 * @brief 计算对齐坐标
 * @param[in] x		            背景对象的x坐标
 * @param[in] y			        背景对象的y坐标
 * @param[in] w		            背景对象的宽度
 * @param[in] h			        背景对象的高度
 * @param[in] wid				被绘制对象的宽度
 * @param[in] hei   			被绘制对象的高度
 * @param[in] align_mode   		对齐方式（默认居中对齐）
 * @return                      被绘制对象的坐标
*/
intPair align(int x, int y, int w, int h, int wid, int hei, int align_mode = CENTER);

/**
 * @brief 在矩形区域内加载图像文件并对齐绘制
 * @param[in] canvas		    Canvas类的实例化
 * @param[in] img_file			图片文件位置
 * @param[in] iWidth			图片目标拉伸宽度（为0表示不拉伸）
 * @param[in] iHeight		    图片目标拉伸高度（为0表示不拉伸）
 * @param[in] pivot_x			锚点x坐标（即区域左上角x坐标）
 * @param[in] pivot_y			锚点y坐标（即区域左上角y坐标）
 * @param[in] wid				区域宽度
 * @param[in] hei   			区域高度
 * @param[in] align_mode   		对齐方式（默认居中对齐）
 * @param[in] alpha	            叠加透明度（默认透明度100%/255U）
 * @param[in] isAlpha       	是否开启混合图像透明通道（默认是）
 * @return                      读取到的IMAGE对象
*/
IMAGE imageAlign_alpha(hiex::Canvas& canvas, LPCTSTR img_file, int iWidth, int iHeight, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, BYTE alpha = 255U, bool isAlpha = true);

/**
 * @brief 在矩形区域内对齐绘制文字
 * @param[in] img/canvas        ImageBlock/Canvas类的实例化
 * @param[in] str			    绘制的字符串
 * @param[in] fHeight		    字符高度
 * @param[in] fWidth			字符宽度（如果值为0，则字符串自适应间距）
 * @param[in] font  			字体
 * @param[in] pivot_x			锚点x坐标（即区域左上角x坐标）
 * @param[in] pivot_y			锚点y坐标（即区域左上角y坐标）
 * @param[in] wid				区域宽度
 * @param[in] hei   			区域高度
 * @param[in] align_mode   		对齐方式（默认居中对齐）
 * @param[in] c	                字体颜色
 * @param[in] esc       		字符串的书写角度（单位0.1°）
 * @param[in] ori         		每个字符的书写角度（单位0.1°）
*/
void textAlign(hiex::Canvas& canvas, LPCTSTR str, int fHeight, int fWidth, LPCTSTR font, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, COLORREF c = BLACK, LONG esc = 0L, LONG ori = 0L, int bg = TRANSPARENT);
void textAlign(hiex::ImageBlock& img, LPCTSTR str, int fHeight, int fWidth, LPCTSTR font, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, COLORREF c = BLACK, LONG esc = 0L, LONG ori = 0L, int bg = TRANSPARENT);

/**
 * @deprecated 此函数已经过时，可能在未来版本中废弃！
 * @brief 在矩形区域内对齐绘制文字
 * @param[in] canvas   		    Canvas类的实例化
 * @param[in] str			    绘制的字符串
 * @param[in] fHeight		    字符宽度
 * @param[in] fWidth			字符宽度（如果值为0，则字符串自适应间距）
 * @param[in] font  			字体
 * @param[in] pivot_x			锚点x坐标（即区域左上角x坐标）
 * @param[in] pivot_y			锚点y坐标（即区域左上角y坐标）
 * @param[in] wid				区域宽度
 * @param[in] hei   			区域高度
 * @param[in] align_mode   		对齐方式（默认居中对齐）
 * @param[in] c	                字体颜色
 * @param[in] esc       		字符串的书写角度（单位0.1°）
 * @param[in] ori         		每个字符的书写角度（单位0.1°）
*/
void __TextAlign(hiex::Canvas& canvas, LPCTSTR str, int fHeight, int fWidth, LPCTSTR font, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, COLORREF c = BLACK, LONG esc = 0L, LONG ori = 0L, int bg = TRANSPARENT);

/**
 * @deprecated 此函数已经过时，在 Ver 0.1Alpha2 及以后版本废弃！
 * @brief 在矩形中对齐绘制文字
 * @param[in] x				    矩形左上角x坐标
 * @param[in] y				    矩形左上角y坐标
 * @param[in] width				矩形宽度
 * @param[in] height			矩形高度
 * @param[in] horizontal	    是否水平居中（默认是）
 * @param[in] vertical  		是否垂直居中（默认是）
*/
void __textAlign(LPCTSTR str, int x, int y, int width, int height, bool horizontal = true, bool vertical = true, int mode = TRANSPARENT);


/*其它*/

/**
 * @brief char转换wchat（注意有内存泄露的风险）
 * @param[in] cchar	            char字符串
 * @return                      wchar字符串
*/
wchar_t* char2wchar(const char* cchar);