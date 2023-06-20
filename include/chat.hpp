#ifndef CHAT_HPP
#define CHAT_HPP

#include <iostream>
#include <string>
#include <map>
#include <user.hpp>

using namespace std;


class Chat {
    public:
        void setUser();
        void setToUser();
        User getUser();
        User getToUser();
    private:
        User& user;
        User toUser;
};



#endif // CHAT_HPP