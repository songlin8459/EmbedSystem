#ifndef _LINKLIST_LOOP_DOUBLE_H
#define _LINKLIST_LOOP_DOUBLE_H
#include <stdio.h>
#include <stdlib.h>

typedef int data_t;
typedef struct node
{
    data_t data;
    struct node *next;
    struct node *prior;
}Node;

Node *Linklist_Loop_Double_Create(void);
void Linklist_Loop_Double_Show(Node *head);
void Linklist_Loop_Double_Insert_Pos(Node *head, int pos, data_t data);
void Linklist_Loop_Double_Delete_Pos(Node *head, int pos);
int Linklist_Loop_Double_Is_Empty(Node *head);
#endif