#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE
#include<iostream>
#include<windows.h>
using namespace std;

// Luu toa do x,y cua cua so console
struct POSITION
{
	int x;
	int y;
	void ChangePos(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}
};
// Luu vi tri, du lieu va kich thuoc cua cac object tren man hinh
struct REGION
{
	RECT pos;
	string data;
	void SetRegion(int x1, int y1, int x2, int y2, string str = "")
	{
		pos.left = x1;
		pos.top = y1;
		pos.right = x2;
		pos.bottom = y2;
		data = str;
	}
	void SetRegion(RECT region, string str = "")
	{
		pos = region;
		data = str;
	}
};

// struct node co them bien kieu REGION luu vi tri ve len man hinh cua node
struct NODE
{
	NODE(string new_data, REGION region = { 0,0,0,0 })
	{
		data = new_data;
		node_region = region;
		pNext = pPrev = nullptr;
	}
	string data;
	REGION node_region;
	NODE* pPrev, * pNext;
};

// Linked stack
struct LINKEDSTACK
{
	NODE* pTop;
	int capacity, size;
	void init(int capacity)
	{
		pTop = nullptr;
		this->capacity = capacity;
		size = 0;
	}
	bool IsEmpty()
	{
		return pTop == nullptr;
	}
	bool InsertNode(string value)
	{
		NODE* temp = new NODE(value);
		if (size == capacity)
			return false;
		if (IsEmpty())
		{
			pTop = temp;
			size++;
			return true;
		}
		temp->pNext = pTop;
		pTop = temp;
		size++;
		return true;
	}
	NODE* DeleteNode()
	{
		if (IsEmpty())
			return nullptr;
		size--;
		NODE* temp = new NODE(pTop->data, pTop->node_region);
		pTop = pTop->pNext;
		return temp;
	}
};

// QUEUE
struct QUEUE
{
	NODE* pFront;
	NODE* pRear;
	int capacity, size;
	void init(int capacity)
	{
		pFront = nullptr;
		pRear = nullptr;
		this->capacity = capacity;
		size = 0;
	}
	bool IsEmpty()
	{
		return pFront == nullptr;
	}
	bool InsertNode(string str)
	{
		if (size == capacity)
			return false;
		NODE* temp = new NODE(str);
		if (pRear == nullptr) {
			pFront = pRear = temp;
			size++;
			return true;
		}
		size++;
		pRear->pNext = temp;
		pRear = temp;
		return true;
	}
	NODE* DeleteNode()
	{
		if (IsEmpty())
			return nullptr;
		NODE* temp = pFront;
		pFront = pFront->pNext;
		if (pFront == nullptr)
			pRear = nullptr;
		size--;
		return temp;
	}
};

// DEQUEUE
struct DEQUEUE
{
	NODE* pFront;
	NODE* pRear;
	int capacity, size;
	void init(int capacity)
	{
		pFront = pRear = nullptr;
		this->capacity = capacity;
		size = 0;
	}
	bool IsEmpty()
	{
		return pFront == nullptr;
	}
	bool InsertNode(string str, bool front)
	{
		if (size == capacity)
			return false;
		NODE* temp = new NODE(str);
		if (pFront == nullptr) {
			pFront = pRear = temp;
			size++;
			return true;
		}
		if (front)
		{
			temp->pNext = pFront;
			pFront->pPrev = temp;
			pFront = temp;
		}
		else
		{
			temp->pPrev = pRear;
			pRear->pNext = temp;
			pRear = temp;
		}
		size++;
		return true;
	}
	NODE* DeleteNode(bool front)
	{
		if (IsEmpty())
			return nullptr;
		NODE* temp;
		if (front)
		{
			temp = pFront;
			pFront = pFront->pNext;
			if (pFront == nullptr)
				pRear = nullptr;
			else pFront->pPrev = nullptr;
			temp->pNext = nullptr;
		}
		else
		{
			temp = pRear;
			pRear = pRear->pPrev;
			if (pRear == nullptr)
				pFront = nullptr;
			else
				pRear->pNext = nullptr;
			temp->pPrev = nullptr;
		}
		size--;
		return temp;
	}
};

