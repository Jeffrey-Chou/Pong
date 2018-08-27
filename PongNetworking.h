

#pragma once

#include <SFML/Network.hpp>

class PongNetworking
{
public:
    
    PongNetworking(unsigned short port = 42069);
    ~PongNetworking();

    bool WaitForClient();
    bool ConnectToHost();
    void SetDest(sf::String ip);
    
    sf::UdpSocket& GetUDPSock();
    
    void SendData(void* data, size_t length);
    size_t RecieveData(void* data, size_t length);
    
    static const unsigned short SERVER_PORT = 42069;
    
private:
    unsigned short port;
    sf::UdpSocket udpSock;
    sf::IpAddress dest;
    unsigned short destPort;
    sf::TcpSocket tcpSock;
    sf::TcpListener listener;
};
