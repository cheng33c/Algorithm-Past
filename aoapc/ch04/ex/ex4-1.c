/***
    UVa1589
 ***/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool godie(const int, const int);
bool rg_kill(const int, const int);
bool hkill(const int, const int);
bool ckill(const int, const int);

char map[11][10];
char answer[50][4];
int bx, by, ans = 0;

int main()
{
  int n, x, y;
  char type;
  while(scanf("%d%d%d",&n,&by,&bx) == 3 && n > 1 && n < 8)
    {
      memset(map,0,sizeof(map));
      getchar();
      for(int i = 0; i < n; i++) {
          scanf("%c%d%d",&type,&y,&x);
          getchar();
          map[y][x] = type;
      }
      if((bx > 4 && godie(by,bx-1) || bx == 4) &&
         (bx < 6 && godie(by,bx+1) || bx == 6) &&
         (by < 3 && godie(by+1,bx) || by == 3) &&
         (by > 1 && godie(by-1,bx) || by == 1)) memcpy(answer[ans++],"YES",3);
      else memcpy(answer[ans++],"NO",2);
    }

  for(int i = 0; i < ans; i++) printf("%s\n",answer[i]);

  return 0;
}

bool godie(const int by1, const int bx1)
{
  if(!rg_kill(by1, bx1) && !hkill(by1, bx1) && !ckill(by1, bx1)) return false;
  return true;
}

bool rg_kill(const int by1, const int bx1)
{
  bool flag = 0;

  for(int i = bx1+1; i < 10; i++)
    if(map[by1][i]) {
      if(map[by1][i] == 'R') flag = 1;
      break;
    }

  for(int i = bx1-1; i > 0 && !flag; i--)
    if(map[by1][i]) {
      if(map[by1][i] == 'R') flag = 1;
      break;
    }

  for(int i = by1+1; i < 11 && !flag; i++)
    if(map[i][bx1]) {
      if(map[i][bx1] == 'R' ||
	 map[i][bx1] == 'G') flag = 1;;
      break;
    }

  for(int i = by1-1; i > 0 && !flag; i--)
    if(map[i][bx1]) {
      if(map[i][bx1] == 'R') flag = 1;
      break;
    }

  return flag;
}

bool hkill(const int by1, const int bx1)
{
  bool flag = 0;

  //up
  if((map[by1+2][bx1+1] == 'H' && !map[by1+1][bx1+1]) ||
     (map[by1+2][bx1-1] == 'H' && !map[by1+1][bx1-1])) flag = 1;
  //right
  else if ((by1 > 1 && map[by1-1][bx1-2] == 'H' && !map[by1-1][bx1-1]) ||
	   (map[by1+1][bx1-2] == 'H' && !map[by1+1][bx1-1])) flag = 1;
  //down
  else if (by1 > 2 && ((map[by1-2][bx1+1] == 'H' && !map[by1-1][bx1+1]) ||
		      (map[by1-2][bx1-1] == 'H' && !map[by1-1][bx1-1]))) flag = 1;
  //left
  else if ((map[by1+1][bx1+2] == 'H' && !map[by1+1][bx1+1]) ||
	   (by1 > 1 && map[by1-1][bx1+2] == 'H' && !map[by1-1][bx1+1])) flag = 1;

  return flag;
}

bool ckill(const int by1, const int bx1)
{
  bool flag = 0, barrier = 0;
  int times = 0;

  if(by1 == 3 && map[by1-1][bx1] && map[by1-2][bx1] == 'C') flag = 1;
  else {
    for(int i = bx1-1; i != 0 && times < 2; i--)
      if(map[by1][i]) {
	times++;
	if(map[by1][i] == 'C' && times == 2) {flag = 1; break;}
      }

    for(int i = bx1+1, barrier = 0, times = 0; i < 10 && !flag && times < 2; i++)
      if(map[by1][i]) {
	times++;
	if(map[by1][i] == 'C' && times == 2) {flag = 1; break;}
      }
    for(int i = by1+1, barrier = 0, times = 0; i < 11 && !flag && times < 2; i++)
      if(map[i][bx1]) {
	times++;
	if(map[i][bx1] == 'C' && times == 2) {flag = 1; break;}
      }
  }

  return flag;
}
