#include "client.h"
#include <iostream>

Client::Client(std::shared_ptr<sf::TcpSocket> p_socket) : p_socket_(p_socket) {};

Client::~Client() {
    std::cout << "Client " << p_socket_->getRemoteAddress() << ":" << p_socket_->getRemotePort() << " destroyed" << std::endl;
    p_socket_->disconnect();
}