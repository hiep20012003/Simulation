#ifndef GLOBAL
#define GLOBAL
#include"DataStructure.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int DENTAL_MOVE;
extern const int SLEEP_TIME;

extern const int STACK_SIZE;
extern const int QUEUE_SIZE;
extern const int DEQUEUE_SIZE;
extern const int LIST_SIZE;
extern int RECT_NODE_WIDTH;
extern int RECT_NODE_HEIGHT;

extern int font_size;
extern POSITION start_cursor;
extern POSITION cursor;

extern REGION insert_box;
extern REGION delete_box;
extern REGION end_box;
extern REGION command_box;
extern REGION display_box;
extern REGION menu_box;

string RealTimeInputString();
int RealTimeInputInt();
void PrintObject(REGION object, int color = 15);
void PrintToNewLine(int x, int y, string str);
void PrintTo(int x, int y, string str);
void CheckCurrentCursor();

void InitConsoleWindow();
#endif // !1