#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

/**
 * User class interfacing
*/
class User {
    public:
        map<string, User> users;

        void setUsername(string username);
        void setFullname(string fullname);
        void setPassword(string password);
        void setUser(string username, string fullname, string password);
        void addUser(string username, string fullname, string password);
        User& setUsers(vector<vector<string>> users);
        map<string, User> getUsers();
        string getUsername();
        string getFullname();
        string getPassword();

    private:
        // map<string, User> users;
        string username;
        string fullname;
        string password;

};

#endif // USER_HPP
