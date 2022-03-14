#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct Node {
    int data;
    struct Node* previous;
};

struct List {
    struct Node* lastNode;
    int(*length)(struct List*);
    void(*printListByLastNode)(struct Node*);
    void(*enqueue)(int, struct List*);
    void(*dequeue)(struct List*);
};

void printNode(struct Node *node){
    printf("DATA: %d | THIS ADDRESS: %x | PREVIOUS ADDRESS: %x\n", node->data, node, node->previous);
}

int length(struct List* list){
    int counter = 0;
    struct Node *n = list->lastNode;
    while(n){
        n = n->previous;
        counter++;
    }
    return counter;
}

void printListByLastNode(struct Node* n)
{
    while (n) {
        printNode(n);
        n = n->previous;
    }
}

struct Node * newNode (int data, struct Node *previous) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    (*node).data = data;
    if(previous){ (*node).previous = previous; }
    else node->previous = NULL;
    return node;
}

void dequeue(struct List *list) {
    struct Node* node = list->lastNode;
    while(node){
        if(node->previous->previous == NULL) break;
        node = node->previous;
    }
    node->previous = NULL;
}

void enqueue(int data, struct List *list){
    struct Node *node = NULL;
    if (list->lastNode != NULL) node = newNode(data, list->lastNode);
    else node = newNode(data, NULL);
    list->lastNode = node;
}

struct List* newList(){
    struct List *list = (struct List *) malloc(sizeof (struct List));
    list->lastNode = NULL;
    list->length = &length;
    list->printListByLastNode = &printListByLastNode;
    list->enqueue = &enqueue;
    list->dequeue = &dequeue;

    return list;
}




int main()
{
    struct List* list = newList();
    list->enqueue(11, list);
    list->enqueue(22, list);
    list->enqueue(33, list);
    list->enqueue(44, list);
    list->printListByLastNode(list->lastNode);
    list->dequeue(list);
    printf("AFTER DEQUEUE  ************\n");
    list->printListByLastNode(list->lastNode);
    printf("\nList Size: %d", list->length(list));

    return 0;
}