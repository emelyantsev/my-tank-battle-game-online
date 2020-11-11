#pragma once



enum class Command {

    MOVE = 0,
    STOP = 1,
    ROTATE = 2,
    FIRE = 3,
    FINAL = -1,
};


enum class ServerCommand {
    
    PLAY = 0,
    STOP = 1,
    CHECK_WAITING = 2,
};
