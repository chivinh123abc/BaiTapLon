#include "mylib.h"
#include <iostream>
#include <conio.h>
#include <cmath>
#pragma once;

using namespace std;

void drawRectangle(int x, int y, int width, int height)
{
    for (int ix = x; ix <= x + width; ix++)
    {
        gotoxy(ix, y);
        cout << char(196);
        gotoxy(ix, y + height);
        cout << char(196);
    }
    for (int iy = y; iy <= y + height; iy++)
    {
        gotoxy(x, iy);
        cout << char(179);
        gotoxy(x + width, iy);
        cout << char(179);
    }
    gotoxy(x, y);
    cout << char(218);
    gotoxy(x, y + height);
    cout << char(192);
    gotoxy(x + width, y);
    cout << char(191);
    gotoxy(x + width, y + height);
    cout << char(217);
}

void drawRectangleReverse(int x, int y, int x2, int height)
{

    for (int ix = x; ix >= x2; ix--)
    {
        gotoxy(ix, y);
        cout << char(196);
        gotoxy(ix, y + height);
        cout << char(196);
    }
    for (int iy = y; iy <= y + height; iy++)
    {
        gotoxy(x, iy);
        cout << char(179);
        gotoxy(x2, iy);
        cout << char(179);
    }
    gotoxy(x, y);
    cout << char(191);
    gotoxy(x, y + height);
    cout << char(217);
    gotoxy(x2, y);
    cout << char(218);
    gotoxy(x2, y + height);
    cout << char(192);
}

void titleCuaLietKeHoaDon(int x, int y, int ScreenWidth, int ScreenHeight)
{
    SetColor(0x3);
    int x2 = strlen("BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN") / 2;
    gotoxy(ceil(ScreenWidth * 0.5) - x2, y + 1);
    cout << "BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN";
    gotoxy(ceil(ScreenWidth * 0.25) - x2 / 3, y + 3);
    cout << "Tu ngay : ##/##/##";
    gotoxy(floor(ScreenWidth * 0.7) - x2 / 3, y + 3);
    cout << "Den ngay : ##/##/##";
    gotoxy(ceil(ScreenWidth * 0.125) - x2 / 5, y + 5);
    cout << "So HD";
    gotoxy(ceil(ScreenWidth * 0.325) - x2 / 5, y + 5);
    cout << "Ngay Lap";
    gotoxy(ceil(ScreenWidth * 0.525) - x2 / 5, y + 5);
    cout << "Loai HD";
    gotoxy(ceil(ScreenWidth * 0.7) - x2 / 5, y + 5);
    cout << "Ho ten NV lap";
    gotoxy(ceil(ScreenWidth * 0.875) - x2 / 5, y + 5);
    cout << "Tri gia hoa don";

    //
    gotoxy(x, ScreenHeight - 1);
    cout << "ESC = Stop Program";

    SetColor(0xF);
}

