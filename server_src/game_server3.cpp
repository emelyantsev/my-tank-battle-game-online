#include "game_server.h"
#include "../common_src/utils.h"
#include "../common_src/protocol.h"

void GameServer::handleMessageFromClient(sf::Packet& packet_, Tank& ref_tank, ShellsList& shells_list, NetworkGame& game) {

    int command;

    packet_ >> command;

    while (command != int(Command::FINAL)) {


        switch (command) {

            case int(Command::MOVE): {

                int speed;
                packet_ >> speed;

                ref_tank.Move(speed);
                
                break;
            }
            case int(Command::ROTATE): {

                float angle;
                packet_ >> angle;

                ref_tank.Rotate(angle);

                break;
            }
            case int(Command::STOP): {

                ref_tank.Stop();
                break;
            }
            case int(Command::FIRE): {

                shells_list.push_back(ref_tank.Fire());
                game.sounds_.push_back( NetworkGame::Sound(0, ref_tank.GetPosition() )) ;
                break;
            }

            default:
                break;

        }


        packet_ >> command;

    }


    packet_.clear();


}



void GameServer::prepareMessageForClients(sf::Packet& packet, NetworkGame& game, bool client0_ok, bool client1_ok) {

    if (!game.stopped) {
        packet << int(ServerCommand::PLAY) ;
    }
    else {
        packet << int(ServerCommand::STOP) ;
    }


    packet << game.tank0.GetPosition().x << game.tank0.GetPosition().y << game.tank0.GetRotation() << game.tank0.GetPoints();
    packet << game.tank1.GetPosition().x << game.tank1.GetPosition().y << game.tank1.GetRotation() << game.tank1.GetPoints();

    packet << (int) game.tank_shells_0.size() ;

    for (auto& shell : game.tank_shells_0) {
        packet << shell.GetPosition().x << shell.GetPosition().y ;
    }

    packet << (int) game.tank_shells_1.size() ;

    for (auto& shell : game.tank_shells_1) {
        packet << shell.GetPosition().x << shell.GetPosition().y ;
    }

    packet << game.game_timer_.getElapsedTime().asSeconds();



    packet << (int) game.obstacles_.size() ;

    for (auto& p_obstacle : game.obstacles_) {
        
        packet << (int) p_obstacle->GetQuality() << p_obstacle->GetPosition().x << p_obstacle->GetPosition().y <<
            p_obstacle->GetSize().x << p_obstacle->GetSize().y ;
        ;
    }


    packet << (int) game.targets_.size() ;

    for (auto& p_target : game.targets_) {


        if (dynamic_cast<const SimpleTarget*>(p_target.get()) != nullptr ) {

            packet << 0;
        }

        else if (dynamic_cast<const AdvancedTarget*>(p_target.get()) != nullptr ) {

            packet << 1;
        }

        else if (dynamic_cast<const StarTarget*>(p_target.get()) != nullptr ) {

            packet << 2;
        }


        packet << p_target->GetPosition().x << p_target->GetPosition().y;

        if (p_target->GetState() == Target::State::ALIVE) {
            
            packet << true;
        }
        else {
            packet << false;
        }


    }


    packet << (int) game.sounds_.size() ;

    for (const auto& sound : game.sounds_) {

        packet << sound.id_ << sound.pos_.x << sound.pos_.y;
    }

    game.sounds_.clear();


    packet << client0_ok << client1_ok;

}; 






bool GameServer::checkWaiting() {

    sf::Packet packet;
    sf::TcpSocket::Status status;

    packet << int(ServerCommand::CHECK_WAITING);

    status = p_waiting_client_->p_socket_->send(packet) ;

    //std::cout << "Waiting socket send status = " << status << std::endl;
    
    if (status != sf::TcpSocket::Status::Done) {

        //std::cout << "Check waiting send false" << std::endl;
        return false;
    }


    packet.clear();


    sf::Packet packet2;

    status = p_waiting_client_->p_socket_->receive(packet2);

    //std::cout << "Waiting socket receive status = " << status << std::endl;

    if (status != sf::TcpSocket::Status::Done) {

        //std::cout << "Check waiting receive false" << std::endl;
        return false;
    }

    int command;

    packet2 >> command;

    if (command == int(Command::FINAL)) {

        std::cout << "Check waiting true" << std::endl;
        
        return true;
    } 
    

    //std::cout << "command " << command << " size " << packet2.getDataSize() << std::endl;

    std::cout << "Check waiting command false" << std::endl;

    return false;
}