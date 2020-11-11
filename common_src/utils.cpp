#include "utils.h"

#define _USE_MATH_DEFINES
#include <math.h>

std::ostream& operator<<(std::ostream &os, const sf::TcpSocket::Status& status) {
    
    
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


std::vector<sf::Vector2f> Collisions::getPoints(const sf::RectangleShape shape) {


    std::vector<sf::Vector2f> vertexes = {
        sf::Vector2f(shape.getSize().x / 2, shape.getSize().y / 2),
        sf::Vector2f(shape.getSize().x / 2, -shape.getSize().y / 2),
        sf::Vector2f(-shape.getSize().x / 2, -shape.getSize().y / 2),
        sf::Vector2f(-shape.getSize().x / 2, shape.getSize().y / 2),
    } ;


    
    float theta = shape.getRotation() * M_PI/180 ;
       
    std::vector<sf::Vector2f> result;
    
    for (const auto& v : vertexes) {

        float tx = v.x * cos(theta) - v.y * sin(theta) ;
        float ty = v.x * sin(theta) + v.y * cos(theta) ;

        result.push_back(sf::Vector2f( shape.getPosition() + sf::Vector2f{tx, ty} ));

    }

    return result;
}




bool Collisions::IsRectangleShapesIntersecting(const sf::RectangleShape& A, const sf::RectangleShape& B) {

    std::vector<sf::Vector2f> pointsA = getPoints(A) ;
    std::vector<sf::Vector2f> pointsB = getPoints(B) ;

    std::vector<sf::Vector2f>* points[] = { &pointsA, &pointsB } ;
    

    for (int i = 0 ; i < 2; ++i) {

        for (int i1 = 0; i1 < points[i]->size(); ++i1)  {

            int i2 = (i1 + 1) % points[i]->size();

            sf::Vector2f  p1 = (*points[i])[i1];
            sf::Vector2f  p2 = (*points[i])[i2];

            sf::Vector2f normal(p2.y - p1.y, p1.x - p2.x);

            float minA = -std::numeric_limits<float>::infinity();
            float maxA = std::numeric_limits<float>::infinity();

            for (const auto& p : pointsA) {

                float projected = normal.x * p.x + normal.y * p.y;

                if (minA == -std::numeric_limits<float>::infinity() || projected < minA) {
                    
                    minA = projected;
                }

                if (maxA == std::numeric_limits<float>::infinity() || projected > maxA) {
                
                    maxA = projected;
                }
            }


            float minB = -std::numeric_limits<float>::infinity();
            float maxB = std::numeric_limits<float>::infinity();


            for (const auto& p : pointsB) {

                float projected = normal.x * p.x + normal.y * p.y;

                if (minB == -std::numeric_limits<float>::infinity() || projected < minB) {
                    
                    minB = projected;
                }

                if (maxB == std::numeric_limits<float>::infinity() || projected > maxB) {
                
                    maxB = projected;
                }
            }

            if (maxA < minB || maxB < minA) {

                return false;
            }


        }

    }

    return true;
}