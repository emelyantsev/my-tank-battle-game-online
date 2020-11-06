#include "game_server.h"

#include "game_server.h"
#include "../common_src/network_game.h"

#include "../common_src/utils.h"

#include <iostream>

void GameServer::handleGameSession() {


    Client& client0 = clients_[clients_.size() - 2 ];
    Client& client1 = clients_[clients_.size() - 1 ];

    sf::TcpSocket::Status status0;
    sf::TcpSocket::Status status1;

    
    NetworkGame game;


    sf::Packet out_message;

    
    prepareMessageForClients(out_message, game);


    status0 = client0.p_socket_->send(out_message);
    std::cout << "Client 0 send status " << status0 << std::endl;

    status1 = client1.p_socket_->send(out_message);
    std::cout << "Client 1 send status " << status1 << std::endl;



    sf::Packet in_message0;
    sf::Packet in_message1;


    while (true) {


        in_message0.clear();
        in_message1.clear();


        if (status0 == sf::TcpSocket::Status::Done) {
        
            status0 = client0.p_socket_->receive(in_message0);

            std::cout << "Client 0 receive status " << status0 << std::endl;

            if (status0 == sf::TcpSocket::Status::Done) {

                handleMessageFromClient(in_message0, game.tank0, game.tank_shells_0);
            }
        }


        if (status1 == sf::TcpSocket::Status::Done) {

            status1 = client1.p_socket_->receive(in_message1);
            std::cout << "Client 1 receive status " << status1 << std::endl;

            if (status1 == sf::TcpSocket::Status::Done) {
                handleMessageFromClient(in_message1, game.tank1, game.tank_shells_1);
            }
        }


        game.Update();

        out_message.clear();

        prepareMessageForClients(out_message, game);


        if (status0 == sf::TcpSocket::Status::Done) {

            status0 = client0.p_socket_->send(out_message);
            std::cout << "Client 0 send status " << status0 << std::endl;
        }


        if (status1 == sf::TcpSocket::Status::Done) {
            
            status1 = client1.p_socket_->send(out_message);
            std::cout << "Client 1 send status " << status1 << std::endl;
        }


        if (status0 != sf::TcpSocket::Status::Done && status1 != sf::TcpSocket::Status::Done) {
            break;
        }
    }

    std::cout << "Ending game session" << std::endl;

}








