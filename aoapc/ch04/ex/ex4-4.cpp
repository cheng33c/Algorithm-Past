#include <iostream>
#include <fstream>
#include <string>
using namespace std;

inline void roatex(string&);
inline void roatey(string&);

int main()
{
  ofstream fout("out.txt");
  string input,cube[2],cubetmp;
  int tor[2],tog[2],tob[2],flag;

  while(cin>>input) {
    flag=0;
    cube[0] = input.substr(0,6);
    cube[1] = input.substr(6,11);
    for(int i=0; i < 2; i++) tor[i]=tob[i]=tog[i]=0;
    for(int i=0; i< 6; i++) {
      if(input[i] == 'r') tor[0]++;
      else if(input[i] == 'g') tog[0]++;
      else if(input[i] == 'b') tob[0]++;
      if(input[i+6] == 'r') tor[1]++;
      else if(input[i+6] == 'g') tog[1]++;
      else if(input[i+6] == 'b') tob[1]++;
    }
    if(tog[0] != tog[1] || tob[0] != tob[1] || tor[0] != tor[1]) {
      fout<<"FALSE"<<endl;
      continue;
    }
    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 4; j++) {
        for(int k = 0; k < 6; k++){
          if(cube[0][k] == cube[1][k] && k != 5) continue;
          if(cube[0][k] != cube[1][k]) break;
          if(cube[0][k] == cube[1][k] && k == 5) flag = 1;
        }
        if(flag) break;
        roatex(cube[0]);
      }
      if(flag) { fout<<"TRUE"<<endl; break; }
      roatey(cube[0]);
    }

    if(!flag) {
      cube[0] = input.substr(0,6);
      cube[1] = input.substr(6,11);
      for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
          for(int k = 0; k < 6; k++) {
            if(cube[0][k] == cube[1][k] && k != 5) continue;
            if(cube[0][k] != cube[1][k]) break;
            if(cube[0][k] == cube[1][k] && k == 5) flag = 1;
          }
          if(flag) break;
          roatey(cube[0]);
        }
        if(flag) { fout << "TRUE" << endl; break; }
        roatex(cube[0]);
      }
    }

    if(!flag) fout<<"FALSE"<<endl;
  }



  return 0;
}

inline void roatex(string& cube)
{
  string cpy(cube);
  cpy[0] = cube[4];     cpy[1] = cube[0];
  cpy[5] = cube[1];     cpy[4] = cube[5];
  cube = cpy;
}

inline void roatey(string& cube)
{
  string cpy(cube);
  cpy[1] = cube[2];     cpy[3] = cube[1];
  cpy[4] = cube[3];     cpy[2] = cube[4];
  cube = cpy;
}
