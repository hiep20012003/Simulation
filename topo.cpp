#include<iostream>
#include"graphics.h"
#include"global.h"
#include"topo.h"
#include<conio.h>
#include<string>
#include<stdio.h>
using namespace std;

int N, num_edges, num_vertices;
bool check;
NODE_TOPO A[40];
SUCCESSOR* P;

// Hàng đợi dùng mảng
REGION QLINK[40];

// Khai báo các mảng lưu vị trí các thuộc tính của NODE trên console
REGION* node;
REGION* count_prev;
REGION* top;

// Mảng lưu thứ tự topo
int out[40];

// Biến thông báo thoát của MenuTopo
int end_simulation;

void TopoSimulation()
{
	end_simulation = 0;
	system("cls");
	MenuTopo();
	if (end_simulation == 1) return;
	InitAlgorithm();
	Sleep(SLEEP_TIME * 150);
	InputTopo();
	cout << "Dang xu ly..." << endl;
	ProcessTopoSort();
	_getch();
	//system("cls");
}

// Menu
void MenuTopo()
{
	Sleep(100);
	check = false;
	PrintObject({ 600,300,1000,380,"1. Vi du mau" });
	PrintObject({ 600,400,1000,480,"2. Nguoi dung nhap" });

	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == '1')		// Dùng ví dụ mẫu
			{
				FILE* stream;
				freopen_s(&stream, "input_topo.txt", "r", stdin);
				check = true;
				break;
			}
			if (c == '2')		// Người dùng tự nhập
				break;
			if (c == 27)		// Thoát
			{
				end_simulation = 1;
				return;
			}
		}
	}
	system("cls");
}
// Vẽ các đối tượng để biểu diễn đồ thị bằng linked list
void InitAlgorithm()
{
	Sleep(SLEEP_TIME * 150);
	int vt = 250;
	int color = 15;

	PrintObject({ vt,50,vt + 200,100,"NODE[k]" }, color);
	PrintObject({ vt,130,vt + 200,180,"COUNT[k]" }, color);
	PrintObject({ vt,180,vt + 200,230,"TOP[k]" }, color);
	PrintObject({ vt,350,vt + 200,400,"SUC" }, color);
	PrintObject({ vt,460,vt + 200,510,"SUC" }, color);
	PrintObject({ vt,570,vt + 200,620,"SUC" }, color);
	PrintObject({ vt,680,vt + 200,730,"SUC" }, color);
}

