#pragma once

#include "tank.h"
#include "shell.h"
#include "obstacle.h"
#include "target.h"

#include <list>
#include <vector>

struct NetworkGame {


    NetworkGame();

    void InitNewGame();

    void Update();

    void checkShellsTanksCollisions();
    void checkShellsObstaclesCollisions() ;
    void checkShellsTargetsCollisions() ;

    sf::FloatRect getField();


    Tank tank0;
    Tank tank1;

    std::list<Shell> tank_shells_0;
    std::list<Shell> tank_shells_1;


    sf::Clock clock_;

    sf::Clock game_timer_;
    float game_duration_ = 120.f;

    std::vector<std::shared_ptr<Obstacle>> obstacles_;
    std::list<std::shared_ptr<Target>> targets_ ;

    bool stopped = false;

    void spawnItems() ;


    struct Sound {

        Sound(int id, sf::Vector2f pos);

        int id_;
        sf::Vector2f pos_;
    };


    std::vector<Sound> sounds_;
    
};