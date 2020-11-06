#include "game_server.h"
#include "../common_src/utils.h"
#include "../common_src/protocol.h"

void GameServer::handleMessageFromClient(sf::Packet& packet_, Tank& ref_tank, ShellsList& shells_list) {

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
                break;
            }

            default:
                break;

        }


        packet_ >> command;

    }


    packet_.clear();


}



void GameServer::prepareMessageForClients(sf::Packet& packet, NetworkGame& game) {


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



}; 