#include "game.h"
#include "../common_src/utils.h"
#include <iostream>
#include "../common_src/network_game.h"

#include <thread>

Game::Game() : window_(sf::VideoMode(640, 360), "Tanks Online", sf::Style::Titlebar | sf::Style::Close ) {


    window_.setFramerateLimit(60);
    //window_.setMouseCursorVisible(false);

    view_.setCenter({320, 180});
    view_.setSize({640, 360});
    
    window_.setView(view_);


    if ( !font_.loadFromFile("resources/fonts/ARCADE.ttf") ) {
        
        exit(EXIT_FAILURE);
    }

    PrepareMenu();
    PrepareStatus();

    terrain_.setFillColor(sf::Color(10, 10, 10));
    terrain_.setPosition(20, 40);
    terrain_.setSize({600, 300});

    PrepareWaiting();
    PrepareConnecting();


    tank_ = Tank( sf::Vector2f{100.f, 100.f},   
                    sf::Color(150, 40, 40), 
                    sf::Color(200, 20, 30), 
                    sf::Color(200, 20, 30),
                    nullptr ) ;
    
    enemy_ = Tank( sf::Vector2f{200.f, 200.f}, 
                    sf::Color(50, 50, 250), 
                    sf::Color(0, 0, 250), 
                    sf::Color(0, 0, 250),
                    nullptr ) ;

}


void Game::run() {



    while (window_.isOpen() ) {

        
        handleInput();        
        update();        
        render();
    }

}


void Game::handleInput() {

    
    sf::Event event;

    while (window_.pollEvent(event)) {


        if (event.type == sf::Event::Closed) {

            StopGameSession();    
            window_.close();

        }


        switch (state_) {


            case State::MENU: {


                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        
                        window_.close();
                    }
                    else if (event.key.code == sf::Keyboard::Return) {

                        //InitNewGame();

                        connection_finished = false;
                        state_ = State::ESTABLISHING_CONNECTION;
                        std::thread(&Game::ConnectToServer, this).detach();

                    }
                    else if (event.key.code == sf::Keyboard::F11) {

                        ToggleFullScreen();
                    }
                    else if (event.key.code == sf::Keyboard::F1) {
                       // state_ = State::DISPLAY_HELP;
                    }

                }


                break;
            } 


            case State::DISPLAY_RESULT : {


                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        
                        state_ = State::MENU;
                    }
                    
                    else if (event.key.code == sf::Keyboard::F11) {

                        ToggleFullScreen();
                    }
                }

                break;

            }


            case State::WAITING: {                

                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                         
                         StopGameSession();

                    }
                }
                break;
            }



            case State::RUNNING: {                

                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                         
                         StopGameSession();
                    }

                    
                    if (event.key.code == sf::Keyboard::W ) {


                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ) {

                            //tank_.Move(50);
                            
                            out_packet_ << int(Command::MOVE) << 50;
                        }
                        else {
                            
                            //tank_.Move(25);

                            out_packet_ << int(Command::MOVE) << 25;
                        }
                            
                    }
                    else if (event.key.code == sf::Keyboard::LShift) {

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {

                                //tank_.Move(50);

                                out_packet_ << int(Command::MOVE) << 50;
                        }
                        
                    }

                    else if (event.key.code == sf::Keyboard::S ) {

                        //tank_.Move(-25);

                        out_packet_ << int(Command::MOVE) << -25;
                    }

                    else if (event.key.code == sf::Keyboard::A ) {
                        
                        //tank_.Rotate(-5);

                        out_packet_ << int(Command::ROTATE) << -5.f;

                    }

                    else if (event.key.code == sf::Keyboard::D ) {

                        //tank_.Rotate(5);

                        out_packet_ << int(Command::ROTATE) << 5.f;
                    }    

                    else if (event.key.code == sf::Keyboard::Space ) {

                        if (tank_.GetElapsedTimeForShooting() > 500) {

                            out_packet_ << int(Command::FIRE);
                            tank_.RestartShootingTimer();
                        }
                    }


                    else if (event.key.code == sf::Keyboard::F11) {
                         ToggleFullScreen();
                    }

                }

                else if (event.type == sf::Event::KeyReleased) {


                    if (event.key.code == sf::Keyboard::W ) {

                        //tank_.Stop();
                        out_packet_ << int(Command::STOP) ;
                    }

                    else if (event.key.code == sf::Keyboard::S ) {
                        
                        //tank_.Stop();
                        out_packet_ << int(Command::STOP) ;
                    }

                    else if (event.key.code == sf::Keyboard::LShift) {

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {

                            //tank_.Move(10);
                            out_packet_ << int(Command::MOVE) << 25;
                        }
                        
                    }

                }

                break;
                

            }

        }

    }   

}



void Game::update() {


    if (state_ == State::MENU) {
        
        return ;
    }

    else if (state_ == State::ESTABLISHING_CONNECTION)  {

        sprite1_.rotate(-90*clock_.restart().asSeconds()) ;

        if (!connection_finished) {

            return;
        }

        if (connection_ok) {

            InitNewGame();
        }
        else {

            state_ = State::CONNECTION_FAILED;
            connect_timer_.restart();
        }


    }

    else if (state_ == State::CONNECTION_FAILED) {

        sprite1_.rotate(-90*clock_.restart().asSeconds()) ;

        if (connect_timer_.getElapsedTime().asSeconds() > 5.f) {
            state_ = State::MENU;
        }
    }


    else if (state_ == State::WAITING) {

        sprite1_.rotate(-90*clock_.restart().asSeconds()) ;

        sf::TcpSocket::Status status = socket_.receive(in_packet_);

        //std::cout << "Waiting socket status " << status << std::endl;

        if (status == sf::TcpSocket::Status::Done) {

            processDataFromServer(in_packet_);
            
        }

    }


    else if (state_ == State::DISPLAY_RESULT) {

        if (clock2_.getElapsedTime().asSeconds() > 5) {
            state_ = State::MENU;
        }

        return ;
    }

    else if (state_ == State::RUNNING) {

        out_packet_ << int(Command::FINAL) ;

        socket_.send(out_packet_);
        out_packet_.clear();


        socket_.receive(in_packet_);
        processDataFromServer(in_packet_);

        UpdateStatus();

    }

}


void Game::render() {


    window_.clear();

    if (state_ == State::MENU) {
        
        RenderMenu();     
    }
    else if (state_ == State::WAITING) {

        RenderWaiting();
    }
    else if (state_ == State::ESTABLISHING_CONNECTION) {

        RenderConnecting();
    }
    else if (state_ == State::CONNECTION_FAILED) {
        
        RenderConnectingFailed();
    }

    else if (state_ == State::RUNNING || state_ == State::DISPLAY_RESULT) {


        window_.draw(terrain_);

        
        for (const auto& shell : shells_) {
            shell.Render(window_);
        }


        for (const auto& shell : enemy_shells_) {
            shell.Render(window_);
        }
        


        enemy_.Render(window_);
        tank_.Render(window_);

        window_.draw(status_text_0);
        window_.draw(status_text_1);
        window_.draw(time_str_);

    }


    if (state_ == State::DISPLAY_RESULT) {

        RenderResult();
    }

    window_.display();
}

