#include <socket_server.hpp>


/**
 * SOCKET HANDLER
 * 
 * set constructor of class Socket
*/
Socket::Socket() {
    // Set logging settings
    server.set_error_channels(websocketpp::log::alevel::all);
    server.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);
    // server.set_access_channels(websocketpp::log::alevel::all);
    server.clear_error_channels(websocketpp::log::alevel::all);
    server.clear_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

    // Initialize asio non tls connection
    server.init_asio();


    server.set_message_handler(bind(
        &Socket::onMessage,
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
void Socket::run(int port = 5000) {
        // Set port to listen
        this->port = port;

        try {
            // Listening port
            server.listen(this->port);

            // Start queue accept connection
            server.start_accept();

            // server.set_fail_handler()

            if (server.is_listening())
                printf("Running on port : %d\n", this->port);

            // Start asio io_server loop
            server.run();
        } catch (const std::exception & e) {
            string errorMessage = e.what();
            string expectErrMsg = "Underlying Transport Error"; 
            if (errorMessage == expectErrMsg) {
                std::cout << "Port " + to_string(port) + " sudah digunakan!" << endl;
                return;
            }

            std::cout << "Server gagal dijankan : " <<  e.what() << endl;
        }
}

// Set method onOpen on class Socket
void Socket::onOpen(conn_hdl connectionHandler) {
    _connection conn = this->server.get_con_from_hdl(connectionHandler);
    string userId = conn->get_request_header("user-id");
    string toUserId = conn->get_request_header("to-user-id");
    string userFullname = conn->get_request_header("user-fullname");
    string toUserFullname = conn->get_request_header("to-user-fullname");
    
    if (this->userExist(userId)) {
        return server.send(connectionHandler, "connection-exists", websocketpp::frame::opcode::text);
    }

    this->addUser(userId, connectionHandler);

    if (this->sessionExistToOther(userId, toUserId)) {
        return server.send(connectionHandler, "connection-to-other", websocketpp::frame::opcode::text);
    }



    if (!this->sessionExist(userId, toUserId)) {
        this->sessions.push_back({ userId, toUserId });
        for (auto s: this->sessions) {
            cout << s[0] << "-" << s[1] << endl;
        }
    }
 
    if (!this->userExist(toUserId)) {
        std::cout << "To " + toUserFullname << " (" << toUserId <<  ") offline" << std::endl;


        server.send(connectionHandler, "user-not-found", websocketpp::frame::opcode::text);
    } else {

        std::cout << userFullname << " (" << userId <<  ") connected" << std::endl;
        if (this->sessionExist(toUserId, userId)) {
            server.send(this->getUserConnectionHandler(toUserId), "user-connected", websocketpp::frame::opcode::text);
        }
    }
}

// Set method onClose on class Socket
void Socket::onClose(conn_hdl connectionHandler) {
    _connection conn = this->server.get_con_from_hdl(connectionHandler);
    string userId = conn->get_request_header("user-id");
    string toUserId = conn->get_request_header("to-user-id");
    string userFullname = conn->get_request_header("user-fullname");
    string toUserFullname = conn->get_request_header("to-user-fullname");
 


    
    std::cout << userFullname << " (" << userId <<  ") disconected" << std::endl;
    if (this->userExist(userId)) this->removeUser(userId);

    if (this->userExist(toUserId)) {
        server.send(this->getUserConnectionHandler(toUserId), "user-disconected", websocketpp::frame::opcode::text);
    }

}

// Set method addUser on class Socket
void Socket::addUser(string userId, conn_hdl connectionHandler) {
    users.insert(make_pair(userId, connectionHandler));
}

// Set method removeUser on class Socket
void Socket::removeUser(string userId) {
    users.erase(userId);
}

// Set method userExist on class Socket
bool Socket::userExist(string userId) {
    users_t::iterator user = this->users.find(userId);
    if (user == this->users.end()) return false;

    return true;
}

// Set method sessionExist on class Socket
bool Socket::sessionExist(string userId, string toUserId) {
    for (auto session: this->sessions) {
        if (session[0] == userId && session[1] == toUserId) return true;
         
    }

    return false;
}

// Set method sessionExistToOther on class Socket
bool Socket::sessionExistToOther(string userId, string toUserId) {
    int existCount = 0;
    for (auto session: this->sessions) {
         cout << "xx " << session[0] << endl;
        if (session[0] == toUserId || session[1] == toUserId) existCount++;
    }

    return (existCount >= 2) ? true : false;
}

// Set method getUserConnectionHandler on class Socket
conn_hdl Socket::getUserConnectionHandler(string userId) {
    users_t::iterator user = this->users.find(userId);
    if (user == this->users.end()) {
        std::cout << "User " << userId << " not found!" << endl;
    }
    // if (user == this->users.end()) std::cout << "User " << userId << " not found!" << endl;

    return user->second;
}

// Set method onMessage on class Socket
void Socket::onMessage(conn_hdl connectionHandler, _message message) {
    
    _connection conn = this->server.get_con_from_hdl(connectionHandler);
    string messageText = message->get_payload();
    string userId = conn->get_request_header("user-id");
    string userFullname = conn->get_request_header("user-fullname");
    string toUserId = conn->get_request_header("to-user-id");
    string toUserFullname = conn->get_request_header("to-user-fullname");

    std::cout << userFullname << " (" << userId <<  ") to " << toUserFullname << " (" << toUserId << ") : " << messageText << endl;
    if (messageText == "stop-listen") {
        server.stop();
        server.stop_listening();
        return;
    }
    


    if (this->userExist(toUserId) &&
        this->sessionExist(toUserId, userId) &&
        messageText.length() != 0) {
        try {
            server.send(this->getUserConnectionHandler(toUserId), messageText, websocketpp::frame::opcode::text);

        } catch (websocketpp::exception const & e) {
            std::cout << "Failed resend message: "
                    << "(" << e.what() << ")" << std::endl;
        }
    }
}