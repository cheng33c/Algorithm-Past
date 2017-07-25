#include <stdio.h>
#include <stdlib.h>

#ifndef _HashSep_H

typedef int ElementType;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;


HashTable InitTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);

#endif

struct ListNode
{
    ElementType Element;
    Position Next;
};

typedef Position List;

struct HashTbl
{
    int TableSize;
    List *TheList;
};

HashTable
InitTable(int TableSize)
{
    HashTable H;
    int i;

    if (TableSize < MinTableSize) {
        printf("Table size too small!!!");
        return NULL;
    }

    H = malloc(sizeof(struct HashTbl));
    if (H == NULL) printf("Out of space!!!");

    H->TableSize = NextPrime(TableSize);

    H->TheList = malloc(sizeof(List) * H->TableSize);
    if (H->TheList == NULL) printf("Out of space!!!");

    for (i = 0; i < H->TableSize; i++) {
        H->TheList[i] = malloc(sizeof(struct ListNode));
        if (H->TheList[i] == NULL) printf("Out of space!!!");
        else H->TheList[i]->Next = NULL;
    }

    return H;
}

Position
Find(ElementType Key, HashTable H)
{
    Position P;
    List L;

    L = H->TheList[Hash(Key, H->TableSize)];
    P = L->Next;
    while (P != NULL && P->Element != Key) P = P->Next;
    return P;
}