#include "game.h"

#include <iostream>

void Game::InitNewGame() {


    tank_ = Tank( {100, 100},   
                    sf::Color(150, 40, 40), 
                    sf::Color(200, 20, 30), 
                    sf::Color(200, 20, 30)
            ) ;
    
    enemy_ = Tank( {200, 200}, 
                    sf::Color(50, 50, 250), 
                    sf::Color(0, 0, 250), 
                    sf::Color(0, 0, 250)
            ) ;


    sf::TcpSocket::Status  status = socket_.connect("127.0.0.1", 45000);
    std::cout << status << std::endl;

    status = socket_.receive(in_packet_);
    std::cout << status << std::endl;

    in_packet_ >> id_;

    in_packet_.clear();

    status = socket_.receive(in_packet_);

    processDataFromServer(in_packet_);
}



void Game::processDataFromServer(sf::Packet& packet) {

    sf::Vector2f pos1 ;
    float angle1 ;
    int points1 ;

    packet >> pos1.x >> pos1.y >> angle1 >> points1;


    if (id_ == 0) {

        tank_.SetPosition(pos1);
        tank_.SetRotation(angle1);
        tank_.SetPoints(points1);
    }
    else {

        enemy_.SetPosition(pos1);
        enemy_.SetRotation(angle1);
        enemy_.SetPoints(points1);
    }



    sf::Vector2f pos2 ;
    float angle2 ;
    int points2 ;

    packet >> pos2.x >> pos2.y >> angle2 >> points2;

    if (id_ == 1) {

        tank_.SetPosition(pos2);
        tank_.SetRotation(angle2);
        tank_.SetPoints(points2);
    }
    else {

        enemy_.SetPosition(pos2);
        enemy_.SetRotation(angle2);
        enemy_.SetPoints(points2);
    }


    int shells_size;
    packet >> shells_size;

    //shells_
    





    in_packet_.clear();
}


void Game::StopGameSession() {

    socket_.disconnect();
    state_ = State::MENU ;

}