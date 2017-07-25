
#include "user.hpp"

namespace __TrainManage__
{

    User::User ()
    {}
    User::User (string na, string se, string ad, string te, int ag)
        : name(na), sex(se), address(ad), tel(te), age(ag) { }
    User::User (const User & rhs)
        : name(rhs.name), sex(rhs.sex), address(rhs.address), tel(rhs.tel), age(rhs.age) { }
    User::~User()
    {}

    bool User::operator== ( User & myuser ) const
    {
        return name == myuser.name && sex == myuser.sex && age == myuser.age &&
                tel == myuser.tel && address == myuser.address ? 1 : 0;
    }

    const bool User::operator== ( const User & myuser ) const
    {
        return name == myuser.name && sex == myuser.sex && age == myuser.age &&
                tel == myuser.tel && address == myuser.address ? 1 : 0;
    }
    User & User::operator= ( User & myuser )
    {
        if ( this == &myuser )     return *this;
        name = myuser.name;     sex = myuser.sex;   age = myuser.age;
        tel = myuser.tel;       address = myuser.address;
        return *this;
    }

    void User::show_user_info() const
    {
        cout << "你的个人信息：" << endl;
        cout << "姓名\t性别\t年龄\t联系方式\t家庭地址" << endl;
        cout << name << "\t" << sex << "\t" << age << "\t" << tel << "\t" << address << "\t" << endl;
    }

    void User::get_user_info()
    {
        cout << "输入你的个人信息。" << endl << "姓名：";
        cin >> name;
        cout << "性别:";
        cin >> sex;
        cout << "年龄：";
        cin >> age;
        cout << "地址：";
        cin >> address;
        cout << "联系方式：";
        cin >> tel;
    }
}