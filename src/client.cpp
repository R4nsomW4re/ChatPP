#include "header.h"

const int MAX_BUFFER_SIZE = 1024;

int main()
{

    static WSADATA wsaData;
    int wsaerr = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (wsaerr)
        exit(1);

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    std::cout << "Connected to server" << std::endl;

    char message[MAX_BUFFER_SIZE] = "Hello, server!";
    send(client_socket, message, strlen(message), 0);

    char buffer[MAX_BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
    buffer[bytes_received] = '\0';

    std::cout << "Server responded: " << buffer << std::endl;

    close(client_socket);
    WSACleanup();

    return 0;
}