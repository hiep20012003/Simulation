#include"graphics.h"
#include"queue.h"
#include"global.h"
#include<conio.h>

REGION queue_box;
QUEUE* queue;
int pos_in_queue_box;
RECT pos_node_appear_queue;

// Gọi chương trình mô phỏng
void QueueSimulation()
{
	queue = new QUEUE();
	queue->init(QUEUE_SIZE);
	start_cursor = { 60, WINDOW_HEIGHT / 2 - 120 };

	cursor = start_cursor;
	InitConsoleWindow();
	InitPositionObjectsQueue();
	DrawOriginalObjectsQueue();
	RunProgramQueue();
	system("cls");

}

// Khởi tạo vị trí và kích thước
// cho các đối tượng vẽ lên console ban đầu
void InitPositionObjectsQueue()
{
	RECT_NODE_WIDTH = 120;
	RECT_NODE_HEIGHT = 150;

	command_box = { 20,WINDOW_HEIGHT / 2 + 100,WINDOW_WIDTH / 3 - 70,WINDOW_HEIGHT - 50 };
	menu_box = { command_box.pos.right + 10,command_box.pos.top,WINDOW_WIDTH - 20,WINDOW_HEIGHT - 50 };
	display_box = { 20,20,WINDOW_WIDTH - 20,command_box.pos.top - 10 };

	queue_box.pos.left = display_box.pos.left + 300;
	queue_box.pos.top = display_box.pos.top + 150;
	queue_box.pos.right = queue_box.pos.left + (RECT_NODE_WIDTH + 10) * QUEUE_SIZE + 10;
	queue_box.pos.bottom = queue_box.pos.top + RECT_NODE_HEIGHT + 20;

	pos_in_queue_box = queue_box.pos.left;

	insert_box = { menu_box.pos.left + 100, menu_box.pos.top + 120,
		menu_box.pos.left + 300, menu_box.pos.bottom - 120, "1. INSERT" };
	delete_box = {
	insert_box.pos.right + 80,
	insert_box.pos.top ,
	insert_box.pos.right + 280,
	insert_box.pos.bottom,
	"2. DELETE" };
	end_box = {
	delete_box.pos.right + 200,
	delete_box.pos.top,
	delete_box.pos.right + 400,
	delete_box.pos.bottom ,
	"ESC. END" };

	pos_node_appear_queue.left = queue_box.pos.right + RECT_NODE_WIDTH - 100;
	pos_node_appear_queue.top = queue_box.pos.top + 10;
	pos_node_appear_queue.right = pos_node_appear_queue.left + RECT_NODE_WIDTH;
	pos_node_appear_queue.bottom = pos_node_appear_queue.top + RECT_NODE_HEIGHT;


}

// Vẽ các đối tượng ban đầu lên console
void DrawOriginalObjectsQueue()
{
	setBrushColor(16);
	setcolor(9);
	rectangle(command_box.pos);

	setBrushColor(16);
	setcolor(8);
	rectangle(menu_box.pos);

	setBrushColor(16);
	setcolor(10);
	rectangle(display_box.pos);

	rectangle(queue_box.pos);
	setBrushColor(15);
	PrintObject(insert_box);
	PrintObject(delete_box);
	PrintObject(end_box);

	setcolor(16);
	setBrushColor(16);
	rectangle(queue_box.pos.right - 10, queue_box.pos.top + 10, queue_box.pos.right + 10, queue_box.pos.bottom - 10);
	rectangle(queue_box.pos.left - 10, queue_box.pos.top + 10, queue_box.pos.left + 10, queue_box.pos.bottom - 10);
}

