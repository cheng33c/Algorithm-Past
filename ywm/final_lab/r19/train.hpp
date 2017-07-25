#include "user.cpp"
#include <vector>
#include <fstream>

using std::vector;  using std::cin;  using std::ofstream;

namespace __TrainManage__
{
    class Train : public User
    {
    private:
        /* 票务结构体 */
        struct Ticket
        {
            User myuser; // 用户信息
            int  seat_number; // 座位号
            
            Ticket() {}
            Ticket(User my, int seat) : myuser(my), seat_number(seat) {}
            bool user_equal( const User & r ) const
            {
                return myuser.name == r.name && myuser.sex == r.sex && myuser.address == r.address &&
                        myuser.tel == r.tel && myuser.age == r.age;
            }
            void set_user(User & rhs) { myuser = rhs; }
        };
    private:
        string train_id, station_start, station_end; // 车号， 起始站， 终点站
        int    train_times; // 车次
        int    seat_limit, seat_now; // 限载量（最大座位量）， 现在已占的座位量
        int    count_book_ticket, count_unsubscribe_ticket; // 总订票数， 退票数
        vector<string> station_pass; // 路过的车站
        vector<Ticket>  booked_tickets; // 已经出售的票
        vector<User>    waiting_user; // 在队列中等待购票的乘客

    public:
        /* 构造函数和析构函数 */
        Train();
        Train(string id, string star, string en, int tim, int limit, vector<string> & pass);
        Train(string id, string start, string end, int times, int limit, int now, int book, int unsubscribe,
                vector<string> & pass, vector<Ticket> & tickets, vector<User> & waiting);
        Train(string id, string start, string end, int times, int limit, int now, int book, int unsubscribe, 
                vector<string> & pass);
        Train(const Train & mytrain);
        ~Train();

        /* 其他函数定义 */
        void addTicket(Ticket & ticket);
        void showTicketInfo(Ticket & ticket);
        bool book_ticket(User & user);
        void unsubscribe_ticket( User & user );
        void showTrainInfo() const;
        bool ask_waiting_user( User & myuser, Ticket & myticket );
        void save_train_to_file( const string & filename );
        void show_all_ticket();
		void query_ticket(User & myuser);

        /* 返回参数、赋值函数 */
        string rtnId() const { return train_id; }
        string rtnEnd() const { return station_end; }
        int    rtn_left_ticket_number() const { return seat_limit - seat_now; }

    };
}
