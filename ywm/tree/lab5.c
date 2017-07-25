#include <stdio.h>
#include <stdlib.h>

#define Max(a, b) ( a > b ? a : b )
typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;

struct TNode {
  ElementType Data;
  BinTree Left;
  BinTree Right;
};

void Preorder( BinTree BT );
void Inorder( BinTree BT );
void Postorder( BinTree BT );

BinTree CreateNode();
BinTree Insert( BinTree BT, ElementType X );
int LeafNodeCount( BinTree BT );
int CountLeaf( BinTree BT, int leaf );
int TotalNodeCount( BinTree BT );
int CountNode( BinTree BT, int node );
int DepthBT( BinTree BT );
int CountDepth( BinTree BT, int depth );

int main()
{
  BinTree BT = NULL;
  int N, tmp, cnt;
  
  scanf("%d", &cnt);

  for( int i = 0; i < cnt; i++ ) {
    scanf("%d", &N);
    BT = Insert(BT, N);
  }

  printf("Preorder: ");
  Preorder( BT );
  printf("\n");

  printf("Inorder: ");
  Inorder( BT );
  printf("\n");

  printf("Postorder: ");
  Postorder( BT );
  printf("\n");

  printf("Depth: ");
  tmp = DepthBT( BT );
  printf("%d\n", tmp);

  printf("Leaf Node: ");
  tmp = LeafNodeCount( BT );
  printf("%d\n", tmp);

  printf("Total Node: ");
  tmp = TotalNodeCount( BT );
  printf("%d\n", tmp);
  
  return 0;
}

BinTree CreateNode()
{
  struct TNode *node = malloc(sizeof(struct TNode));
  node->Left = node->Right = NULL;
  return node;
}

BinTree Insert( BinTree BT, ElementType X )
{
  if( BT ) {
    if( X < BT->Data) BT->Left = Insert(BT->Left, X);
    else BT->Right = Insert(BT->Right, X);
  }
  else {
    BT = CreateNode();
    BT->Data = X;
  }
  return BT;
}

void Preorder( BinTree BT )
{ BT ? printf("%d ", BT->Data), Preorder( BT->Left ), Preorder( BT->Right ) : NULL ; }

void Inorder( BinTree BT )
{ BT ? Inorder( BT->Left ), printf("%d ", BT->Data), Inorder(BT->Right) : NULL; }

void Postorder( BinTree BT )
{ BT ? Postorder( BT->Left ), Postorder( BT->Right ), printf("%d ", BT->Data) : 0; }

int DepthBT( BinTree BT )
{ return BT ? CountDepth( BT, 0 ) : 0; }

int CountDepth( BinTree BT, int depth )
{ return BT ? Max(CountDepth(BT->Left, depth), CountDepth(BT->Right, depth)) + 1 : depth; }

int LeafNodeCount( BinTree BT )
{ return BT ? CountLeaf( BT, 0 ) : 0; }

int CountLeaf( BinTree BT, int leaf )
{
  if( BT == NULL ) return leaf;
  else if( BT->Left == NULL && BT->Right == NULL ) return leaf+1;
  else return CountLeaf( BT->Right, leaf ) + CountLeaf( BT->Left, leaf );
}

int TotalNodeCount( BinTree BT )
{ return BT ? CountNode( BT, 0 ) : 0; }

int CountNode( BinTree BT, int node )
{ return BT ? CountNode(BT->Left,node) + CountNode(BT->Right,node) + 1 : node; }
