/***
UVa133
***/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define maxn 20

int n,k,m;
bool stay[maxn];
int go(const int step, int start, const int move);

int main(void)
{
  
  while( scanf("%d%d%d",&n,&k,&m) == 3 && n ) {
    memset(stay, 1, sizeof(stay));
    int start_a = n, start_b = 1;
    int left = n;
    while( left ) { 
      start_a = go(k, start_a, 1);
      start_b = go(m, start_b, -1);

      
      printf("%3d", start_a);
      left--;
      if(start_a != start_b) { printf("%3d", start_b); left--; }
      stay[start_a] = stay[start_b] = 0;
      if(left) printf(",");

      /*  错误！ 
     if(start_a != start_b) {
       left-=2;
       stay[start_a] = stay[start_b] = 0;
       printf("%d %d ",start_a,start_b);
     }
     else { left--; !stay[start_a]; printf("%d",start_a); }
      */
     }
  }
  
  return 0;
}

int go(int step, int start, int move)
{
  while(step--) {
    do { start = (start + move + n - 1) % n + 1; } while(stay[start] == 0);
  }

  return start;
}
