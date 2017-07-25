#include "train.h"

inline bool operator== (User & rhs) const
{
    return name == rhs.name && sex == rhs.sex && address == rhs.address &&
}

inline const bool operator== (const User & rhs) const
{
    return name == rhs.name && sex == rhs.sex && address == rhs.address &&
}

inline void User::show_user_info()
{
    cout << "你的个人信息：" << endl;
    cout << "姓名：" << name << endl << "性别：" << sex << endl
        << "年龄：" << age << endl << "联系方式：" << tel << endl
        << "家庭地址：" << address << endl;
}

inline void User::get_user_info()
{
    cout << "姓名：";
    cin >> name;
    cout << "性别：";
    cin >> sex;
    cout << "年龄：";
    cin >> age;
    cout << "联系方式：";
    cin >> tel;
    cout << "家庭地址：";
    cin >> address;
    this->name = name;  this->sex = sex;
    this->age  = age;   this->tel = tel;
    this->address = address;
}