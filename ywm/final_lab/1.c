#include <stdio.h>

#define islegal(a,b,c) ((a^b)&&(b^c))
#define pass(a,b,c) (a&&b&&c)

int guohe(int a, int b, int c);
void show_status(int a, int b, int c);

int main()
{
	show_status( 0, 0, 0 );
	guohe( 0, 0, 0 );

	return 0;
}

/*
a: 狼 b: 羊 c: 菜
三个均为0,1
在对岸的为1,不在对岸的为0
全1即返回
*/
int guohe(int a, int b, int c)
{
	if ( pass(a,b,c) )	return 1;
	if (!islegal(a,b,c)) {
		b = !b;
		show_status(a,b,c);
		if (!(a^b)) a = 1;
		else c = 1;
	}
	else b = 1;
	show_status(a,b,c);
	guohe(a,b,c);
}

void show_status(int a, int b, int c)
{
	printf("狼->");
	a ? printf("过河") : printf("未过河");
	printf("   羊->");
	b ? printf("过河") : printf("未过河");
	printf("   菜->");
	c ? printf("过河") : printf("未过河");
	printf("\n\n");
}
