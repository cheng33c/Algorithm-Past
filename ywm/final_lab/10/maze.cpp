#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <array>
using namespace std;

// 迷宫长、宽
#define MAZE_Y          4
#define MAZE_X          4
// 开始坐标     默认为（0,0）
#define IN_X            0
#define IN_Y            0
// 出口坐标
#define OUT_X           2
#define OUT_Y           3

// test func
#include <fstream>
ofstream of("test_log.txt");
void printlist( const list< array<type, 3> > & mylist)
{
  cout << "List: " << endl;
  for ( auto i = mylist.begin(); i != mylist.end(); i++ )
    cout << "(" << (*i)[0] << "," << (*i)[1] << "," << (*i)[2] << ")" << endl;
}

bool walking( const vector< vector<bool> > & maze, list< int* > & walking_list );

int main()
{
    vector< vector<bool> > maze(MAZE_Y);
    list< array<type, 3> > walking_list;
    bool status=0;

    ifstream in("mymaze.txt");
    if ( !in ) {
        cout << "找不到mymaze.txt。" << endl;
        exit ( 1 );
    }

    for ( int i = 0; i < MAZE_Y; i++ ) 
        for ( int j = 0; j < MAZE_X; j++ ) {
            in >> status;
            maze[i].push_back(status);
        }
    
    cout << walking( maze, walking_list ) << endl;;        

    in.close();

    return 0;
}

/*
    上：1 下：2 左：3 右：4
*/
bool walking( const vector< vector<bool> > & maze, list< array<type, 3> > & walking_list )
{
    // status 显示是否添加到队列中 如果没添加则标记0 否则标记1
    vector< vector<bool> > status(MAZE_Y);
    bool success = 0;
    int *tmp_ptr;

    for ( int i = 0; i < MAZE_Y; i++ )
        for ( int j = 0; j < MAZE_X; j++ )
            status[i].push_back(0);
    
    for ( int x = 0, y = 0; ; ) {
        // 判断现在的情况是否符合寻路成功的条件，如果是，返回成功，退出
        if ( x == OUT_X && y == OUT_Y ) return 1;
        // 周围无可用通路情况，寻路失败并退出
        if ( ( maze[y][x+1] || ( x == MAZE_X) ) &&
	     ( maze[y][x-1] || ( x == 0 ) ) &&
	     ( maze[y-1][x] || ( y == 0 ) ) &&
	     ( maze[y+1][x] || ( y == MAZE_Y) ) ) return 0;
        // 搜索周围可用寻路点，如果有，加入队列中。 然后深度优先搜索。
        // 向上搜索的情况
	if ( y != 0 && !maze[y-1][x] && !status[y-1][x] ) {
	  int tmp[3];
	  tmp[0] = y-1; tmp[1] = x; tmp[2] = 1;
	  status[y-1][x] = 1;
	  walking_list.push_back(tmp);
        }
        // 向下搜索的情况
        if ( y != MAZE_Y-1 && !maze[y+1][x] && !status[y+1][x] ) {
	  int tmp[3];
	  tmp[0] = y+1; tmp[1] = x; tmp[2] = 2;
	  status[y+1][x] = 1;
	  walking_list.push_back(tmp);
        }
        // 向左搜索的情况
        if ( x != 0 && !maze[y][x-1] && !status[y][x-1] ) {
	  int tmp[3];
	  tmp[0] = y; tmp[1] = x-1; tmp[2] = 3;
	  status[y][x-1]= 1;
	  walking_list.push_back(tmp);
        }
        // 向右搜索的情况
        if ( x != MAZE_X-1 && !maze[y][x+1] && !status[y][x+1] ) {
	  int tmp[3];
	  tmp[0] = y; tmp[1] = x+1; tmp[2] = 4;
	  status[y][x+1] = 1;
	  walking_list.push_back(tmp);
        }
	status[y][x] = 1;
	if ( walking_list.size() == 0 ) return 0;
        // 深度优先搜索
        int *tmp_ptr = walking_list.back(); walking_list.pop_back();
        // 广度优先搜索 tmp = walking_list.pop_front(tmp);
        y = tmp_ptr[0]; x = tmp_ptr[1];
        
        // 测试
        of << "log: (" << tmp_ptr[0] << "," << tmp_ptr[1] << "," << tmp_ptr[2] << ")" << endl;
	if ( walking_list.size() != 0 ) printlist( walking_list );
        continue;
    }
}
