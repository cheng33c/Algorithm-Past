#ifndef _Tree_H

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElemType;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElemType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElemType X, SearchTree T);
SearchTree Delete(ElemType X, SearchTree T);
ElemType Retrieve(Position P);

#endif

struct TreeNode
{
    ElemType Data;
    SearchTree Left;
    SearchTree Right;
};

SearchTree
MakeEmpty(SearchTree T)
{
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position
Find(ElemType X, SearchTree T)
{
    if (T == NULL) return NULL;
    if (X < T->Data) return Find(X, T->Left);
    else if (X > T->Data) return Find(X, T->Right);
    else return T;
}

Position
FindMin(SearchTree T)
{
    if (T == NULL) return NULL;
    else if (T->Left == NULL) return T;
    else return FindMin(T->Left); 
}

Position
FindMax(SearchTree T)
{
    if (T != NULL)
        while (T->Right != NULL) 
            T = T->Right;
    return T;
}

SearchTree
Insert(ElemType X, SearchTree T)
{
    if (T == NULL) {
        T = malloc(sizeof(struct TreeNode));
        if (T == NULL) printf("Out of space!!!");
        else {
            T->Data = X;
            T->Left = T->Right = NULL;
        }
    }
    else if (X < T->Data) T->Left = Insert(X, T->Left);
    else if (X > T->Data) T->Right = Insert(X, T->Right);

    return T;
}


/* 这里没搞懂！！！ */
SearchTree
Delete(ElemType X, SearchTree T)
{
    Position TmpCell;

    if (T == NULL) printf("Element not found");
    else if (X < T->Data) T->Left = Delete(X, T->Left);
    else if (X > T->Data) T->Right = Delete(X, T->Left);
    else if (T->Left && T->Right) {
        TmpCell = FindMin(T->Right);
        T->Data = TmpCell->Data;
        T->Right = Delete(T->Data, T->Right);
    }
    else {
        TmpCell = T;
        if (T->Left == NULL) T = T->Right;
        else if (T->Right ==  NULL) T = T->Left;
        free(TmpCell);
    }
    return T;
}