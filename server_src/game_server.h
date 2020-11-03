#pragma once

#include <SFML/Network.hpp>

#include <memory>
#include <vector>

#include "client.h"
#include "../common_src/tank.h"

class GameServer {

    public:

        GameServer();

        void run();

    private:

        void handleNewClient(std::shared_ptr<sf::TcpSocket> p_tcp_socket);    
        void handleGameSession();
        void handleGameSession1();
        void handleMessageFromClient(sf::Packet packet_, Tank& ref_tank);

        sf::TcpListener listener_;

        std::vector<Client> clients_;

};


