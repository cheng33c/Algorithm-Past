#include "train.cpp"

#include <sstream>
#include <fstream>
#include <list>

using namespace __TrainManage__;
using std::ifstream; using std::ofstream;
using std::stringstream;  using std::list;

/* menu */
void user_menu(list<Train> & train_list);
void manager_menu(list<Train> & train_list);

/* user func */
void user_book_ticket(list<Train> & train_list);
void user_unsubscribe(list<Train> & train_list);
void user_query_ticket_info(list<Train> & train_list);

/* manager func */
bool manager_confirm_password();
void manager_add_train(list<Train> & train_list);

/* other func */
void query_train_menu();
void show_all_train_info(const list<Train> & train_list);
bool query_train_by_id(const list<Train> & train_list, const string & id, list<Train>::const_iterator & result);
bool query_train_by_end(const list<Train> & train_list, const string & end, vector<Train> & result);

/* read and write file func */
void read_train_info(list<Train> & train_list, const string & filename);
void write_train_info(Train & mytrain, const string & filename);


#define train_file_name "train_info.txt"
#define password_file   "password.txt"


int main()
{
    list<Train> train_list;
    bool want_exit=0;

    read_train_info(train_list, train_file_name);

    while (1) {
        cout << "欢迎你使用火车售票系统" << endl
             << "=====>1) 进入用户订票系统" << endl
             << "=====>2) 进入管理员系统" << endl
             << "=====>3) 退出程序" << endl;
        int choice;
        cin >> choice;

        switch(choice) {
        case 1:
            user_menu(train_list);
            break;
        case 2:
            manager_menu(train_list);
            break;
        case 3:
            want_exit = 1;
            break;
        default:
            cout << "输入错误。请重新输入。" << endl;
            break;
        }
        system("clear");
        if (want_exit == 1) {
            cout << "感谢你的使用。" << endl;
            break;
        }
    }
    
    return 0;
}

/* user func */

void user_menu(list<Train> & train_list)
{
    int choice;
    bool want_exit=0;
    while (!want_exit) {
        cout << "欢迎你使用用户订票系统" << endl
             << "=====1) 订购火车票" << endl
             << "=====2) 查询火车票" << endl
             << "=====3) 退订火车票" << endl
             << "=====4) 查询火车信息" << endl
             << "=====5) 退出用户订票系统" << endl;
        cin >> choice;

        switch(choice) {
        case 1: user_book_ticket(train_list); break;
        case 2: user_query_ticket_info(train_list); break;
        case 3: user_unsubscribe(train_list); break;
        case 4: show_all_train_info(train_list); break;
        case 5: want_exit = 1; break;
        default: cout << "输入错误，请重新输入。" << endl; break;
        }
    }
}

void user_book_ticket(list<Train> & train_list)
{
    string id;
    int success=0;
    User myuser;
    if (!train_list.empty()) {
      show_all_train_info(train_list);
      cout << "输入你要乘坐的火车号：";
      cin >> id;

      for (auto & e : train_list) {
        if (e.rtnId() == id) {
          myuser.get_user_info();
          e.book_ticket(myuser);
          success = 1;
        }
      }
      if (!success) cout << "没有找到该火车。" << endl;
    }
    else cout << "当前没有火车。" << endl;
}

void user_unsubscribe(list<Train> & train_list)
{
    string id;
    int success = 0;
    cout << "请输入火车号：" << endl;
    cin >> id;
    for (auto & e : train_list) {
      if (e.rtnId() == id) {
        User myuser;
        success = 1;
        myuser.get_user_info();
        e.unsubscribe_ticket(myuser);
        break;
      }
    }
    if (!success) cout << "没有找到该火车" << endl;
}

void user_query_ticket_info(list<Train> & train_list)
{
	string id;
	int success;
	cout << "请输入火车号:" << endl;
	cin >> id;
	for (auto & e : train_list) {
		if (e.rtnId() == id) {
			User myuser;
			success = 1;
			myuser.get_user_info();
			e.query_ticket(myuser);
			break;
		}	
	}
	if (!success) cout << "没有找到该火车" << endl;
}

/* manager func */
void manager_menu(list<Train> & train_list)
{
    if (!manager_confirm_password()) {
        cout << "您输入的密码不正确，请重新核实你的管理员身份。" << endl;
        return;
    }
    
    bool want_exit=0;
    int choice;
    while (!want_exit) {
        cin.clear();
        cout << "欢迎使用管理员系统" << endl
             << "=====>1) 添加火车信息" << endl
             << "=====>2) 查询火车信息" << endl
             << "=====>3) 退出管理员系统" << endl
             << "请输入你的选择：";
        cin >> choice;
        switch(choice) {
        case 1:
            manager_add_train(train_list);
            break;
        case 2:
            show_all_train_info(train_list);
            break;
        case 3:
            cout << "感谢你使用管理员系统。" << endl;
            want_exit = 1;
            break;
        default:
            cout << "您输入的选项有误，请重新输入。" << endl;
            break;
        }
    }
}

