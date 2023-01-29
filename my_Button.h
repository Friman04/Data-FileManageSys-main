#pragma once
#include "Core.h"

class my_Button
{
/// <summary>
/// 重写底层时被废弃的类，但部分方法仍有用。
/// </summary>
public:
    my_Button();
    my_Button(int _x, int _y, int _w, int _h);
    void operator()(int _x, int _y, int _w, int _h);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    LPCTSTR getText();
    //hiex::ImageBlock getIcon();
    //hiex::ImageBlock getHoveringImage();
    //hiex::ImageBlock getPushingImage();
    void setPos(int x, int y);
    void setSize(int w, int h);
    void setIconSize(int icon_w, int icon_h);
    void setText(LPCTSTR str);
    void setImage(hiex::ImageBlock& img);
    void setImage(LPCTSTR str);
    void setRoundRadius(int r);

    bool isIn(ExMessage msg);
    bool isLCD(ExMessage msg);
    bool isLCU(ExMessage msg);
    void createIconCanvas();
    void createHoverCanvas();
    void createPushCanvas();

    void draw_default_img();
    void draw_default_txt();
    //void draw_hover();
    void draw_hover(hiex::Canvas& canvas);
    void draw_push();

    ~my_Button() {}

private:
    int x;
    int y;
    int w;
    int h;
    int icon_w;
    int icon_h;
    bool isRound = true;
    int round_radius = 20;
    Text text;
    LPCTSTR icon_filename;
    //hiex::ImageBlock icon;
    //hiex::ImageBlock bg_hover;
    //hiex::ImageBlock bg_push;
    COLORREF cur_c;
    COLORREF default_c;
    COLORREF hover_c = RGB(245, 245, 245);
    COLORREF push_c = RGB(225, 225, 225);

private:
    intPair icon_pos;
};

