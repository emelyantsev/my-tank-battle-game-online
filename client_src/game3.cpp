#include "game.h"


void Game::ToggleFullScreen() {

    if (!is_full_screen) {

        window_position_ = window_.getPosition();

        is_full_screen = true;
        window_.create( sf::VideoMode(1920, 1080), "Tanks", sf::Style::Fullscreen) ;

    }
    else {

        is_full_screen = false;
        window_.create( sf::VideoMode(640, 360), "Tanks", sf::Style::Titlebar | sf::Style::Close) ;
        window_.setIcon(image0_.getSize().x, image0_.getSize().y, image0_.getPixelsPtr() );
        window_.setPosition(window_position_);
    }

    window_.setView(view_);
    window_.setFramerateLimit(60);
    window_.setMouseCursorVisible(false);

    

}