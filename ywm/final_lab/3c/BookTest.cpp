#include <stdio.h>
#include <fstream>
#include "BookList.h"

int main()
{
	char isbn[50],name[50],author[50];
	int exist,stock;
	myListPtr lt = createList();
	FILE *fin = fopen("data.in", "rb");
	FILE *fout = fopen("data.out", "wb");
	if( !fin ) {
		printf("文件打开失败。请创建data.in并输入相关数据。\n");
		exit(1);
	}

	while(fscanf(fin, "%s%s%s%d%d",isbn,name,author,&exist,&stock)) {
		BookNode mybook(isbn,name,author,exist,stock);
		addBook2List(lt, mybook.data);	
	}

	

	return 0;
}
