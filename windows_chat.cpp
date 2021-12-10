
// Seak Yith

#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>
#pragma comment(lib, "ws2_32.lib")


void send1(const char* message)
{
    using namespace std;
    const char* srcIP = "127.0.0.1";
    const char* destIP = "127.0.0.1";
    sockaddr_in dest;
    sockaddr_in local;
    WSAData data;
    WSAStartup(MAKEWORD(2, 2), &data);

    local.sin_family = AF_INET;
    inet_pton(AF_INET, srcIP, &local.sin_addr.s_addr);
    local.sin_port = htons(0);

    dest.sin_family = AF_INET;
    inet_pton(AF_INET, destIP, &dest.sin_addr.s_addr);
    dest.sin_port = htons(3514);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bind(s, (sockaddr*)&local, sizeof(local));

    sendto(s, message, strlen(message), 0, (sockaddr*)&dest, sizeof(dest));

    closesocket(s);
    WSACleanup();
}
void recieve1()
{
    using namespace std;
    const char* srcIP = "127.0.0.1";
    const char* destIP = "127.0.0.1";
    sockaddr_in dest;
    sockaddr_in local;
    WSAData data;
    WSAStartup(MAKEWORD(2, 2), &data);

    local.sin_family = AF_INET;
    inet_pton(AF_INET, srcIP, &local.sin_addr.s_addr);
    local.sin_port = htons(0);

    dest.sin_family = AF_INET;
    inet_pton(AF_INET, destIP, &dest.sin_addr.s_addr);
    dest.sin_port = htons(3515);

    char buffer[100];
    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bind(s, (sockaddr*)&local, sizeof(local));
    int size = sizeof(dest);
    int n;
    n = recvfrom(s, buffer, 100, 0, (sockaddr*)&dest, &size);
    buffer[n] = '\O';
    cout << "Server: " << buffer << endl;
    closesocket(s);
    WSACleanup();

}


int main() {
    std::cout << "Enter the message to send: ";
    std::string str;
    std::cin >> str;
    const char* pkt = str.c_str();

    std::thread client(send1, pkt);
    std::thread server(recieve1);
    client.join();
    server.join();


    return 0;
}