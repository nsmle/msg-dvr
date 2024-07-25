#ifndef SOCKET_SERVER_HPP
#define SOCKET_SERVER_HPP

#include <iostream>
#include <map>
#include <boost/config.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <session.hpp>

using namespace std;
const int PORT = 5000;
/**
 * Define type
*/
typedef websocketpp::config::asio asio;
typedef websocketpp::server<asio> socket_server;
typedef websocketpp::connection_hdl conn_hdl;
typedef socket_server::connection_ptr _connection;
typedef socket_server::message_ptr _message;
typedef map<string, conn_hdl> users_t;


/**
 * Socket class interfacing
*/
class Socket {
public:
    typedef std::shared_ptr<Socket> ptr;

    Socket();
    void run(int port);
    void addUser(string userId, conn_hdl connectionHandler);
    void removeUser(string userId);
    conn_hdl getUserConnectionHandler(string userId);
    bool userExist(string userId);
    bool sessionExist(string userId, string toUserId);
    bool sessionExistToOther(string userId, string toUserId);
    void onOpen(conn_hdl connectionHandler);
    void onClose(conn_hdl connectionHandler);
    void onMessage(conn_hdl connectionHandler, _message message);

private:
    users_t users;
    vector<vector<string>> sessions;
    socket_server server;
    int port;
};

#endif // SOCKET_SERVER_HPP
