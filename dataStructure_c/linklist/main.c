#include "linklist.h"

int main()
{
    Node *linklist = Linklist_Create();
    int n = 15;
    while(n)
    {
        n--;
        Linklist_Insert_Head(linklist, n);
    }
    Linklist_Show(linklist);
    // puts("");
    // Linklist_Inverse(linklist);
    // Linklist_Show(linklist);
    // puts("");
    /*
    Linklist_Insert_Pos(linklist, 3, 999);
    Linklist_Show(linklist);
    puts("");
    data_t result = Linklist_Search_Pos(linklist, 16);
    printf("%d",result);
    puts("");
    */
    Linklist_Destory(&linklist);
    
    return 0;
    
}