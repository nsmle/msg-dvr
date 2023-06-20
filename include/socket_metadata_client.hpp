#ifndef SOCKET_METADATA_CLIENT_HPP
#define SOCKET_METADATA_CLIENT_HPP

#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <boost/config.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>


typedef websocketpp::client<websocketpp::config::asio_client> socket_client;
typedef websocketpp::connection_hdl conn_hdl; 
typedef socket_client::connection_ptr _connection;


using namespace std;

class SocketMetadata {
public:
    typedef websocketpp::lib::shared_ptr<SocketMetadata> ptr;
    SocketMetadata(string id, conn_hdl connectionHandler, string uri);
    void onOpen(socket_client *_client, conn_hdl connectionHandler); 
    void onClose(socket_client *_client, conn_hdl connectionHandler);
    void onFail(socket_client *_client, conn_hdl connectionHandler);
    conn_hdl getConnectionHandler();
    string getStatus();
    friend ostream& operator<< (ostream &out, const SocketMetadata &data);
private:
    string id;
    conn_hdl connectionHandler;
    string status;
    string uri;
    string server;
    string errorReason;
};


#endif // SOCKET_METADATA_CLIENT_HPP