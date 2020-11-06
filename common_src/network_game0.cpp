#include "network_game.h"


NetworkGame::NetworkGame() {

    InitNewGame();

}


void NetworkGame::InitNewGame() {


    std::srand(std::time(nullptr));

    tank0 = Tank(  sf::Vector2f{ static_cast<float>(20. + std::rand() % 150),  static_cast<float>(40. + std::rand() % 300 ) }, 
        sf::Color::Black, sf::Color::Black, sf::Color::Black, this
     );    
    tank1 = Tank(  sf::Vector2f{ static_cast<float>(320. + std::rand() % 150),  static_cast<float>(40. + std::rand() % 300 ) },
        sf::Color::Black, sf::Color::Black, sf::Color::Black, this ) ;

    tank1.Rotate(180);

    game_timer_.restart();

}


void NetworkGame::Update() {


    float time_diff = clock_.restart().asSeconds();


    tank0.Update(time_diff) ;
    tank1.Update(time_diff) ;

    for (auto& shell : tank_shells_0) {

        shell.Update(time_diff);           
    }


    std::list<Shell>::iterator it = tank_shells_0.begin();

    while (it != tank_shells_0.end()) {

        float distance = sqrt(pow(tank0.GetPosition().x - it->GetPosition().x, 2) +  pow(tank0.GetPosition().y - it->GetPosition().y, 2));

        if (distance > 200) {
            it = tank_shells_0.erase(it);
        }
        else {
            ++it;
        }
    }


   

    for (auto& shell : tank_shells_1) {

        shell.Update(time_diff);           
    }


    it = tank_shells_1.begin();

    while (it != tank_shells_1.end()) {

        float distance = sqrt(pow(tank1.GetPosition().x - it->GetPosition().x, 2) +  pow(tank1.GetPosition().y - it->GetPosition().y, 2));


        if (distance > 200) {
            it = tank_shells_1.erase(it);
        }
        else {
            ++it;
        }
    }


    checkShellsTanksCollisions();

}


