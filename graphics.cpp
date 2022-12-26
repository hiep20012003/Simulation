#include <iostream>
#include <math.h>
#include <windows.h>
#include"graphics.h"

using namespace std;

HDC hDC;
HPEN PEN;
HBRUSH BRUSH, ERASER;
HANDLE StdOut, StdIn;
WORD COLOR;
COORD BGN, POS;
HWND hWnd;
RECT    pRECT = { 0 };
short mov;
short movx;

void initgraph(void)
{
	system("cls");
	mov = 30;
	movx = 0;
	hWnd = GetForegroundWindow();
	SetWindowPos(hWnd, HWND_TOP, 30, 30, 1600, 1000, SWP_SHOWWINDOW);
	COORD   POS1 = { 0 };
	COORD   BGN1 = setCordScale(POS1, pRECT);
	GetWindowRect(hWnd, &pRECT);
	hDC = GetWindowDC(hWnd);
	PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255));
	ERASER = getBrush(PS_SOLID, RGB(12, 12, 12, 255));
	BRUSH = getBrush(BS_SOLID, RGB(12, 12, 12, 255));
	StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void changex(int value) { if (value > -1000 & value < 1000) movx = (short)value; }
void changey(int value) { if (value > -1000 & value < 1000) mov = (short)value; }
int getmaxx(void) { return 640; }
int getmaxy(void) { return 300; }

void setcolorRGB(int r, int g, int b)
{
	PEN = getPen(PS_SOLID, 2, RGB(r, g, b));
}
void setcolor(int color)
{
	if (color == 16) {
		PEN = getPen(PS_SOLID, 2, RGB(12, 12, 12, 255));
		return;
	}
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
	case 0: PEN = getPen(PS_SOLID, 2, RGB(0, 0, 0)); break;
	case 1: PEN = getPen(PS_SOLID, 2, RGB(0, 0, 128)); break;
	case 2: PEN = getPen(PS_SOLID, 2, RGB(0, 128, 0)); break;
	case 3: PEN = getPen(PS_SOLID, 2, RGB(128, 0, 0)); break;
	case 4: PEN = getPen(PS_SOLID, 2, RGB(0, 128, 128)); break;
	case 5: PEN = getPen(PS_SOLID, 2, RGB(128, 0, 128)); break;
	case 6: PEN = getPen(PS_SOLID, 2, RGB(128, 128, 0)); break;
	case 7: PEN = getPen(PS_SOLID, 2, RGB(0, 0, 255)); break;
	case 8: PEN = getPen(PS_SOLID, 2, RGB(0, 255, 0)); break;
	case 9: PEN = getPen(PS_SOLID, 2, RGB(255, 0, 0)); break;
	case 10: PEN = getPen(PS_SOLID, 2, RGB(0, 255, 255)); break;
	case 11: PEN = getPen(PS_SOLID, 2, RGB(255, 0, 255)); break;
	case 12: PEN = getPen(PS_SOLID, 2, RGB(255, 255, 0)); break;
	case 13: PEN = getPen(PS_SOLID, 2, RGB(192, 192, 192)); break;
	case 14: PEN = getPen(PS_SOLID, 2, RGB(192, 192, 192)); break;
	case 15: PEN = getPen(PS_SOLID, 2, RGB(255, 255, 255)); break;
	}
}

void setfontcolor(int color)
{
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
	case 0: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); COLOR = COMMON_LVB_REVERSE_VIDEO; break;
	case 1: COLOR = (FOREGROUND_BLUE); break;
	case 2: COLOR = (FOREGROUND_GREEN); break;
	case 3: COLOR = (FOREGROUND_RED); break;
	case 4: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN); break;
	case 5: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED); break;
	case 6: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED); break;
	case 7: COLOR = (FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
	case 8: COLOR = (FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
	case 9: COLOR = (FOREGROUND_RED | FOREGROUND_INTENSITY); break;
	case 10: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
	case 11: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
	case 12: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
	case 13: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); break;
	case 14: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO); break;
	case 15: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO | FOREGROUND_INTENSITY); break;
	}
	SetConsoleTextAttribute(StdOut, COLOR);
}

void line(int x1, int y1, int x2, int y2)
{
	BGN.X = (short)x1 + movx;
	BGN.Y = (short)y1 + mov;
	POS.X = (short)x2 + movx;
	POS.Y = (short)y2 + mov;
	PlotLine(hDC, PEN, BGN, POS);
}

void putpixel(int x, int y)
{
	line(x, y, x, y);
}

void circle(int x, int y, int radius)
{
	BGN.X = (short)x + movx - radius / 2;
	BGN.Y = (short)y + mov - radius / 2;
	POS.X = (short)x + movx + radius / 2;
	POS.Y = (short)y + mov + radius / 2;
	PlotCirc(hDC, PEN, BGN, POS);
}

