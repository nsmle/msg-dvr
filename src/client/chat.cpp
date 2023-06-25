#include <chat.hpp>

void Chat::setChat(string from, string message) {
    this->from = from;
    this->message = message;
}

string Chat::getFrom() {
    return this->from;
}

string Chat::getMessage() {
    return this->message;
}