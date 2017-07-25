#include "train.cpp"
#include "trainmanage.cpp"
#include "user.cpp"

void user_menu();
void manager_menu();

/* user menu */
void user_book_ticket_menu();
void user_query_ticket_menu();
void user_unsubscribe_menu();
void user_query_train_menu();

/* manager menu */
void confirm_password();
void manager_add_train_menu();
void manager_query_train_menu();

int main()
{
    TrainManage mytrain;
    mytrain.showAllTrainInfo();
    mytrain.book_ticket();
    mytrain.query_trains_by_end_station();

    while (1) {
        cout << "欢迎你使用火车售票系统" << endl
             << "=====>1) 进入用户订票系统" << endl
             << "=====>2) 进入管理员系统" << endl;
        int choice;
        cin >> choice;

        switch(choice) {
        case 1:
            user_menu();
            break;
        case 2:
            manager_menu();
            break;
        default:
            cout << "输入错误。请重新输入。" << endl;
            break;
        }
        system("pause");    system("clear");
    }
    
    return 0;
}

void user_menu()
{
    int choice;
    while (1) {
        cout << "欢迎你使用用户订票系统" << endl
             << "=====1) 订购火车票" << endl
             << "=====2) 查询火车票" << endl
             << "=====3) 退订火车票" << endl
             << "=====4) 查询火车信息" << endl
             << "=====5) 退出用户订票系统" << endl;
        cin >> choice;

        switch(choice) {
        case 1:
            user_book_ticket_menu();
            break;
        case 2:
            user_query_ticket_menu();
            break;
        case 3:
            user_unsubscribe_menu();
            break;
        case 4:
            user_query_train_menu();
            break;
        default:
            cout << "输入错误，请重新输入。" << endl;
            break;
        }
        system("pause");    system("clear");
    }
}

void user_book_ticket_menu()
{
    cout << "用户订票系统 —— 订购火车票" << endl
         << "姓名：";
}

void manager_menu()
{
    if (!confirm_password()) {
        cout << "您输入的密码不正确，请重新核实你的管理员身份。" << endl;
        return;
    }
    int choice;
    while (1) {
        cout << "欢迎使用管理员系统" << endl
             << "=====>1) 添加火车信息" << endl
             << "=====>2) 查询火车信息" << endl
             << "=====>3) 退出管理员系统" << endl
             << "请输入你的选择：";
        cin >> choice;
        switch(choice) {
        case 1:
            manager_add_train_menu();
            break;
        case 2:
            manager_query_train_menu();
            break;
        case 3:
            cout << "感谢你使用管理员系统。" << endl;
            system("pause");
            return;;
        default:
            cout << "您输入的选项有误，请重新输入。" << endl;
            break;
        }
        system("pause");    system("clear");
    }
}

void manager_add_train_menu()
{
    Train mytrain;
    string temp;
    cout << "管理员系统 —— 火车添加" << endl
         << "火车号：";
    cin >> mytrain.train_id;
    cout << "经过的站名：";
    while (cin >> temp)
        mytrain.push_back(stations);
    cout << "车次：";
    cin >> mytrain.train_times;
    cout << "票价：";
    cin >> mytrain.ticket_price;
    cout << "座位限制:";
    cin >> mytrain.seat_limit;
    mytrain.seat_now = mytrain.count_book_ticket = mytrain.count_unsubscribe_ticket = 0;
}

bool confirm_password()
{
    string input;
    ifstream in("password.txt");
    if (!in) {
        cout << "无法读取到你的password.txt。请创建该文件并键入你的管理员密码。" << endl;
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