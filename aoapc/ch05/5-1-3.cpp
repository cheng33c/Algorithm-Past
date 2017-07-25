/***
    UVa10474
 ***/
#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;
int a[100000],q[100000];
int main()
{
  int N,Q,kase=0,flag=0;

  while(scanf("%d %d",&N,&Q) == 2 && N && Q) {
    flag = 0;
    memset(a,0,sizeof(a)); memset(q,0,sizeof(q));
    ++kase;
    for(int i = 0; i < N; i++) scanf("%d",&a[i]);
    for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
        if(a[i] < a[j]) swap(a[i],a[j]);
    for(int j = 0; j < Q; j++) scanf("%d",&q[j]);
    printf("\nCASE# %d:\n",kase);
    for(int i = 0; i < Q; i++,flag=0){
      for(int j = 0; j < N; j++)
        if(q[i] == a[j]){
          printf("%d found at %d\n",q[i],j+1);
          flag = 1;
          break;
        }
      if(!flag) printf("%d not found\n",q[i]);
    }
  }
  printf("Time used = %.2f\n",(double)clock() / CLOCKS_PER_SEC);

  return 0;
}
