#include <socket_client.hpp>

/**
 * SOCKET HANDLER
 * 
 * set constructor of class Socket
*/
Socket::Socket() {
    client.clear_access_channels(websocketpp::log::alevel::all);
    client.clear_error_channels(websocketpp::log::elevel::all);

    client.init_asio();
    client.start_perpetual();

    this->thread.reset(new websocketpp::lib::thread(&socket_client::run, &client));
}

// Set method getMetadata on class Socket
SocketMetadata::ptr Socket::getMetadata() {
    return this->metadata;
}

// Set method connect on class Socket
string Socket::connect(User *_user, User *_toUser, string uri = "default") {
    error_code error;
    if (uri == "default") uri = this->getUri();

    _connection conn = this->client.get_connection(uri, error);
    this->_user = _user;
    this->_toUser = _toUser;
    conn->append_header("user-id", _user->getUsername());
    conn->append_header("user-fullname", _user->getFullname());
    conn->append_header("to-user-id", _toUser->getUsername());
    conn->append_header("to-user-fullname", _toUser->getFullname());

    if (error) return "Koneksi Error : " + error.message();

    SocketMetadata::ptr _metadata(new SocketMetadata(_user->getUsername(), conn->get_handle(), uri));
    this->metadata = _metadata;

    conn->set_open_handler(bind(
        &SocketMetadata::onOpen,
        _metadata,
        &this->client,
        placeholders::_1
    ));

    conn->set_fail_handler(bind(
        &SocketMetadata::onFail,
        _metadata,
        &this->client,
        placeholders::_1
    ));

    conn->set_close_handler(bind(
        &SocketMetadata::onClose,
        _metadata,
        &this->client,
        placeholders::_1
    ));

    conn->set_message_handler(bind(
        &SocketMetadata::onMessage,
        _metadata,
        &this->client,
        placeholders::_1,
        placeholders::_2
    ));

    this->client.connect(conn);

    while (_metadata->getStatus() != "Open") {
        if (_metadata->getStatus() == "Failed") {
            this->close();
            return _metadata->getErrorReason();
        };
    }

    return _user->getUsername();
}


// Set method close on class Socket
void Socket::close() {
    string status = metadata->getStatus();
    client.stop_perpetual();
    
    error_code error;
    client.close(this->metadata->getConnectionHandler(), websocketpp::close::status::going_away, "Shut down", error);
    
    if (error && status == "Open") std::cout << "Gagal menutup koneksi : " << error.message() << endl;

    this->thread->join();
}

// Set method sendMessage on class Socket
bool Socket::listen_chat() {
    // system("clear");
    vector<string> chats = this->metadata->getReceiveMessage();
    
    if (chats.size()) {
        // fputs("\033[A\033[2K", stdout);
        // fputs("\033[2K", stdout);
        // rewind(stdout);
        // fputs("Fiki Pratama (fiki) : ", stdout);

        fputs("\033[2K\r", stdout);
        
        for (auto chat: chats) {
            // std::cout << chat.getFrom() << chat.getMessage() << endl << "Fiki Pratama (fiki) : ";
            fputs(chat.c_str(), stdout);
        }

        fputs(("\n" + this->_user->getFullname() + " (" + this->_user->getUsername() + ") : ").c_str(), stdout);
        rewind(stdout);
    }
    
    


    // std::cout << endl << this->_user->getFullname() + " (" + this->_user->getUsername() + ") : ";
    this_thread::sleep_for(chrono::milliseconds(500));
    return chats.size() ? true : false;
}

// Set method sendMessage on class Socket
void Socket::sendMessage(string *_message) {
    error_code error;

    SocketMetadata::ptr _metadata = this->getMetadata();
    // _metadata->onSendMessage(this->_user, _message);
      

    client.send(_metadata->getConnectionHandler(), *_message, websocketpp::frame::opcode::text, error);
    if (error) {
        std::cout << "Error send message : " << error.message() << endl;
        return;
    }
}