#pragma once

#include "tank.h"
#include "shell.h"

#include <list>

struct NetworkGame {


    NetworkGame();

    void InitNewGame();

    void Update();

    void checkShellsTanksCollisions();


    Tank tank0;
    Tank tank1;

    std::list<Shell> tank_shells_0;
    std::list<Shell> tank_shells_1;

    sf::Clock clock_;

    sf::Clock game_timer_;

};