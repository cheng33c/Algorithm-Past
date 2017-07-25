/*
书籍类实现
*/

#ifndef __HEADINCLUDE__
#include <string>
#include <iostream>
using namespace std;
#endif

#ifndef __BookList__
namespace __listbook__ {
	class BookList
	{
	private:
		typedef struct Book *BookPos;
		struct Book
		{
			string isbn;
			string name;
			string author;
			int    stock;	// 库存量
			int    exist;	// 现存量
		};
		BookPos next;
		Book    node;
		inline void inputBookInfo();
		inline void existBookEmptyError();
	public:
		BookList();
		BookList(string i, string n, string a, int s, int e);
		~BookList();
		bool borrowBook();
		void returnBook();
		const string getBookIsbn() const { return node.isbn; }
		const string getBookName() const { return node.name; }
		const string getBookAuthor() const { return node.author; }
		const int getBookStock() const { return node.stock; }
		const int getBookExist() const { return node.exist; }
		const void showBookInfo() const;
		// void showBookInfo();
	};
}
#endif
