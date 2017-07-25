/***
    UVa201
 ***/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define maxn 100

bool isquare(unsigned long int,unsigned long int,unsigned long int);
unsigned long int n,cnt[100][5000],prob_flag[100],side[100];

struct Point {
  bool left,right,up,down;
} map[maxn][maxn];

int main()
{
  int oper,vx,vy, prob_num=0;
  char type;
  while(scanf("%d%d",&n,&oper) == 2 && n) {
    //init
    getchar(); memset(map,0,sizeof(map)); side[++prob_num] = n;
    while(oper-- && scanf("%c",&type)) {
      getchar();
        if(type == 'H') {
          scanf("%d%d",&vy,&vx);
          getchar();
          map[vy][vx].right = map[vy][vx+1].left = 1;
        }
        else if(type == 'V') {
          scanf("%d%d",&vx,&vy);
          getchar();
          map[vy][vx].down = map[vy+1][vx].up = 1;
        }
    }

    //count
    for(int t = 1; t <= n; t++) //y
      for(int f = 1; f <= n; f++) //x
        for(int i = 1; i <= n; i++) //side len
          if(isquare(t,f,i)) {
            prob_flag[prob_num]=1;
            cnt[prob_num][i]++;
          } 
  }

  //print
  for(int i = 1; i <= prob_num; i++){
    if(i != 1) printf("\n**********************************\n");
    printf("\nProblem #%d\n\n",i);
    if(prob_flag[i]) {
      for(int j = 1; j <= side[i]; j++)
        if(cnt[i][j])
          printf("%d square (s) of size %d\n",cnt[i][j],j);
      
    }
    else printf("No completed squares can be found.\n");
  }

  return 0;
}

bool isquare(unsigned long int vx, unsigned long int vy, unsigned long int n1)
{
  for(int i = 0; i < n1; i++) {
    if((vx == n ? 1 : map[vy][vx+i].right) && (vy == n ? 1 : map[vy+i][vx].down)
       && (vx == 1 ? 1 : map[vy+n1][vx+n1-i].left) && map[vy+n1-i][vx+n1].up) ;
    else return 0;
  }
  return 1;
}
