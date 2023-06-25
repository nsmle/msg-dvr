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

// Set method addUser on class User
void User::addUser(string username, string fullname, string password) {
    vector<string> defaultUser = { 
        this->username,
        this->fullname,
        this->password
    };
    
    this->setUser(username, fullname, password);
    this->users.insert(make_pair(username, *this));

    this->setUser(defaultUser[0], defaultUser[1], defaultUser[2]);
}

// Set method setUsers on class User
User& User::setUsers(vector<vector<string>> users) {
    for (int i = 0; i < users.size(); i++) {
        if (users.at(i).size() != 3 ) {
            throw runtime_error("setUser Error, Masukan data user seperti: setUser({{ 'username', 'fullname', 'password' }})");
        }

        this->addUser(
            users.at(i)[0],   // Username = at vector index 0
            users.at(i)[1],   // Fullname = at vector index 1
            users.at(i)[2]    // Password = at vector index 2
        );
    }
    
    return *this;
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

// Set method getUsers on class User
map<string, User> User::getUsers() {
    return this->users;
}