#include "network_game.h"


void NetworkGame::checkShellsTanksCollisions() {


    std::list<Shell>::iterator it_shells = tank_shells_0.begin();

    while (it_shells != tank_shells_0.end()) {


        if (tank1.GetBounds().contains( it_shells->GetPosition() ) ) {

            
            tank0.UpdatePoints(1);

            it_shells = tank_shells_0.erase(it_shells);

            continue;
        } 

        
        ++it_shells;

    }



    it_shells = tank_shells_1.begin();

    while (it_shells != tank_shells_1.end()) {


        if (tank0.GetBounds().contains( it_shells->GetPosition() ) ) {

            
            tank1.UpdatePoints(1);
            
            it_shells = tank_shells_1.erase(it_shells);

            continue;
        } 
        
        ++it_shells;
    }



}

