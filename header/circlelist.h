#ifndef CIRCLE_LIST_SIMULATION
#define CIRCLE_LIST_SIMULATION
#include"DataStructure.h"

extern CIRCLELIST* circle_list;

void InsertSimulationCircleList(int k);
void DeleteSimulationCircleList(int k);

void RunProgramCircleList();

void CircleListSimulation();
void DrawLinkCircle(NODE* head, NODE* tail);
void ClearLinkCircle(NODE* head, NODE* tail);
#endif 

