#pragma once

#include <memory>
#include <SFML\Network.hpp>

struct Client {

    Client(std::shared_ptr<sf::TcpSocket> p_socket);

    std::shared_ptr<sf::TcpSocket> p_socket_;

};