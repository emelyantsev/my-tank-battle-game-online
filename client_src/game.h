
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "../common_src/tank.h"
#include "../common_src/protocol.h"
#include "../common_src/shell.h"

#include <memory>
#include <vector>



class Game {

    enum class State {
        
        MENU,
        RUNNING,
    };



    public:

        Game() ;

        void run() ;

    private:

        void handleInput() ;
        void update() ;
        void render() ;


        void InitNewGame() ;
        void processDataFromServer(sf::Packet& packet);

       
        sf::RenderWindow window_;      
        //sf::Clock clock_;

        State state_ = State::MENU;


        Tank tank_;
        Tank enemy_;


        std::vector<Shell> shells_;
        std::vector<Shell> enemy_shells;



        // ---- Network ---- //

        void StopGameSession();


        sf::TcpSocket socket_;
        int id_;

        sf::Packet in_packet_;
        sf::Packet out_packet_;
 




        // --- Assets ---//

        sf::Font font_;



        // ---- Menu ----// 

        void PrepareMenu() ;
        void RenderMenu() ;


        sf::Text menu_text0_;
        sf::Text menu_text1_;
        sf::Image image0_;
        sf::Texture texture0_;
        sf::Sprite sprite0_;


        // ---------------  Handle FullScreen ----------------- //

        void ToggleFullScreen() ;

        bool is_full_screen = false;
        sf::View view_;
        sf::Vector2i window_position_;

};
