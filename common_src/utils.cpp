#include "utils.h"

std::ostream& operator<<(std::ostream &os, const sf::TcpSocket::Status& status) 
{
    
    switch (status) {

        case sf::TcpSocket::Status::Disconnected :
            os << "Disconnected" ;
            break;
        
        case sf::TcpSocket::Status::Done :
            os << "Done" ;
            break;
        
        case sf::TcpSocket::Status::Error :
            os << "Error" ;
            break;

        case sf::TcpSocket::Status::NotReady :
            os << "Not ready" ;
            break;

        case sf::TcpSocket::Status::Partial :
            os << "Partial" ;
            break;

        default:
            break;

    }


    return os;
}