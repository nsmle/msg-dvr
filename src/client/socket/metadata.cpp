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

    std::cout << "Closed" << endl;

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
    _connection conn = _client->get_con_from_hdl(connectionHandler);
    string errorMessage = conn->get_ec().message();
    this->errorReason = errorMessage == "Underlying Transport Error" 
        ? "Gagal tersambung ke server " + this->uri 
        : "Gagal tersambung ke server : " + errorMessage;

    this->status = "Failed";
}

// Set method onMessage on class Metadata
void SocketMetadata::onMessage(socket_client *_client, conn_hdl connectionHandler, _message message) {
    string messageText = message->get_payload();
    _connection conn = _client->get_con_from_hdl(connectionHandler);

    string userId = conn->get_request_header("user-id");
    string userFullname = conn->get_request_header("user-fullname");
    string toUserId = conn->get_request_header("to-user-id");
    string toUserFullname = conn->get_request_header("to-user-fullname");

    if (messageText == "connection-exists") {
        this->messages.push_back("\033[1;31mPengguna dengan sesi " + userFullname + " (" + userId + ") sedang login, multi sesi tidak diizinkan!\033[0m");
        return _client->close(connectionHandler, websocketpp::close::status::bad_gateway, "connection-exists");
    }

    if (messageText == "connection-to-other") {
        this->messages.push_back("\033[1;31mPengguna " + toUserFullname + " (" + toUserId + ") sedang chat dengan pengguna lain!\033[0m");
        return _client->close(connectionHandler, websocketpp::close::status::bad_gateway, "connection-exists");
    }

    if (messageText == "user-not-found" || messageText == "user-disconected" || messageText == "user-connected") {
        string color = messageText == "user-connected" ? "\033[1;36m" : "\033[1;31m";
        return this->messages.push_back(color + toUserFullname + " (" + toUserId + ")" + (messageText == "user-disconected" ? " " : messageText == "user-connected" ? " kembali " : " sedang ") + "offline\033[0m");
    }

    if (this->id == userId && messageText.length() != 0) {
        // cout << toUserFullname + " (" + toUserId + ") : " + messageText << endl;
        this->messages.push_back("\033[1;34m" + toUserFullname + " (" + toUserId + ") : " + messageText + "\033[0m");
    }
    
}

void SocketMetadata::onSendMessage(User *_user, string *_message) {
    this->messages.push_back(_user->getFullname() + " (" + _user->getUsername() + ") : " + *_message );
}

vector<string> SocketMetadata::getReceiveMessage() {
    vector<string> tempMessages = this->messages;
    this->messages.clear();

    return tempMessages;
    
    

    // for (int i = 0; i < chats.size(); i++) {
    //     cout << endl << chats[i].getFrom() << chats[i].getMessage();
    // }
}

conn_hdl SocketMetadata::getConnectionHandler() {
    return this->connectionHandler;
}

string SocketMetadata::getStatus() {
    return this->status;
}

string SocketMetadata::getErrorReason() {
    return this->errorReason;
}

string SocketMetadata::getServer() {
    return this->server;
}
string SocketMetadata::getUri() {
    return this->uri;
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