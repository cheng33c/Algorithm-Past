#include "train.hpp"

namespace __TrainManage__
{
    Train::Train()
		: seat_now(0), count_book_ticket(0), count_unsubscribe_ticket(0)
    {}
    // 创建的构造函数
    Train::Train(string id, string star, string en, int tim, int limit,
            vector<string> & pass) : 
            train_id(id), station_start(star), station_end(en), train_times(tim), seat_limit(limit),
            seat_now(0), count_book_ticket(0), count_unsubscribe_ticket(0), station_pass(pass)
    {}
    // 读文件使用的构造函数
    Train::Train(string id, string start, string end, int times, int limit, int now, int book, int unsubscribe,
                vector<string> & pass, vector<Ticket> & tickets, vector<User> & waiting) :
        train_id(id), station_start(start), station_end(end), train_times(times),
        seat_limit(limit), seat_now(now), count_book_ticket(book), 
        count_unsubscribe_ticket(unsubscribe), station_pass(pass), 
        booked_tickets(tickets), waiting_user(waiting)
    {}
    Train::Train(string id, string start, string end, int times, int limit, int now, int book, int unsubscribe,
                vector<string> & pass) :
        train_id(id), station_start(start), station_end(end), train_times(times),
        seat_limit(limit), seat_now(now), count_book_ticket(book), 
        count_unsubscribe_ticket(unsubscribe), station_pass(pass)
    {}
    // 拷贝构造函数
    Train::Train(const Train & m) :
        train_id(m.train_id), station_start(m.station_start), station_end(m.station_end), train_times(m.train_times),
        seat_limit(m.seat_limit), seat_now(m.seat_now), count_book_ticket(m.count_book_ticket),
        count_unsubscribe_ticket(m.count_unsubscribe_ticket), station_pass(m.station_pass),
        booked_tickets(m.booked_tickets), waiting_user(m.waiting_user)
    {}
    Train::~Train()
    {}

    bool Train::book_ticket( User & user )
    {
        if (seat_limit - seat_now == 0) {
            cout << "已满座" << endl;
            return 0;
        }
        Ticket myticket(user, ++seat_now);
        booked_tickets.push_back(myticket);
        cout << "订票成功" << endl;
        count_book_ticket++;
        return 1;
    }

    void Train::unsubscribe_ticket( User & user )
    {
      int find_waiting_user = 0, find_ticket = 0;
      for (auto & e : booked_tickets) {
        if (e.user_equal(user)) {
          find_ticket = 1;
          if (waiting_user.size()!=0) {
            for (auto & a : waiting_user) {
                // 询问正在排队中的用户
                if (ask_waiting_user(a, e)) {
                find_waiting_user = 1;
                break;
                }
            }
          }
          // 惰性删除
          if (!find_waiting_user) {
            count_book_ticket--;
            count_unsubscribe_ticket++;
            seat_now--;
            e.myuser.name = "";
          }
          cout << "退订成功" << endl;
        }
        if (find_ticket) break;
      }
    }

    bool Train::ask_waiting_user( User & myuser, Ticket & myticket )
    {
        cout << "你好，排队等候的用户。现在有一张退订的票。" << endl;
        showTrainInfo();
        cout << "座位号" << myticket.seat_number << endl;
        cout << "你是否要购买本票？（是/否）" << endl;
        string choice;
        cin >> choice;
        if ( choice == "是" ) {
            myticket.myuser = myuser;
            cout << "购买成功" << endl;
            return 1;
        }
        return 0;
    }

    void Train::showTrainInfo() const
    {
        cout << train_id << "\t" << station_start << "\t" << station_end << "\t" << train_times
            << "\t" << seat_limit << "\t" << seat_now << "\t";
        for (auto & t : station_pass) cout << t << "\t";
        cout << endl;
    }

    void Train::save_train_to_file(const string & filename)
    {
        ofstream out(filename, std::ios::app);

        out << train_id << "\t" << station_start << "\t" << station_end << "\t" << train_times << "\t"
            << seat_limit << "\t" << seat_now << endl;
        for (auto & t : station_pass) out << t << "\t";
        cout << endl;
    }

	void Train::show_all_ticket()
	{
		for (auto & e : booked_tickets) {
			e.myuser.show_user_info();
			cout << e.seat_number << endl;
		}
	}
	
	void Train::query_ticket(User & user) {
		int success = 0;
		for (auto & e : booked_tickets) {
			if (e.myuser == user) {
				success = 1;
				e.myuser.show_user_info();	
			}
		}
		if (!success) cout << "没有该用户的票" << endl;
	}
}
