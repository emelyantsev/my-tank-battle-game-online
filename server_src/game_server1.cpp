


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
            std::cout << p_new_socket->getRemoteAddress() << ":" << p_new_socket->getRemotePort() << std::endl;
        }

        //handleNewClient(p_new_socket);

        std::thread(&GameServer::handleNewClient1, this, p_new_socket).detach();
        
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

        std::thread(&GameServer::handleGameSession, this).detach();
    }
    else {

        packet << 0;

        status = p_tcp_socket->send(packet) ;

        std::cout << "Send id " << 0 << " status = " << status << std::endl;
    }



}



void GameServer::handleNewClient1(std::shared_ptr<sf::TcpSocket> p_tcp_socket) {


    mtx_.lock();

    if (p_waiting_client_ == nullptr) {

        p_waiting_client_ = std::unique_ptr<Client>(new Client(p_tcp_socket) );

        sf::Packet packet;
        sf::TcpSocket::Status status;

        packet << 0;
        status = p_tcp_socket->send(packet) ;

        std::cout << "Send id " << 0 << " status = " << status << std::endl;

    }

    else {

        std::unique_ptr<Client> p_new_client( new Client(p_tcp_socket) ) ;

        sf::Packet packet;
        sf::TcpSocket::Status status;

        packet << 1;
        status = p_tcp_socket->send(packet) ;
        std::cout << "Send id " << 1 << " status = " << status << std::endl;


        std::thread( &GameServer::handleGameSession1, this, 
                std::move(p_waiting_client_),
                std::move(p_new_client)
                ).detach();

        p_waiting_client_ = nullptr;

    }

    mtx_.unlock();

    



}