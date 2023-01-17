#include <iostream>
#include <cstring>
#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <unistd.h>

const int PORT = 8080;
const char *SERVER_IP = "127.0.0.1";