#include"graphics.h"
#include"circlelist.h"
#include"linklist.h"
#include"global.h"
#include<conio.h>

// Khoi tao circle_list
CIRCLELIST* circle_list;

// Gọi chương trình mô phỏng
void CircleListSimulation()
{
	circle_list = new CIRCLELIST();
	circle_list->init(LIST_SIZE);
	start_cursor = { 60, WINDOW_HEIGHT / 2 - 120 };
	cursor = start_cursor;
	InitConsoleWindow();
	InitPositionObjectsList();
	list_box.pos.top -= 50;
	list_box.pos.bottom -= 50;
	DrawOriginalObjectsList();
	RunProgramCircleList();
	system("cls");
}

// Chạy chương trình mô phỏng
void RunProgramCircleList()
{
	NODE* node_deleted;
	string str;
	int vt;
	while (true)
	{
		if (_kbhit())				// Bắt sự kiện bàn phím
		{
			CheckCurrentCursor();	// Kiếm tra vị trí con trỏ
			char c = _getch();
			if (c == '1')			// Nút INSERT
			{
				// Thông báo
				if (circle_list->size == LIST_SIZE)
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

				// Thêm NODE
				circle_list->InsertNode(str, vt);
				// Mô phỏng thêm NODE
				InsertSimulationCircleList(vt);

				PrintToNewLine(cursor.x, cursor.y, "Completed " + insert_mes);
			}
			else if (c == '2')		// Nút INSERT
			{
				// Thông báo
				if (circle_list->IsEmpty())
				{
					PrintToNewLine(cursor.x, cursor.y, "List Empty. Can't delete");
					continue;
				}
				string delete_mes;
				delete_mes = "Delete";
				PrintTo(cursor.x, cursor.y, delete_mes + " In Position: ");

				// NODE và vị trí xóa NODE
				vt = RealTimeInputInt();
				DeleteSimulationCircleList(vt);
				node_deleted = circle_list->DeleteNode(vt);

				PrintToNewLine(cursor.x, cursor.y, "Completed " + delete_mes + " NODE");

				// pos_node_linklist luôn trỏ đến pTail và vị trí con trỏ NULL
				if (circle_list->pTail != nullptr)
					pos_node_linklist.pos = circle_list->pTail->node_region.pos;
				delete node_deleted;
				if (circle_list->size == 0)
				{
					null.pos.left = pos_node_linklist.pos.right;
					null.pos.right = pos_node_linklist.pos.right + 100;
				}
				// Vẽ liên kết NODE đầu và Cuối
				if (vt > circle_list->size)
					DrawLinkCircle(circle_list->pHead, circle_list->pTail);
			}
			else if (c == 27)
			{
				break;
			}
		}
	}
}

