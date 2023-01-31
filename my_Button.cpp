#include "my_Button.h"

/// <summary>
/// 被注释的方法已被完全弃用，重新启用有危险
/// </summary>
my_Button::my_Button()
{

}

my_Button::my_Button(int _x, int _y, int _w, int _h)
    :x(_x), y(_y), w(_w), h(_h)
{

}

void my_Button::operator()(int _x, int _y, int _w, int _h)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

int my_Button::getX() { return x; }

int my_Button::getY() { return y; }

int my_Button::getWidth() { return w; }

int my_Button::getHeight() { return h; }

LPCTSTR my_Button::getText() { return text.str; }

//hiex::ImageBlock my_Button::getIcon() { return icon; }
//
//hiex::ImageBlock my_Button::getHoveringImage() { return bg_hover; }
//
//hiex::ImageBlock my_Button::getPushingImage() { return bg_push; }


void my_Button::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void my_Button::setSize(int w, int h)
{
    this->w = w;
    this->h = h;
}

void my_Button::setIconSize(int icon_w, int icon_h)
{
    this->icon_w = icon_w;
    this->icon_h = icon_h;
    this->icon_pos = align(x, y, w, h, icon_w, icon_h);
}

void my_Button::setText(LPCTSTR _str, int _nHeight, int _nWidth, LPCTSTR _font, COLORREF _c, LONG _esc, LONG _ori, int _mode)
{
    text.str = _str;
    text.nHeight = _nHeight;
    text.nWidth = _nWidth;
    text.font = _font;
    text.c = _c;
    text.esc = _esc;
    text.ori = _ori;
    text.mode = _mode;
}

//void my_Button::setImage(hiex::ImageBlock& img)
//{
//    this->icon = img;
//}

void my_Button::setImage(LPCTSTR str)
{
    this->icon_filename = str;
}

void my_Button::setRoundRadius(int r)
{
    this->round_radius = r;
}

bool my_Button::isIn(ExMessage msg)
{
    if (msg.x >= x && msg.x <= x + w && msg.y >= y && msg.y <= y + h)
        return true;
    else
        return false;
}

bool my_Button::isLCD(ExMessage msg)
{
    if (isIn(msg))
    {
        if (msg.message == WM_LBUTTONDOWN)
            return true;
    }
    return false;
}

bool my_Button::isLCU(ExMessage msg)
{
    if (isIn(msg))
    {
        if (msg.message == WM_LBUTTONUP)
            return true;
    }
    return false;
}

//void my_Button::createIconCanvas()
//{
//    icon.CreateCanvas(icon_w, icon_h);
//}
//
//void my_Button::createHoverCanvas()
//{
//    bg_hover.CreateCanvas(w, h);
//}
//
//void my_Button::createPushCanvas()
//{
//    bg_push.CreateCanvas(w, h);
//}
//
//
//void my_Button::draw_default_img()
//{
//    // 绘制图标
//    //createIconCanvas();
//    icon.SetPos(icon_pos.x, icon_pos.y);
//    icon.GetCanvas()->Load_Image_Alpha(icon_filename, 0, 0, false, icon_w, icon_h);
//    icon.bUseSrcAlpha = true;
//    //ReverseAlpha(icon.GetCanvas()->GetBuffer(), icon.GetCanvas()->GetBufferSize());
//}
//
//void my_Button::draw_default_txt()
//{
//    // 绘制按钮文本
//    //createIconCanvas();
//    icon.SetPos(icon_pos.x, icon_pos.y);
//    icon.GetCanvas()->OutTextXY(0, 0, text.str, true, text.c);
//    icon.bUseSrcAlpha = true;
//    ReverseAlpha(icon.GetCanvas()->GetBuffer(), icon.GetCanvas()->GetBufferSize());;
//}
//
//void my_Button::draw_hover()
//{
//    // 绘制鼠标覆盖时图标背景
//    //createBgCanvas(bg_hover);
//    bg_hover.SetPos(x, y);
//    bg_hover.GetCanvas()->SetFillColor(hover_c);
//    bg_hover.GetCanvas()->FillRoundRect(x, y, x + w, y + h, round_radius, round_radius);
//    icon.bUseSrcAlpha = true;
//    ReverseAlpha(icon.GetCanvas()->GetBuffer(), icon.GetCanvas()->GetBufferSize());
//
//}

void my_Button::draw_default_txt(hiex::Canvas& canvas)
{
    textAlign(canvas, text.str, text.nHeight, text.nWidth, text.font, x, y, w, h);
}

void my_Button::draw_hover(hiex::Canvas& canvas)
{
    canvas.SetLineThickness(4);
    canvas.SetLineColor(BLACK);
    canvas.Rectangle(x + 1, y + 1, x + w - 2, y + h - 2);
    REDRAW_WINDOW();
    canvas.SetLineThickness(2);
    canvas.SetLineColor(0xAAAAAA);

}

void my_Button::draw_detailed_default(hiex::Canvas& canvas)
{
    canvas.SetLineStyle(PS_SOLID);
    canvas.SetLineThickness(1);
    canvas.FillRoundRect(x, y, x + w, y + h, 10, 10, true, BLACK, WHITE);
}

void my_Button::draw_detailed_hover(hiex::Canvas& canvas)
{
    canvas.SetLineStyle(PS_SOLID);
    canvas.SetLineThickness(1);
    canvas.FillRoundRect(x, y, x + w, y + h, 10, 10, true, BLACK, hover_c);
}

void my_Button::draw_detailed_push(hiex::Canvas& canvas)
{
    canvas.SetLineStyle(PS_SOLID);
    canvas.SetLineThickness(1);
    canvas.FillRoundRect(x, y, x + w, y + h, 10, 10, true, BLACK, push_c);
}

//void my_Button::draw_push()
//{
//    // 绘制按钮按下时图标背景
//    //createBgCanvas(bg_hover);
//    bg_push.GetCanvas()->SetFillColor(push_c);
//    bg_push.GetCanvas()->FillRoundRect(x, y, x + w, y + h, round_radius, round_radius);
//    icon.bUseSrcAlpha = true;
//    ReverseAlpha(icon.GetCanvas()->GetBuffer(), icon.GetCanvas()->GetBufferSize());
//}