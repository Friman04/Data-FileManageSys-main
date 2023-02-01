#pragma once
#include "Configuration.h"


/*�ṹ��*/

/*
* @brief ���ڴ���û�������
* @note ����valueΪ��������ֵ
*/
typedef struct
{
    char id[16];        ///<-�û���
    long long uid;      ///<-�û�Ψһ��ʶ
    char pwd[20];       ///<-����
    int value1;
    int value2;
    int sex;            ///<-�Ա�
    tm reg_date;        ///<-ע������
}user;

/*
* @brief �ı���Ϣ
*/
typedef struct Text  ///<-[?]C++20��׼��typerdef������ʹ�õ�δ�������಻�������Ǿ�̬���ݳ�Ա����Աö�ٻ��Ա������ĳ�Ա�����ýṹ���в��������ʵ���������bug�Ľ����ʽ�������Ľṹ�塣
{
    LPCTSTR str;    ///<-�ı�����
    int nHeight;    ///<-���ָ߶�
    int nWidth;     ///<-���ֿ��
    LPCTSTR font;   ///<-����
    COLORREF c;     ///<-��ɫ
    LONG esc = 0;   ///<-�ַ�����д�Ƕ�
    LONG ori = 0;   ///<-ÿ���ַ�����б��
    int mode = TRANSPARENT;     ///<-���ֻ���ģʽ��Ĭ��Ϊ͸��������
}Text;

/*
* @brief ������Ϣ
*/
typedef struct
{
    char filename[MAX_LEN];     ///<-�ļ���
    tm create_time;             ///<-����ʱ��
    tm recent_edited_time;      ///<-����޸�ʱ��
    float data[N];              ///<-����
    float processed_data[N];    ///<-����������
    int count;                  ///<-���ݸ���
    float mean;                 ///<-��ֵ
    float variance;             ///<-����
    float max;                  ///<-���ֵ
    float min;                  ///<-��Сֵ
    float scale;                ///<-����
    char status;                ///<-�ļ�״̬
    bool is_valid;              ///<-�����ļ��Ƿ�Ϸ�
    long long uid;              ///<-���һ���޸��ߵ�uid
}dataInfo;

/*
* @brief ����int
* @note ���ڴ������
*/
typedef struct
{
    int x, y;
}intPair;

/*
* @brief ����intPair
* @note ���ڴ�ž�������
*/
typedef struct
{
    intPair point1;     ///<- ���Ͻǵ�
    intPair point2;     ///<- ���½ǵ�
}squaredArea;


/*���鴦����*/

/**
 * @brief ��������
 * @param[in] destination       Ŀ������
 * @param[in] source            Դ����
 * @param[in] n 	            ���鳤��
*/
void arraycopy(float destination[], float source[], int n);

/**
 * @brief �������
 * @param[in] x                 ��������
 * @param[in] y                 ������
 * @param[in] z 	            ������
 * @param[in] n 	            ���鳤��
*/
void arraysub(float x[], float y[], float z[], int n);

/**
 * @brief ���������ֵ
 * @param[in] a                 һά����
 * @param[in] n 	            ���鳤��
*/
float arraymax(float a[], int n);

/**
 * @brief ��������Сֵ
 * @param[in] a                 һά����
 * @param[in] n 	            ���鳤��
*/
float arraymin(float a[], int n);

/**
 * @brief �����鷶Χ
 * @param[in] a                 һά����
 * @param[in] n 	            ���鳤��
*/
float arrayscale(float a[], int n);


/*����ͳ�Ʒ���*/

/**
 * @brief �����ݾ�ֵ
 * @param[in] a                 һά����
 * @param[in] n 	            ���鳤��
*/
float mean(float a[], int n);

/**
 * @brief �����ݷ���
 * @param[in] a                 һά����
 * @param[in] n 	            ���鳤��
*/
float variance(float a[], int n);


/*���ݷ�������*/

/**
 * @brief ��ֵ�˲�1(����ƫ��)
 * @param[in] destination       һάĿ������
 * @param[in] source            һάԴ����
 * @param[in] n 	            ���鳤��
 * @param[in] kernel_size       ���ڴ�С������Ϊ������
*/
int mean_filter1(float destination[], float a[], int n, int kernel_size);

/**
 * @brief ��ֵ�˲�2������ƫ�ƣ�
 * @param[in] destination       һάĿ������
 * @param[in] source            һάԴ����
 * @param[in] n 	            ���鳤��
 * @param[in] kernel_size       ���ڴ�С������Ϊ������
*/
int mean_filter2(float destination[], float a[], int n, int kernel_size);


/*������Ʒ���*/

/**
 * @brief �����������
 * @param[in] x		            ���������x����
 * @param[in] y			        ���������y����
 * @param[in] w		            ��������Ŀ��
 * @param[in] h			        ��������ĸ߶�
 * @param[in] wid				�����ƶ���Ŀ��
 * @param[in] hei   			�����ƶ���ĸ߶�
 * @param[in] align_mode   		���뷽ʽ��Ĭ�Ͼ��ж��룩
 * @return                      �����ƶ��������
*/
intPair align(int x, int y, int w, int h, int wid, int hei, int align_mode = CENTER);