void manager_add_train(list<Train> & train_list)
{
    string temp,id, start, end;
    vector<string> stations;
    int times, limit;
    cout << "管理员系统 —— 火车添加" << endl
         << "火车号：";
    cin >> id;
    cout << "起点站：";
    cin >> start;
    cout << "终点站：";
    cin >> end;
    cout << "车次：";
    cin >> times;
    cout << "座位限制:";
    cin >> limit;
    cout << "经过的站名：";
    cin >> temp;
    while (1) {
        stations.push_back(temp);
        string temp;
        cin >> temp;
        if (temp.length() == 0) break;
    }
    /*for (int i = 0; i < 3; i++) {
        cin >> temp;
        stations.push_back(temp);
    }*/
    Train mytrain(id, start, end, times, limit, stations);
    train_list.push_back(mytrain);
    mytrain.save_train_to_file(train_file_name);
}

bool manager_confirm_password()
{
    string input, password;
    ifstream in(password_file);
    if (!in) {
        cout << "无法读取到你的" << password_file << "。请创建该文件并键入你的管理员密码。" << endl;
        return 0;
    }
    in >> password;
    in.close();
    for (int i = 3; i >= 1; i--) {
        cout << "请输入管理员密码：" << endl;
        cin >> input;
        if (input == password) return 1;
        cout << "密码不正确，请重新输入。你还有" << i << "次机会" << endl;
    }
    return 0;

}

/* other func */

void query_train_menu(list<Train> & train_list)
{
    string temp;
    cout << "=======> 1) 火车号查询" << endl << "=======> 2) 火车终点站查询" << endl;
    int choice;
    cin >> choice;
    switch(choice)
    {
    case 1:
    {
        cout << "请输入火车号：";
        cin >> temp;
        list<Train>::const_iterator resultid;
        if (query_train_by_id(train_list, temp, resultid)) {
        }
        else cout << "没有找到该火车。请重新确认你输入的火车号是否正确。" << endl;
        break;
    }
    case 2:
    {
        cout << "请输入终点站名：";
        cin >> temp;
        vector<Train> resultvec;
        if (query_train_by_end(train_list, temp, resultvec)) {

        }
        else cout << "没有找到该火车。请重新确认你输入的火车号是否正确。" << endl;
        break;
    }
    default:
        cout << "输入错误" << endl;
        break;
    }
}

void show_all_train_info(const list<Train> & train_list)
{
  cout << "火车号\t起点站\t终点站\t车次\t座位数\t已占座位数\t经过车站" << endl<< endl;
  for (auto & cursor : train_list) {
    cursor.showTrainInfo();
  }
}

bool query_train_by_id(const list<Train> & train_list, const string & id, list<Train>::const_iterator & iter)
{
    for ( auto cursor = train_list.begin(); cursor != train_list.end(); cursor++ ) {
        if (cursor->rtnId() == id) {
            iter = cursor;
            return 1;
        }
    }
    return 0;
}

bool query_train_by_end(const list<Train> & train_list, const string & end, vector<Train> & result)
{
    for (auto cursor : train_list) {
        if (cursor.rtnEnd() == end)
            result.push_back(cursor);
    }
    return !result.empty();
}


/* read and write file func */
void read_train_info(list<Train> & train_list, const string & filename)
{
    string buffer1,buffer2, temp;
    string id, start, end;
    vector<string> station;
    int times, limit, now, book, unsubscribe;
    ifstream in(filename);
    if (!in) {
        return;
    }
    getline(in,buffer1);
	getline(in,buffer2);
    while (in.eof()) {
        /*
            将火车 和 车站写到文件中
        */
        stringstream ss1(buffer1);
		stringstream ss2(buffer2);
        ss1 >> id >> start >> end >> times >> limit >> now >> book >> unsubscribe;
        
        while (ss2 >> temp)
            station.push_back(temp);
        
        Train mytrain(id,start,end,times,limit,now,book,unsubscribe,station);
        train_list.push_back(mytrain);

		string buffer1, buffer2;
        getline(in,buffer1);
		getline(in,buffer2);
		if (buffer1.length() == 0) break;
    }
    in.close();
}
