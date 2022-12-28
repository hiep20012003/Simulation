#include"graphics.h"
#include"global.h"
#include"deque.h"
#include<conio.h>

DEQUEUE* deque;

REGION dequeue_box;
REGION insert_front_box;
REGION insert_rear_box;
REGION delete_front_box;
REGION delete_rear_box;

// Biến lưu vị trí xuất hiện ban đầu khi thêm NODE
RECT pos_node_appear_front;
RECT pos_node_appear_rear;

// Biến xác định vị trí trong dequeue_box
int pos_node_deque;

// Gọi chương trình mô phỏng
void DequeueSimulation()
{
	deque = new DEQUEUE();
	deque->init(DEQUEUE_SIZE);
	start_cursor = { 60, WINDOW_HEIGHT / 2 - 120 };

	cursor = start_cursor;
	InitConsoleWindow();
	InitPositionObjectsDequeue();
	DrawOriginalObjectsDequeue();
	RunProgramDequeue();
	system("cls");
}

// Khởi tạo vị trí và kích thước
// cho các đối tượng vẽ lên console ban đầu
void InitPositionObjectsDequeue()
{
	RECT_NODE_WIDTH = 120;
	RECT_NODE_HEIGHT = 150;

	command_box = { 20,WINDOW_HEIGHT / 2 + 100,WINDOW_WIDTH / 3 - 70,WINDOW_HEIGHT - 50 };
	menu_box = { command_box.pos.right + 10,command_box.pos.top,WINDOW_WIDTH - 20,WINDOW_HEIGHT - 50 };
	display_box = { 20,20,WINDOW_WIDTH - 20,command_box.pos.top - 10 };

	dequeue_box.pos.left = display_box.pos.left + 300;
	dequeue_box.pos.top = display_box.pos.top + 150;
	dequeue_box.pos.right = dequeue_box.pos.left + (RECT_NODE_WIDTH + 10) * QUEUE_SIZE + 10;
	dequeue_box.pos.bottom = dequeue_box.pos.top + RECT_NODE_HEIGHT + 20;

	pos_node_deque = dequeue_box.pos.left;

	insert_front_box = { menu_box.pos.left + 50, menu_box.pos.top + 70,
		menu_box.pos.left + 400, menu_box.pos.top + 150, "1. INSERT FRONT" };
	insert_rear_box = {
		insert_front_box.pos.left,
		menu_box.pos.bottom - 150,
		insert_front_box.pos.right,
		menu_box.pos.bottom - 70,
		"2. INSERT REAR" };
	delete_front_box = {
		insert_front_box.pos.right + 50,
		insert_front_box.pos.top,
		insert_front_box.pos.right + 450,
		insert_front_box.pos.bottom,
		"3. DELETE FRONT" };
	delete_rear_box = {
		insert_rear_box.pos.right + 50,
		insert_rear_box.pos.top,
		insert_front_box.pos.right + 450,
		insert_rear_box.pos.bottom,
		"4. DELETE REAR" };
	end_box = {
		delete_rear_box.pos.right + 50,
		insert_front_box.pos.top,
		delete_rear_box.pos.right + 230,
		delete_rear_box.pos.bottom ,
		"ESC.END" };

	pos_node_appear_front.left = dequeue_box.pos.left - RECT_NODE_WIDTH - 100;				
	pos_node_appear_front.top = dequeue_box.pos.top + 10;
	pos_node_appear_front.right = pos_node_appear_front.left + RECT_NODE_WIDTH;
	pos_node_appear_front.bottom = pos_node_appear_front.top + RECT_NODE_HEIGHT;

	pos_node_appear_rear.left = dequeue_box.pos.right + RECT_NODE_WIDTH;					
	pos_node_appear_rear.top = dequeue_box.pos.top + 10;
	pos_node_appear_rear.right = pos_node_appear_rear.left + RECT_NODE_WIDTH;
	pos_node_appear_rear.bottom = pos_node_appear_rear.top + RECT_NODE_HEIGHT;
}

// Vẽ các đối tượng ban đầu lên console
void DrawOriginalObjectsDequeue()
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

	rectangle(dequeue_box.pos);
	setBrushColor(15);
	PrintObject(insert_front_box);
	PrintObject(insert_rear_box);
	PrintObject(delete_front_box);
	PrintObject(delete_rear_box);
	PrintObject(end_box);

	setcolor(16);
	setBrushColor(16);
	rectangle(dequeue_box.pos.right - 10, dequeue_box.pos.top + 10, dequeue_box.pos.right + 10, dequeue_box.pos.bottom - 10);
	rectangle(dequeue_box.pos.left - 10, dequeue_box.pos.top + 10, dequeue_box.pos.left + 10, dequeue_box.pos.bottom - 10);
}

