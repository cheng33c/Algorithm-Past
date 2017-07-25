#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
using namespace std;
#define STACK_INIT_SIZE 20
#define STACKINICREMENT 10
#define OVERFLOW -2
#define OK 1
#define ERROR 0
typedef int Status;

typedef char TElemType;

typedef struct BiNode{
	TElemType data;
	struct BiNode *lchild,*rchild;
}BiNode,*BiTree;

typedef BiTree SElemType;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

int i=0;
TElemType ch[]="ABC--D--EFG--H--I--";


Status CreateBiTree(BiTree &T){
	TElemType c1;
	c1=ch[i++];
	if(c1=='-') T=NULL;
	else {
		if(!(T=new BiNode)) exit(OVERFLOW);
		T->data=c1;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

void Visit(TElemType e){
	putchar(e);
}

void Preorder (BiTree T){
	if(T){
		Visit(T->data);
		Preorder(T->lchild);
		Preorder(T->rchild);
	}
}

void InOrder(BiTree T){
	if(T){
		InOrder(T->lchild);
		Visit(T->data);
		InOrder(T->rchild);
	}
}

void PostOrder(BiTree T){
	if(T){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		Visit(T->data);
	}
}

void CountLeaf (BiTree T, int &count){
	if(T){
		if((!T->lchild)&&(!T->rchild))
			count++;
		CountLeaf(T->lchild,count);
		CountLeaf(T->rchild,count);
	}
}

void CountNode(BiTree T,int &n){
	if(T){
		n++;
		CountNode(T->lchild,n);
		CountNode(T->rchild,n);
	}
}

int Depth(BiTree T){
	int depthval,depthLeft,depthRight;
	if(!T) depthval=0;
	else {
		depthLeft =Depth(T->lchild);
		depthRight=Depth(T->rchild);
		depthval=1+(depthLeft>depthRight?depthLeft:depthRight);
	}
	return depthval;
}

