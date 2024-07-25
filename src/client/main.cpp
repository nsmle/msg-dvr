#include <user.hpp>
#include <socket_client.hpp>
#include <chrono>
#include <future>

using namespace std;

// Config
const int PORT = 5000;
const string HOST = "192.168.0.3";
// const string HOST = "192.168.4.45";


void initialize() {

}


void useDummyUser(User *_user) {
    try {
        // username at index 0, fullname at index 1, password at index 2, 
        _user->setUsers({
            { "fiki", "Fiki Pratama", "fikisecret" },
            { "rizka", "Rizka Amelia Sari", "rizkasecret" },
            { "nanda", "Muhammad Nanda Maulana Yasin", "nandasecret" },
            { "sabib", "Sabib Prastio", "sabibsecret" }
        });
    } catch(const std::exception& e) {
        std::cout << e.what() << endl;
    }
}

string getMessage(User *_user, bool isInit = false) {
    string message;

    if (!isInit) fputs((_user->getFullname() + " (" + _user->getUsername() + ") : ").c_str(), stdout);
    getline(cin, message);

    return message;
}

void chat(Socket *_socket, User *_user) {
    future<string> futureMsg = async(launch::async, [_user]() {
        return getMessage(_user, true);
    });

    while (true) {
        if (futureMsg.wait_for(chrono::seconds(0)) == future_status::ready) {
            string message = futureMsg.get();

            futureMsg = async(launch::async, [_user]() {
                return getMessage(_user);
            });

            if (message == "clear") {
                system("clear");
                continue;
            } else if (message == "reconnect") {
                _socket->connect(_socket->_user, _socket->_toUser, "ws://"+HOST+":"+to_string(PORT));
                continue;
            } else if (message == "exit") {
                _socket->close();
                return;
            }

            _socket->sendMessage(&message);
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        
        string promiseMessage = futureMsg.get();
        std::cout << promiseMessage << std::endl;
        _socket->listen_chat();
        if (_socket->getMetadata()->getStatus() == "Closed") return;
        // if (!ready) {
        //     fputs("\033[A\033[2K", stdout);
        //     ready = true;
        // }
        // if (isChatReplied) {
        //     fputs("\033[A\033[2K", stdout);
        //     rewind(stdout);
        //     isChatReplied = false;
        // }

        // std::cout << "waiting..." << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    User user, toUser;
    useDummyUser(&user);

    
    // map<string, User>::iterator user1 = user.users.find("nanda");
    // map<string, User>::iterator user2 = user.users.find("rizka");
    string input;
    std::cout << "from user : ";
    std::cin >> input; 
    map<string, User>::iterator user1 = user.users.find(input);
    std::cout << "to user : ";
    std::cin >> input; 
    map<string, User>::iterator user2 = user.users.find(input);


    if (user1 == user.users.end() || user2 == user.users.end()) {
        std::cout << "No User" << endl;
        return 0;
    }

    user.setUser(user1->second.getUsername(), user1->second.getFullname(), user1->second.getPassword());
    toUser.setUser(user2->second.getUsername(), user2->second.getFullname(), user2->second.getPassword());
    
    Socket socket;
    string connected = socket.connect(&user, &toUser, "ws://"+HOST+":"+to_string(PORT));
    if (connected != user.getUsername()) {
        std::cout << connected << endl;
        return 0;
    }

    chat(&socket, &user);

    // string message;
    // while (true) {
    //     std::cout << user.getFullname() + " (" + user.getUsername() + ") : ";
    //     getline(cin, message);

    //     if (message == "quit" || message == "\\q") return 0;
    //     socket.sendMessage(&message);
    // }




    return 0;
}



/**

    menu -> login -> chat menu -> chat to
                                

*/