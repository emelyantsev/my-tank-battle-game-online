#include "game.h"


void Game::ToggleFullScreen() {

    if (!is_full_screen) {

        window_position_ = window_.getPosition();

        is_full_screen = true;
        window_.create( sf::VideoMode(1920, 1080), "Tanks Online", sf::Style::Fullscreen) ;

    }
    else {

        is_full_screen = false;
        window_.create( sf::VideoMode(640, 360), "Tanks Online", sf::Style::Titlebar | sf::Style::Close) ;
        window_.setIcon(image0_.getSize().x, image0_.getSize().y, image0_.getPixelsPtr() );
        window_.setPosition(window_position_);
    }

    window_.setView(view_);
    window_.setFramerateLimit(60);
    //window_.setMouseCursorVisible(false);

    

}



void Game::PrepareResult() {


    result_terrain_.setFillColor(sf::Color(10, 20, 10, 200));
    result_terrain_.setPosition(5, 5);
    result_terrain_.setSize({630, 350});


    result_text4_.setFont(font_);

    Result result_ = tank_.GetPoints() > enemy_.GetPoints() ? Result::WIN :
                    tank_.GetPoints() == enemy_.GetPoints() ? Result::DRAW : Result::LOST;

    
    std::string result_str_;

    switch (result_) {

        case (Result::WIN) : {

            result_str_ = std::string("You win with score ") + std::to_string(tank_.GetPoints()) + " : " + std::to_string(enemy_.GetPoints() );
            result_text4_.setColor(sf::Color::Green) ;
            break;
        }

        case (Result::LOST) : {

            result_str_ = std::string("You lost with score ") + std::to_string(tank_.GetPoints()) + " : " + std::to_string(enemy_.GetPoints() );
            result_text4_.setColor(sf::Color::Red) ;
            break;
        }

        case (Result::DRAW) : {
            
            result_str_ = std::string("The game ended in a draw ") + std::to_string(tank_.GetPoints()) + " : " + std::to_string(enemy_.GetPoints() );
            result_text4_.setColor(sf::Color::Blue) ;
            break;
        }
    }


    result_text4_.setString(result_str_) ;
    result_text4_.setOrigin( result_text4_.getGlobalBounds().width / 2 , result_text4_.getGlobalBounds().height / 2) ;
    result_text4_.setPosition( { 320, 180} ) ;

    clock2_.restart();
}


void Game::RenderResult() {

    window_.draw(result_terrain_);
    window_.draw(result_text4_);
}



void Game::PrepareWaiting() {

    waiting_text4_.setFont(font_);
    waiting_text4_.setString("Waiting for an opponent") ;
    waiting_text4_.setOrigin( waiting_text4_.getGlobalBounds().width / 2 , waiting_text4_.getGlobalBounds().height / 2) ;
    waiting_text4_.setPosition( { 320, 280} ) ;
    waiting_text4_.setColor(sf::Color(120, 120, 120)) ;


    image1_.loadFromFile("resources\\images\\image02.png");

    texture1_.loadFromImage(image1_);
    sprite1_.setTexture(texture1_);

    sprite1_.setOrigin( 256 , 256) ;

    sprite1_.setScale(0.1, 0.1);
    sprite1_.setColor(sf::Color(120, 120, 120)) ;

    sprite1_.setPosition({320, 180}) ;

}



void Game::RenderWaiting() {

    window_.draw(sprite1_);
    window_.draw(waiting_text4_) ;
}

void Game::PrepareConnecting() {

    connecting_text5_.setFont(font_);
    connecting_text5_.setString("Connecting to server") ;
    connecting_text5_.setOrigin( connecting_text5_.getGlobalBounds().width / 2 , connecting_text5_.getGlobalBounds().height / 2) ;
    connecting_text5_.setPosition( { 320, 280} ) ;
    connecting_text5_.setColor(sf::Color(120, 120, 120)) ;


    connecting_failed_text5_.setFont(font_);
    connecting_failed_text5_.setString("Connection failed") ;
    connecting_failed_text5_.setOrigin( connecting_failed_text5_.getGlobalBounds().width / 2 , connecting_failed_text5_.getGlobalBounds().height / 2) ;
    connecting_failed_text5_.setPosition( { 320, 280} ) ;
    connecting_failed_text5_.setColor(sf::Color(120, 120, 120)) ;

}


void Game::RenderConnecting() {

    window_.draw(sprite1_);
    window_.draw(connecting_text5_) ;
}

void Game::RenderConnectingFailed() {

    window_.draw(sprite1_);
    window_.draw(connecting_failed_text5_) ;
}


void Game::LoadSounds() {
    

    buffer0_.loadFromFile("resources\\sounds\\aexp2.wav");
    buffer1_.loadFromFile("resources\\sounds\\Gun_Silencer.wav");

    //buffer0_.loadFromMemory(&aexp2_wav, aexp2_wav_len);
    //buffer1_.loadFromMemory(&Gun_Silencer_wav, Gun_Silencer_wav_len);

    sound0_.setBuffer(buffer0_);
    sound1_.setBuffer(buffer1_);
}