

#include "PongNetworking.h"


PongNetworking::PongNetworking(unsigned short port)
: port(port)
{
    destPort = SERVER_PORT;
    udpSock.bind(port);
}


PongNetworking::~PongNetworking()
{
    if(udpSock.getLocalPort())
    {
        udpSock.unbind();
    }
}



bool PongNetworking::WaitForClient()
{
    if(listener.listen(port) != sf::Socket::Done)
    {
        return false;
    }
    
    if(listener.accept(tcpSock) != sf::Socket::Done)
    {
        return false;
    }
    
    dest = tcpSock.getRemoteAddress();
    destPort = tcpSock.getRemotePort();
    tcpSock.disconnect();
    return true;
}

bool PongNetworking::ConnectToHost()
{
    if(dest == sf::IpAddress::None)
    {
        return false;
    }
    if(tcpSock.connect(dest, SERVER_PORT) != sf::Socket::Status::Done)
    {
        return false;
    }
    tcpSock.disconnect();
}

void PongNetworking::SetDest(sf::String ip)
{
    dest = sf::IpAddress(ip);
}

void PongNetworking::SendData(void* data, size_t length)
{
    if( udpSock.send(data, length, dest, destPort) != sf::Socket::Status::Done )
    {
        
    }


}

size_t PongNetworking::RecieveData(void* data, size_t length)
{
    size_t recv = 0;
    if( udpSock.receive(data, length, recv, dest, destPort) != sf::Socket::Status::Done)
    {
        
    }
    
    return recv;
}

sf::UdpSocket& PongNetworking::GetUDPSock()
{
    return udpSock;
}
