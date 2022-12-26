#include"graphics.h"
#include"circlelist.h"
#include"linklist.h"
#include"global.h"
#include<conio.h>

// Khoi tao circle_list
CIRCLELIST* circle_list;

// Ham goi chuong trinh mo phong
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

// Bat su kien ban phim cho chuc nang insert, delete, end
void RunProgramCircleList()
{
	NODE* node_deleted;
	string str;
	int vt;
	while (true)
	{
		if (_kbhit())
		{
			CheckCurrentCursor();
			char c = _getch();
			if (c == '1')
			{
				if (circle_list->size == LIST_SIZE)
				{
					PrintToNewLine(cursor.x, cursor.y, "List was Full");
					continue;
				}
				string insert_mes;
				insert_mes = "Insert NODE";
				PrintTo(cursor.x, cursor.y, insert_mes + ": ");
				str = RealTimeInputString();
				PrintTo(cursor.x, cursor.y, "Positon: ");
				vt = RealTimeInputInt();
				circle_list->InsertNode(str, vt);
				InsertSimulationCircleList(vt);
				PrintToNewLine(cursor.x, cursor.y, "Completed " + insert_mes);
			}
			else if (c == '2')
			{
				if (circle_list->IsEmpty())
				{
					PrintToNewLine(cursor.x, cursor.y, "List Empty. Can't delete");
					continue;
				}
				string delete_mes;
				delete_mes = "Delete";
				PrintTo(cursor.x, cursor.y, delete_mes + " In Position: ");
				vt = RealTimeInputInt();
				DeleteSimulationCircleList(vt);
				node_deleted = circle_list->DeleteNode(vt);
				if (vt >= circle_list->size - 1)
					DrawLinkCircle(circle_list->pHead, circle_list->pTail);
				PrintToNewLine(cursor.x, cursor.y, "Completed " + delete_mes + " NODE");
				if (circle_list->pTail != nullptr)
					pos_in_linklist.pos = circle_list->pTail->node_region.pos;
				delete node_deleted;
				if (circle_list->size == 0)
				{
					null.pos.left = pos_in_linklist.pos.right;
					null.pos.right = pos_in_linklist.pos.right + 100;
				}
			}
			else if (c == 27)
			{
				break;
			}
		}
	}
}