// Chạy chương trình mô phỏng
void RunProgramDequeue()
{
	NODE* node_deleted;

	string str;
	bool front = true;
	while (true)
	{
		if (_kbhit())
		{
			CheckCurrentCursor();
			char c = _getch();
			if (c == '1' || c == '2')			// Nút INSERT
			{
				// Thông báo
				if (deque->size == DEQUEUE_SIZE)
				{
					PrintToNewLine(cursor.x, cursor.y, "Dequeue was Full");
					continue;
				}
				string insert_mes;
				if (c == '2')
				{
					front = false;
					insert_mes = "Insert Rear NODE";
				}
				else
				{
					front = true;
					insert_mes = "Insert Front NODE";
				}
				PrintTo(cursor.x, cursor.y, insert_mes + ": ");
				// Input
				str = RealTimeInputString();
				// Thêm NODE 
				deque->InsertNode(str, front);
				// Mô phỏng thêm NODE
				InsertSimulationDequeue(front);

				PrintToNewLine(cursor.x, cursor.y, "Completed " + insert_mes);
			}
			else if (c == '3' || c == '4')		// Nút DELETE
			{
				// Thông báo
				if (deque->IsEmpty())
				{
					PrintToNewLine(cursor.x, cursor.y, "Dequeue Empty. Can't delete");
					continue;
				}
				string delete_mes;
				if (c == '4')
				{
					front = false;
					delete_mes = "Delete Rear NODE";
				}
				else
				{
					front = true;
					delete_mes = "Delete Front NODE";
				}
				// Mô phỏng xóa NODE
				DeleteSimulationDequeue(front);
				// Xóa NODE
				node_deleted = deque->DeleteNode(front);
				PrintToNewLine(cursor.x, cursor.y, "Completed " + delete_mes);
			}
			else if (c == 27)			// Nút END
			{
				break;
			}
		}
	}
}

// Mô phỏng thêm NODE
void InsertSimulationDequeue(bool front)
{
	// Thêm vào phía trước
	if (front)
	{
		// Xác định vị trí thêm NODE trên console
		pos_node_deque = dequeue_box.pos.left;
		deque->pFront->node_region.SetRegion(pos_node_appear_front, deque->pFront->data);

		// Di chuyển các NODE ra phía sau để trống vị trí thêm NODE
		NODE* p = deque->pRear;
		int limit = p->node_region.pos.right + RECT_NODE_WIDTH + 20;
		while (p != deque->pFront)
		{
			while (p->node_region.pos.right != limit - 10)
			{
				clearObjectOnScreen(p->node_region.pos);
				p->node_region.pos.left += DENTAL_MOVE;
				p->node_region.pos.right += DENTAL_MOVE;
				PrintObject(p->node_region);
				Sleep(SLEEP_TIME);
			}
			limit = p->node_region.pos.left;
			p = p->pPrev;
		}

		// Di chuyển NODE vào hàng đợi
		REGION& i = deque->pFront->node_region;
		while (i.pos.left != pos_node_deque + 10)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left += DENTAL_MOVE;
			i.pos.right += DENTAL_MOVE;
			PrintObject(deque->pFront->node_region);
			Sleep(SLEEP_TIME);
		}
	}
	// Thêm vào phía sau
	else
	{
		// Xác định vị trí thêm NODE
		if (deque->pRear == deque->pFront)
			pos_node_deque = dequeue_box.pos.left;
		else
			pos_node_deque = deque->pRear->pPrev->node_region.pos.right;
		deque->pRear->node_region.SetRegion(pos_node_appear_rear, deque->pRear->data);
		
		// Di chuyển NODE vào hàng đợi
		REGION& i = deque->pRear->node_region;
		while (i.pos.left != pos_node_deque + 10)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left -= DENTAL_MOVE;
			i.pos.right -= DENTAL_MOVE;
			PrintObject(deque->pRear->node_region);
			Sleep(SLEEP_TIME);
		}
	}
}

// Mô phỏng xóa NODE
void DeleteSimulationDequeue(bool front)
{
	// Xóa NODE phía trước
	if (front)
	{
		// Đưa NODE bị xóa ra khỏi hàng đợi
		REGION& i = deque->pFront->node_region;
		while (i.pos.left != dequeue_box.pos.left - 200)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left -= DENTAL_MOVE;
			i.pos.right -= DENTAL_MOVE;
			PrintObject(i);
			Sleep(SLEEP_TIME);
		}
		while (i.pos.top != dequeue_box.pos.bottom + 50)
		{
			clearObjectOnScreen(i.pos);
			i.pos.top += DENTAL_MOVE;
			i.pos.bottom += DENTAL_MOVE;
			PrintObject(i);
			Sleep(SLEEP_TIME);
		}
		while (i.pos.left != dequeue_box.pos.left + 400)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left += DENTAL_MOVE;
			i.pos.right += DENTAL_MOVE;
			PrintObject(i);
			Sleep(SLEEP_TIME);
		}
		// Di chuyển các NODE phía sau lên trước
		NODE* p = deque->pFront->pNext;
		int limit = dequeue_box.pos.left;
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
	}
	// Xóa NODE phía sau
	else
	{
		// Đưa NODE bị xóa ra khỏi hàng đợi
		REGION& i = deque->pRear->node_region;
		while (i.pos.right != dequeue_box.pos.right + 200)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left += DENTAL_MOVE;
			i.pos.right += DENTAL_MOVE;
			PrintObject(i);
			Sleep(SLEEP_TIME);
		}
		while (i.pos.top != dequeue_box.pos.bottom + 50)
		{
			clearObjectOnScreen(i.pos);
			i.pos.top += DENTAL_MOVE;
			i.pos.bottom += DENTAL_MOVE;
			PrintObject(i);
			Sleep(SLEEP_TIME);
		}
		while (i.pos.left != dequeue_box.pos.left + 400)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left -= DENTAL_MOVE;
			i.pos.right -= DENTAL_MOVE;
			PrintObject(i);
			Sleep(SLEEP_TIME);
		}
	}
}