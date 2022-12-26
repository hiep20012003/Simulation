#include"graphics.h"
#include"global.h"
#include<conio.h>
#include"stack.h"

LINKEDSTACK* stack;
REGION stack_box;
int pos_in_stack_box;
RECT pos_node_appear;

void StackSimulation()
{
	stack = new LINKEDSTACK();
	stack->init(STACK_SIZE);
	start_cursor = { 60, 30 };
	cursor = start_cursor;
	InitConsoleWindow();
	InitPositionObjectsStack();
	DrawOriginalObjectsStack();
	RunProgramStack();
	system("cls");
}
void InitPositionObjectsStack()
{
	RECT_NODE_WIDTH = 200;
	RECT_NODE_HEIGHT = 80;

	command_box = { 20,20,WINDOW_WIDTH / 3 - 50,WINDOW_HEIGHT / 2 };
	display_box = { command_box.pos.right + 10,20,WINDOW_WIDTH - 20,WINDOW_HEIGHT - 50 };
	menu_box = { 20,WINDOW_HEIGHT / 2 + 20,WINDOW_WIDTH / 3 - 50,WINDOW_HEIGHT - 50 };

	stack_box.pos.left = display_box.pos.left + 2 * RECT_NODE_WIDTH;
	stack_box.pos.top = display_box.pos.top + 200;
	stack_box.pos.right = stack_box.pos.left + RECT_NODE_WIDTH + 20;
	stack_box.pos.bottom = stack_box.pos.top + (RECT_NODE_HEIGHT + 10) * STACK_SIZE + 10;

	pos_in_stack_box = stack_box.pos.bottom;

	insert_box = {
		menu_box.pos.left + 50,
		menu_box.pos.top + 50,
		menu_box.pos.right - 50,
		menu_box.pos.top + 120, "1. INSERT" };
	delete_box = {
	insert_box.pos.left,
	insert_box.pos.top + 100,
	insert_box.pos.right,
	insert_box.pos.bottom + 100,
	"2. DELETE" };
	end_box = {
	delete_box.pos.left,
	delete_box.pos.top + 150,
	delete_box.pos.right,
	delete_box.pos.bottom + 150 ,
	"ESC. END" };

	pos_node_appear.left = stack_box.pos.right + 200;
	pos_node_appear.top = stack_box.pos.top - 1.5 * RECT_NODE_HEIGHT;
	pos_node_appear.right = pos_node_appear.left + RECT_NODE_WIDTH;
	pos_node_appear.bottom = pos_node_appear.top + RECT_NODE_HEIGHT;

}
void DrawOriginalObjectsStack()
{
	setBrushColor(16);
	setcolor(9);
	rectangle(command_box.pos);

	setBrushColor(16);
	setcolor(10);
	rectangle(display_box.pos);

	setBrushColor(16);
	setcolor(8);
	rectangle(menu_box.pos);

	rectangle(stack_box.pos);
	setBrushColor(15);
	PrintObject(insert_box);
	PrintObject(delete_box);
	PrintObject(end_box);

	setcolor(16);
	line(stack_box.pos.left + 10, stack_box.pos.top, stack_box.pos.right - 10, stack_box.pos.top);
}
void RunProgramStack()
{
	POSITION limit_pos_insert;
	POSITION limit_post_delete;

	NODE* node_deleted;
	NODE* value_peek;

	limit_pos_insert.ChangePos(stack_box.pos.left, pos_in_stack_box);
	string str;
	while (true)
	{
		if (_kbhit())
		{
			CheckCurrentCursor();
			char c = _getch();
			if (c == '1')
			{
				if (stack->size == STACK_SIZE)
				{
					PrintToNewLine(cursor.x, cursor.y, "Stack was Full");
					continue;
				}
				string insert_mes;
				insert_mes = "Insert Top NODE";
				PrintTo(cursor.x, cursor.y, insert_mes + ": ");
				str = RealTimeInputString();
				stack->InsertNode(str);
				InsertSimulationStack();
				PrintToNewLine(cursor.x, cursor.y, "Completed " + insert_mes);
			}
			else if (c == '2')
			{
				if (stack->IsEmpty())
				{
					PrintToNewLine(cursor.x, cursor.y, "Stack Empty. Can't delete");
					continue;
				}
				string delete_mes;
				delete_mes = "Delete Top NODE";
				DeleteSimulationStack();
				node_deleted = stack->DeleteNode();
				PrintToNewLine(cursor.x, cursor.y, delete_mes);
			}
			else if (c == 27)
			{
				break;
			}
		}
	}
}
void InsertSimulationStack()
{
	stack->pTop->node_region.SetRegion(pos_node_appear, stack->pTop->data);
	REGION& i = stack->pTop->node_region;
	while (i.pos.left != stack_box.pos.left + 10)
	{
		clearObjectOnScreen(i.pos);
		i.pos.left -= DENTAL_MOVE;
		i.pos.right -= DENTAL_MOVE;
		PrintObject(stack->pTop->node_region);
		Sleep(SLEEP_TIME);
	}
	while (i.pos.bottom != pos_in_stack_box - 10)
	{
		clearObjectOnScreen(i.pos);
		i.pos.top += DENTAL_MOVE;
		i.pos.bottom += DENTAL_MOVE;
		PrintObject(stack->pTop->node_region);
		Sleep(SLEEP_TIME);
	}
	pos_in_stack_box = i.pos.top;
}
void DeleteSimulationStack()
{
	REGION& i = stack->pTop->node_region;
	while (i.pos.bottom != pos_node_appear.bottom)
	{
		clearObjectOnScreen(i.pos);
		i.pos.top -= DENTAL_MOVE;
		i.pos.bottom -= DENTAL_MOVE;
		PrintObject(stack->pTop->node_region);
		Sleep(SLEEP_TIME);
	}
	while (i.pos.right != stack_box.pos.left - RECT_NODE_WIDTH / 2)
	{
		clearObjectOnScreen(i.pos);
		i.pos.left -= DENTAL_MOVE;
		i.pos.right -= DENTAL_MOVE;
		PrintObject(stack->pTop->node_region);
		Sleep(SLEEP_TIME);
	}
	while (i.pos.top != stack_box.pos.top)
	{
		clearObjectOnScreen(i.pos);
		i.pos.top += DENTAL_MOVE;
		i.pos.bottom += DENTAL_MOVE;
		PrintObject(stack->pTop->node_region);
		Sleep(SLEEP_TIME);
	}
	if (stack->pTop->pNext != nullptr)
		pos_in_stack_box = stack->pTop->pNext->node_region.pos.top;
	else
		pos_in_stack_box = stack_box.pos.bottom;
}
