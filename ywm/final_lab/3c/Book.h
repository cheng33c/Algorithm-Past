#include <string.h>

typedef struct Book
{
    char isbn[50],name[50],author[50];
    int  exist, stock;

	Book(char * i,char * n,char * a,int e, int s) : exist(e), stock(s)
	{
		strcpy(isbn,i);
		strcpy(name,n);
		strcpy(author,a);
	}
} Book;

typedef struct BookNode
{
    Book    data;
    struct BookNode *prev, *next;

	BookNode(char * i,char * n,char * a,int e,int s)
		: data(i,n,a,e,s) {}
} BookNode, *BookNodePtr;


typedef struct myList
{
	BookNodePtr head, tail;
} myList, *myListPtr;
