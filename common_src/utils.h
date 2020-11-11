#pragma once

#include <SFML\Network.hpp>
#include <SFML\Graphics.hpp>

#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream &os, const sf::TcpSocket::Status& status) ;


namespace Collisions {


    std::vector<sf::Vector2f> getPoints(const sf::RectangleShape shape) ;

    bool IsRectangleShapesIntersecting(const sf::RectangleShape& A, const sf::RectangleShape& B);


}