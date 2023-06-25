#include <socket_client.hpp>
#include <user.hpp>

// int main() {    
//     Socket io;
//     string uri = "ws://localhost:9082";

//     string connection = io.connect(uri, "asdf");
//     cout << connection << endl;

//     printf("==== CLIENT ====\n");

//     return 0;
// }

const string URI = "ws://localhost:9782";
// const string ID = "winda";


void initUsers (User *_user) {
    string usernames[3] = {
        "fiki",
        "rizka",
        "nanda",
    };
    string fullname[3] = {
        "Fiki Pratama",
        "Rizka Amelia Sari",
        "Muhammad Nanda Maulana Yasin",
    };
    string passwords[3] = {
        "fikisecret",
        "rizkasecret",
        "nandasecret",
    };



    User user = *(_user);
    for (int i = 0; i < 3; i++) {
        User userCreated = user.createUser(usernames[i], fullname[i], passwords[i]);
        _user->users.insert(make_pair(usernames[i], user));
    }
}


void login(User *_user, string *_input) {    
    
    cout << "Username : ";
    getline(cin, *_input);

    map<string, User>::iterator userIt = _user->users.find(*_input);
    if (userIt == _user->users.end()) {
        cout << "User not found, Please retry again!\n\n";
        login(_user, _input);
    }

    cout << "Password : ";
    getline(cin, *_input);

    if (userIt->second.getPassword() != *_input) {
        cout << "Password wrong, Please retry again!\n\n";
        login(_user, _input);
    }
        
    cout << "Berhasil login sebagai " << userIt->second.getFullname() << endl << endl;


    _user->setUser(userIt->second.it());

}



int main() {
    // bool done = false;
    // string input;
    // Socket io;
    // User user;
    // initUsers(&user);
    // login(&user, &input);

    // string ID;

    // cout << "ID : ";
    // getline(cin, ID);
    
    // string connId = io.connect(ID, URI);
    // if (connId != "error") {
    //     cout << "> Created connection with id " << connId << endl << endl;
    // }


    
    // while (!done) {
    //     cout << connId << " : ";
    //     getline(cin, input);

    //     if (input == "quit") {
    //         done = true;
    //     } else {
    //         io.sendMessage("wulan", input);
    //     }
        
    //     // if (input == "quit") {
    //     //     done = true;
    //     // } else if (input == "clear") {
    //     //     system("clear");
    //     // } else if (input == "help") {
    //     //     cout
    //     //         << "\nCommand List:\n"
    //     //         << "connect <ws uri>\n"
    //     //         << "show <connection id>\n"
    //     //         << "help: Display this help text\n"
    //     //         << "quit: Exit the program\n"
    //     //         << std::endl;
    //     // } else if (input.substr(0,7) == "connect") {
    //     //     string connId = io.connect(ID, URI);

    //     //     if (connId != "error") {
    //     //         std::cout << "> Created connection with id " << connId << std::endl;
    //     //     }
    //     // } else if (input == "test") {
    //     //     io.sendMessage("wulan", "user-connect");
    //     // } else if (input.substr(0,4) == "show") {
    //     //     SocketMetadata::ptr metadata = io.getMetadata();
    //     //     if (metadata) {
    //     //         std::cout << *metadata << std::endl;
    //     //     } else {
    //     //         std::cout << "> Unknown connection id " << ID << std::endl;
    //     //     }
    //     // } else {
    //     //     cout << "> Unrecognized Command" << std::endl;
    //     // }
    // }

    return 0;
}
