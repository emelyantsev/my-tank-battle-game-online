
#include "game_server.h"
#include "../common_src/tank.h"
#include "../common_src/utils.h"
#include "../common_src/protocol.h"
#include <iostream>

void GameServer::handleGameSession() {

    Client& client1 = clients_[clients_.size() - 2 ];
    Client& client2 = clients_[clients_.size() - 1 ];

    sf::TcpSocket::Status status1;
    sf::TcpSocket::Status status2;
    
    Tank tank1( {100, 200});    
    Tank tank2( {400, 200});


    

    sf::Packet message1;
    message1 << 1 << tank1.GetPosition().x << tank1.GetPosition().y << tank1.GetRotation() << tank1.GetPoints();
    message1 << tank2.GetPosition().x << tank2.GetPosition().y << tank2.GetRotation() << tank2.GetPoints();


    sf::Packet message2;
    message2 << 2 << tank1.GetPosition().x << tank1.GetPosition().y << tank1.GetRotation() << tank1.GetPoints();
    message2 << tank2.GetPosition().x << tank2.GetPosition().y << tank2.GetRotation() << tank2.GetPoints();


    status1 = client1.p_socket_->send(message1);
    std::cout << "Client 1 send status " << status1 << std::endl;


    status2 = client2.p_socket_->send(message2);
    std::cout << "Client 2 send status " << status2 << std::endl;


    sf::Clock clock;


    while (true) {


        message1.clear();
        message2.clear();


        if (status1 == sf::TcpSocket::Status::Done) {
        
            status1 = client1.p_socket_->receive(message1);
            std::cout << "Client 1 receive status " << status1 << std::endl;

            if (status1 == sf::TcpSocket::Status::Done) {
                handleMessageFromClient(message1, tank1);
            }
        }


        if (status2 == sf::TcpSocket::Status::Done) {

            status2 = client2.p_socket_->receive(message2);
            std::cout << "Client 2 receive status " << status2 << std::endl;

            if (status2 == sf::TcpSocket::Status::Done) {
                handleMessageFromClient(message2, tank2);
            }
        }


        float time_diff = clock.restart().asSeconds();

        tank1.Update(time_diff);
        tank2.Update(time_diff);


        sf::Packet message;

        message << tank1.GetPosition().x << tank1.GetPosition().y << tank1.GetRotation() << tank1.GetPoints();
        message << tank2.GetPosition().x << tank2.GetPosition().y << tank2.GetRotation() << tank2.GetPoints();


         if (status1 == sf::TcpSocket::Status::Done) {

            status1 = client1.p_socket_->send(message);
            std::cout << "Client 1 send status " << status1 << std::endl;
         }


        if (status2 == sf::TcpSocket::Status::Done) {
            
            status2 = client2.p_socket_->send(message);
            std::cout << "Client 2 send status " << status2 << std::endl;
        }


        if (status1 != sf::TcpSocket::Status::Done && status2 != sf::TcpSocket::Status::Done) {
            break;
        }
    }

    std::cout << "Ending game session" << std::endl;

};


