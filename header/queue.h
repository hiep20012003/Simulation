#ifndef QUEUE_SIMULATION
#define QUEUE_SIMULATION
#include"DataStructure.h"

extern REGION queue_box;
extern QUEUE* queue;
extern int pos_in_queue_box;
extern RECT pos_node_appear_queue;

void InsertSimulationQueue();
void DeleteSimulationQueue();

void InitPositionObjectsQueue();
void DrawOriginalObjectsQueue();
void RunProgramQueue();

void QueueSimulation();
#endif // !QUEUE