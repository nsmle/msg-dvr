#ifndef SESSION_HPP
#define SESSION_HPP

#include <iostream>
#include <string>
#include <map>

using namespace std;

/**
 * Session class interfacing
*/
class Session {
    public:
        typedef map<string, Session> sessions_t;

        sessions_t getSessions();
        void addSession(string userId1, string userId2);
        static bool exists(string userId, sessions_t *_sessions);
    
    private:
        string userId1;
        string userId2;
        map<string, Session> sessions;

        bool match(string userId);
};

/**
 * Define type
*/

#endif // SESSION_HPP