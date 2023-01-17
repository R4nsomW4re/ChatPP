#include "header.h"

const int MAX_BUFFER_SIZE = 1024;
const int MAX_CONNECTIONS = 5;

int main() {

    static WSADATA wsaData;
    int wsaerr = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (wsaerr)
        exit(1);
        
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, MAX_CONNECTIONS);

    std::cout << "Server started on port " << PORT << std::endl;

    while (true) {
        int client_socket = accept(server_socket, NULL, NULL);
        std::cout << "Client connected" << std::endl;

        char buffer[MAX_BUFFER_SIZE];
        while (true) {
            int bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
            if (bytes_received <= 0) break;

            std::cout << "Received from client: " << buffer << std::endl;

            send(client_socket, buffer, bytes_received, 0);
        }

        std::cout << "Client disconnected" << std::endl;
        close(client_socket);
    }

    close(server_socket);
    WSACleanup();

    return 0;
}
