#include "BookManageByList.h"
using namespace __listbook__;

inline BookList::BookList()
{	inputBookInfo();	}

inline BookList::BookList(string i, string n, string a, int s, int e)
{
	node.isbn = i;
	node.name = n;
	node.author = a;
	node.stock = s;
	node.exist = e;
}

inline BookList::~BookList()
{}

inline void BookList::inputBookInfo()
{
	cout << "ISBN: ";
	cin >> node.isbn;
	cout << "书名： ";
	cin >> node.name;
	cout << "作者: ";
	cin >> node.author;
	cout << "库存量: ";
	cin >> node.stock;
	cout << "现存量: ";
	cin >> node.exist;
}

inline void BookList::returnBook()
{
	++node.exist;
}

inline void BookList::existBookEmptyError()
{
	cout << "本书没有现存。" << endl;
}

inline bool BookList::borrowBook()
{
	return node.exist ? (node.exist--, 1) : (existBookEmptyError(), 0);
}

inline const void BookList::showBookInfo() const
{
	cout << "ISBN: " << node.isbn << endl << "书名: " << node.name << endl;
    cout << "作者: " << node.author << endl << "现存: " << node.exist << endl;
    cout << "库存: " << node.stock << endl;
}

// inline void BookList::showBookInfo() const
// {
// 	cout << "ISBN: " << node.isbn << endl << "书名: " << node.name << endl;
//     cout << "作者: " << node.author << endl << "现存: " << node.exist << endl;
//     cout << "库存: " << node.stock << endl;
// }