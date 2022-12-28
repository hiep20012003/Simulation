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

// Hàm chỉnh lại của sổ console :
// tắt cuộn, tắt quick edit mode,
// đặt lại input mode
void InitConsoleWindow()
{
	system("cls");
	disableScroll();
	disableSelection();
	setConsoleMode();
	gotoxy(cursor.x / 8, cursor.y / 12);
	Sleep(1000);
}

// Trả về chuỗi nhập từ bàn phím và hiển thị ký tự người dùng nhập theo thời gian thực
// với điều kiện: Chỉ nhập số nguyên >= 0 , hoặc chữ cái 
// và điều khiển vị trí con trỏ luôn nằm trong command_box
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
		else if (ch == 8)		// Backspace
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
		else if (ch == 13)		// Enter
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

	string str2(str, 0, 4);		// Chỉ lấy 4 ký tự đầu tiên trong chuỗi
	return str2;
}

// Trả về số nguyên nhập từ bàn phím và hiển thị ký tự người dùng nhập theo thời gian thực
// với điều kiện: Chỉ nhập số nguyên >= 0
// và điều khiển vị trí con trỏ luôn nằm trong command_box

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
		else if (ch == 13)
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
	// Chỉ lấy 4 ký tự đầu tiên
	if (count > 4)
	{
		num = num / (10 * (count - 4));
	}
	return num;
}

// Kiểm tra vị trí con trỏ có nằm ngoài command_box hay không
// Nếu nằm ngoài command_box thì reset cursor = start_cursor
// và xóa màn hình khu vực command_box
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

// In chuỗi ra console 
// và trỏ đến dòng tiếp theo trong command_box
void PrintToNewLine(int x, int y, string str)
{
	setfontcolor(10);
	outtextxy(x, y, str);
	gotoxy(cursor.x / 8, cursor.y / 12 + 1);
	cursor.ChangePos(cursor.x, y + 12);
}

// In ra màn hình không xuống dòng trong pham vi command_box
void PrintTo(int x, int y, string str)
{
	setfontcolor(10);
	outtextxy(x, y, str);
	cursor.ChangePos(60, y);
}
// Vẽ đối tượng lên console
// Kiểu REGION bao gồm : data va pos
void PrintObject(REGION object, int color)
{
	setcolor(color / 2);
	setBrushColor(color);
	rectangle(object.pos);
	if (object.data != "")
		printText(object.data, object.pos, font_size, color);
}