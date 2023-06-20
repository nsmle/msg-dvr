#include <socket_metadata_client.hpp>


/**
 * METADATA HANDLER
 * 
 * Set constructor on class SocketMetadata
*/
SocketMetadata::SocketMetadata(string id, conn_hdl connectionHandler, string uri) {
    this->id = id;
    this->connectionHandler = connectionHandler;
    this->status = "Connecting";
    this->uri = uri;
    this->server = "N/A";
}

// Set method action onOpen in class Metadata
void SocketMetadata::onOpen(socket_client *_client, conn_hdl connectionHandler) {
    this->status = "Open";

    _connection conn = _client->get_con_from_hdl(connectionHandler);
    this->server = conn->get_response_header("Server");
    
    // try {
    //     _client->send(connectionHandler, "user-connect", websocketpp::frame::opcode::text);
    // } catch (websocketpp::exception const & e) {
    //     cout << "Failed connect because: "
    //               << "(" << e.what() << ")" << std::endl;
    // }
};

// set method action onClose in class Metadata
void SocketMetadata::onClose(socket_client *_client, conn_hdl connectionHandler) {
    this->status = "Closed";

    _connection conn = _client->get_con_from_hdl(connectionHandler);
    this->server = conn->get_response_header("Server");
    // this->errorReason = conn->get_ec().message();

    std::stringstream ss;
    ss << "close code: " << conn->get_remote_close_code() << " (" 
        << websocketpp::close::status::get_string(conn->get_remote_close_code()) 
        << "), close reason: " << conn->get_remote_close_reason();
    this->errorReason = ss.str();

    // try {
    //     _client->send(connectionHandler, "user-close", websocketpp::frame::opcode::text);
    // } catch (websocketpp::exception const & e) {
    //     cout << "Failed close because: "
    //               << "(" << e.what() << ")" << std::endl;
    // }
}

// set method action onFail in class Metadata
void SocketMetadata::onFail(socket_client *_client, conn_hdl connectionHandler) {
    this->status = "Failed";

    _connection conn = _client->get_con_from_hdl(connectionHandler);
    this->server = conn->get_response_header("Server");
    this->errorReason = conn->get_ec().message();
}

conn_hdl SocketMetadata::getConnectionHandler() {
    return this->connectionHandler;
}

string SocketMetadata::getStatus() {
    return this->status;
}

// Set out of message
ostream& operator<<(ostream &out, const SocketMetadata &data) {
    out 
        << "URI: " << data.uri << endl
        << "Status: " << data.status << endl
        << "Server: " << (data.server.empty() ? "None Specified" : data.server) << endl
        << "Reason: " << (data.errorReason.empty() ? "N/A" : data.errorReason)<< endl;

    return out;
};