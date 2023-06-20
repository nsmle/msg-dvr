#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <iostream>
#include <map>
#include <boost/config.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using namespace std;

typedef websocketpp::config::asio asio;
typedef websocketpp::server<asio> socket_server;
typedef websocketpp::connection_hdl conn_hdl;
typedef socket_server::connection_ptr _connection;
typedef socket_server::message_ptr _message;


class SocketServer {
public:
    typedef websocketpp::lib::shared_ptr<SocketServer> ptr;

    SocketServer();
    void run();
    void addUser(string userId, conn_hdl connectionHandler);
    void removeUser(string userId);
    void getUserConnectionHandler(string userId);
    void userExist();
    void onOpen(conn_hdl connectionHandler);
    void onClose(conn_hdl connectionHandler);
    void onMessage(conn_hdl connectionHandler, _message message);

private:
    map<string, conn_hdl> users;
    socket_server server;
    int port = 9782;
};


#endif