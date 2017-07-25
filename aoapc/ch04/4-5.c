#include <stdio.h>
#include <string.h>
#include <time.h>
#define maxn 50

int excel[maxn][maxn];
void ex(int, int, int, int);
void dc(int, const int, const int);
void dr(int, const int, const int);
void ic(int, const int, const int);
void ir(int, const int, const int);
void q(int, int);

int main()
{
  int r,c,n,i;
  char oper[2];
  memset(excel,0,sizeof(excel));
  while(scanf("%d%d%d",&r,&c,&n) == 3){
    for(int i = 0; i < r; i++)
      for(int j = 0; j < c; j++)
	scanf("%d", &excel[i][j]);
    for(; n--;) {
      scanf("%s%d",oper,&i);
      if(strcmp(oper,"DC")) dc(i, r, c--);
      else if(strcmp(oper,"DR")) dr(i, r--, c);
      else if(strcmp(oper,"IC")) ic(i, r, c++);
      else if(strcmp(oper,"IR")) ir(i, r, c++);
    }
    for(int i = 0; i < r; i++) {
      for(int j = 0; j < c; j++)
	printf("%d\t", excel[i][j]);
      printf("\n");
    }
    printf("%.2f\n", (double)clock() / CLOCKS_PER_SEC);
  }
  return 0;
}

void ex(int r1, int c1, int r2, int c2)
{
  int tmp = excel[r2][c2];
  excel[r2][c2] = excel[r1][c1];
  excel[r1][c1] = tmp;
}

void dc(int delc, const int r, const int c)
{
  int tr = r, tc = delc;
  for(; ++tc != c; tr = r) 
    for(; tr--;) excel[tr][tc-1] = excel[tr][tc];
}

void dr(int delr, const int r, const int c)
{
  int tr = delr, tc = c;
  for(; ++tr != r; tc = c)
    for(; tc--;) excel[tr-1][tc] = excel[tr][tc];
}

void ic(int insc, const int r, const int c)
{
  int tr = r, tc = c;
  for(; tc != insc; tc--, tr = r)
    for(; tr--;) excel[tr+1][tc] = excel[tr][tc];
  for(int i = 0; i < r; i++) excel[i][insc] = 0;
}

void ir(int insr, const int r, const int c)
{
  int tr = r, tc = c;
  for(; tr != insr; tr--, tc = c)
    for(; tc--;) excel[tr][tc+1] = excel[tr][tc];
  for(int i = 0; i < c; i++) excel[insr][i] = 0;
}



