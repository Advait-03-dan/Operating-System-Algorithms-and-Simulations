#include <stdio.h>
#include <stdlib.h>

//Making queue for PCB by creating doubally linked list
//It represents Ready Queue

// 						head			 tail
//arrival time 			 1,     2,3,4,    5

typedef struct Node Node;
struct Node
{
    Node* ahead;
    Node* behind;
    PCB* process;
};

typedef struct 
{
    Node* head;
    Node* tail;
    
}Queue;


// --- Function List --- //
Node* createEmptyNode();
Node* createNode(PCB*);
Queue* createQueue();
Node* pop(Queue*);
void push(Queue*, Node*);
void pushByArrival(Queue* q, Node* node);
void pushByBurstRemaining(Queue* q, Node* node);


// --- Function Definitions --- //
// Empty Node Constructor
Node* createEmptyNode()
{
	Node* returnNode = (Node*) malloc(sizeof(Node));

	returnNode->ahead = NULL;
	returnNode->behind = NULL;
	returnNode->process = NULL;

	return returnNode;
}

Node* createNode(PCB* process)
{
	Node* returnNode = (Node*) malloc(sizeof(Node));

	returnNode->ahead = NULL;
	returnNode->behind = NULL;
	returnNode->process = process;

	return returnNode;
}

// Empty Queue Constructor
Queue* createQueue()
{
	Queue* q = (Queue*) malloc(sizeof(Queue));

	q->head = NULL;
	q->tail = NULL;

	return q;
}

// Pop the head of the queue.
Node* pop(Queue* q)
{
	Node* nodeToPop;

	if (q == NULL)
		return NULL;
	if (q->head == NULL)
		return NULL;

	nodeToPop = q->head;
	q->head = nodeToPop->ahead;
	nodeToPop->ahead = NULL;

	if (q->head != NULL)
        	q->head->behind = NULL;

	return nodeToPop;
}

// Push Node to the end of the Queue
void push(Queue* q, Node* node)
{
	// Seg Fault prevention
	if (q == NULL || node == NULL)
		return;

	// Empty Queue
	if (q->head == NULL)
	{
		q->head = node;
		node->ahead = NULL;
		node->behind = NULL;
	}

	// Only one node in Queue (head)
	else if (q->tail == NULL)
	{
	    	q->head->ahead = node;
		q->tail = node;
		node->ahead = NULL;
		node->behind = q->head;
	}

	// Queue has two or more nodes.
	else
	{
	    	q->tail->ahead = node;
        	node->behind = q->tail;
        	q->tail = node;
        	node->ahead = NULL;
	}
}

// pushing while making ll sorted by arrival time
void pushByArrival(Queue* q, Node* node)
{
	Node* currentNode;

	if (q == NULL || node == NULL)
		return;

	currentNode = q->head;

	while(currentNode != NULL)
	{
		if (node->process->arrivalTime < currentNode->process->arrivalTime)
				break;
        currentNode = currentNode->ahead;
	}

	// Head Insert
	if (q->head == NULL)
	{
		q->head = node;
	}
	// Tail Insert
	else if (currentNode == NULL)
	{
		// Null Tail
		if (q->tail == NULL)
		{
			q->tail = node;
			q->head->ahead = node;
			q->tail->behind = q->head;
		}

		// There is a Tail
		else
		{
			q->tail->ahead = node;
			node->behind = q->tail;
			q->tail = node;
		}
	}
	else
	{
	    if (currentNode == q->head)
            	q->head = node;
		node->behind = currentNode->behind;
		node->ahead = currentNode;
		currentNode->behind = node;
	}

}

// pushing while making ll sorted by burst time
void pushByBurstRemaining(Queue* q, Node* node)
{
	Node* currentNode;

	if (q == NULL || node == NULL)
		return;

	currentNode = q->head;

	while(currentNode != NULL)
	{
		if (node->process->burstRemaining < currentNode->process->burstRemaining)
				break;
        currentNode = currentNode->ahead;
	}

	// Head Insert
	if (q->head == NULL)
	{
		q->head = node;
	}
	// Tail Insert
	else if (currentNode == NULL)
	{
		// Null Tail
		if (q->tail == NULL)
		{
			q->tail = node;
			q->head->ahead = node;
			q->tail->behind = q->head;
		}

		// There is a Tail
		else
		{
			q->tail->ahead = node;
			node->behind = q->tail;
			q->tail = node;
		}
	}
	else
	{
	    if (currentNode == q->head)
            	q->head = node;
		node->behind = currentNode->behind;
		node->ahead = currentNode;
		currentNode->behind = node;
	}

}