// Mô phỏng Insert
void InsertSimulationCircleList(int k)
{
	RECT clear;

	// Thêm NODE đầu 
	if (k <= 0 || circle_list->size == 1)
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
		circle_list->pHead->node_region.SetRegion(temp_head.pos, circle_list->pHead->data);

		// Nếu list ban đầu không trống
		// Di chuyển các NODE ra phía sau làm trống vị trí đầu tiên để thêm NODE mới
		if (circle_list->size > 1)
		{
			NODE* temp = circle_list->pTail;
			pos_node_linklist.pos = circle_list->pTail->node_region.pos;
			pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
			while (temp != nullptr && temp != circle_list->pHead)
			{
				while (temp->node_region.pos.right != pos_node_linklist.pos.right)
				{
					clear = temp->node_region.pos;
					clear.right += RECT_NODE_WIDTH + 15;
					clearObjectOnScreen(clear);
					temp->node_region.pos.left += DENTAL_MOVE;
					temp->node_region.pos.right += DENTAL_MOVE;
					DrawListNode(temp);
					DrawLinkCircle(circle_list->pHead->pNext, circle_list->pTail);
					Sleep(SLEEP_TIME);
				}
				NODE* prev_temp = circle_list->pHead;
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
		while (circle_list->pHead->node_region.pos.left != pos_node_linklist.pos.left)
		{
			clear = circle_list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 15;
			clearObjectOnScreen(clear);
			circle_list->pHead->node_region.pos.left += DENTAL_MOVE;
			circle_list->pHead->node_region.pos.right += DENTAL_MOVE;
			DrawListNode(circle_list->pHead);

			Sleep(SLEEP_TIME);
		}
		// Vẽ liên kiết giữa NODE đầu và NODE cuối
		DrawLinkCircle(circle_list->pHead, circle_list->pTail);
	}
	// Thêm NODE cuối
	else if (k >= circle_list->size - 1)
	{
		// Đặt lại vị trí thêm NODE nếu list ban đầu không trống
		if (circle_list->pHead != circle_list->pTail)
		{
			pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
		}

		// Tạo vị trí ban đầu của NODE và vị trí NODE di chuyển tới
		REGION temp_tail = pos_node_linklist;
		temp_tail.pos.top = display_box.pos.top + 20;
		temp_tail.pos.bottom = temp_tail.pos.top + RECT_NODE_HEIGHT;
		circle_list->pTail->node_region.SetRegion(temp_tail.pos, circle_list->pTail->data);

		// Di chuyển NODE mới vào vị trí trong list
		while (circle_list->pTail->node_region.pos.top != pos_node_linklist.pos.top)
		{
			clear = circle_list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 20;
			clear.left -= 5;
			clearObjectOnScreen(clear);
			circle_list->pTail->node_region.pos.top += DENTAL_MOVE;
			circle_list->pTail->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(circle_list->pTail);
			DrawLinkCircle(circle_list->pHead, circle_list->pTail);

			Sleep(SLEEP_TIME);
		}
	}
	// Thêm NODE vào giữa list
	else
	{
		// Tìm NODE phía trước NODE được thêm
		NODE* p = circle_list->pHead;
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
		NODE* temp = circle_list->pTail;
		RECT clear;
		pos_node_linklist.pos = circle_list->pTail->node_region.pos;
		pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
		pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
		while (temp != nullptr && temp != p)
		{
			while (temp->node_region.pos.right != pos_node_linklist.pos.right)
			{
				clear = temp->node_region.pos;
				clear.right += RECT_NODE_WIDTH + 15;
				clearObjectOnScreen(clear);
				temp->node_region.pos.left += DENTAL_MOVE;
				temp->node_region.pos.right += DENTAL_MOVE;
				DrawListNode(temp);
				DrawLinkCircle(circle_list->pHead, circle_list->pTail);

				Sleep(SLEEP_TIME);
			}
			NODE* prev_temp = circle_list->pHead;
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
			DrawLinkCircle(circle_list->pHead, circle_list->pTail);

			Sleep(SLEEP_TIME);
		}
	}
	pos_node_linklist.pos = circle_list->pTail->node_region.pos;
}

// Mô hỏng xóa NODE
void DeleteSimulationCircleList(int k)
{
	REGION null_deleted;
	RECT clear;

	// Xóa khu vực hiện thị NODE được xóa trước đó
	clear = {
		display_box.pos.left + 20,
		list_box.pos.bottom + 100,
		display_box.pos.right - 20,
		display_box.pos.bottom - 20,
	};
	clearObjectOnScreen(clear);

	// Xóa NODE đầu
	if (k <= 0 || circle_list->pHead == circle_list->pTail)
	{
		// Xác định vị trí trên console của NODE bị xóa
		pos_node_linklist.pos = circle_list->pHead->node_region.pos;

		// Di chuyển NODE Head ra khỏi list
		REGION temp_head = pos_node_linklist;
		temp_head.pos.top += 200;
		temp_head.pos.bottom = temp_head.pos.top + RECT_NODE_HEIGHT;
		while (circle_list->pHead->node_region.pos.top != temp_head.pos.top)
		{
			clear = circle_list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			circle_list->pHead->node_region.pos.top += DENTAL_MOVE;
			circle_list->pHead->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(circle_list->pHead, 8);
			Sleep(SLEEP_TIME);
		}

		// Vẽ con trỏ NULL cho NODE bị xóa
		null_deleted = {
			circle_list->pHead->node_region.pos.left,
			circle_list->pHead->node_region.pos.top,
			circle_list->pHead->node_region.pos.right + 40,
			circle_list->pHead->node_region.pos.bottom,
			"NULL"
		};
		int limit_null_deleted = circle_list->pHead->node_region.pos.right + 2 * RECT_NODE_WIDTH + 50;
		while (null_deleted.pos.right != limit_null_deleted)
		{
			clear = circle_list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(null_deleted.pos);
			DrawListNode(circle_list->pHead, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			setBrushColor(15);
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}

		// Nếu số phần tử của list > 1
		// Di chuyển các NODE ra phía trước lấp vị trí vừa xóa NODE
		if (circle_list->size > 1)
		{
			NODE* temp = circle_list->pHead->pNext;
			while (temp != circle_list->pHead)
			{
				while (temp->node_region.pos.left != pos_node_linklist.pos.left)
				{
					clear = temp->node_region.pos;
					clear.right += RECT_NODE_WIDTH + 5;
					clearObjectOnScreen(clear);
					temp->node_region.pos.left -= DENTAL_MOVE;
					temp->node_region.pos.right -= DENTAL_MOVE;
					DrawListNode(temp);
					DrawLinkCircle(circle_list->pHead->pNext, circle_list->pTail);
					Sleep(SLEEP_TIME);
				}
				pos_node_linklist.pos = temp->node_region.pos;
				pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
				pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
				temp = temp->pNext;
			}
		}

	}
	// Xóa NODE cuối
	else if (k >= circle_list->size - 1)
	{
		// Xác định vị trí trên console của NODE bị xóa
		pos_node_linklist.pos = {
			circle_list->pTail->node_region.pos.left,
			circle_list->pTail->node_region.pos.top ,
			circle_list->pTail->node_region.pos.right ,
			circle_list->pTail->node_region.pos.bottom,
		};

		// Di chuyển NODE Head ra khỏi list
		REGION temp_tail = pos_node_linklist;
		temp_tail.pos.top += 200;
		temp_tail.pos.bottom = temp_tail.pos.top + RECT_NODE_HEIGHT;
		while (circle_list->pTail->node_region.pos.top != temp_tail.pos.top)
		{
			clear = circle_list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			circle_list->pTail->node_region.pos.top += DENTAL_MOVE;
			circle_list->pTail->node_region.pos.bottom += DENTAL_MOVE;
			DrawListNode(circle_list->pTail, 8);
			Sleep(SLEEP_TIME);
		}

		// Vẽ con trỏ NULL cho NODE bị xóa
		null_deleted = {
			circle_list->pTail->node_region.pos.left,
			circle_list->pTail->node_region.pos.top,
			circle_list->pTail->node_region.pos.right + 40,
			circle_list->pTail->node_region.pos.bottom,
			"NULL"
		};
		int limit_null_deleted = circle_list->pTail->node_region.pos.right + 2 * RECT_NODE_WIDTH + 50;
		while (null_deleted.pos.right != limit_null_deleted)
		{
			clear = circle_list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(null_deleted.pos);
			DrawListNode(circle_list->pTail, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			setBrushColor(15);
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}
	}
	// Xóa NODE giữa
	else
	{
		// Tìm NODE sẽ xóa
		NODE* p = circle_list->pHead;
		int prev_node_k = k - 1;
		while (p->pNext != nullptr && prev_node_k != 0)
		{
			p = p->pNext;
			prev_node_k--;
		}
		p = p->pNext;

		// Xác định vị trí trên console của NODE bị xóa
		pos_node_linklist.pos = p->node_region.pos;

		REGION temp_middle = pos_node_linklist;
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
		while (temp != circle_list->pHead && temp != p)
		{
			while (temp->node_region.pos.left != pos_node_linklist.pos.left)
			{
				clear = temp->node_region.pos;
				clear.right += RECT_NODE_WIDTH + 5;
				clearObjectOnScreen(clear);
				temp->node_region.pos.left -= DENTAL_MOVE;
				temp->node_region.pos.right -= DENTAL_MOVE;
				DrawListNode(temp);
				DrawLinkCircle(circle_list->pHead, circle_list->pTail);
				Sleep(SLEEP_TIME);
			}
			pos_node_linklist.pos = temp->node_region.pos;
			pos_node_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_node_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
			temp = temp->pNext;
		}
	}
}

// Vẽ mũi tên liên két Tail->next -> Head
void DrawLinkCircle(NODE* head, NODE* tail)
{
	ClearLinkCircle(head, tail);
	if (head != nullptr && tail != nullptr)
	{
		setBrushColor(15);
		circle(tail->node_region.pos.right + RECT_NODE_WIDTH + 12,
			tail->node_region.pos.top + (tail->node_region.pos.bottom - tail->node_region.pos.top) / 2, 10);
		line(
			tail->node_region.pos.right + RECT_NODE_WIDTH + 12,
			tail->node_region.pos.top + (tail->node_region.pos.bottom - tail->node_region.pos.top) / 2,
			tail->node_region.pos.right + RECT_NODE_WIDTH + 12,
			list_box.pos.bottom + 50);
		line(
			tail->node_region.pos.right + RECT_NODE_WIDTH + 12,
			head->node_region.pos.bottom + 50,
			head->node_region.pos.left + RECT_NODE_WIDTH / 2,
			head->node_region.pos.bottom + 50);
		drawArrow(
			head->node_region.pos.left + RECT_NODE_WIDTH / 2 - 10,
			head->node_region.pos.bottom + 50,
			head->node_region.pos.left + RECT_NODE_WIDTH / 2 - 10,
			head->node_region.pos.bottom);
	}
	else
		clearObjectOnScreen(list_box.pos);
}

// Xóa mũi tên Tail->next -> Head
void ClearLinkCircle(NODE* head, NODE* tail)
{
	RECT clear = {
		display_box.pos.left + 20,
		pos_node_linklist.pos.bottom ,
		display_box.pos.right - 50,
		pos_node_linklist.pos.bottom + 65,
	};
	clearObjectOnScreen(clear);
	if (circle_list->size >= 1)
	{
		clear = {
		tail->node_region.pos.right + RECT_NODE_WIDTH + 2,
		pos_node_linklist.pos.top ,
		display_box.pos.right - 100,
		pos_node_linklist.pos.bottom,
		};
		clearObjectOnScreen(clear);
	}
}
