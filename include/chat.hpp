#ifndef CHAT_HPP
#define CHAT_HPP

#include <iostream>
#include <string>

using namespace std;


class Chat {
    public:
        void setChat(string from, string message);
        string getFrom();
        string getMessage();
    private:
        string from;
        string message;
};


#endif // CHAT_HPP