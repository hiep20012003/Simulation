#include"global.h"
#include"graphics.h"
#include<conio.h>

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1000;

const int DENTAL_MOVE = 10;
const int SLEEP_TIME = 10;

const int STACK_SIZE = 7;
const int QUEUE_SIZE = 7;
const int DEQUEUE_SIZE = 7;
const int LIST_SIZE = 7;

int RECT_NODE_WIDTH;
int RECT_NODE_HEIGHT;

int font_size = 40;
POSITION start_cursor;
POSITION cursor = start_cursor;

REGION insert_box;
REGION delete_box;
REGION end_box;
REGION command_box;
REGION display_box;
REGION menu_box;

// Ham khoi tao cac thuoc tinh cua cua so console
void InitConsoleWindow()
{
	//setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	system("cls");
	disableScroll();
	disableSelection();
	setConsoleMode();
	gotoxy(cursor.x / 8, cursor.y / 12);
	Sleep(1000);
}

// Ham tra ve string nhap tu ban phim
// voi mot so dieu kien nhu: chi chap nhan chu hoac so
// va di chuyen vi tri con tro sau khi nhap theo y muon
string RealTimeInputString()
{
	char ch;
	string str = "";
	do {
		ch = _getch();
		setfontcolor(12);
		if ((ch >= 48 && ch <= 57) ||
			(ch >= 65 && ch <= 90) ||
			(ch >= 97 && ch <= 122))
		{
			str = str + ch;
			CheckCurrentCursor();
			cout << ch;
		}
		else if (ch == 8)
		{
			COORD cursor = getConsoleCursorPosition();
			if (cursor.X > 0 && !str.empty())
			{
				gotoxy(cursor.X - 1, cursor.Y);
				cout << " ";
				gotoxy(cursor.X - 1, cursor.Y);
				str.pop_back();
			}
		}
		else if (ch == 13 || ch == 32)
		{
			CheckCurrentCursor();
			if (str.empty())
			{
				PrintTo(cursor.x, cursor.y + 12, "Type number: ");
				continue;
			}
			PrintToNewLine(cursor.x, cursor.y, "");
		}
	} while (ch != 13 || str.empty());
	string str2(str, 0, 4);
	return str2;
}

// Ham tra ve int nhap tu ban phim
// voi mot so dieu kien nhu: chi so
// va di chuyen vi tri con tro sau khi nhap theo y muon
int RealTimeInputInt()
{
	char ch;
	int num = -100, count = 0;
	do {
		ch = _getch();
		setfontcolor(12);
		if (ch >= 48 && ch <= 57)
		{
			count++;
			if (num == -100) num = 0;
			num = num * 10 + (ch - 48);
			CheckCurrentCursor();
			cout << ch;
		}
		else if (ch == 8)
		{
			COORD cursor = getConsoleCursorPosition();
			if (cursor.X > 0 && num != -100)
			{
				gotoxy(cursor.X - 1, cursor.Y);
				cout << " ";
				gotoxy(cursor.X - 1, cursor.Y);
				num /= 10;
				count--;
			}
		}
		else if (ch == 13 || ch == 32)
		{
			CheckCurrentCursor();
			if (num == -100)
			{
				PrintTo(cursor.x, cursor.y + 12, "Type number: ");
				continue;
			}
			PrintToNewLine(cursor.x, cursor.y, "");
		}
	} while (ch != 13 || num == -100);
	if (count > 4)
	{
		num = num / (10 * (count - 4));
	}
	return num;
}

// Kiem tra vi tri con tro co vuot ngoai pham vi command_box
// Neu vuot qua pham vi command_box thi reset cursor = start_cursor
// va xoa man hinh khu vuc command_box
void CheckCurrentCursor()
{
	int limitY = (command_box.pos.bottom) / 21 - 2;
	int limitX = (command_box.pos.right) / 9 - 5;
	COORD pos = getConsoleCursorPosition();
	if (pos.X >= limitX)
	{
		gotoxy(cursor.x / 8, cursor.y / 12 + 1);
		cursor.ChangePos(cursor.x, cursor.y + 12);
	}
	if (pos.Y >= limitY)
	{
		string clear(limitX - 5, ' ');
		int x = cursor.y;
		cursor = start_cursor;
		for (int i = start_cursor.y; i <= x; i = i + 12)
		{
			PrintToNewLine(cursor.x, cursor.y, clear);
		}
		gotoxy(start_cursor.x / 8, start_cursor.y / 12);
		cursor = start_cursor;
	}
}

// In ra man hinh va dua con tro den dong tiep theo ,trong pham vi command_box
void PrintToNewLine(int x, int y, string str)
{
	setfontcolor(10);
	outtextxy(x, y, str);
	gotoxy(cursor.x / 8, cursor.y / 12 + 1);
	cursor.ChangePos(cursor.x, y + 12);
}

// In ra man hinh khong xuong dong, trong pham vi command_box
void PrintTo(int x, int y, string str)
{
	setfontcolor(10);
	outtextxy(x, y, str);
	cursor.ChangePos(60, y);
}
// Ve doi tuong len len console
// Doi tuong REGION bao gom 2 field: data va pos
void PrintObject(REGION object, int color)
{
	setcolor(color / 2);
	setBrushColor(color);
	rectangle(object.pos);
	if (object.data != "null")
		printText(object.data, object.pos, font_size, color);
}