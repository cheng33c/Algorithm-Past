#include <fstream>
#include "mylist.h"
#include "BookManageByList.cpp"
using namespace std;
using namespace __mylist__;

int main()
{
	MyList<BookList> myBook;
    string isbn_tmp, name_tmp, author_tmp, exist_tmp, stock_tmp;
    ifstream in("book_info.txt");

    for( int i = 0; i < 1; i++ ) {
        BookList b;
        // b(isbn_tmp, name_tmp, author_tmp, exist_tmp, stock_tmp)
        myBook.push_front(b);
    }

    for( MyList<BookList>::const_iterator iter = myBook.begin(); iter != myBook.end(); iter++ ) {
        (*iter).showBookInfo();
    }

    return 0;
}