// Ham mo phong insert
void InsertSimulationCircleList(int k)
{
	RECT clear;
	if (k <= 0 || circle_list->size == 1)
	{
		pos_in_linklist = {
			list_box.pos.left,
			list_box.pos.top,
			list_box.pos.left + RECT_NODE_WIDTH,
			list_box.pos.bottom };

		REGION temp_head = pos_in_linklist;
		temp_head.pos.left = display_box.pos.left + 10;
		temp_head.pos.right = temp_head.pos.left + RECT_NODE_WIDTH;
		circle_list->pHead->node_region.SetRegion(temp_head.pos, circle_list->pHead->data);

		if (circle_list->size > 1)
		{
			NODE* temp = circle_list->pTail;
			pos_in_linklist.pos = circle_list->pTail->node_region.pos;
			pos_in_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_in_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
			while (temp != nullptr && temp != circle_list->pHead)
			{
				while (temp->node_region.pos.right != pos_in_linklist.pos.right)
				{
					clear = temp->node_region.pos;
					clear.right += RECT_NODE_WIDTH + 15;
					clearObjectOnScreen(clear);
					temp->node_region.pos.left += DENTAL_MOVE;
					temp->node_region.pos.right += DENTAL_MOVE;
					DrawListCircleNode(temp);
					DrawLinkCircle(circle_list->pHead->pNext, circle_list->pTail);
					Sleep(SLEEP_TIME);
				}
				NODE* prev_temp = circle_list->pHead;
				while (prev_temp->pNext != nullptr && prev_temp->pNext != temp)
				{
					prev_temp = prev_temp->pNext;
				}
				pos_in_linklist.pos = temp->node_region.pos;
				pos_in_linklist.pos.left -= RECT_NODE_WIDTH * 2 + 10;
				pos_in_linklist.pos.right -= RECT_NODE_WIDTH * 2 + 10;
				temp = prev_temp;
			}
		}
		while (circle_list->pHead->node_region.pos.left != pos_in_linklist.pos.left)
		{
			clear = circle_list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 15;
			clearObjectOnScreen(clear);
			circle_list->pHead->node_region.pos.left += DENTAL_MOVE;
			circle_list->pHead->node_region.pos.right += DENTAL_MOVE;
			DrawListCircleNode(circle_list->pHead);

			Sleep(SLEEP_TIME);
		}
		DrawLinkCircle(circle_list->pHead, circle_list->pTail);
	}
	else if (k >= circle_list->size - 1)
	{
		if (circle_list->pHead != circle_list->pTail)
		{
			pos_in_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_in_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
		}
		REGION temp_tail = pos_in_linklist;
		temp_tail.pos.top = display_box.pos.top + 20;
		temp_tail.pos.bottom = temp_tail.pos.top + RECT_NODE_HEIGHT;
		circle_list->pTail->node_region.SetRegion(temp_tail.pos, circle_list->pTail->data);
		while (circle_list->pTail->node_region.pos.top != pos_in_linklist.pos.top)
		{
			clear = circle_list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 20;
			clear.left -= 5;
			clearObjectOnScreen(clear);
			circle_list->pTail->node_region.pos.top += DENTAL_MOVE;
			circle_list->pTail->node_region.pos.bottom += DENTAL_MOVE;
			DrawListCircleNode(circle_list->pTail);
			DrawLinkCircle(circle_list->pHead, circle_list->pTail);

			Sleep(SLEEP_TIME);
		}
	}
	else
	{
		NODE* p = circle_list->pHead;
		int prev_node_k = k - 1;
		while (p->pNext != nullptr && prev_node_k != 0)
		{
			p = p->pNext;
			prev_node_k--;
		}
		pos_in_linklist.pos = p->node_region.pos;
		pos_in_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
		pos_in_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;

		p = p->pNext;
		REGION temp_middle = pos_in_linklist;
		temp_middle.pos.top = display_box.pos.top + 20;
		temp_middle.pos.bottom = temp_middle.pos.top + RECT_NODE_HEIGHT;
		p->node_region.SetRegion(temp_middle.pos, p->data);


		NODE* temp = circle_list->pTail;
		RECT clear;
		pos_in_linklist.pos = circle_list->pTail->node_region.pos;
		pos_in_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
		pos_in_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
		while (temp != nullptr && temp != p)
		{
			while (temp->node_region.pos.right != pos_in_linklist.pos.right)
			{
				clear = temp->node_region.pos;
				clear.right += RECT_NODE_WIDTH + 15;
				clearObjectOnScreen(clear);
				temp->node_region.pos.left += DENTAL_MOVE;
				temp->node_region.pos.right += DENTAL_MOVE;
				DrawListCircleNode(temp);
				DrawLinkCircle(circle_list->pHead, circle_list->pTail);

				Sleep(SLEEP_TIME);
			}
			NODE* prev_temp = circle_list->pHead;
			while (prev_temp->pNext != nullptr && prev_temp->pNext != temp)
			{
				prev_temp = prev_temp->pNext;
			}
			pos_in_linklist.pos = temp->node_region.pos;
			pos_in_linklist.pos.left -= RECT_NODE_WIDTH * 2 + 10;
			pos_in_linklist.pos.right -= RECT_NODE_WIDTH * 2 + 10;
			temp = prev_temp;
		}
		while (p->node_region.pos.top != pos_in_linklist.pos.top)
		{
			clear = p->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			p->node_region.pos.top += DENTAL_MOVE;
			p->node_region.pos.bottom += DENTAL_MOVE;
			DrawListCircleNode(p);
			DrawLinkCircle(circle_list->pHead, circle_list->pTail);

			Sleep(SLEEP_TIME);
		}
	}
	pos_in_linklist.pos = circle_list->pTail->node_region.pos;
}

