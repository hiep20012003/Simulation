#ifndef LINK_LIST_SIMULATION
#define LINK_LIST_SIMULATION
#include"DataStructure.h"

extern LINKLIST* list;
extern REGION list_box;
extern REGION pos_node_linklist;
extern REGION null;

void InsertSimulationList(int k);
void DeleteSimulationList(int k);

void InitPositionObjectsList();
void DrawOriginalObjectsList();
void RunProgramList();

void ListSimulation();
void DrawListNode(NODE* node_list, int color = 15);
#endif // !LINK_LIST_SIMULATION