void drawLietKeHoaDon()
{
    int currentWidth = getConsoleWidth();
    int currentHeight = getConsoleHeight();
    int previousWidth = 0;
    int previousHeight = 0;
    int x = 1;
    int y = 0;

    while (true)
    {
        currentWidth = getConsoleWidth();
        currentHeight = getConsoleHeight();

        if (currentWidth != previousWidth || currentHeight != previousHeight)
        {
            clrscr();
            drawRectangle(x, y, currentWidth - 2, 2);
            drawRectangle(x, y + 2, ceil(currentWidth * 0.5) - 1, 2);
            drawRectangleReverse(currentWidth - 1, y + 2, ceil(currentWidth * 0.5), 2);
            drawRectangle(x, y + 4, ceil(currentWidth * 0.2), 2);
            drawRectangle(x + ceil(currentWidth * 0.2), y + 4, ceil(currentWidth * 0.2), 2);
            drawRectangle(x + ceil(currentWidth * 0.2) * 2, y + 4, ceil(currentWidth * 0.2), 2);
            drawRectangle(x + ceil(currentWidth * 0.2) * 3, y + 4, ceil(currentWidth * 0.2), 2);
            drawRectangleReverse(currentWidth - 1, y + 4, ceil(currentWidth * 0.2) * 4 + 1, 2);
            drawRectangle(x, y + 6, ceil(currentWidth * 0.2), 20);
            drawRectangle(x + ceil(currentWidth * 0.2), y + 6, ceil(currentWidth * 0.2), 20);
            drawRectangle(x + ceil(currentWidth * 0.2) * 2, y + 6, ceil(currentWidth * 0.2), 20);
            drawRectangle(x + ceil(currentWidth * 0.2) * 3, y + 6, ceil(currentWidth * 0.2), 20);
            drawRectangleReverse(currentWidth - 1, y + 6, ceil(currentWidth * 0.2) * 4 + 1, 20);
            //
            gotoxy(x, y + 2);
            cout << char(195);
            gotoxy(currentWidth - 1, y + 2);
            cout << char(180);
            gotoxy(currentWidth - 1, y + 4);
            cout << char(180);
            //
            gotoxy(ceil(currentWidth * 0.5), y + 2);
            cout << char(194);
            gotoxy(ceil(currentWidth * 0.5), y + 4);
            cout << char(193);
            gotoxy(x, y + 4);
            cout << char(195);
            gotoxy(x + ceil(currentWidth * 0.2), y + 4);
            cout << char(194);
            gotoxy(x + ceil(currentWidth * 0.2) * 2, y + 4);
            cout << char(194);
            gotoxy(x + ceil(currentWidth * 0.2) * 3, y + 4);
            cout << char(194);
            gotoxy(x + ceil(currentWidth * 0.2) * 4, y + 4);
            cout << char(194);
            gotoxy(x + ceil(currentWidth * 0.2), y + 6);
            cout << char(193);
            gotoxy(x + ceil(currentWidth * 0.2) * 2, y + 6);
            cout << char(193);
            gotoxy(x + ceil(currentWidth * 0.2) * 3, y + 6);
            cout << char(193);
            gotoxy(x + ceil(currentWidth * 0.2) * 4, y + 6);
            cout << char(193);
            gotoxy(x, y + 6);
            cout << char(195);
            gotoxy(x + ceil(currentWidth * 0.2), y + 6);
            cout << char(197);
            gotoxy(x + ceil(currentWidth * 0.2) * 2, y + 6);
            cout << char(197);
            gotoxy(x + ceil(currentWidth * 0.2) * 3, y + 6);
            cout << char(197);
            gotoxy(x + ceil(currentWidth * 0.2) * 4, y + 6);
            cout << char(197);
            gotoxy(currentWidth - 1, y + 6);
            cout << char(180);
            gotoxy(x + ceil(currentWidth * 0.2), y + 26);
            cout << char(193);
            gotoxy(x + ceil(currentWidth * 0.2) * 2, y + 26);
            cout << char(193);
            gotoxy(x + ceil(currentWidth * 0.2) * 3, y + 26);
            cout << char(193);
            gotoxy(x + ceil(currentWidth * 0.2) * 4, y + 26);
            cout << char(193);

            titleCuaLietKeHoaDon(x, y, currentWidth, currentHeight);

            previousWidth = currentWidth;
            previousHeight = currentHeight;
        }

        if (_kbhit())
        {
            char c = getch();
            if (c == 27)
            {
                break;
            }
        }
    }
}

void titleCuaThongKeDoanhThuNam(int x, int y, int ScreenWidth, int ScreenHeight)
{
    SetColor(0x3);
    int x2 = strlen("BANG THONG KE DOANH THU NAM") / 2;
    gotoxy(ceil(ScreenWidth * 0.5) - x2, y + 1);
    cout << "BANG THONG KE DOANH THU NAM";
    gotoxy(ceil(ScreenWidth * 0.25) - x2 / 3, y + 3);
    cout << "Thang";
    gotoxy(floor(ScreenWidth * 0.75) - x2 / 3, y + 3);
    cout << "Doanh Thu";

    gotoxy(x, ScreenHeight - 1);
    cout << "ESC = Stop Program";

    SetColor(0xF);
}

void drawThongKeDoanhThuNam()
{
    int currentWidth = getConsoleWidth();
    int currentHeight = getConsoleHeight();
    int previousWidth = 0;
    int previousHeight = 0;
    int x = 1;
    int y = 0;

    while (true)
    {
        currentWidth = getConsoleWidth();
        currentHeight = getConsoleHeight();

        if (currentWidth != previousWidth || currentHeight != previousHeight)
        {
            clrscr();
            drawRectangle(x, y, currentWidth - 2, 2);
            drawRectangle(x, y + 2, ceil(currentWidth * 0.5) - 1, 2);
            drawRectangleReverse(currentWidth - 1, y + 2, ceil(currentWidth * 0.5), 2);
            drawRectangle(x, y + 4, ceil(currentWidth * 0.5) - 1, 20);
            drawRectangleReverse(currentWidth - 1, y + 4, ceil(currentWidth * 0.5), 20);

            gotoxy(x, y + 2);
            cout << char(195);
            gotoxy(x, y + 4);
            cout << char(195);
            gotoxy(currentWidth - 1, y + 2);
            cout << char(180);
            gotoxy(currentWidth - 1, y + 4);
            cout << char(180);
            //
            gotoxy(ceil(currentWidth * 0.5), y + 2);
            cout << char(194);
            gotoxy(ceil(currentWidth * 0.5), y + 4);
            cout << char(197);
            gotoxy(ceil(currentWidth * 0.5), y + 24);
            cout << char(193);

            titleCuaThongKeDoanhThuNam(x, y, currentWidth, currentHeight);
            previousWidth = currentWidth;
            previousHeight = currentHeight;
        }

        if (_kbhit())
        {
            char c = getch();
            if (c == 27)
            {
                break;
            }
        }
    }
}