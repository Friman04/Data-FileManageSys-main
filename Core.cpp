#include "Core.h"

wchar_t* char2wchar(const char* cchar)
{
    wchar_t* m_wchar;
    int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
    m_wchar = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
    m_wchar[len] = '\0';
    return m_wchar;
}

intPair align(int x, int y, int w, int h, int wid, int hei, int align_mode)
{
    intPair pos;
    switch (align_mode)
    {
    case 1:
    {
        pos.x = x;
        pos.y = y;
        return pos;
    }
    case 2:
    {
        pos.x = x + w / 2 - wid / 2;
        pos.y = y;
        return pos;
    }
    case 3:
    {
        pos.x = x + w - wid;
        pos.y = y;
        return pos;
    }
    case 4:
    {
        pos.x = x;
        pos.y = y + h / 2 - hei / 2;
        return pos;
    }
    case 5:
    {
        pos.x = x + w / 2 - wid / 2,
            pos.y = y + h / 2 - hei / 2;
        return pos;
    }
    case 6:
    {
        pos.x = x + w - wid;
        pos.y = y + h / 2 - hei / 2;
        return pos;
    }
    case 7:
    {
        pos.x = x;
        pos.y = y + h - hei;
        return pos;
    }
    case 8:
    {
        pos.x = x + w / 2 - wid / 2;
        pos.y = y + h - hei;
        return pos;
    }
    case 9:
    {
        pos.x = x + w - wid;
        pos.y = y + h - hei;
        return pos;
    }
    }
}

IMAGE imageAlign_alpha(hiex::Canvas& canvas,
    LPCTSTR img_file,
    int iWidth,
    int iHeight,
    int pivot_x,
    int pivot_y,
    int wid,
    int hei,
    int align_mode,
    BYTE alpha,
    bool isAlpha)
{
    // 锚点应设置在区域的左上角
    IMAGE img;
    intPair text_pos = align(pivot_x, pivot_y, wid, hei, iWidth, iHeight, align_mode);
    img = canvas.Load_Image_Alpha(img_file, text_pos.x, text_pos.y, false, iWidth, iHeight, alpha, isAlpha);
    return img;
}

void textAlign(hiex::ImageBlock& img,
    LPCTSTR str,
    int fHeight,
    int fWidth,
    LPCTSTR font,
    int pivot_x,
    int pivot_y,
    int wid,
    int hei,
    int align_mode,
    COLORREF c,
    LONG esc,
    LONG ori,
    int bg)
{
    // 锚点应设置在区域的左上角
    img.GetCanvas()->SetTextEscapement(esc);
    img.GetCanvas()->SetTextOrientation(ori);
    img.GetCanvas()->SetBkMode(bg);
    img.GetCanvas()->SetTextStyle(fHeight, fWidth, font);

    intPair text_pos = align(pivot_x, pivot_y, wid, hei, img.GetCanvas()->TextWidth(str), img.GetCanvas()->TextHeight(str), align_mode);
    img.GetCanvas()->OutTextXY(text_pos.x, text_pos.y, str, true, c);
}

void textAlign(hiex::Canvas& canvas, LPCTSTR str, int fHeight, int fWidth, LPCTSTR font, int pivot_x, int pivot_y, int wid, int hei, int align_mode, COLORREF c, LONG esc, LONG ori, int bg)
{
    // 锚点应设置在区域的左上角
    canvas.SetTextEscapement(esc);
    canvas.SetTextOrientation(ori);
    canvas.SetBkMode(bg);
    canvas.SetTextStyle(fHeight, fWidth, font);

    intPair text_pos = align(pivot_x, pivot_y, wid, hei, canvas.TextWidth(str), canvas.TextHeight(str), align_mode);
    canvas.OutTextXY(text_pos.x, text_pos.y, str, true, c);
}

void __TextAlign(hiex::Canvas& canvas,
    LPCTSTR str,
    int fHeight,
    int fWidth,
    LPCTSTR font,
    int pivot_x,
    int pivot_y,
    int wid,
    int hei,
    int align_mode,
    COLORREF c,
    LONG esc,
    LONG ori,
    int bg)
{
    // 锚点应设置在区域的左上角

    canvas.SetTextEscapement(esc);
    canvas.SetTextOrientation(ori);
    canvas.SetBkMode(bg);
    canvas.SetTextStyle(fHeight, fWidth, font);
    switch (align_mode)
    {
    case 1:
        canvas.OutTextXY(pivot_x, pivot_y, str, true, c);
        break;
    case 2:
        canvas.OutTextXY(
            pivot_x + wid / 2 - canvas.TextWidth(str) / 2,
            pivot_y,
            str,
            true, c);
        break;
    case 3:
        canvas.OutTextXY(
            pivot_x + wid - canvas.TextWidth(str),
            pivot_y,
            str,
            true, c);
        break;
    case 4:
        canvas.OutTextXY(
            pivot_x,
            pivot_y + wid / 2 - canvas.TextHeight(str) / 2,
            str,
            true, c);
        break;
    case 5:
        canvas.OutTextXY(
            pivot_x + wid / 2 - canvas.TextWidth(str) / 2,
            pivot_y + hei / 2 - canvas.TextHeight(str) / 2,
            str,
            true, c);
        break;
    case 6:
        canvas.OutTextXY(
            pivot_x + wid - canvas.TextWidth(str),
            pivot_y + hei / 2 - canvas.TextHeight(str) / 2,
            str,
            true, c);
        break;
    case 7:
        canvas.OutTextXY(
            pivot_x,
            pivot_y + hei - canvas.TextHeight(str),
            str,
            true, c);
        break;

    case 8:
        canvas.OutTextXY(
            pivot_x + wid / 2 - canvas.TextWidth(str) / 2,
            pivot_y + hei - canvas.TextHeight(str),
            str,
            true, c);
        break;
    case 9:
        canvas.OutTextXY(
            pivot_x + wid - canvas.TextWidth(str),
            pivot_y + hei - canvas.TextHeight(str),
            str,
            true, c);
        break;
    }
}

void __textAlign(LPCTSTR str, int x, int y, int width, int height, bool horizontal, bool vertical, int mode)
{
    /* 使用原生EasyX绘制，存在兼容性问题，谨慎使用！*/

    LOGFONT font;
    setbkmode(mode);
    gettextstyle(&font);
    int textHeight = font.lfHeight;
    int textWidth = textHeight;
    int strWidth = 0;
    int strNum = lstrlen(str);
    for (int i = 0; i < strNum; ++i)
        strWidth += (str[i] > 127) ? textHeight : textHeight / 2;
    if (strWidth >= width || textHeight >= height)
    {
        outtextxy(x, y, str);
        return;
    }
    if (horizontal)
        x += (width - strWidth) / 2;
    if (vertical)
        y += (height - textHeight) / 2;
    outtextxy(x, y, str);
}
