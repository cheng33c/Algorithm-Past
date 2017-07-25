#include <iostream>
#include <cstdlib>
using namespace std;

#define SSTable_SIZE 20
#define OK           1
#define OVERFLOW     -2
#define ERROR        0

typedef int   Status;
typedef int   KeyType;

typedef struct {
  KeyType key;
} ElemType , TElemType;

typedef struct {
  ElemType *elem;
  int      length;
} SSTable;

#define EQ(a,b) ( a == b )
#define LT(a,b) ( a <  b )
#define LQ(a,b) ( a <= b )

int compare( ElemType x, ElemType y )
{
	if( EQ(x.key, y.key) )		return 0;
	else if( LQ(x.key, y.key )) return -1;
	else						return 1;
}

Status InitSSTable( SSTable &ST )
{
	ST.elem = new ElemType[SSTable_SIZE + 1 ];
	if( !ST.elem ) exit(OVERFLOW);
	ST.length = 0;
	return OK;
}

Status CreateSSTable( SSTable &ST, int n )
{
	KeyType x;
	cout << "input x(N) = " << endl;
	for( int i = 1; i <= n; i++ ) {
		cin >> x;
		ST.elem[i].key = x;
		++ST.length;
	}
	return OK;
}

void DispSSTable( SSTable ST )
{
	int i = 1;
	while( i <= ST.length )
		cout << ST.elem[ i++ ].key << " ";
	cout << endl;
}

int Search_Seq( SSTable ST, KeyType key )
{
	int i;
	ST.elem[0].key = key;
	for( i = ST.length; ST.elem[i].key != key; i-- )
		;
	return i;
}

int Search_Bin( SSTable ST, KeyType key )
{
	int low, mid, high;
	low = 1; high = ST.length;
	while( low <= high ) {
		mid = ( low + high ) / 2;
		if( EQ(key, ST.elem[mid].key) )
			return mid;
		else if( LT(key, ST.elem[mid].key) )
			high = mid - 1;
		else low = mid + 1;
	}
	return 0;
}

int main()
{
	SSTable ST;
	int n, i;
	InitSSTable( ST );
	
	cout << "input n = ";
	cin >> n;
	CreateSSTable( ST, n );
	DispSSTable( ST );
	KeyType key;
	cout << "input key = ";
	cin >> key;
	// i = Search_Seq( ST, key );
	
	i = Search_Bin( ST, key );
	if( i ) cout << i << endl;
	else    cout << "Can't find." << endl;
	
	return 0;
}
