#include <string>

namespace __TrainManage__
{
    class User
    {
    private:
        std::string name, sex, address, tel;
        int    age;

    public:
        User();
        User(std::string na, std::string se, std::string ad, std::string te, int ag)
            : name(na), sex(se), address(ad), tel(te), age(ag) {}

        bool operator== (User & rhs);
        const bool operator== (const User & rhs) const;
        void show_user_info();
        void get_user_info();
    };
};