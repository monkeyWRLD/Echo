#include <iostream>
#include <WS2tcpip.h>
#include <thread>
#include <sstream>
#include <vector>
#include <Windows.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")


int main()
{   

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        std::cerr << "INITIALIZE WinSock Error : " << err;
        return 0;
    }
    
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
}