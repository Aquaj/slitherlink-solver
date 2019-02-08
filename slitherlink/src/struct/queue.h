#ifndef ___priorityqueue_h___
#define ___priorityqueue_h___


typedef struct node {
    int data;
    // Lower values indicate higher priority
    int priority;
    struct node* next;

} Node;

Node* newNode(int d, int p);
int getHead(Node** head);
void pop(Node** head);
void push(Node** head, int d, int p);

#endif
