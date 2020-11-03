


#include "game_server.h"

#include <iostream>
#include <memory>
#include <thread>

#include "../common_src/utils.h"

GameServer::GameServer() {

    clients_.reserve(16);
}

void GameServer::run() {


    if (listener_.listen(45000) != sf::Socket::Done) {

        std::cout << "Error listening" << std::endl;    
        exit(EXIT_FAILURE);
    }
    else {

        std::cout << "Start listening OK" << std::endl;
    }

    while (true) {


        std::shared_ptr<sf::TcpSocket> p_new_socket(new sf::TcpSocket);

        if (listener_.accept(*p_new_socket) != sf::Socket::Done) {
            
            std::cout << "Error accepting new client" << std::endl;  

            exit(EXIT_FAILURE);
        }
        else {
            std::cout << "New client connected" << std::endl;
        }

        //handleNewClient(p_new_socket);

        std::thread(&GameServer::handleNewClient, this, p_new_socket).detach();
        
    }

}


void GameServer::handleNewClient(std::shared_ptr<sf::TcpSocket> p_tcp_socket) {

    clients_.push_back(Client(p_tcp_socket)) ;

    sf::Packet packet;
    sf::TcpSocket::Status status;

    if (clients_.size() % 2 == 0) {

        
        packet << 1;

        status = p_tcp_socket->send(packet) ;

        std::cout << "Send id " << 1 << " status = " << status << std::endl;

        std::thread(&GameServer::handleGameSession1, this).detach();
    }
    else {

        packet << 0;

        status = p_tcp_socket->send(packet) ;

        std::cout << "Send id " << 0 << " status = " << status << std::endl;
    }



}