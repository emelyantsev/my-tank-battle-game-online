
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
        WAITING,
      //  DISPLAY_RESULT,
      //  DISPLAY_HELP,
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

        float game_time_seconds = 0;
        
        Tank tank_;
        Tank enemy_;


        std::vector<Shell> shells_;
        std::vector<Shell> enemy_shells_;



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


        // Status

        sf::Text status_text_0;
        sf::Text status_text_1;

        sf::Text time_str_;

        void PrepareStatus();
        void UpdateStatus() ;


        // Terrain

        sf::RectangleShape terrain_;


};
