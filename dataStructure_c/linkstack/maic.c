#include "linkstack.h"

int main()
{
    Node *head = Linklist_Ceate();
    for(int i = 0; i < 10; i++)
    {
        Linklist_Push(head, i);
    }
    int pop = Linklist_Pop(head);
    printf("%d\n", pop);
    pop = Linklist_Pop(head);
    printf("%d\n", pop);
    return 0;
}