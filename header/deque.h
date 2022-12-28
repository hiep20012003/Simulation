#ifndef DEQUEUE_SIMULATION
#define DEQUEUE_SIMULATION
#include"DataStructure.h"

extern DEQUEUE* deque;
extern REGION dequeue_box;

extern REGION insert_front_box;
extern REGION insert_rear_box;
extern REGION delete_front_box;
extern REGION delete_rear_box;

extern RECT pos_node_appear_front;
extern RECT pos_node_appear_rear;

extern int pos_node_dequeue;

void InsertSimulationDequeue(bool front);
void DeleteSimulationDequeue(bool front);

void InitPositionObjectsDequeue();
void DrawOriginalObjectsDequeue();
void RunProgramDequeue();

void DequeueSimulation();
#endif // !DEQUEUE_SIMULATION

