#include "game.h"

void Game::PrepareMenu() {

    menu_text0_.setFont(font_) ;
    menu_text1_.setFont(font_) ;

    menu_text0_.setString("Tanks Online");
    menu_text1_.setString("<Enter> to start playing ...");
    //menu_text1_.setString("<Enter> to start playing ...\n<F1> for help");
    
    menu_text0_.setCharacterSize(80);


    menu_text0_.setColor(sf::Color(160, 80, 40)) ;
    menu_text0_.setOrigin( menu_text0_.getGlobalBounds().width / 2 , menu_text0_.getGlobalBounds().height / 2) ;


    menu_text1_.setColor(sf::Color(10, 150, 10)) ;
    menu_text1_.setOrigin( menu_text1_.getGlobalBounds().width / 2 , menu_text1_.getGlobalBounds().height / 2) ;
    
   

    menu_text0_.setPosition( {320, 30} );
    menu_text1_.setPosition( {320, 300} );

    image0_.loadFromFile("resources\\images\\image01.png");

    
    window_.setIcon(image0_.getSize().x, image0_.getSize().y, image0_.getPixelsPtr() );


    texture0_.loadFromImage(image0_);
    sprite0_.setTexture(texture0_);

    sprite0_.setScale(0.5, 0.5);

    sprite0_.setOrigin( sprite0_.getGlobalBounds().width / 2 , sprite0_.getGlobalBounds().height / 2) ;
    sprite0_.setPosition({280, 150}) ;

}


void Game::RenderMenu() {

    window_.draw(sprite0_);
    window_.draw(menu_text0_);
    window_.draw(menu_text1_);

}