// Ham mo phong delete
void DeleteSimulationCircleList(int k)
{
	REGION null_deleted;
	RECT clear;
	clear = {
		display_box.pos.left + 20,
		list_box.pos.bottom + 100,
		display_box.pos.right - 20,
		display_box.pos.bottom - 20,
	};
	clearObjectOnScreen(clear);
	if (k <= 0 || circle_list->pHead == circle_list->pTail)
	{
		pos_in_linklist.pos = circle_list->pHead->node_region.pos;

		REGION temp_head = pos_in_linklist;
		temp_head.pos.top += 200;
		temp_head.pos.bottom = temp_head.pos.top + RECT_NODE_HEIGHT;
		while (circle_list->pHead->node_region.pos.top != temp_head.pos.top)
		{
			clear = circle_list->pHead->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			circle_list->pHead->node_region.pos.top += DENTAL_MOVE;
			circle_list->pHead->node_region.pos.bottom += DENTAL_MOVE;
			DrawListCircleNode(circle_list->pHead, 8);
			Sleep(SLEEP_TIME);
		}
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
			DrawListCircleNode(circle_list->pHead, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			setBrushColor(15);
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}
		if (circle_list->size > 1)
		{
			NODE* temp = circle_list->pHead->pNext;
			while (temp != circle_list->pHead)
			{
				while (temp->node_region.pos.left != pos_in_linklist.pos.left)
				{
					clear = temp->node_region.pos;
					clear.right += RECT_NODE_WIDTH + 5;
					clearObjectOnScreen(clear);
					temp->node_region.pos.left -= DENTAL_MOVE;
					temp->node_region.pos.right -= DENTAL_MOVE;
					DrawListCircleNode(temp);
					DrawLinkCircle(circle_list->pHead->pNext, circle_list->pTail);
					Sleep(SLEEP_TIME);
				}
				pos_in_linklist.pos = temp->node_region.pos;
				pos_in_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
				pos_in_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
				temp = temp->pNext;
			}
		}

	}
	else if (k >= circle_list->size - 1)
	{
		pos_in_linklist.pos = {
			circle_list->pTail->node_region.pos.left,
			circle_list->pTail->node_region.pos.top ,
			circle_list->pTail->node_region.pos.right ,
			circle_list->pTail->node_region.pos.bottom,
		};
		REGION temp_tail = pos_in_linklist;
		temp_tail.pos.top += 200;
		temp_tail.pos.bottom = temp_tail.pos.top + RECT_NODE_HEIGHT;
		while (circle_list->pTail->node_region.pos.top != temp_tail.pos.top)
		{
			clear = circle_list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			circle_list->pTail->node_region.pos.top += DENTAL_MOVE;
			circle_list->pTail->node_region.pos.bottom += DENTAL_MOVE;
			DrawListCircleNode(circle_list->pTail, 8);
			Sleep(SLEEP_TIME);
		}
		null_deleted = {
			circle_list->pTail->node_region.pos.left,
			circle_list->pTail->node_region.pos.top,
			circle_list->pTail->node_region.pos.right + 40,
			circle_list->pTail->node_region.pos.bottom,
			"NULL"
		};
		//NODE* prev_tail = circ 
		//while()
		int limit_null_deleted = circle_list->pTail->node_region.pos.right + 2 * RECT_NODE_WIDTH + 50;
		while (null_deleted.pos.right != limit_null_deleted)
		{
			clear = circle_list->pTail->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(null_deleted.pos);
			DrawListCircleNode(circle_list->pTail, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			setBrushColor(15);
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}
	}
	else
	{
		NODE* p = circle_list->pHead;
		int prev_node_k = k - 1;
		while (p->pNext != nullptr && prev_node_k != 0)
		{
			p = p->pNext;
			prev_node_k--;
		}
		p = p->pNext;
		pos_in_linklist.pos = p->node_region.pos;

		REGION temp_middle = pos_in_linklist;
		temp_middle.pos.top += 200;
		temp_middle.pos.bottom = temp_middle.pos.top + RECT_NODE_HEIGHT;


		while (p->node_region.pos.top != temp_middle.pos.top)
		{
			clear = p->node_region.pos;
			clear.right += RECT_NODE_WIDTH + 5;
			clearObjectOnScreen(clear);
			p->node_region.pos.top += DENTAL_MOVE;
			p->node_region.pos.bottom += DENTAL_MOVE;
			DrawListCircleNode(p, 8);
			Sleep(SLEEP_TIME);
		}
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
			DrawListCircleNode(p, 8);
			null_deleted.pos.left += DENTAL_MOVE;
			null_deleted.pos.right += DENTAL_MOVE;
			setBrushColor(15);
			PrintObject(null_deleted);
			Sleep(SLEEP_TIME);
		}
		NODE* temp = p->pNext;
		RECT clear;
		while (temp != circle_list->pHead && temp != p)
		{
			while (temp->node_region.pos.left != pos_in_linklist.pos.left)
			{
				clear = temp->node_region.pos;
				clear.right += RECT_NODE_WIDTH + 5;
				clearObjectOnScreen(clear);
				temp->node_region.pos.left -= DENTAL_MOVE;
				temp->node_region.pos.right -= DENTAL_MOVE;
				DrawListCircleNode(temp);
				DrawLinkCircle(circle_list->pHead, circle_list->pTail);
				Sleep(SLEEP_TIME);
			}
			pos_in_linklist.pos = temp->node_region.pos;
			pos_in_linklist.pos.left += RECT_NODE_WIDTH * 2 + 10;
			pos_in_linklist.pos.right += RECT_NODE_WIDTH * 2 + 10;
			temp = temp->pNext;
		}
	}

}

// Ham ve node cua circle list
void DrawListCircleNode(NODE* node_list, int color)
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

// Ham ve mui ten cho lien ket Tail->next -> Head
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

// Ham xoa mui ten lien ket Tail->next -> Head
void ClearLinkCircle(NODE* head, NODE* tail)
{
	RECT clear = {
		display_box.pos.left + 20,
		pos_in_linklist.pos.bottom ,
		display_box.pos.right - 50,
		pos_in_linklist.pos.bottom + 65,
	};
	clearObjectOnScreen(clear);
	if (circle_list->size >= 1)
	{
		clear = {
		tail->node_region.pos.right + RECT_NODE_WIDTH + 2,
		pos_in_linklist.pos.top ,
		display_box.pos.right - 100,
		pos_in_linklist.pos.bottom,
		};
		clearObjectOnScreen(clear);
	}
}
