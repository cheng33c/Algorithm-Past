/***
    UVa220
 ***/

#include <iostream>

using namespace std;
#define maxn 8
char table[maxn][maxn];

inline void _L(char&);
inline void _M(char&,int&,int&,int,int);

int main()
{
  int n,tow,tob,x,y;
  char oper,color,input[3];

  cin>>n;

  while(n--) {
    for(int i = 0; i < maxn; i++)
      for(int j = 0; j < maxn; j++) {
        cin>>table[i][j];
        if( table[i][j] == 'B' ) tob++;
        else if( table[i][j] == 'W' ) tow++;
      }

    cin>>color;
    while(cin>>input && input[0] != 'Q'){
      switch(input[0]) {
      case 'L':
        _L(color);
        break;
      case 'M':
        y = input[1] - 48;
        x = input[2] - 48;
        _M(color,tob,tow,y,x);
        break;
      default: break;
      }
    }
    for(int i = 0; i < maxn; i++){
      for(int j = 0; j < maxn; j++)
        cout<<table[i][j];
      cout<<endl;
    }
    cout<<endl;
  }

  return 0;
}

inline void _L(char& color)
{
  char findcolor = 'B';
  int r, c, lemo = 0, first=1;
  if (color == 'B') findcolor = 'W';
  for(int vy = 0; vy < maxn; vy++)
    for(int vx = 0; vx < maxn; vx++) {
      if( table[vy][vx] == '-' ) {
        int flag = 0;
        // x
        if( table[vy][vx-1] == findcolor )
          for(int i = vx-2; i >= 0; i--) {
            if(table[vy][i] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[vy][i] == '-') break;
          }
        if( table[vy][vx+1] == findcolor && !flag )
          for(int i = vx+2; i < maxn; i++) {
            if(table[vy][i] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[vy][i] == '-') break;
          }
        // y
        if( table[vy+1][vx] == findcolor && !flag )
          for(int i = vy+2; i < maxn; i++) {
            if(table[i][vx] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[i][vx] == '-') break;
          }
        if( table[vy-1][vx] == findcolor && !flag )
          for(int i = vy-2; i >= 0; i--) {
            if(table[i][vx] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[i][vx] == '-') break;
          }

        // xy
        if( table[vy+1][vx+1] == findcolor && !flag )
          for(int i = vy+2, j = vx+2; i < maxn && j < maxn; i++,j++) {
            if(table[i][j] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[i][j] == '-') break;
          }
        if( table[vy-1][vx+1] == findcolor && !flag)
          for(int i = vy-2, j = vx+2; i >=0 && j < maxn; i--,j++) {
            if(table[i][j] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[i][j] == '-') break;
          }
        if( table[vy-1][vx-1] == findcolor && !flag)
          for(int i = vy-2, j = vx-2; i >= 0 && j >= 0; i--,j--) {
            if(table[i][j] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[i][j] == '-') break;
          }
        if( table[vy+1][vx-1] == findcolor && !flag )
          for(int i = vy+2, j = vx-2; i < maxn && j >= 0; i++,j--) {
            if(table[i][j] == color) { flag = 1; r = vy+1; c = vx+1; break; }
            else if(table[i][j] == '-') break;
          }
        if( flag ) {
          if(first) { cout<<"("<<r<<","<<c<<")"; first=0; lemo=1; }
          else { cout<<" ("<<r<<","<<c<<")"; lemo = 1; }
        }
      }
    }
  if(!lemo) { cout<<"No legal move."; color = findcolor; }
  printf("\n");
}

inline void _M(char& color,int& tow, int& tob,int vy,int vx)
{
  char findcolor = 'B';

  if( color == 'B' ) findcolor = 'W';
  vx -= 1; vy -= 1;
  tow = tob = 0;
  table[vy][vx] = color;

  // x
  if( table[vy][vx-1] == findcolor )
    for(int i = vx-2; i >= 0; i--)
      if(table[vy][i] == color) {
        for(int k = vx-1; k >= i; k--) table[vy][k] = color;
        break;
      }

  if( table[vy][vx+1] == findcolor )
    for(int i = vx+2; i < maxn; i++)
      if(table[vy][i] == color) {
        for(int k = vx+1; k <= i; k++) table[vy][k] = color;
        break;
      }

  // y
  if( table[vy+1][vx] == findcolor )
    for(int i = vy+2; i < maxn; i++)
      if(table[i][vx] == color) {
        for(int k = vy+1; k <= i; k++) table[k][vx] = color;
        break;
      }

  if( table[vy-1][vx] == findcolor )
    for(int i = vy-2; i >= 0; i--)
      if(table[i][vx] == color) {
        for(int k = vy-1; k >= i; k--) table[k][vx] = color;
        break;
      }
  // xy
  if( table[vy+1][vx+1] == findcolor )
    for(int i = vy+2, j = vx+2; i < maxn && j < maxn; i++,j++)
      if(table[i][j] == color) {
        for(int k = vy+1, m = vx+1; k <= i && m <= j; k++,m++ ) table[k][m] = color;
        break;
      }

  if( table[vy-1][vx+1] == findcolor )
    for(int i = vy-2, j = vx+2; i >= 0 && j < maxn; i--,j++)
      if(table[i][j] == color) {
        for(int k = vy-1, m = vx+1; k >= i && m <= j; k--,m++ ) table[k][m] = color;
        break;
      }

  if( table[vy-1][vx-1] == findcolor )
    for(int i = vy-2, j = vx-2; i >= 0 && j >= 0; i--,j--)
      if(table[i][j] == color) {
        for(int k = vy-1, m = vx-1; k >= i && m >= j; k--,m-- ) table[k][m] = color;
        break;
      }

  if( table[vy+1][vx-1] == findcolor )
    for(int i = vy+2, j = vx-2; i < maxn && j >= 0; i++,j--)
      if(table[i][j] == color) {
        for(int k = vy+1, m = vx-1; k <= i && m >= j; k++,m-- ) table[k][m] = color;
        break;
      }


  for(int i = 0; i < maxn; i++)
    for(int j = 0; j < maxn; j++)
      if( table[i][j] == 'W' ) tow++;
      else if( table[i][j] == 'B' ) tob++;
  if( color == 'B' ) color = 'W';
  else if( color == 'W' ) color = 'B';
  cout<<"Black -  "<<tob<<" "<<"White -  "<<tow<<endl;
}