/**
 * @brief �ھ��������ڼ���ͼ���ļ����������
 * @param[in] canvas		    Canvas���ʵ����
 * @param[in] img_file			ͼƬ�ļ�λ��
 * @param[in] iWidth			ͼƬĿ�������ȣ�Ϊ0��ʾ�����죩
 * @param[in] iHeight		    ͼƬĿ������߶ȣ�Ϊ0��ʾ�����죩
 * @param[in] pivot_x			ê��x���꣨���������Ͻ�x���꣩
 * @param[in] pivot_y			ê��y���꣨���������Ͻ�y���꣩
 * @param[in] wid				������
 * @param[in] hei   			����߶�
 * @param[in] align_mode   		���뷽ʽ��Ĭ�Ͼ��ж��룩
 * @param[in] alpha	            ����͸���ȣ�Ĭ��͸����100%/255U��
 * @param[in] isAlpha       	�Ƿ������ͼ��͸��ͨ����Ĭ���ǣ�
 * @return                      ��ȡ����IMAGE����
*/
IMAGE imageAlign_alpha(hiex::Canvas& canvas, LPCTSTR img_file, int iWidth, int iHeight, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, BYTE alpha = 255U, bool isAlpha = true);

/**
 * @brief �ھ��������ڶ����������
 * @param[in] img/canvas        ImageBlock/Canvas���ʵ����
 * @param[in] str			    ���Ƶ��ַ���
 * @param[in] fHeight		    �ַ��߶�
 * @param[in] fWidth			�ַ���ȣ����ֵΪ0�����ַ�������Ӧ��ࣩ
 * @param[in] font  			����
 * @param[in] pivot_x			ê��x���꣨���������Ͻ�x���꣩
 * @param[in] pivot_y			ê��y���꣨���������Ͻ�y���꣩
 * @param[in] wid				������
 * @param[in] hei   			����߶�
 * @param[in] align_mode   		���뷽ʽ��Ĭ�Ͼ��ж��룩
 * @param[in] c	                ������ɫ
 * @param[in] esc       		�ַ�������д�Ƕȣ���λ0.1�㣩
 * @param[in] ori         		ÿ���ַ�����д�Ƕȣ���λ0.1�㣩
*/
void textAlign(hiex::Canvas& canvas, LPCTSTR str, int fHeight, int fWidth, LPCTSTR font, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, COLORREF c = BLACK, LONG esc = 0L, LONG ori = 0L, int bg = TRANSPARENT);
void textAlign(hiex::ImageBlock& img, LPCTSTR str, int fHeight, int fWidth, LPCTSTR font, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, COLORREF c = BLACK, LONG esc = 0L, LONG ori = 0L, int bg = TRANSPARENT);

/**
 * @deprecated �˺����Ѿ���ʱ��������δ���汾�з�����
 * @brief �ھ��������ڶ����������
 * @param[in] canvas   		    Canvas���ʵ����
 * @param[in] str			    ���Ƶ��ַ���
 * @param[in] fHeight		    �ַ����
 * @param[in] fWidth			�ַ���ȣ����ֵΪ0�����ַ�������Ӧ��ࣩ
 * @param[in] font  			����
 * @param[in] pivot_x			ê��x���꣨���������Ͻ�x���꣩
 * @param[in] pivot_y			ê��y���꣨���������Ͻ�y���꣩
 * @param[in] wid				������
 * @param[in] hei   			����߶�
 * @param[in] align_mode   		���뷽ʽ��Ĭ�Ͼ��ж��룩
 * @param[in] c	                ������ɫ
 * @param[in] esc       		�ַ�������д�Ƕȣ���λ0.1�㣩
 * @param[in] ori         		ÿ���ַ�����д�Ƕȣ���λ0.1�㣩
*/
void __TextAlign(hiex::Canvas& canvas, LPCTSTR str, int fHeight, int fWidth, LPCTSTR font, int pivot_x, int pivot_y, int wid, int hei, int align_mode = CENTER, COLORREF c = BLACK, LONG esc = 0L, LONG ori = 0L, int bg = TRANSPARENT);

/**
 * @deprecated �˺����Ѿ���ʱ���� Ver 0.1Alpha2 ���Ժ�汾������
 * @brief �ھ����ж����������
 * @param[in] x				    �������Ͻ�x����
 * @param[in] y				    �������Ͻ�y����
 * @param[in] width				���ο��
 * @param[in] height			���θ߶�
 * @param[in] horizontal	    �Ƿ�ˮƽ���У�Ĭ���ǣ�
 * @param[in] vertical  		�Ƿ�ֱ���У�Ĭ���ǣ�
*/
void __textAlign(LPCTSTR str, int x, int y, int width, int height, bool horizontal = true, bool vertical = true, int mode = TRANSPARENT);


/*����*/

/**
 * @brief charת��wchat��ע�����ڴ�й¶�ķ��գ�
 * @param[in] cchar	            char�ַ���
 * @return                      wchar�ַ���
*/
wchar_t* char2wchar(const char* cchar);