#include "train.h"

void split(const std::string & s, std::vector<std::string> & v, const std::string & c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2) {
    v.push_back(s.substr(pos1, pos2-pos1));
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

inline TrainManage::TrainManage()
{
    string  id;
    int     limit, times;
    float   ticket_price;
    ifstream in("dbtrain.txt");
    while( in >> id >> times >> ticket_price >> limit ) {
        vector<string> stations;
        string station, temp;
        while ( getline(in, temp) && temp == "" ) ;
        split(temp, stations, " ");
        vector<string>::const_iterator start = stations.begin();
        vector<string>::const_iterator end   = stations.end() - 1;
        Train mytrain(id,*start,*end,stations,times,ticket_price, limit);
        addTrain(mytrain);
    }
    in.close();
}

inline TrainManage::~TrainManage()
{}


inline bool TrainManage::addTrain(TrainManage::Train & myTrain)
{
    allTrain.push_back(myTrain);
}

inline void TrainManage::query_trains_by_end_station()
{
    vector<Train> res;
    string end_station;
    cout << "请输入终点站：";
    cin >> end_station;
    query_trains_by_end_station(end_station,res);
    size_t res_size = res.size();
    for ( int i = 0; i < res_size; i++ ) {
        res[i].showTrainInfo();
    }
}

inline void TrainManage::query_trains_by_end_station(string end_station, vector<Train> & result)
{
    for (auto & a : allTrain) {
        if (a.end == end_station) {
            result.push_back(a);
        }
    }
}

inline void TrainManage::book_ticket()
{
    string end,train_id;
    User myuser;
    myuser.get_user_info();
    cout << "信息录入完毕。请输入你的终点站：";
    cin >> end;
    vector<Train> result;
    query_trains_by_end_station(end,result);
    size_t result_size = result.size();
    for ( size_t i = 0; i < result_size; i++ )
        showTrainInfo(result[i]);
    
    for( int try_time = 0; try_time < 5; try_time++ ) {
        /*
            status: 用户订票状态
            0: 未订票
            1: 订票成功
            2: 输入火车号错误
            3: 没有空余座位
        */
        int status = 0, i;
        cout << "输入要乘坐火车的火车号：";
        cin >> train_id;
        for ( i = 0; i < result_size; i++ ) {
            if (result[i].train_id == train_id ) {
                if (result[i].seat_now == result[i].seat_limit) {
                    status = 3;
                    break;
                }
                Ticket myticket(myuser, ++result[i].seat_now);
                status = 1;
            }
        }
        if ( status == 1 ) {
            cout << "订票成功。" << endl;
            result[i].count_book_ticket++;
            break;
        }
        if ( i == result.size() && status != 1 )
            cout << "火车号输入错误,未找到该火车。" << endl;
        if ( status == 3 )
            cout << "该火车没有空余座位。" << endl;
        string choice;
        cout << "你是否需要排队等候其他乘客退票？前面还有" << result[i].waiting_user.size() << "个等待乘客（是/否）";
        cin >> choice;
        if (choice == "是") {
            result[i].waiting_user.push_back(myuser);
            cout << "你已经成功加入等待队列，如果有票系统会帮助您预订。" << endl;
        }
        cout << "你是否需要重新选择(是/否)？";
        
        cin >> choice;
        if (choice == "是") continue;
        else                break;
    }
}

inline void TrainManage::showTrainInfo(TrainManage::Train & mytrian) const
{
    cout << "火车号\t起点站\t终点站\t班次\t票价\t剩余票数" << endl;
    cout << mytrian.train_id << "\t" << mytrian.start << "\t" << mytrian.end << "\t";
    cout << mytrian.train_times << "\t" << mytrian.ticket_price << "\t";
    cout << mytrian.seat_limit - mytrian.seat_now << endl;
}
