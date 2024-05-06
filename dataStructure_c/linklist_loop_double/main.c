#include "linklist_loop_double.h"

int main()
{
    Node *head = Linklist_Loop_Double_Create();
    int i = 0 ;
    for(i; i < 10; i++)
    {
        Linklist_Loop_Double_Insert_Pos(head, i, i);
    }
    Linklist_Loop_Double_Show(head);
    Linklist_Loop_Double_Delete_Pos(head, 3);
    Linklist_Loop_Double_Show(head);
    return 0;
}