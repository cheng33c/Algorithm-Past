#ifndef __User__
#define __User__

#include <string>
#include <iostream>

using std::string;  using std::cout;   using std::endl;   using std::cin;

namespace __TrainManage__
{
    class User
    {
    public:
        string name, sex, address, tel;
        int age;

    public:

        User ();
        User (string na, string se, string ad, string te, int ag);
        User (const User & rhs);
        ~User();
    
        bool operator== ( User & myuser ) const;
        const bool operator== ( const User & myuser ) const;
        User & operator= ( User & myuser );

        void show_user_info() const;
        void get_user_info();
    };
}

#endif