#include <iostream>
#include<conio.h>
#include"global.h"
#include"graphics.h"
#include"stack.h"
#include"queue.h"
#include"deque.h"
#include"linklist.h"
#include"circlelist.h"
#include"topo.h"

void MenuSimulation();
int main()
{
	initgraph();
	InitConsoleWindow();
	gotoxy(10, 46);
	MenuSimulation();
	while (true)
	{
		char ch;
		//system("pause");
		if (_kbhit())
		{
			ch = _getch();
			if (ch == '1')
			{
				StackSimulation();
			}
			else if (ch == '2')
				QueueSimulation();
			else if (ch == '3')
				DequeueSimulation();
			else if (ch == '4')
				ListSimulation();
			else if (ch == '5')
				CircleListSimulation();
			else if (ch == '6')
				TopoSimulation();
			else if (ch == 27)
				break;
			setcolor(9);
			Sleep(100);
			MenuSimulation();
		}
	}
	_getch();
	return 0;
}
void MenuSimulation()
{
	setcolor(16);
	setBrushColor(16);
	rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	setcolor(13);
	setBrushColor(16);
	REGION menu = { 250, 100, WINDOW_WIDTH - 300, WINDOW_HEIGHT - 300 };
	REGION stack_option = {
		menu.pos.left + 80,
		menu.pos.top + 50,
		menu.pos.right - 80,
		menu.pos.top + 100,
		"1. Stack Simulation" };
	REGION queue_option = {
		menu.pos.left + 80,
		menu.pos.top + 120,
		menu.pos.right - 80,
		menu.pos.top + 170,
		"2. Queue Simulation" };
	REGION dequeue_option = {
		menu.pos.left + 80,
		menu.pos.top + 190,
		menu.pos.right - 80,
		menu.pos.top + 240,
		"3. Dequeue Simulation" };
	REGION link_list_option = {
		menu.pos.left + 80,
		menu.pos.top + 260,
		menu.pos.right - 80,
		menu.pos.top + 310,
		"4. Linked List Simulation" };
	REGION circle_list_option = {
		menu.pos.left + 80,
		menu.pos.top + 330,
		menu.pos.right - 80,
		menu.pos.top + 380,
		"5. Circle List Simulation" };
	REGION topo_option = {
		menu.pos.left + 80,
		menu.pos.top + 400,
		menu.pos.right - 80,
		menu.pos.top + 450,
		"6. Topo Sort" };
	PrintObject(menu,16);
	setBrushColor(15);
	PrintObject(stack_option);
	PrintObject(queue_option);
	PrintObject(dequeue_option);
	PrintObject(link_list_option);
	PrintObject(circle_list_option);
	PrintObject(topo_option);
}


