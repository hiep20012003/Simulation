#include"graphics.h"
#include"linklist.h"
#include"global.h"
#include<conio.h>


LINKLIST* list;
REGION list_box;
REGION pos_node_linklist;
REGION null;

// Gọi chương trình mô phỏng
void ListSimulation()
{
	list = new LINKLIST();
	list->init(LIST_SIZE);
	start_cursor = { 60, WINDOW_HEIGHT / 2 - 120 };
	cursor = start_cursor;
	InitConsoleWindow();
	InitPositionObjectsList();
	DrawOriginalObjectsList();
	RunProgramList();
	system("cls");

}

// Khởi tạo vị trí và kích thước
// cho các đối tượng vẽ lên console ban đầu
void InitPositionObjectsList()
{
	// Kích thước NODE
	RECT_NODE_WIDTH = 80;
	RECT_NODE_HEIGHT = 80;

	// Khu vực hiện thị mô phỏng, menu và nhập dữ liệu
	command_box = { 20,WINDOW_HEIGHT / 2 + 100,WINDOW_WIDTH / 3 - 70,WINDOW_HEIGHT - 40 };
	menu_box = { command_box.pos.right + 10,command_box.pos.top,WINDOW_WIDTH - 40,WINDOW_HEIGHT - 40 };
	display_box = { 20,20,WINDOW_WIDTH - 40,command_box.pos.top - 10 };

	// list box ( không vẽ list box)
	list_box.pos.left = display_box.pos.left + 150;
	list_box.pos.top = display_box.pos.top + 170;
	list_box.pos.right = list_box.pos.left + (RECT_NODE_WIDTH * 2 + 10) * LIST_SIZE + 10;
	list_box.pos.bottom = list_box.pos.top + RECT_NODE_HEIGHT;

	// Vị trí thêm node
	pos_node_linklist = {
		list_box.pos.left,
		list_box.pos.top,
		list_box.pos.left + RECT_NODE_WIDTH,
		list_box.pos.bottom };

	// ví trí con trỏ null
	null = {
		pos_node_linklist.pos.right,
		pos_node_linklist.pos.top,
		pos_node_linklist.pos.right + 100,
		pos_node_linklist.pos.bottom,
		"NULL"
	};

	// Ví trí các nút insert, delete, end
	insert_box = { menu_box.pos.left + 60, menu_box.pos.top + 100,
		menu_box.pos.left + 260, menu_box.pos.bottom - 100, "1. INSERT" };
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
}

// Vẽ các đối tượng ban đầu lên console
void DrawOriginalObjectsList()
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

	setBrushColor(15);
	PrintObject(insert_box);
	PrintObject(delete_box);
	PrintObject(end_box);

}

// Chạy chương trình mô phỏng
void RunProgramList()
{
	NODE* node_deleted;
	string str;
	int vt;
	while (true)
	{
		if (_kbhit())		// Bắt sự kiện bàn phím
		{
			CheckCurrentCursor();		// Kiểm tra vị trí con trỏ
			char c = _getch();
			if (c == '1')				// Nút INSERT
			{
				// Thông báo
				if (list->size == LIST_SIZE)
				{
					PrintToNewLine(cursor.x, cursor.y, "List was Full");
					continue;
				}
				string insert_mes;
				insert_mes = "Insert NODE";
				PrintTo(cursor.x, cursor.y, insert_mes + ": ");

				// NODE và vị trí thêm NODE
				str = RealTimeInputString();
				PrintTo(cursor.x, cursor.y, "Positon: ");
				vt = RealTimeInputInt();

				// Thêm NODE vào list
				list->InsertNode(str, vt);
				// Mô phỏng thêm NODE
				InsertSimulationList(vt);

				PrintToNewLine(cursor.x, cursor.y, "Completed " + insert_mes);
			}
			else if (c == '2')			// Nút DELETE
			{
				// Thông báo
				if (list->IsEmpty())
				{
					PrintToNewLine(cursor.x, cursor.y, "List Empty. Can't delete");
					continue;
				}
				string delete_mes;
				delete_mes = "Delete";
				PrintTo(cursor.x, cursor.y, delete_mes + " In Position: ");

				// Ví trí xóa
				vt = RealTimeInputInt();

				// Mô phỏng xóa NODE
				DeleteSimulationList(vt);
				// Xóa NODE khỏi list
				node_deleted = list->DeleteNode(vt);

				PrintToNewLine(cursor.x, cursor.y, "Completed " + delete_mes + " NODE");

				// Cập nhập ví trí sẽ thêm NODE mới
				if (list->pTail != nullptr)
					pos_node_linklist.pos = list->pTail->node_region.pos;
				delete node_deleted;

				// Nếu list trống cập nhập lại vị trí con trỏ NULL
				if (list->size == 0)
				{
					null.pos.left = pos_node_linklist.pos.right;
					null.pos.right = pos_node_linklist.pos.right + 100;
				}

			}
			else if (c == 27)			// Nút END
			{
				break;
			}
		}
	}
}

