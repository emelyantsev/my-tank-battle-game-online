#include "game_server.h"

#include "game_server.h"
#include "../common_src/network_game.h"

#include "../common_src/utils.h"

#include <iostream>



void GameServer::handleGameSession(std::unique_ptr<Client> client0_, std::unique_ptr<Client> client1_) {


    Client& client0 = (*client0_);
    Client& client1 = (*client1_);

    sf::TcpSocket::Status status0;
    sf::TcpSocket::Status status1;

    bool client0_ok = true;
    bool client1_ok = true;

    
    NetworkGame game;


    sf::Packet out_message;

    
    prepareMessageForClients(out_message, game);


    status0 = client0.p_socket_->send(out_message);
    //std::cout << "Client 0 send status " << status0 << std::endl;

    status1 = client1.p_socket_->send(out_message);
    //std::cout << "Client 1 send status " << status1 << std::endl;



    sf::Packet in_message0;
    sf::Packet in_message1;


    while (!game.stopped) {


        in_message0.clear();
        in_message1.clear();


        if (status0 == sf::TcpSocket::Status::Done) {
        
            status0 = client0.p_socket_->receive(in_message0);

            if (status0 == sf::TcpSocket::Status::Done) {

                handleMessageFromClient(in_message0, game.tank0, game.tank_shells_0, game);
            }
            else {
                std::cout << "Client 0 receive status " << status0 << std::endl;
                client0_ok = false;
            }
        }


        if (status1 == sf::TcpSocket::Status::Done) {

            status1 = client1.p_socket_->receive(in_message1);
            
            if (status1 == sf::TcpSocket::Status::Done) {
                handleMessageFromClient(in_message1, game.tank1, game.tank_shells_1, game);
            }
            else {
                std::cout << "Client 1 receive status " << status1 << std::endl;
                client1_ok = false;
            }
        }


        game.Update();

        out_message.clear();




        prepareMessageForClients(out_message, game, client0_ok, client1_ok);


        if (status0 == sf::TcpSocket::Status::Done) {

            status0 = client0.p_socket_->send(out_message);

            if (status0 != sf::TcpSocket::Status::Done) {

                std::cout << "Client 0 send status " << status0 << std::endl;
                client0_ok = false;
            }
        }


        if (status1 == sf::TcpSocket::Status::Done) {
            
            status1 = client1.p_socket_->send(out_message);

            if (status1 != sf::TcpSocket::Status::Done) {

                std::cout << "Client 1 send status " << status1 << std::endl;
                client1_ok = false;
            }
        }


        if (status0 != sf::TcpSocket::Status::Done && status1 != sf::TcpSocket::Status::Done) {
            break;
        }
    }

    std::cout << "Ending game session" << std::endl;

}