void rectangle(int x1, int y1, int x2, int y2)
{
	BGN.X = (short)x1 + movx;
	BGN.Y = (short)y1 + mov;
	POS.X = (short)x2 + movx;
	POS.Y = (short)y2 + mov;
	PlotRect(hDC, PEN, BGN, POS);
}

void gotoxy(int x, int y)
{
	//StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	BGN.X = (short)x;
	BGN.Y = (short)y;
	SetConsoleCursorPosition(StdOut, BGN);
}

void outtextxy(int x, int y, char* text)
{
	gotoxy(x / 8, y / 12);
	std::cout << text;
}

void clrscr()
{
	setcolor(0);
	for (int i = 5; i <= 645; i++)
		line(i - movx, 32 - mov, i - movx, 331 - mov);
}

HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF)
{
	return CreatePen(iPEN_STYLE, iPEN_SIZE, iCOLORREF);
}

BOOL SetPoint(HDC hDC, HPEN hPen, COORD PNT)
{
	EXTLOGPEN pINFO;
	GetObject(hPen, sizeof(EXTLOGPEN), &pINFO);
	SelectObject(hDC, hPen);
	return Ellipse
	(
		hDC,
		PNT.X - pINFO.elpWidth,
		PNT.Y + pINFO.elpWidth,
		PNT.X + pINFO.elpWidth,
		PNT.Y - pINFO.elpWidth
	);
}

BOOL PlotLine(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
	//HPEN arrow = getPen(PS_SOLID, 4, RGB(255, 255, 255));
	SelectObject(hDC, hPen);
	SelectObject(hDC, BRUSH);
	MoveToEx(hDC, BGN.X, BGN.Y, NULL);
	LineTo(hDC, END.X, END.Y);
	DeleteObject(hPen);
	DeleteObject(BRUSH);
	return true;
}

BOOL PlotRect(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
	SelectObject(hDC, hPen);
	SelectObject(hDC, BRUSH);
	Rectangle(hDC, BGN.X, BGN.Y, END.X, END.Y);
	DeleteObject(hPen);
	DeleteObject(BRUSH);
	return true;
}

BOOL  PlotCirc(HDC hDC, HPEN hPen, COORD BGN, COORD END)
{
	SelectObject(hDC, hPen);
	SelectObject(hDC, BRUSH);
	Ellipse(hDC, BGN.X, BGN.Y, END.X, END.Y);
	DeleteObject(hPen);
	DeleteObject(BRUSH);
	return true;
}

COORD setCordScale(COORD POS, RECT pRECT)
{
	if (POS.X == 0)
		POS.X = 1;
	if (POS.Y == 0)
		POS.Y = 1;

	int nROWS = 25;
	int nCOLS = 80;

	double CX = (pRECT.right - pRECT.left) / nCOLS;
	double CY = (pRECT.bottom - pRECT.top) / nROWS;

	//При текстовом режиме(text mode) экран  делится  на  ячейки
	//(80  или 40 колонок в ширину и 25 строк в высоту)
	POS.X *= CX;
	POS.Y *= CY;

	int xBORDER = GetSystemMetrics(SM_CXBORDER);//Ширина границы окна
	int yBORDER = GetSystemMetrics(SM_CYMENU);  //Высота заголовка окна ~= высоте строк меню
	int xDRAG = GetSystemMetrics(SM_CXDRAG);  //Число пикселей на гориз дрожение мыши
	int yDRAG = GetSystemMetrics(SM_CYDRAG);  //Число пикселей на вертик дрожение мыши

	POS.X += xBORDER + xDRAG;//Ширина границы окна + число пикселей на дрожение мыши
	POS.Y += yBORDER + yDRAG;
	return POS;
}

// Cac ham tao them