// LINKLIST
struct LINKLIST
{
	NODE* pHead;
	NODE* pTail;
	int capacity;
	int size;
	void init(int SIZE)
	{
		pHead = pTail = nullptr;
		capacity = SIZE;
		size = 0;
	}
	bool IsEmpty()
	{
		return pHead == nullptr;
	}
	bool InsertNode(string str, int k)
	{
		if (size == capacity) return false;
		NODE* temp = new NODE(str);
		if (IsEmpty())
		{
			pHead = pTail = temp;
			size++;
			return true;
		}
		if (k <= 0)
		{
			temp->pNext = pHead;
			pHead = temp;
		}
		else if (k > size - 1)
		{
			pTail->pNext = temp;
			pTail = temp;
		}
		else
		{
			NODE* p = pHead;
			int prev_node_k = k - 1;
			while (p->pNext != nullptr && prev_node_k != 0)
			{
				p = p->pNext;
				prev_node_k--;
			}
			temp->pNext = p->pNext;
			p->pNext = temp;
		}
		size++;
		return true;
	}
	NODE* DeleteNode(int k)
	{
		if (IsEmpty())
		{
			return nullptr;
		}
		NODE* temp;
		if (k <= 0 || pHead == pTail)
		{
			temp = pHead;
			pHead = pHead->pNext;
		}
		else if (k >= size - 1)
		{
			temp = pTail;
			NODE* p = pHead;
			int prev_node_k = size - 2;
			while (p->pNext != nullptr && prev_node_k != 0)
			{
				p = p->pNext;
				prev_node_k--;
			}
			pTail = p;
			pTail->pNext = nullptr;
		}
		else
		{
			NODE* p = pHead;
			int prev_node_k = k - 1;
			while (p->pNext != nullptr && prev_node_k != 0)
			{
				p = p->pNext;
				prev_node_k--;
			}
			temp = p->pNext;
			p->pNext = temp->pNext;
			temp->pNext = nullptr;
		}
		size--;
		return temp;
	}
};

// CIRCLE LIST
struct CIRCLELIST
{
	NODE* pHead;
	NODE* pTail;
	int capacity;
	int size;
	void init(int SIZE)
	{
		pHead = pTail = nullptr;
		capacity = SIZE;
		size = 0;
	}
	bool IsEmpty()
	{
		return pHead == nullptr;
	}
	bool InsertNode(string str, int k)
	{
		if (size == capacity) return false;
		NODE* temp = new NODE(str);
		if (IsEmpty())
		{
			pHead = pTail = temp;
			pHead->pNext = pTail;
			pTail->pNext = pHead;
			size++;
			return true;
		}
		if (k <= 0)
		{
			temp->pNext = pTail->pNext;
			pTail->pNext = temp;
			pHead = temp;
		}
		else if (k > size - 1)
		{
			temp->pNext = pTail->pNext;
			pTail->pNext = temp;
			pTail = temp;
		}
		else
		{
			NODE* p = pHead;
			int prev_node_k = k - 1;
			while (p->pNext != nullptr && prev_node_k != 0)
			{
				p = p->pNext;
				prev_node_k--;
			}
			temp->pNext = p->pNext;
			p->pNext = temp;
		}
		size++;
		return true;
	}
	NODE* DeleteNode(int k)
	{
		if (IsEmpty())
		{
			return nullptr;
		}
		NODE* temp;
		if (k <= 0 || pHead == pTail)
		{
			temp = pHead;
			if (pHead->pNext == pHead)
				pHead = pTail = nullptr;
			else {
				pHead = pHead->pNext;
				pTail->pNext = pHead;
			}
		}
		else if (k >= size - 1)
		{
			temp = pTail;
			NODE* p = pHead;
			int prev_node_k = size - 2;
			while (p->pNext != nullptr && prev_node_k != 0)
			{
				p = p->pNext;
				prev_node_k--;
			}
			pTail = p;
			pTail->pNext = pHead;
		}
		else
		{
			NODE* p = pHead;
			int prev_node_k = k - 1;
			while (p->pNext != nullptr && prev_node_k != 0)
			{
				p = p->pNext;
				prev_node_k--;
			}
			temp = p->pNext;
			p->pNext = temp->pNext;
			temp->pNext = nullptr;
		}
		size--;
		return temp;
	}
};
#endif