// Mô phỏng thêm NODE
void InsertSimulationList(int k)
{
	// Đặt vị trí cho con trỏ NULL
	int limit_null;
	if (list->size == 1)
		limit_null = pos_node_linklist.pos.right + RECT_NODE_WIDTH + 10;
	else
		limit_null = null.pos.left + 2 * RECT_NODE_WIDTH + 10;

	// Di chuyển con trỏ NULL
	REGION& i = null;
	while (i.pos.left != limit_null)
	{
		clearObjectOnScreen(i.pos);
		i.pos.left += DENTAL_MOVE;
		i.pos.right += DENTAL_MOVE;
		PrintObject(i);
		Sleep(SLEEP_TIME);
	}

	RECT clear; // Biến dùng lưu vị trí xóa đối tượng

	// Thêm NODE vào đầu list
	if (k <= 0 || list->size == 1)
	{
		// Xác định vị trí thêm NODE trên màn hình console
		pos_node_linklist = {
			list_box.pos.left,
			list_box.pos.top,
			list_box.pos.left + RECT_NODE_WIDTH,
			list_box.pos.bottom };

		// Tạo ví trí ban đầu của NODE và vị trí NODE di chuyển tới
		REGION temp_head = pos_node_linklist;
		temp_head.pos.left = display_box.pos.left + 10;
		temp_head.pos.right = temp_head.pos.left + RECT_NODE_WIDTH;
		list->pHead->node_region.SetRegion(temp_head.pos, list->pHead->data);

		// Nếu list ban đầu không trống
		// Di chuyển các NODE ra phía sau làm trống vị trí đầu tiên để thêm NODE mới
		if (list->size > 1)
		{
			NODE* temp = list->pTail;
			pos_node_linklist.pos = list->pTail->node_region.pos;
			pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
			while (temp != nullptr && temp != list->pHead)
			{
				while (temp->node_region.pos.right != pos_node_linklist.pos.right)
				{
					clear = temp->node_region.pos;
					clear.right += RECT_NODE_WIDTH + 5;
					clearObjectOnScreen(clear);
					temp->node_region.pos.left += DENTAL_MOVE;
					temp->node_region.pos.right += DENTAL_MOVE;
					DrawListNode(temp);
					Sleep(SLEEP_TIME);
				}
				NODE* prev_temp = list->pHead;
				while (prev_temp->pNext != nullptr && prev_temp->pNext != temp)
				{
					prev_temp = prev_temp->pNext;
				}
				pos_node_linklist.pos = temp->node_region.pos;
				pos_node_linklist.pos.left -= RECT_NODE_WIDTH * 2 + 10;
				pos_node_linklist.pos.right -= RECT_NODE_WIDTH * 2 + 10;
				temp = prev_temp;
			}
		}

		// Di chuyển NODE mới vào vị trí trong list
		while (list->pHead->node_region.pos.left != pos_node_linklist.pos.left)
		{
			clear = list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			list->pHead->node_region.pos.left += DENTAL_MOVE;
			list->pHead->node_region.pos.right += DENTAL_MOVE;
			DrawListNode(list->pHead);
			Sleep(SLEEP_TIME);
		}
	}
	// Thêm NODE vào cuối list
	else if (k >= list->size - 1)
	{
		// Đặt lại vị trí thêm NODE nếu list ban đầu không trống 
		if (list->pHead != list->pTail)
		{
			pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
		}

		// Tạo vị trí ban đầu của NODE và vị trí NODE di chuyển tới
		REGION temp_tail = pos_node_linklist;
		temp_tail.pos.top = display_box.pos.top + 20;
		temp_tail.pos.bottom = temp_tail.pos.top + RECT_NODE_HEIGHT;
		list->pTail->node_region.SetRegion(temp_tail.pos, list->pTail->data);

		// Di chuyển NODE mới vào vị trí trong list
		while (list->pTail->node_region.pos.top != pos_node_linklist.pos.top)
		{
			clear = list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			list->pTail->node_region.pos.top += DENTAL_MOVE;
			list->pTail->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(list->pTail);
			Sleep(SLEEP_TIME);
		}
	}
	// Thêm NODE mới vào giữa list
	else
	{
		// Tìm NODE phía trước NODE được thêm
		NODE* p = list->pHead;
		int prev_node_k = k - 1;
		while (p->pNext != nullptr && prev_node_k != 0)
		{
			p = p->pNext;
			prev_node_k--;
		}

		// Đặt lại vị trí thêm NODE 
		pos_node_linklist.pos = p->node_region.pos;
		pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
		pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;

		// Trỏ đến NODE được thêm
		p = p->pNext;

		// Tạo ví trí ban đầu của NODE và vị trí NODE di chuyển tới
		REGION temp_middle = pos_node_linklist;
		temp_middle.pos.top = display_box.pos.top + 20;
		temp_middle.pos.bottom = temp_middle.pos.top + RECT_NODE_HEIGHT;
		p->node_region.SetRegion(temp_middle.pos, p->data);

		// Di chuyển các NODE để tạo chỗ trống thêm NODE mới
		NODE* temp = list->pTail;
		RECT clear;
		pos_node_linklist.pos = list->pTail->node_region.pos;
		pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
		pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
		while (temp != nullptr && temp != p)
		{
			while (temp->node_region.pos.right != pos_node_linklist.pos.right)
			{
				clear = temp->node_region.pos;
				clear.right += RECT_NODE_WIDTH + 5;
				clearObjectOnScreen(clear);
				temp->node_region.pos.left += DENTAL_MOVE;
				temp->node_region.pos.right += DENTAL_MOVE;
				DrawListNode(temp);
				Sleep(SLEEP_TIME);
			}
			NODE* prev_temp = list->pHead;
			while (prev_temp->pNext != nullptr && prev_temp->pNext != temp)
			{
				prev_temp = prev_temp->pNext;
			}
			pos_node_linklist.pos = temp->node_region.pos;
			pos_node_linklist.pos.left -= RECT_NODE_WIDTH * 2 + 10;
			pos_node_linklist.pos.right -= RECT_NODE_WIDTH * 2 + 10;
			temp = prev_temp;
		}

		// Di chuyển NODE mới vào vị trí trong list
		while (p->node_region.pos.top != pos_node_linklist.pos.top)
		{
			clear = p->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			p->node_region.pos.top += DENTAL_MOVE;
			p->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(p);
			Sleep(SLEEP_TIME);
		}
	}
	pos_node_linklist.pos = list->pTail->node_region.pos;
}

