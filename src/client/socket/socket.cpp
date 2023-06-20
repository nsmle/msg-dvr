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

// Set method connect on class Socket
string Socket::connect(string id, string uri = "default") {
    error_code error;
    if (uri == "default") uri = this->getUri();

    _connection conn = this->client.get_connection(uri, error);
    conn->append_header("user-id", id);
    conn->append_header("to-user-id", id);

    if (error) {
        cout << "Connect Initialization Error : " << error.message() << endl;
        return "error";        
    }

    SocketMetadata::ptr _metadata(new SocketMetadata(id, conn->get_handle(), uri));
    // connections[id] = _metadata;
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

    this->client.connect(conn);

    return id;
}

// Set method getMetadata on class Socket
SocketMetadata::ptr Socket::getMetadata() {
    return this->metadata;
}

// Set method sendMessage on class Socket
void Socket::sendMessage(string id, string message) {
    error_code error;

    SocketMetadata::ptr _metadata = this->getMetadata();  

    client.send(_metadata->getConnectionHandler(), message, websocketpp::frame::opcode::text, error);
    if (error) {
        cout << "Error send message : " << error.message() << endl;
        return;
    }
}