#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP


#include <iostream>
#include <iomanip>
#include <bits/stdc++.h>
#include <boost/config.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <socket_metadata_client.hpp>
#include <user.hpp>

using namespace std;

typedef websocketpp::client<websocketpp::config::asio_client> socket_client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::thread> socket_thread; 
typedef websocketpp::lib::error_code error_code;
typedef socket_client::message_ptr _message;

class Socket {
public:
    User *_user;
    User *_toUser;

    Socket();
    SocketMetadata::ptr getMetadata();
    string connect(User *_user, User *_toUser, string uri);
    void sendMessage(string *_message);
    bool listen_chat();
    void close();

private:
    string host = "localhost";
    int port = 9000;


    socket_client client;
    socket_thread thread;
    SocketMetadata::ptr metadata;

    string getUri() {
        return "ws://" + this->host + ":" + to_string(this->port);
    }
};

#endif // SOCKET_CLIENT_HPP