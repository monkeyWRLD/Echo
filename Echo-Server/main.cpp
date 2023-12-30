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

    //create the socket
    
    sockaddr_in sAddress;
    sAddress.sin_family = AF_INET;
    sAddress.sin_port = htons(6969);
    sAddress.sin_addr.S_un.S_addr = INADDR_ANY;

    SOCKET sServerSocket = socket(AF_INET, SOCK_STREAM, 0);

    int status = bind(sServerSocket, (sockaddr*)&sAddress, sizeof(sAddress));

    if (status == SOCKET_ERROR)
    {
        cleanup(sServerSocket);
    }

    status = listen(sServerSocket, SOMAXCONN);
    if (status == SOCKET_ERROR)
    {
        cleanup(sServerSocket);
    }
    std::cout << "Listening..." << std::endl;
}


void cleanup(SOCKET serversocket) {
        std::cout << "Socket ERROR!, Aborting" << std::endl;
        closesocket(serversocket);
        WSACleanup();
        return;
}