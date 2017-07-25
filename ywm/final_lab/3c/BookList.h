#include "Book.h"
#include <stdlib.h>
#include <stdio.h>

#define TRUE  1
#define FALSE 0

void showMyList( BookNodePtr head )
{
    while( head = head->next )
        printf("%s\t%s\t%s\t%d\t%d\n", head->data.isbn, head->data.name, 
            head->data.author, head->data.exist, head->data.stock);
}

myListPtr createList()
{
	myListPtr lt = (myListPtr)malloc(sizeof(struct myList));
    lt->head = (BookNodePtr)malloc(sizeof(struct BookNode));
	lt->tail = (BookNodePtr)malloc(sizeof(struct BookNode));
	lt->head->next = lt->tail;
    lt->tail->prev = lt->head;
	return lt;
}

void addBook2List(myListPtr lt, Book b)
{
    BookNodePtr tmp = (BookNodePtr)malloc(sizeof(struct BookNode));
    tmp->data = b;
    tmp->prev = lt->head;
    tmp->next = lt->head->next;
    lt->head->next = tmp;
}

int delBookByISBN(myListPtr lt, char * isbn)
{
    BookNodePtr cursor = lt->head->next;
    while ( strcmp(cursor->data.isbn, isbn) && cursor != lt->tail ) 
		cursor = cursor->next;
	if ( cursor == lt->tail ) return FALSE;
	return TRUE;
}

BookNodePtr searchBookByIsbn(myListPtr lt, char * isbn)
{
	BookNodePtr cursor = lt->head->next;
	while ( strcmp(cursor->data.isbn, isbn) && cursor != lt->tail ) 
		cursor = cursor->next;
	if ( cursor == lt->tail ) return NULL;
	return cursor;
}

myListPtr searchBookByName(myListPtr lt, char * name)
{
	BookNodePtr cursor = lt->head->next;
	myListPtr searchres = createList();
	while ( cursor != lt->tail ) {
		if( strcmp(cursor->data.name, name) )
			addBook2List(searchres, cursor->data);
		cursor = cursor->next;
	}
	return searchres;
}

myListPtr searchBookByAuthor(myListPtr lt, char * author)
{
	BookNodePtr cursor = lt->head->next;
	myListPtr searchres = createList();
	while ( cursor != lt->tail ) {
		if ( strcmp(cursor->data.author, author) )
			addBook2List(searchres, cursor->data);
		cursor = cursor->next;
	}
	return searchres;
}

void showBookInfo(Book b)
{
	printf("ISBN: %s\n书名: %s\n作者: %s\n现存: %d\n库存: %d\n",
			b.isbn, b.name, b.author, b.exist, b.stock);
}

void showList(myListPtr lt)
{
	BookNodePtr cursor = lt->head;
	while( cursor ) {
		showBookInfo(cursor->data);
		cursor = cursor->next;	
	}
}

