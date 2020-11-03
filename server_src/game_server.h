#pragma once

#include <SFML/Network.hpp>

#include <memory>
#include <vector>
#include <list>

#include "client.h"
#include "../common_src/tank.h"

class GameServer {

    public:

        GameServer();

        void run();

        using ShellsList = std::list<Shell>;

    private:

        void handleNewClient(std::shared_ptr<sf::TcpSocket> p_tcp_socket);    
        //void handleGameSession();
        void handleGameSession1();
        void handleMessageFromClient(sf::Packet packet_, Tank& ref_tank, ShellsList& shells_list);

        sf::TcpListener listener_;

        std::vector<Client> clients_;

};