// Disable Quick edit mode cua so console
void disableSelection()
{
	StdIn = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(StdIn, ENABLE_EXTENDED_FLAGS);
}
// Set cac mode cua so console
void setConsoleMode()
{
	StdIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	mode = ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT;
	SetConsoleMode(StdIn, mode);
}
// Lay vi tri cua con tro
COORD getConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(StdOut, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}
// Tat cuon cua so console
void disableScroll()
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	GetConsoleScreenBufferInfo(StdOut, &screenBufferInfo);

	COORD new_screen_buffer_size;
	new_screen_buffer_size.X = screenBufferInfo.srWindow.Right -
		screenBufferInfo.srWindow.Left + 1;
	new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom -
		screenBufferInfo.srWindow.Top + 1;
	SetConsoleScreenBufferSize(StdOut, new_screen_buffer_size);
}
// Tao Brush de chon mau cho ben trong cho rectangle hay circle
HBRUSH getBrush(int iBRUSH_STYLE, int iCOLORREF)
{
	LOGBRUSH br;
	br.lbColor = iCOLORREF;
	br.lbStyle = iBRUSH_STYLE;
	return CreateBrushIndirect(&br);
}
// Chon mau brush
void setBrushColor(int color)
{
	if (color == 16) {
		BRUSH = getBrush(PS_SOLID, RGB(12, 12, 12, 255));
		return;
	}
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
	case 0: BRUSH = getBrush(PS_SOLID, RGB(0, 0, 0)); break;
	case 1: BRUSH = getBrush(PS_SOLID, RGB(0, 0, 128)); break;
	case 2: BRUSH = getBrush(PS_SOLID, RGB(0, 128, 0)); break;
	case 3: BRUSH = getBrush(PS_SOLID, RGB(128, 0, 0)); break;
	case 4: BRUSH = getBrush(PS_SOLID, RGB(0, 128, 128)); break;
	case 5: BRUSH = getBrush(PS_SOLID, RGB(128, 0, 128)); break;
	case 6: BRUSH = getBrush(PS_SOLID, RGB(128, 128, 0)); break;
	case 7: BRUSH = getBrush(PS_SOLID, RGB(0, 0, 255)); break;
	case 8: BRUSH = getBrush(PS_SOLID, RGB(0, 255, 0)); break;
	case 9: BRUSH = getBrush(PS_SOLID, RGB(255, 0, 0)); break;
	case 10: BRUSH = getBrush(PS_SOLID, RGB(0, 255, 255)); break;
	case 11: BRUSH = getBrush(PS_SOLID, RGB(255, 0, 255)); break;
	case 12: BRUSH = getBrush(PS_SOLID, RGB(255, 255, 0)); break;
	case 13: BRUSH = getBrush(PS_SOLID, RGB(192, 192, 192)); break;
	case 14: BRUSH = getBrush(PS_SOLID, RGB(192, 192, 192)); break;
	case 15: BRUSH = getBrush(PS_SOLID, RGB(255, 255, 255)); break;
	}
}
// Lay gia tri mau hien tai cua brush
COLORREF getBrushColor(HBRUSH brush)
{
	LOGBRUSH lbr;
	if (GetObject(brush, sizeof(lbr), &lbr) != sizeof(lbr)) {
		return COLOR;
	}
	if (lbr.lbStyle != BS_SOLID) {
		return COLOR;
	}
	return lbr.lbColor;
}
// Ve text len man hinh console voi font, color tuy chinh
void printText(string mes, RECT pos, int fontSize, int color)
{
	HFONT f1 =
		CreateFont(fontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE, NULL);
	UINT format = DT_NOCLIP | DT_SINGLELINE | DT_CENTER;
	SelectObject(hDC, f1);
	SetTextColor(hDC, COLOR);
	SetBkColor(hDC, getBrushColor(BRUSH));
	int y = (pos.bottom - pos.top) / 2 + 8;
	pos.top += y;
	pos.bottom += y;
	DrawTextA(hDC, mes.c_str(), -1, &pos, format);
	DeleteObject(f1);
}
// Overload ham rectangle voi tham so khac
void rectangle(RECT position)
{
	BGN.X = (short)position.left + movx;
	BGN.Y = (short)position.top + mov;
	POS.X = (short)position.right + movx;
	POS.Y = (short)position.bottom + mov;
	PlotRect(hDC, PEN, BGN, POS);
}
// Ham xoa doi tuong, xoa 1 vung theo 1 hinh chu nhat truyen vao
void clearObjectOnScreen(RECT pos)
{
	setBrushColor(16);
	setcolor(16);
	rectangle(pos);
	setcolor(15);
	setBrushColor(15);
}
// Overload ham outtextxy voi tham so truyen vao la string
void outtextxy(int x, int y, string text)
{
	gotoxy(x / 8, y / 12);
	std::cout << text;
}
// Ham ve mui ten 
void drawArrow(int x1, int y1, int x2, int y2)
{
	double widthArrow = 6, x, y;
	double lengthLine = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	x = x2 - (widthArrow / lengthLine) * (x2 - x1);
	y = y2 - (widthArrow / lengthLine) * (y2 - y1);
	double a = x2 - x1 + 1;
	double b = y2 - y1 + 1;
	double dental = (2 * a) * (2 * a) - 4 * (a * a + b * b) * (1 - widthArrow * widthArrow * b * b);
	double x1_arrow, x2_arrow, y1_arrow, y2_arrow;
	x1_arrow = ((-2 * a) + sqrt(dental)) / (2 * (a * a + b * b));
	y1_arrow = (-1 - a * (x1_arrow)) / b + y;
	x2_arrow = ((-2 * a) - sqrt(dental)) / (2 * (a * a + b * b));
	y2_arrow = (-1 - a * (x2_arrow)) / b + y;
	x1_arrow += x;
	x2_arrow += x;
	line(x1, y1, x2, y2);
	line(x2, y2, x1_arrow, y1_arrow);
	line(x2, y2, x2_arrow, y2_arrow);
	setBrushColor(8);
	SelectObject(hDC, BRUSH);
	setcolor(8);
	circle(x1, y1, 15);
	DeleteObject(BRUSH);
}
