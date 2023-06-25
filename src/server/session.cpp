#include <session.hpp>

/**
 * SESSION HANDLER
 * 
 * Initialize constructor of class Session
*/


// Initialize method exists on class Session
void Session::addSession(string userId1, string userId2) {
    this->userId1 = userId1;
    this->userId2 = userId2;
}

/**
 * Initialize method exists on class Session
 * 
 * Check string match between property userId1|userId2 with param userId 
*/
bool Session::exists(string userId) {
    bool exist = false;
    for (auto session: this->sessions) {
        if (session.second.userId1 == userId ||
            session.second.userId2 == userId) exist = true;
    }
    
    return false;
}