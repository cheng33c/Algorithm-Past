#include "train.h"

/*
    TrainManage构造函数
    在文件夹中创建dbtrains.txt文件，并将数据写到该文件中
    数据格式：
        火车号 班次 票价 人数限制
        中途经过的站点（可能有多个）
*/

inline void TrainManage::Train::showTrainInfo() const
{
    cout << "火车号\t起点站\t终点站\t班次\t票价\t剩余票数" << endl;
    cout << train_id << "\t" << start << "\t" << end << "\t";
    cout << train_times << "\t" << ticket_price << "\t";
    cout << seat_limit - seat_now << endl;
}

inline void TrainManage::showAllTrainInfo() const
{
    size_t mysize = allTrain.size();
    cout << "火车号\t起点站\t终点站\t班次\t票价\t剩余票数" << endl;
    for ( size_t i = 0; i < mysize; i++ ) {
        cout << allTrain[i].train_id << "\t" << allTrain[i].start << "\t" << allTrain[i].end << "\t";
        cout << allTrain[i].train_times << "\t" << allTrain[i].ticket_price << "\t";
        cout << allTrain[i].seat_limit - allTrain[i].seat_now << endl;
        cout << "途经站点： ";
        size_t station_size = allTrain[i].stations.size();
        for ( size_t t = 0; t < station_size; t++ ) {
            cout << allTrain[i].stations[t] << " ";
        }
        cout << endl;
    }
}

inline void TrainManage::Train::addTicket(TrainManage::Ticket & myticket)
{
    alltickets.push_back(myticket);
}

inline void TrainManage::Train::unsubscribe_ticket( TrainManage::User & myuser )
{
    size_t alltickets_size = alltickets.size();
    for ( int i = 0; i < alltickets_size; i++ ) {
        if ( alltickets[i].user == myuser ) {
            myuser.show_user_info();
            string choice;
            cout << "确定退订已购买的火车票吗？(是/否)";
            cin >> choice;
            if ( choice == "是" ) {
                cout << "退订成功" << endl;
                // 开始查找是否有正在排队等待的乘客
                // 如果有，将该票的乘客信息替换为队列中第一位乘客信息。
                // 如果没有， 则退出
                count_unsubscribe_ticket++;
                count_book_ticket--;
                size_t waiting_size = waiting_user.size();
                // status = 0: 没有替换该乘客的乘客
                // status = 1: 有替换该乘客的乘客
                bool   status = 0;
                for ( int k = 0; k < waiting_size; k++ ) {
                    if ( ask_waiting_user(waiting_user[k], alltickets[i]) ) { 
                        status = 1;
                        alltickets[i].user = waiting_user[k];
                        count_book_ticket++;
                        count_unsubscribe_ticket++;
                        break;
                    }
                }
                // 无人替换该乘客，将此票删除
                if (status == 0) alltickets.erase( alltickets.begin() + i );
            }
            break;
        }
    }
}

inline bool TrainManage::Train::ask_waiting_user( TrainManage::User & myuser, TrainManage::Ticket & myticket )
{
    cout << "你好，排队等候的用户。现在有一张退订的票：" << endl;
    showTrainInfo();
    cout << "座位号" << myticket.seat << endl;
    cout << "你是否要购买本票？（是/否）" << endl;
    string choice;
    cin >> choice;
    if ( choice == "是" ) {
        myticket.user = myuser;
        cout << "购买成功" << endl;
        return 1;
    }
    return 0;
}