#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <memory>
#include <string>
#include <map>

using namespace std;

class User {
    public:
        map<string, User> users;

        void setUsername(string username);
        void setFullname(string fullname);
        void setPassword(string password);
        void setUser(string username, string fullname, string password);
        void setUser(User user);
        User& createUser(string username, string fullname, string password);
        User& it();
        void addUser(User user);
        string getUsername();
        string getFullname();
        string getPassword();

    private:
        string username;
        string fullname;
        string password;

};



#endif // USER_HPP