// Input và biểu diễn đồ thị theo liên kết đơn từ input
void InputTopo()
{
	// Nhập số nút và số cạnh của đồ thị
	cout << "Nhap so dinh va canh" << endl;
	do
	{
		cin >> N >> num_edges;
		if (N > 7 || N <= 0)
			cout << "So dinh <= 6" << endl;
	} while (N > 7 || N <= 0);
	if (check == true)
	{
		cout << N << " " << num_edges << '\n';
		Sleep(SLEEP_TIME * 150);
	}
	num_vertices = N;

	// Khởi tạo các mảng dùng biểu diễn đồ thị trên console
	node = new REGION[N + 1];
	count_prev = new REGION[N + 1];
	top = new REGION[N + 1];

	// Vẽ giá trị ban đầu của các field của NODE
	int vt = 580;
	for (int i = 1; i <= N; i++)
	{
		string s;
		s = i + 48;
		node[i].SetRegion(vt, 50, vt + 120, 100, s);
		PrintObject(node[i]);
		count_prev[i].SetRegion(vt, 130, vt + 120, 180, "0");
		PrintObject(count_prev[i]);
		PrintObject({ vt,180,vt + 120,230,"*" });
		drawArrow(
			vt + 60,
			210,
			vt + 60,
			300);
		top[i].SetRegion(vt, 350, vt + 120, 400, "nullptr");
		PrintObject(top[i]);
		vt += 150;
	}

	// Đặt giá trị ban đầu của các field của NODE
	for (int i = 1; i <= N; i++)
	{
		A[i].COUNT = 0;
		A[i].TOP = nullptr;
	}
	// Nhập danh sách các cạnh và vẽ đồ thị lên console biểu diễn bằng linked list
	cout << "Nhap danh sach canh" << endl;
	for (int i = 0; i < num_edges; i++)
	{
		int x, y;
		do
		{
			cin >> x >> y;
			if (x > num_vertices || y > num_vertices || x <= 0 || y <= 0)
				cout << "Nhap lai canh: ";
		} while (x > num_vertices || y > num_vertices || x <= 0 || y <= 0);
		if (check == true)
		{
			cout << x << " " << y << '\n';
			Sleep(SLEEP_TIME * 150);
		}
		// Đặt các giá trị của NODE từ input
		A[y].COUNT = A[y].COUNT + 1;
		count_prev[y].data = A[y].COUNT + 48;
		PrintObject(count_prev[y]);
		top[x].data = y + 48;
		P = new SUCCESSOR(y, top[x]);
		P->next = A[x].TOP;
		A[x].TOP = P;

		// Vẽ lên console đồ thị biểu diễn bằng linked list
		SUCCESSOR* head = A[x].TOP;
		if (head != nullptr)
		{
			SUCCESSOR* cur = head;
			while (cur->next != nullptr)
			{
				cur = cur->next;
			}
			SUCCESSOR* tail = cur;
			while (cur != nullptr && cur != head)
			{
				int limit = cur->pos.pos.bottom + 60;
				while (cur->pos.pos.top != limit)
				{
					RECT clear = cur->pos.pos;
					clear.bottom += 50;
					clearObjectOnScreen(clear);
					cur->pos.pos.top += DENTAL_MOVE;
					cur->pos.pos.bottom += DENTAL_MOVE;
					DrawSuccessor(cur);
					Sleep(SLEEP_TIME);
				}
				SUCCESSOR* prev = head;
				while (prev->next != nullptr && prev->next != cur)
				{
					prev = prev->next;
				}
				cur = prev;
			}
			REGION null = tail->pos;
			null.data = "nullptr";
			null.pos.top += 110;
			null.pos.bottom += 110;
			PrintObject(null);
		}
		else continue;
		int limit = A[x].TOP->pos.pos.top;
		A[x].TOP->pos.pos.top -= 50;
		A[x].TOP->pos.pos.bottom -= 50;
		while (A[x].TOP->pos.pos.top != limit)
		{
			RECT clear = A[x].TOP->pos.pos;
			clear.bottom += 50;
			clearObjectOnScreen(clear);
			A[x].TOP->pos.pos.top += DENTAL_MOVE;
			A[x].TOP->pos.pos.bottom += DENTAL_MOVE;
			DrawSuccessor(A[x].TOP);
			Sleep(SLEEP_TIME);
		}
	}
}
void ProcessTopoSort()
{
	// Tạo hàng đợi và đặt tất cả giá trị QLINK = 0
	int R = 0, F;
	for (int i = 0; i <= num_vertices; i++)
		QLINK[i].data = "0";
	// Vẽ hàng đợi lên console
	REGION queue = { 800,WINDOW_HEIGHT - 200, WINDOW_WIDTH - 400,WINDOW_HEIGHT - 100 };
	setBrushColor(16);
	rectangle(queue.pos);
	REGION pos_rear_queue = { queue.pos.left + 10,queue.pos.top + 10,queue.pos.left + 60,queue.pos.bottom - 10 };
	REGION pos_front_queue = { queue.pos.left + 10,queue.pos.top + 10,queue.pos.left + 60,queue.pos.bottom - 10 };

	// biến COUNT lưu số cạnh đi vào NODE đó
	// Kiếm tra và đẩy các NODE mà COUNT = 0 vào hàng đợi
	// ( các NODE không có cạnh nào đi vào )
	for (int i = 1; i <= num_vertices; i++)
	{
		if (A[i].COUNT == 0)
		{
			QLINK[R].data = i + 48;
			QLINK[R].pos = pos_rear_queue.pos;
			pos_rear_queue.pos.left = pos_rear_queue.pos.right + 10;
			pos_rear_queue.pos.right = pos_rear_queue.pos.left + 50;
			PrintObject(count_prev[i], 11);
			Sleep(SLEEP_TIME * 150);
			PrintObject(node[i], 8);
			int limit_queue = QLINK[R].pos.left;
			QLINK[R].pos.left = queue.pos.right + 50;
			QLINK[R].pos.right = QLINK[R].pos.left + 50;

			// Di chuyển NODE vào trong hàng đợi
			while (QLINK[R].pos.left != limit_queue)
			{
				RECT clear = QLINK[R].pos;
				clearObjectOnScreen(clear);
				QLINK[R].pos.left -= DENTAL_MOVE;
				QLINK[R].pos.right -= DENTAL_MOVE;
				PrintObject(QLINK[R], 8);
				Sleep(SLEEP_TIME);
			}
			Sleep(SLEEP_TIME * 150);
			PrintObject(QLINK[R]);
			PrintObject(node[i]);

			R = i;
			Sleep(SLEEP_TIME * 150);
		}
	}

	//xu ly topo

	int nout = 0;
	out[num_vertices + 1] = { 0 };
	int ptr_front = 0;
	int out_limit = 300;

	// Duyệt từng NODE theo thứ tự lấy ra từ hàng đợi
	for (F = stoi(QLINK[0].data); F != 0; F = stoi(QLINK[F].data))
	{
		out[nout++] = F;
		N--;			// Nếu sau thuật toán N == 0 thì có thứ tự topo 

		// Lấy ra Front NODE từ hàng đợi
		REGION& i = QLINK[ptr_front];
		while (i.pos.left != out_limit)
		{
			clearObjectOnScreen(i.pos);
			i.pos.left -= DENTAL_MOVE;
			i.pos.right -= DENTAL_MOVE;
			PrintObject(i, 9);
			Sleep(SLEEP_TIME);
		}

		// Cập nhập lại vị trí thêm node trong hàng đợi
		pos_rear_queue.pos.right = pos_rear_queue.pos.left - 10;
		pos_rear_queue.pos.left = pos_rear_queue.pos.left - 60;
		int queue_limit = pos_front_queue.pos.left;

		// Bỏ tô màu đối tượng được chọn trước đó
		int j = F;
		while (stoi(QLINK[j].data) != 0)
		{
			REGION& k = QLINK[j];
			while (k.pos.left != queue_limit)
			{
				clearObjectOnScreen(k.pos);
				k.pos.left -= DENTAL_MOVE;
				k.pos.right -= DENTAL_MOVE;
				PrintObject(k);
				Sleep(SLEEP_TIME);
			}
			queue_limit = k.pos.right + 10;
			j = stoi(QLINK[j].data);
		}
		Sleep(SLEEP_TIME * 150);
		SUCCESSOR* restore = A[ptr_front].TOP;
		while (restore != nullptr)
		{
			PrintObject(restore->pos);
			restore = restore->next;
		}
		Sleep(SLEEP_TIME * 150);
		PrintObject(node[F], 9);

		// Duyệt các successor của NODE lấy ra từ hàng đợi
		// Nếu COUNT[k] -- == 0
		// nghĩa là NODE successor đó chỉ có 1 cạnh đi vào nó
		// thì đẩy NODE successor vào hàng đợi
		// Nếu không duyệt đến successor tiếp theo
		for (P = A[F].TOP; P != nullptr; P = P->next)
		{
			// Tô màu các đối tượng được chọn
			Sleep(SLEEP_TIME * 150);
			PrintObject(P->pos, 8);
			Sleep(SLEEP_TIME * 150);
			PrintObject(node[P->SUC], 8);
			Sleep(SLEEP_TIME * 150);
			PrintObject(count_prev[P->SUC], 10);
			count_prev[P->SUC].data = A[P->SUC].COUNT - 1 + 48;
			Sleep(SLEEP_TIME * 150);
			if (count_prev[P->SUC].data == "0")
				PrintObject(count_prev[P->SUC], 11);
			else
				PrintObject(count_prev[P->SUC], 10);
			Sleep(SLEEP_TIME * 150);

			// Kiểm tra COUNT[k] == 0 hay không và thực hiện COUNT[k]--
			if (--A[P->SUC].COUNT != 0)
			{
				PrintObject(node[P->SUC]);
				continue;
			}

			// Đưa NODE successor vào hàng đợi
			QLINK[R].data = P->SUC + 48;
			QLINK[R].pos = pos_rear_queue.pos;
			int limit_queue = QLINK[R].pos.left;
			QLINK[R].pos.left = queue.pos.right + 50;
			QLINK[R].pos.right = QLINK[R].pos.left + 50;
			while (QLINK[R].pos.left != limit_queue)
			{
				RECT clear = QLINK[R].pos;
				clearObjectOnScreen(clear);
				QLINK[R].pos.left -= DENTAL_MOVE;
				QLINK[R].pos.right -= DENTAL_MOVE;
				PrintObject(QLINK[R], 8);
				Sleep(SLEEP_TIME);
			}
			R = P->SUC;
			pos_rear_queue.pos.left = pos_rear_queue.pos.right + 10;
			pos_rear_queue.pos.right = pos_rear_queue.pos.left + 50;
			Sleep(SLEEP_TIME * 150);

			PrintObject(node[P->SUC]);
		}
		ptr_front = F;
		out_limit += 60;
		PrintObject(i);
		PrintObject(node[F], 12);
	}
	// Nếu N == 0 thì đồ thị có thứ tự topo
	if (N != 0)
		PrintObject({ 200,300,1400,500,"Do thi khong co thu tu topo" }, 14);
	else
	{
		cout << "Thu tu topo la:" << endl;
		for (int i = 0; i < num_vertices; i++)
			cout << out[i] << " ";
	}
}
// Vẽ successor của NODE
void DrawSuccessor(SUCCESSOR* node, int color)
{
	setcolor(4);
	PrintObject(node->pos, color);
	int x = node->pos.pos.left + (node->pos.pos.right - node->pos.pos.left) / 2;
	int y = node->pos.pos.bottom;
	drawArrow(x, y, x, y + 50);
}