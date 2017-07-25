#include "BinTree.h"

void main(){
	BiTree T;
	int count=0,n=0;
	TElemType e;
	CreateBiTree(T);
	puts("Preorder(T)");
	Preorder(T);
	puts("\n");
	puts("InOrder(T)");
	InOrder(T);
	puts("\n");
	puts("PostOrder(T)");
	PostOrder(T);
	puts("\n");
	CountLeaf(T,count);
	CountNode(T,n);
	cout<<"叶结点个数="<<count<<endl;
	cout<<"树的深度="<<Depth(T)<<endl;
	cout<<"树结点的个数="<<n<<endl;



}