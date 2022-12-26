#ifndef TOPO_SIMULATION
#define TOPO_SIMULATION
#include"DataStructure.h"

struct SUCCESSOR
{
	int SUC;
	REGION pos;
	SUCCESSOR* next;
	SUCCESSOR(int value, REGION position)
	{
		SUC = value;
		pos = position;
	}
};
struct NODE_TOPO
{
	int COUNT;
	SUCCESSOR* TOP;
};

extern int N, num_edges, num_vertices;
extern bool check;

extern NODE_TOPO A[40];
extern SUCCESSOR* P;

extern REGION QLINK[40];

extern REGION* node;
extern REGION* count_prev;
extern REGION* top;

extern int out[40];

extern int end_simulation;


void MenuTopo();
void TopoSimulation();
void InputTopo();
void InitAlgorithm();
void ProcessTopoSort();
//void InitWindowTopo();
void DrawSuccessor(SUCCESSOR* node, int color = 15);
#endif // !TOPO
