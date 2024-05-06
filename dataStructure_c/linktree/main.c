#include "linktree.h"
int main()
{
    //测试输入：abdh##j##ek###cf##g##
    char arr[32] = "abdh##j##ek###cf##g##";
    Tree_node *root = Linktree_Create(arr);
    //遍历
    Linktree_Front(root);
    printf("\n");
    // Linktree_Mid(root);
    // printf("\n");
    // Linktree_After(root);
    // printf("\n");
    // Linktree_Level(root);
    return 0;
}