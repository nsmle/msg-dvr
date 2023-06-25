#include <socket_server.hpp>

// const int PORT = 5000;

int main() {
    printf("==== SERVER ====\n");
    Socket socket;


    socket.run(PORT);

    return 0;
}


