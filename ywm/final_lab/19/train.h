#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef __TrainH__
#define __TrainH__
class TrainManage
{
private:

    typedef struct User
    {
        string name, sex, address, tel;
        int    age;

        User() {}
        User(string n, string s, int a, string t, string add)
            : name(n), sex(s), age(a), address(add), tel(t)
            {}

        void get_user_info();
        void show_user_info();
        bool operator== ( User & myuser)
        {
            return (name == myuser.name && sex == myuser.sex &&
                    address == myuser.address && tel == myuser.tel && age == myuser.age) ? 1 : 0;
        }
        const bool operator== ( const User & myuser ) const
        {
            return (name == myuser.name && sex == myuser.sex &&
                    address == myuser.address && tel == myuser.tel && age == myuser.age) ? 1 : 0;
        }
    } User;

    typedef struct Ticket
    {
        User    user;
        int     seat;
        Ticket(User u, int s) : user(u), seat(s) {}
    } Ticket;
    typedef struct Train
    {
        string          train_id;
        string          start, end;
        int             train_times;
        float           ticket_price;
        int             seat_limit;
        int             seat_now;
        int             count_book_ticket;
        int             count_unsubscribe_ticket;
        vector<string>  stations;
        vector<Ticket>  alltickets;
        vector<User>    waiting_user;
        Train(string id, string s, string e, vector<string> st, int times, float ti, int li)
            : train_id(id), start(s), end(e), stations(st), train_times(times),
                ticket_price(ti), seat_limit(li), seat_now(0), count_book_ticket(0), count_unsubscribe_ticket(0)
            {}
        void addTicket(Ticket & ticket);
        void showTicketInfo(Ticket & ticket);
        void unsubscribe_ticket( User & user );
        void showTrainInfo() const;
        bool ask_waiting_user( User & myuser, Ticket & myticket );
    } Train;
    vector<Train> allTrain;

private:

    bool addTrain(Train & mytrain);
    void query_trains_by_end_station(string end_station, vector<Train> & res);

public:

    TrainManage();
    ~TrainManage();
    void query_trains_by_end_station();
    void book_ticket();
    void showTrainInfo(Train & mytrain) const;
    void showAllTrainInfo() const;
    Train & query_train_by_id(string id) const;
};

#endif