// Chạy chương trình mô phỏng
void RunProgramQueue()
{
	NODE* node_deleted;
	string str;
	while (true)
	{
		if (_kbhit())					// Bắt sự kiện bàn phím
		{
			CheckCurrentCursor();		// Kiểm tra vị trí con trỏ
			char c = _getch();
			if (c == '1')				// Nút INSERT
			{
				// Thông báo
				if (queue->size == QUEUE_SIZE)
				{
					PrintToNewLine(cursor.x, cursor.y, "Queue was Full");
					continue;
				}
				string insert_mes;
				insert_mes = "Insert Front NODE";
				PrintTo(cursor.x, cursor.y, insert_mes + ": ");

				// Input
				str = RealTimeInputString();
				// Thêm NODE
				queue->InsertNode(str);
				// Mô phỏng thêm NODE
				InsertSimulationQueue();

				PrintToNewLine(cursor.x, cursor.y, "Completed " + insert_mes);
			}
			else if (c == '2')			// Nút DELETE
			{
				// Thông báo
				if (queue->IsEmpty())
				{
					PrintToNewLine(cursor.x, cursor.y, "Queue Empty. Can't delete");
					continue;
				}
				string delete_mes;
				delete_mes = "Delete Rear NODE";

				// Mô phỏng xóa NODE
				DeleteSimulationQueue();
				// Xóa NODE
				node_deleted = queue->DeleteNode();

				PrintToNewLine(cursor.x, cursor.y, delete_mes);
			}
			else if (c == 27)			// Nút END
			{
				break;
			}
		}
	}
}

// Mô phỏng thêm NODE
void InsertSimulationQueue()
{
	// Đặt vị trí cho NODE mới thêm
	queue->pRear->node_region.SetRegion(pos_node_appear_queue, queue->pRear->data);

	// Di chuyển NODE vào hàng đợi
	REGION& i = queue->pRear->node_region;
	while (i.pos.left != pos_in_queue_box + 10)
	{
		clearObjectOnScreen(i.pos);
		i.pos.left -= DENTAL_MOVE;
		i.pos.right -= DENTAL_MOVE;
		PrintObject(queue->pRear->node_region);
		Sleep(SLEEP_TIME);
	}
	// Cập nhập vị trí thêm NODE tiếp theo
	pos_in_queue_box = i.pos.right;
}
void DeleteSimulationQueue()
{
	// Di chuyển NODE ra khỏi hàng đợi
	REGION& i = queue->pFront->node_region;
	while (i.pos.left != queue_box.pos.left - 200)
	{
		clearObjectOnScreen(i.pos);
		i.pos.left -= DENTAL_MOVE;
		i.pos.right -= DENTAL_MOVE;
		PrintObject(queue->pFront->node_region);
		Sleep(SLEEP_TIME);
	}

	while (i.pos.top != queue_box.pos.bottom + 50)
	{
		clearObjectOnScreen(i.pos);
		i.pos.top += DENTAL_MOVE;
		i.pos.bottom += DENTAL_MOVE;
		PrintObject(i);
		Sleep(SLEEP_TIME);
	}
	while (i.pos.left != queue_box.pos.left + 400)
	{
		clearObjectOnScreen(i.pos);
		i.pos.left += DENTAL_MOVE;
		i.pos.right += DENTAL_MOVE;
		PrintObject(i);
		Sleep(SLEEP_TIME);
	}
	// Đưa các NODE phía sau lên trước
	NODE* p = queue->pFront->pNext;
	int limit = queue_box.pos.left;
	while (p != nullptr)
	{
		while (p->node_region.pos.left != limit + 10)
		{
			clearObjectOnScreen(p->node_region.pos);
			p->node_region.pos.left -= DENTAL_MOVE;
			p->node_region.pos.right -= DENTAL_MOVE;
			PrintObject(p->node_region);
			Sleep(SLEEP_TIME);
		}
		limit = p->node_region.pos.right;
		p = p->pNext;
	}
	// Cập nhập vị trí thêm NODE tiếp theo
	if (queue->pFront->pNext != nullptr)
		pos_in_queue_box = queue->pFront->node_region.pos.right;
	else
		pos_in_queue_box = queue_box.pos.left;
}
