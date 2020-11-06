#pragma once

#include <SFML/Network.hpp>

#include <memory>
#include <vector>
#include <list>

#include "client.h"
#include "../common_src/tank.h"
#include "../common_src/network_game.h"


class GameServer {

    public:

        GameServer();

        void run();

        using ShellsList = std::list<Shell>;

    private:

        void handleNewClient(std::shared_ptr<sf::TcpSocket> p_tcp_socket);    
        void handleGameSession();
        void handleMessageFromClient(sf::Packet& packet_, Tank& ref_tank, ShellsList& shells_list);
        void prepareMessageForClients(sf::Packet& packet_, NetworkGame& game); 

        sf::TcpListener listener_;

        std::vector<Client> clients_;

};


