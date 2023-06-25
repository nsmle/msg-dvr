#ifndef SOCKET_METADATA_CLIENT_HPP
#define SOCKET_METADATA_CLIENT_HPP

#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <boost/config.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <chat.hpp>
#include <user.hpp>


typedef websocketpp::client<websocketpp::config::asio_client> socket_client;
typedef websocketpp::connection_hdl conn_hdl; 
typedef socket_client::connection_ptr _connection;
typedef socket_client::message_ptr _message;


using namespace std;

class SocketMetadata {
public:
    typedef websocketpp::lib::shared_ptr<SocketMetadata> ptr;
    SocketMetadata(string id, conn_hdl connectionHandler, string uri);
    void onOpen(socket_client *_client, conn_hdl connectionHandler); 
    void onClose(socket_client *_client, conn_hdl connectionHandler);
    void onFail(socket_client *_client, conn_hdl connectionHandler);
    void onMessage(socket_client *_client, conn_hdl connectionHandler, _message message);
    void onSendMessage(User *_user, string *_message);
    vector<string> getReceiveMessage();
    conn_hdl getConnectionHandler();
    string getStatus();
    string getErrorReason();
    string getServer();
    string getUri();
    friend ostream& operator<< (ostream &out, const SocketMetadata &data);
private:
    string id;
    conn_hdl connectionHandler;
    string status;
    string uri;
    string server;
    string errorReason;

    vector<string> messages;
};


#endif // SOCKET_METADATA_CLIENT_HPP