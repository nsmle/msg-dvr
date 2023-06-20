#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP


#include <iostream>
#include <boost/config.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <socket_metadata_client.hpp>

using namespace std;

typedef websocketpp::client<websocketpp::config::asio_client> socket_client;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::thread> socket_thread; 
typedef websocketpp::lib::error_code error_code;
typedef socket_client::message_ptr _message;

class Socket {
public:
    Socket();
    string connect(string id, string uri);
    SocketMetadata::ptr getMetadata();
    void onMessage();
    void sendMessage(string id, string message);

private:
    // typedef map<string, SocketMetadata::ptr> conn_list;

    socket_client client;
    socket_thread thread;
    SocketMetadata::ptr metadata;
    string host = "localhost";
    int port = 9000;
    

    string getUri() {
        return "ws://" + this->host + ":" + to_string(this->port);
    }
};

#endif // SOCKET_CLIENT_HPP