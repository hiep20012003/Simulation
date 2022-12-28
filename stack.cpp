#include"graphics.h"
#include"global.h"
#include<conio.h>
#include"stack.h"

LINKEDSTACK* stack;
REGION stack_box;
int pos_insert_node_stack;
RECT pos_node_appear;

// Gọi chương trình mô phỏng
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

// Khởi tạo vị trí và kích thước
// cho các đối tượng vẽ lên console ban đầu
void InitPositionObjectsStack()
{
	// Kích thước NODE
	RECT_NODE_WIDTH = 200;
	RECT_NODE_HEIGHT = 80;

	// Khu vực hiện thị mô phỏng, menu và nhập dữ liệu
	command_box = { 20,20,WINDOW_WIDTH / 3 - 50,WINDOW_HEIGHT / 2 };
	display_box = { command_box.pos.right + 10,20,WINDOW_WIDTH - 20,WINDOW_HEIGHT - 50 };
	menu_box = { 20,WINDOW_HEIGHT / 2 + 20,WINDOW_WIDTH / 3 - 50,WINDOW_HEIGHT - 50 };

	// Stack box
	stack_box.pos.left = display_box.pos.left + 2 * RECT_NODE_WIDTH;
	stack_box.pos.top = display_box.pos.top + 200;
	stack_box.pos.right = stack_box.pos.left + RECT_NODE_WIDTH + 20;
	stack_box.pos.bottom = stack_box.pos.top + (RECT_NODE_HEIGHT + 10) * STACK_SIZE + 10;

	// Ví trí sẽ insert node trong stack_box
	pos_insert_node_stack = stack_box.pos.bottom;

	// Ví trí các nút insert, delete, end
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

	// Ví trí node xuất hiện ban đầu khi thêm node
	pos_node_appear.left = stack_box.pos.right + 200;
	pos_node_appear.top = stack_box.pos.top - 1.5 * RECT_NODE_HEIGHT;
	pos_node_appear.right = pos_node_appear.left + RECT_NODE_WIDTH;
	pos_node_appear.bottom = pos_node_appear.top + RECT_NODE_HEIGHT;

}

// Vẽ các đối tượng ban đầu lên console
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

// Chạy chương trình mô phỏng
void RunProgramStack()
{
	NODE* node_deleted;
	string str;
	while (true)
	{
		if (_kbhit())				// Bắt sự kiện bàn phím
		{
			CheckCurrentCursor();	// Kiểm tra vị trí con trỏ
			char c = _getch();
			if (c == '1')			// Nút INSERT
			{
				// Thông báo
				if (stack->size == STACK_SIZE)
				{
					PrintToNewLine(cursor.x, cursor.y, "Stack was Full");
					continue;
				}
				string insert_mes;
				insert_mes = "Insert Top NODE";
				PrintTo(cursor.x, cursor.y, insert_mes + ": ");

				// Input
				str = RealTimeInputString();
				// Thêm NODE vào Stack
				stack->InsertNode(str);
				// Mô phỏng thêm NODE
				InsertSimulationStack();

				PrintToNewLine(cursor.x, cursor.y, "Completed " + insert_mes);
			}
			else if (c == '2')	// Nút DELETE
			{
				// Thông báo
				if (stack->IsEmpty())
				{
					PrintToNewLine(cursor.x, cursor.y, "Stack Empty. Can't delete");
					continue;
				}
				string delete_mes;
				delete_mes = "Delete Top NODE";

				// Mô phỏng xóa NODE
				DeleteSimulationStack();
				// Xóa NODE trong Stack
				node_deleted = stack->DeleteNode();

				PrintToNewLine(cursor.x, cursor.y, delete_mes);
			}
			else if (c == 27)	// Nút END
			{
				break;
			}
		}
	}
}

// Mô phỏng thêm NODE
void InsertSimulationStack()
{
	// Đặt vị trí cho NODE mới thêm
	stack->pTop->node_region.SetRegion(pos_node_appear, stack->pTop->data);

	// Tham chiếu đến NODE mới thêm trên console
	REGION& i = stack->pTop->node_region;

	// Di chuyển NODE vào Stack
	while (i.pos.left != stack_box.pos.left + 10)
	{
		clearObjectOnScreen(i.pos);
		i.pos.left -= DENTAL_MOVE;
		i.pos.right -= DENTAL_MOVE;
		PrintObject(stack->pTop->node_region);
		Sleep(SLEEP_TIME);
	}
	while (i.pos.bottom != pos_insert_node_stack - 10)
	{
		clearObjectOnScreen(i.pos);
		i.pos.top += DENTAL_MOVE;
		i.pos.bottom += DENTAL_MOVE;
		PrintObject(stack->pTop->node_region);
		Sleep(SLEEP_TIME);
	}
	// Cập nhập ví trí thêm NODE tiếp theo
	pos_insert_node_stack = i.pos.top;
}

// Mô phỏng xóa NODE
void DeleteSimulationStack()
{
	// Đưa NODE ra khỏi stack
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
	// Cập nhập ví trí thêm NODE tiếp theo
	if (stack->pTop->pNext != nullptr)
		pos_insert_node_stack = stack->pTop->pNext->node_region.pos.top;
	else
		pos_insert_node_stack = stack_box.pos.bottom;
}
