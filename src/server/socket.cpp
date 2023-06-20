#include <socket_server.hpp>


/**
 * SOCKET HANDLER
 * 
 * set constructor of class Socket
*/
SocketServer::SocketServer() {
    // Set logging settings
    server.set_access_channels(websocketpp::log::alevel::all);
    server.clear_access_channels(websocketpp::log::alevel::all);

    // Initialize asio non tls connection
    server.init_asio();


    server.set_message_handler(bind(
        &SocketServer::onMessage,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));

    server.set_open_handler([this](websocketpp::connection_hdl hdl) {
        onOpen(hdl);
    });

    server.set_close_handler([this](websocketpp::connection_hdl hdl) {
        onClose(hdl);
    });

}

// Set method run on class Socket
void SocketServer::run() {
    // Listening port
    server.listen(port);

    // Start server loop
    server.start_accept();

    // Start asio io_server loop
    server.run();
}

// Set method onOpen on class Socket
void SocketServer::onOpen(conn_hdl connectionHandler) {
    _connection conn = this->server.get_con_from_hdl(connectionHandler);
    string userId = conn->get_request_header("user");
 
    cout << userId << " connected." << endl;
    this->addUser(userId, connectionHandler);
}

// Set method onClose on class Socket
void SocketServer::onClose(conn_hdl connectionHandler) {
    _connection conn = this->server.get_con_from_hdl(connectionHandler);
    string userId = conn->get_request_header("user");
 
    cout << userId << " disconnected." << endl;
    this->removeUser(userId);
}

// Set method addUser on class Socket
void SocketServer::addUser(string userId, conn_hdl connectionHandler) {
    users.insert(make_pair(userId, connectionHandler));
}

// Set method removeUser on class Socket
void SocketServer::removeUser(string userId) {
    users.erase(userId);
}

// Set method onMessage on class Socket
void SocketServer::onMessage(conn_hdl connectionHandler, _message message) {
    
    _connection conn = this->server.get_con_from_hdl(connectionHandler);
    string messageText = message->get_payload();
    string userId = conn->get_request_header("user-id");
    string userFullname = conn->get_request_header("user-fullname");
    string toUserId = conn->get_request_header("to-user-id");
    string toUserFullname = conn->get_request_header("to-user-fullname");

    cout << "to user : " <<  toUserFullname << endl;
    cout << userId << " : " << messageText << endl;
    
    if (messageText == "stop-listening") {
        server.stop_listening();
        return;
    }

    try {
        server.send(connectionHandler, message->get_payload(), message->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << "Echo failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }
}