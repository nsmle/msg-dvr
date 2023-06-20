#include <user.hpp>


/**
 * USER HANDLER
 *
 * set constructor of class User
*/

// Set method setUser on class User
void User::setUser(string username, string fullname, string password) {
    this->username = username;
    this->fullname = fullname;
    this->password = password;
}

// Set method setUser by user object on class User
void User::setUser(User user) {
    this->username = user.username;
    this->fullname = user.fullname;
    this->password = user.password;
}

// Set method it (returning current user object) on class User
User& User::it() {
    return *this;
}

// Set method createUser on class User
User& User::createUser(string username, string fullname, string password) {
    this->username = username;
    this->fullname = fullname;
    this->password = password;

    return *this;
}

// Set method addUser on class User
void User::addUser(User user) {
    users.insert(make_pair(user.username, user));
}

// Set method setUsername on class User
void User::setUsername(string username) {
    this->username = username;
}

// Set method setFullname on class User
void User::setFullname(string fullname) {
    this->fullname = fullname;
}

// Set method setPassword on class User
void User::setPassword(string password) {
    this->password = password;
}

// Set method getUsername on class User
string User::getUsername() {
    return this->username;
}

// Set method getFullname on class User
string User::getFullname() {
    return this->fullname;
}

// Set method getPassword on class User
string User::getPassword() {
    return this->password;
}