// Mô phỏng xóa NODE
void DeleteSimulationList(int k)
{
	REGION null_deleted;

	// Xóa khu vực hiện thị NODE được xóa trước đó
	RECT clear = {
		display_box.pos.left + 20,
		list_box.pos.bottom + 20,
		display_box.pos.right - 20,
		display_box.pos.bottom - 20
	};
	clearObjectOnScreen(clear);

	// Xóa NODE Head
	if (k <= 0 || list->pHead == list->pTail)
	{
		// Xác định vị trí trên console của NODE bị xóa
		pos_node_linklist.pos = list->pHead->node_region.pos;

		// Di chuyển NODE Head ra khỏi list
		REGION temp_head = list->pHead->node_region;
		temp_head.pos.top += 200;
		temp_head.pos.bottom = temp_head.pos.top + RECT_NODE_HEIGHT;
		while (list->pHead->node_region.pos.top != temp_head.pos.top)
		{
			clear = list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			list->pHead->node_region.pos.top += DENTAL_MOVE;
			list->pHead->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(list->pHead, 8);
			Sleep(SLEEP_TIME);
		}
		// Vẽ con trỏ NULL cho NODE bị xóa
		null_deleted = {
			list->pHead->node_region.pos.left,
			list->pHead->node_region.pos.top,
			list->pHead->node_region.pos.right + 20,
			list->pHead->node_region.pos.bottom,
			"NULL"
		};
		int limit_null_deleted = list->pHead->node_region.pos.left + 2 * RECT_NODE_WIDTH + 10;
		while (null_deleted.pos.left != limit_null_deleted)
		{
			clear = list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(null_deleted.pos);
			DrawListNode(list->pHead, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}
		// Nếu số phần tử của list > 1
		// Di chuyển các NODE ra phía trước lấp vị trí vừa xóa NODE
		if (list->size > 1)
		{
			NODE* temp = list->pHead->pNext;
			while (temp != nullptr)
			{
				while (temp->node_region.pos.left != pos_node_linklist.pos.left)
				{
					clear = temp->node_region.pos;
					clear.right += RECT_NODE_WIDTH + 5;
					clearObjectOnScreen(clear);
					temp->node_region.pos.left -= DENTAL_MOVE;
					temp->node_region.pos.right -= DENTAL_MOVE;
					DrawListNode(temp);
					Sleep(SLEEP_TIME);
				}
				pos_node_linklist.pos = temp->node_region.pos;
				pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
				pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
				temp = temp->pNext;
			}
		}
	}
	// Xóa NODE Cuối
	else if (k >= list->size - 1)
	{
		// Xác định vị trí trên console của NODE bị xóa
		pos_node_linklist.pos = {
			list->pTail->node_region.pos.left,
			list->pTail->node_region.pos.top ,
			list->pTail->node_region.pos.right ,
			list->pTail->node_region.pos.bottom,
		};

		// Di chuyển NODE Head ra khỏi list
		REGION temp_tail = pos_node_linklist;
		temp_tail.pos.top += 200;
		temp_tail.pos.bottom = temp_tail.pos.top + RECT_NODE_HEIGHT;
		while (list->pTail->node_region.pos.top != temp_tail.pos.top)
		{
			clear = list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			list->pTail->node_region.pos.top += DENTAL_MOVE;
			list->pTail->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(list->pTail, 8);
			Sleep(SLEEP_TIME);
		}

		// Vẽ con trỏ NULL cho NODE bị xóa
		null_deleted = {
			list->pTail->node_region.pos.left,
			list->pTail->node_region.pos.top,
			list->pTail->node_region.pos.right + 40,
			list->pTail->node_region.pos.bottom,
			"NULL"
		};
		int limit_null_deleted = list->pTail->node_region.pos.right + 2 * RECT_NODE_WIDTH + 50;
		while (null_deleted.pos.right != limit_null_deleted)
		{
			clear = list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(null_deleted.pos);
			DrawListNode(list->pTail, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			setBrushColor(15);
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}
	}
	// Xóa NODE giữa list
	else
	{
		// Tìm NODE sẽ xóa
		NODE* p = list->pHead;
		int prev_node_k = k - 1;
		while (p->pNext != nullptr && prev_node_k != 0)
		{
			p = p->pNext;
			prev_node_k--;
		}
		p = p->pNext;

		// Xác định vị trí trên console của NODE bị xóa
		pos_node_linklist.pos = p->node_region.pos;

		REGION temp_middle = p->node_region;
		temp_middle.pos.top += 200;
		temp_middle.pos.bottom = temp_middle.pos.top + RECT_NODE_HEIGHT;

		// Di chuyển NODE bị xóa ra khỏi list
		while (p->node_region.pos.top != temp_middle.pos.top)
		{
			clear = p->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			p->node_region.pos.top += DENTAL_MOVE;
			p->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(p, 8);
			Sleep(SLEEP_TIME);
		}

		// Vẽ con trỏ NULL cho NODE bị xóa
		null_deleted = {
			p->node_region.pos.left,
			p->node_region.pos.top,
			p->node_region.pos.right + 40,
			p->node_region.pos.bottom,
			"NULL"
		};
		int limit_null_deleted = p->node_region.pos.right + 2 * RECT_NODE_WIDTH + 50;
		while (null_deleted.pos.right != limit_null_deleted)
		{
			clear = p->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(null_deleted.pos);
			DrawListNode(p, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			setBrushColor(15);
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}

		// Di chuyển các NODE phía sau NODE bị xóa lên trước
		NODE* temp = p->pNext;
		RECT clear;
		while (temp != nullptr && temp != p)
		{
			while (temp->node_region.pos.left != pos_node_linklist.pos.left)
			{
				clear = temp->node_region.pos;
				clear.right += RECT_NODE_WIDTH + 5;
				clearObjectOnScreen(clear);
				temp->node_region.pos.left -= DENTAL_MOVE;
				temp->node_region.pos.right -= DENTAL_MOVE;
				DrawListNode(temp);
				Sleep(SLEEP_TIME);
			}
			pos_node_linklist.pos = temp->node_region.pos;
			pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
			temp = temp->pNext;
		}
	}
	// Xóa hoặc di chuyển con trỏ NULL
	// dựa vào list có trống hay không sau khi xóa
	int limit_null;
	if (list->size == 1)
	{
		clearObjectOnScreen(null.pos);
	}
	else
	{
		limit_null = null.pos.left - 2 * RECT_NODE_WIDTH - 10;
		REGION& i = null;
		while (i.pos.left != limit_null)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left -= DENTAL_MOVE;
			i.pos.right -= DENTAL_MOVE;
			PrintObject(i);
			Sleep(SLEEP_TIME);
		}
	}
}

// Vẽ LINKLIST NODE và mũi tên 
void DrawListNode(NODE* node_list, int color)
{
	setcolor(4);
	REGION& node = node_list->node_region;
	REGION next_pointer = { node.pos.right,node.pos.top,node.pos.right + RECT_NODE_WIDTH / 2,node.pos.bottom ,"*" };
	PrintObject(node, color);
	PrintObject(next_pointer, color);
	int x = next_pointer.pos.right;
	int y = node_list->node_region.pos.top + (node_list->node_region.pos.bottom - node_list->node_region.pos.top) / 2;
	setcolor(15);
	drawArrow(x - 10, y, x + RECT_NODE_WIDTH / 2, y);
}
