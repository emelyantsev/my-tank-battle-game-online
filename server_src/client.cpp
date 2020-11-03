#include "client.h"

Client::Client(std::shared_ptr<sf::TcpSocket> p_socket) : p_socket_(p_socket) {};

