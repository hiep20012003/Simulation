#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <windows.h>
#include<iostream>
using namespace std;

void initgraph(void);
void changex(int value);
void changey(int value);
int getmaxx(void);
int getmaxy(void);
void setcolorRGB(int r, int g, int b);
void setcolor(int color);
void setfontcolor(int color);
void line(int x1, int y1, int x2, int y2);
void putpixel(int x, int y);
void circle(int x, int y, int radius);
void rectangle(int x1, int y1, int x2, int y2);
void gotoxy(int x, int y);
void outtextxy(int x, int y, char* text);
void clrscr();
HPEN  getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF);
HBRUSH getBrush(int iBRUSH_STYLE, int iCOLORREF);
BOOL  SetPoint(HDC hDC, HPEN hPen, COORD PNT);
BOOL  PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END);
BOOL  PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END);
BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END);
COORD setCordScale(COORD POS, RECT pRECT);

// Ham tao them
void disableSelection();
void setConsoleMode();
COORD getConsoleCursorPosition();
void disableScroll();
void setBrushColor(int color);
COLORREF getBrushColor(HBRUSH brush);
void printText(string mes, RECT pos, int fontSize, int color);
void rectangle(RECT position);
void clearObjectOnScreen(RECT position = { 0,0,1300,800 });
void outtextxy(int x, int y, string text);
void drawArrow(int x1, int y1, int x2, int y2);
#endif
