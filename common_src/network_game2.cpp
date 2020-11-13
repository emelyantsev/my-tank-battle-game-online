#include "network_game.h"

sf::FloatRect NetworkGame::getField() {
     return sf::FloatRect({20, 40}, {600, 300})  ;
};



void NetworkGame::spawnItems() {

    //std::srand(std::time(nullptr));


    while (obstacles_.size() < 3) {


        std::shared_ptr<Obstacle> p_new_obstacle(new WaterObstacle(
            
                { static_cast<float>(40. + std::rand() % 580),  static_cast<float>(60. + std::rand() % 280 ) } ,

                std::rand() % 2 == 0 ? 
                sf::Vector2f{20.f + static_cast<float>(std::rand() % 10) , 40.f + static_cast<float>(std::rand() % 20)} :
                sf::Vector2f{40.f + static_cast<float>(std::rand() % 20), 20.f + static_cast<float>(std::rand() % 10) }   
                ) 
        );


        if (p_new_obstacle->GetBounds().intersects(tank0.GetBounds() ) || p_new_obstacle->GetBounds().intersects(tank1.GetBounds() )) {
            continue;
        }

        obstacles_.push_back(p_new_obstacle);
        
    }



    while (obstacles_.size() < 6) {


        std::shared_ptr<Obstacle> p_new_obstacle(new SolidObstacle(
            
                { static_cast<float>(40. + std::rand() % 580),  static_cast<float>(60. + std::rand() % 280 ) } ,
                std::rand() % 2 == 0 ? 
                sf::Vector2f{20.f + static_cast<float>(std::rand() % 10) , 40.f + static_cast<float>(std::rand() % 20)} :
                sf::Vector2f{40.f + static_cast<float>(std::rand() % 20), 20.f + static_cast<float>(std::rand() % 10) }   
                ) 
        );


        if (p_new_obstacle->GetBounds().intersects(tank0.GetBounds() ) || p_new_obstacle->GetBounds().intersects(tank1.GetBounds() )) {
            continue;
        }

        obstacles_.push_back(p_new_obstacle);
        
    }



    for (int i = 0 ; i < 8 ; ++i) {

        targets_.push_back( std::shared_ptr<Target>(new SimpleTarget(  { static_cast<float>(20. + std::rand() % 600),  static_cast<float>(40. + std::rand() % 300 ) }  )  ) );
    }

    for (int i = 0 ; i < 4 ; ++i) {

        targets_.push_back( std::shared_ptr<Target>(new AdvancedTarget(  { static_cast<float>(20. + std::rand() % 600),  static_cast<float>(40. + std::rand() % 300  ) }  )  ) );
    }


    for (int i = 0 ; i < 2 ; ++i) {

        targets_.push_back( std::shared_ptr<Target>(new StarTarget(  { static_cast<float>(20. + std::rand() % 600),  static_cast<float>(40. + std::rand() % 300  ) }  )  ) );
    }




}



NetworkGame::Sound::Sound(int id, sf::Vector2f pos) : id_(id) , pos_(pos) {} ;