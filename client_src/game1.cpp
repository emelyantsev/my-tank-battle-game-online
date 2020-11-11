#include "game.h"

#include <iostream>


#include "../common_src/protocol.h"

#include "../common_src/utils.h"



void Game::ConnectToServer() {


    sf::TcpSocket::Status  status = socket_.connect("127.0.0.1", 45000);

    std::cout << "Connect status :" << status << std::endl;

    if (status == sf::TcpSocket::Status::Done) {

        connection_finished = true;
        connection_ok = true;
    }
    else {

        connection_finished = true;
        connection_ok = false;

    }

    
}



void Game::InitNewGame() {





    

    sf::TcpSocket::Status status = socket_.receive(in_packet_);
    std::cout << "Receive status:" << status << std::endl;

    in_packet_ >> id_;

    std::cout << "id = " << id_ << std::endl;

    in_packet_.clear();

    state_ = State::WAITING;
    socket_.setBlocking(false);

    //status = socket_.receive(in_packet_);

    //processDataFromServer(in_packet_);
}



void Game::processDataFromServer(sf::Packet& packet) {


    Tank& ref_tank0 =  id_ == 0 ? tank_ : enemy_;
    Tank& ref_tank1 =  id_ == 0 ? enemy_ : tank_;


    std::vector<Shell>& ref_shells0 = id_ == 0 ? shells_ : enemy_shells_;
    std::vector<Shell>& ref_shells1 = id_ == 0 ? enemy_shells_ : shells_ ;


    int command;
    packet >> command;
    
    if (command == int(ServerCommand::CHECK_WAITING) && state_ == State::WAITING) {

        std::cout << "Check waiting command received" << std::endl;

        sf::Packet response_packet;
        response_packet << int(Command::FINAL) ;

        socket_.setBlocking(true);

        auto send_status = socket_.send(response_packet);

        std::cout << "Send status = " << send_status << std::endl;

        return;
    }

    sf::Vector2f pos0;
    float angle0;
    int points0;


    packet >> pos0.x >> pos0.y >> angle0 >> points0;


    ref_tank0.SetPosition(pos0);
    ref_tank0.SetRotation(angle0);
    ref_tank0.SetPoints(points0);



    sf::Vector2f pos1 ;
    float angle1 ;
    int points1 ;

    packet >> pos1.x >> pos1.y >> angle1 >> points1;

    ref_tank1.SetPosition(pos1);
    ref_tank1.SetRotation(angle1);
    ref_tank1.SetPoints(points1);


    int shells0_size;
    packet >> shells0_size;

   // std::cout << "shells 0 size = " << shells0_size << std::endl;

    ref_shells0.clear();
    ref_shells0.reserve(shells0_size);

    for (int i = 0; i < shells0_size; ++i) {

        float sx, sy;

        packet >> sx >> sy;

        ref_shells0.push_back(Shell({sx, sy}, {0,0}, sf::Color::Yellow));
    }
    



    int shells1_size;
    packet >> shells1_size;

  //  std::cout << "shells 1 size = " << shells1_size << std::endl;

    ref_shells1.clear();
    ref_shells1.reserve(shells1_size);

    for (int i = 0; i < shells1_size; ++i) {

        float sx, sy;
        packet >> sx >> sy;

        ref_shells1.push_back(Shell({sx, sy}, {0,0}, sf::Color::Yellow));
    }


    packet >> game_time_seconds;


    in_packet_.clear();



    if (command == int(ServerCommand::STOP)) {

        state_ = State::DISPLAY_RESULT;

        PrepareResult();

        socket_.disconnect();
    }
    else if (command == int(ServerCommand::PLAY) && state_ == State::WAITING) {

        socket_.setBlocking(true);
        state_ = State::RUNNING;
    }

    
}


void Game::StopGameSession() {

    socket_.disconnect() ;
    state_ = State::MENU ;

    socket_.setBlocking(true);

    std::cout << "game session stopped" << std::endl;
}