#include <socket_server.hpp>


int main() {
    printf("==== SERVER ====\n");
    SocketServer socket;


    printf("==> SERVER START\n");
    socket.run();

    return 0;
}