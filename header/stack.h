#ifndef STACK_SIMULATION
#define STACK_SIMULATION
#include"DataStructure.h"

extern LINKEDSTACK* stack;
extern REGION stack_box;
extern int pos_in_stack_box;
extern RECT pos_node_appear;

void InsertSimulationStack();
void DeleteSimulationStack();

void InitPositionObjectsStack();
void DrawOriginalObjectsStack();
void RunProgramStack();

void StackSimulation();
#endif // !STACK