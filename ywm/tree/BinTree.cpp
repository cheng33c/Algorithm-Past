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
	cout<<"Ҷ������="<<count<<endl;
	cout<<"�������="<<Depth(T)<<endl;
	cout<<"�����ĸ���="<<n<<endl;



}