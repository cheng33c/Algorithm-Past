#include <iostream>
#include <ctime>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

// 随机产生的出题数
#define QUESTIONS_NUM 5
#define score_file      "myscore.txt"
#define question_file   "question.txt"

int    showMenu();
void   evalScore( const int newscore, const string & filename );
string getRandLine( const string & fileName );
double calResult( const string & mystr, stack<char> & ops, stack<double> & vals );

int main()
{
    stack<char>   ops;
    stack<double> vals;
    double each_score = 100 / QUESTIONS_NUM, last_score = 0;
    for ( ; ; ) {
        int choice = showMenu();
        if ( choice == 1 ) {
            for ( int i = 0; i < QUESTIONS_NUM; i++ ) {
                string temp;
                double myresult, result;
                temp = getRandLine("dbquestions.txt");
                if ( temp == "" ) exit(1);
                cout << temp << " ";
                cin >> myresult;
                result = calResult( temp, ops, vals );
                
                if ( myresult == result ) {
                    cout << "回答正确" << endl;
                    last_score += each_score;
                }
                else cout << "回答错误。正确答案是：" << result << endl;
            }
            evalScore( last_score, score_file );
        }
        else if ( choice == 2 ) {

        }
        else if ( choice == 3 ) {
            cout << "退出程序，感谢你的使用。" << endl;
            break;
        }
        else cout << "输入错误。请重新输入。" << endl; 
    }

    return 0;
}

string getRandLine( const string& fileName )
{ 
    ifstream in(fileName.c_str()) ;
    if ( !in ) {
        cout << "没有找到该文件。" << endl;
        return "";
    }
    string lineData ;  
    int i = 1 ;  
    string tmpLine ;  
    srand((unsigned int)time(NULL)) ;  
    while (getline(in, tmpLine))  
    {  
        if (rand()%i == 0)  
            lineData = tmpLine ;  
        ++i;  
    }  
    in.close() ;  
    return lineData;
}

double calResult( const string & mystr, stack<char> & ops, stack<double> & vals )
{
    double result;
    for ( int i = 0; i < mystr.length(); i++ ) {
        if ( mystr[i] == ' ' || mystr[i] == '(' ) continue;
        if ( mystr[i] == '+' || ( mystr[i] == '-' && mystr[i+1] == ' ') ||
             mystr[i] == '*' || mystr[i] == '/' )
             ops.push( mystr[i] );
        else if ( mystr[i] == ')' || mystr[i] == '=' ) {
            char   op = ops.top();  ops.pop();
            double v1 = vals.top(); vals.pop();
			double v2 = vals.top(); vals.pop();
            if      ( op == '+' )   v2 += v1;
            else if ( op == '-' )   v2 -= v1;
            else if ( op == '*' )   v2 *= v1;
            else if ( op == '/' )   v2 /= v1;
            vals.push(v2);
        }
        else {
            string temp;
            if ( mystr[i] == '-' ) temp += mystr[i++];
            for ( ; mystr[i] - '0' < 10 && mystr[i] - '0' >= 0; i++ )
                temp += mystr[i];
            result = atof(temp.c_str());
            vals.push(result);
        }
    }
    result = vals.top();
    vals.pop();
    return result;
}

int showMenu()
{
    int choice;

    cout << "\t1=>开始测试\n\t2=>评测分数\n\t3=>退出程序\n请输入你的选择（1-3）：";
    cin  >> choice;
    return choice;
}

void evalScore( const int nowscore, const string & filename )
{
	fstream in( filename.c_str() );
	int lastscore;
    if ( !in ) {
        cout << "文件打开错误。请查看是否建立了" << filename << "在当前目录下" << endl;
        exit ( 1 );
    }
    in >> lastscore;
	in << nowscore;
    if ( nowscore > lastscore )         cout << "恭喜你，你比上次评测进步了" << nowscore - lastscore << "分。" << endl;
    else if ( lastscore == nowscore )   cout << "你此次评测分数和上次持平。" << endl;
    else                                cout << "你比上次少了" << lastscore - nowscore << "分，请继续加油" << endl;

    in.close();
}
