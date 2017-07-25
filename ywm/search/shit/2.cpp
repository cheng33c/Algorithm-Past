#include <iostream>
#include <cstdlib>
using namespace std;

#define STACK_INIT_SIZE 20
#define STACK_INCREMENT 10
#define OVERFLOW		-2
#define OK				1
#define ERROR			0
#define TRUE			1
#define FALSE			0

typedef int Status;
typedef int KeyType;

#define EQ( a, b ) ( a == b )
#define LT( a, b ) ( a <  b )
#define LQ( a, b ) ( a <= b )

typedef struct {
	KeyType key;	
} ElemType, TElemType;

typedef struct BiTNode {
	TElemType      data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

Status CreateBiTree( BiTree & T )
{
	KeyType x;
	cin >> x;
	if( x == 0 ) T = NULL;
	else {
		if( !(T = new BiTNode) )
			exit(OVERFLOW);
		T->data.key = x;
		CreateBiTree( T->lchild );
		CreateBiTree( T->rchild );
	}
	return OK;
}

void visit( KeyType e )
{	cout << e << " ";	}

void preorder( BiTree T )
{
	if( T ) {
		visit( T->data.key );
		preorder( T->lchild );
		preorder( T->rchild );
	}
}

void inorder( BiTree T )
{
	if( T ) {
		inorder( T->lchild );
		visit( T->data.key );
		inorder( T->rchild );
	}
}

Status Search_BST( BiTree T, KeyType key, BiTree f, BiTree & p )
{
	p = T;
	while( p ) {
		if( EQ(key, p->data.key) )
			return TRUE;
		else if( LT(key, p->data.key) )
			p = p->lchild;
		else p = p->rchild;
	}
	return FALSE;
}

Status Insert_BST( BiTree & T, ElemType e )
{
	BiTree p;
	BiTNode *s;

	// Search_BST( T, e.key, NULL, p );
	if( !Search_BST(T, e.key, NULL, p) ) {
		s = new BiTNode;
		s->data = e;
		s->lchild = s->rchild = NULL;
		if( !p )	T = s;
		else
			if( LT(e.key, p->data.key) )
				p->lchild = s;
			else p->rchild = s;
		
		return TRUE;
	}
	else return FALSE;
}

void Delete( BiTree & p )
{
	BiTree q, s;
	if( !p->rchild ) 
	{	q = p; p = p->lchild; delete(q);	}
	else if( !p->lchild )
	{	q = p; p = p->rchild; delete(q);	}
	else {
		q = p; s = p->lchild;
		while( s->rchild ) {
			q = s; s = s->rchild;	
		}
		p->data = s->data;
		if( q != p ) q->rchild = s->lchild;
		else q->lchild = s->lchild;
		delete(s);
	}
}

Status DeleteBST( BiTree & T, KeyType key )
{
	if( !T ) return FALSE;
	else {
		if( EQ(key, T->data.key) )
		{	Delete( T ); return TRUE; }
		else if( LT(key, T->data.key) )
			DeleteBST( T->lchild, key );
		else
			DeleteBST( T->rchild, key );
	}
}

int main()
{
	BiTree T;
	cout << "input x = ";
	CreateBiTree( T );
	preorder( T );
	cout << endl;
	inorder( T );
	cout << endl;

	KeyType key;
	BiTree f = NULL, p;
	for( int i = 1; i < 5; i++ ) {
		cout << "input key = ";
		cin >> key;
		if( Search_BST( T, key, NULL, p ) )
			cout << p->data.key << " find!" << endl;
		else
			cout << key << " find failed!" << endl;
	}

	ElemType e;
	T = NULL;
	cout << "input e.key = ";
	cin >> e.key;
	while( e.key != 0 ) {
		Insert_BST( T, e );
		cin >> e.key;
	}
	preorder( T );
	cout << endl;
	inorder( T );
	cout << endl;

	key = 12;
	cout << "delete node = " << key << endl;
	DeleteBST( T, key );
	cout << "preorder binary tree " << endl;
	preorder( T );
	cout << endl;
	cout << "inorder binary tree " << endl;
	inorder( T );
	cout << endl;

	return 0;	
}
