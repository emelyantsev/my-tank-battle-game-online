#include "network_game.h"

#include "utils.h"


void NetworkGame::checkShellsTanksCollisions() {


    std::list<Shell>::iterator it_shells = tank_shells_0.begin();

    while (it_shells != tank_shells_0.end()) {


        //if (tank1.GetBounds().contains( it_shells->GetPosition() ) ) {

        if (Collisions::IsRectangleShapePointIntersecting(tank1.getCorpusRef(), it_shells->GetPosition())) {

            
            tank0.UpdatePoints(1);

            it_shells = tank_shells_0.erase(it_shells);


            sounds_.push_back( NetworkGame::Sound(1, tank1.GetPosition() )) ;

            continue;
        } 

        
        ++it_shells;

    }



    it_shells = tank_shells_1.begin();

    while (it_shells != tank_shells_1.end()) {


      //  if (tank0.GetBounds().contains( it_shells->GetPosition() ) ) {

        if (Collisions::IsRectangleShapePointIntersecting(tank0.getCorpusRef(), it_shells->GetPosition())) {

            
            tank1.UpdatePoints(1);
            
            it_shells = tank_shells_1.erase(it_shells);

            sounds_.push_back( NetworkGame::Sound(1, tank1.GetPosition() )) ;

            continue;
        } 
        
        ++it_shells;
    }



}




void NetworkGame::checkShellsObstaclesCollisions() {


    std::list<Shell>::iterator it_shells = tank_shells_0.begin();

    while (it_shells != tank_shells_0.end()) {

        bool it_shells_increased = false;

        auto it_obstacles = obstacles_.begin();

        while (it_obstacles != obstacles_.end() ) {


            if ( (*it_obstacles)->GetBounds().contains( it_shells->GetPosition()  ) 
                    && ( (*it_obstacles)->GetQuality() == Obstacle::Quality::UNPENETRABLE ) ) {


                it_shells = tank_shells_0.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_obstacles;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }


    it_shells = tank_shells_1.begin();

    while (it_shells != tank_shells_1.end()) {

        bool it_shells_increased = false;

        auto it_obstacles = obstacles_.begin();

        while (it_obstacles != obstacles_.end() ) {


            if ( (*it_obstacles)->GetBounds().contains( it_shells->GetPosition()  ) 
                    && ( (*it_obstacles)->GetQuality() == Obstacle::Quality::UNPENETRABLE ) ) {


                it_shells = tank_shells_1.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_obstacles;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }



}



void NetworkGame::checkShellsTargetsCollisions() {


    std::list<Shell>::iterator it_shells = tank_shells_0.begin();

    while (it_shells != tank_shells_0.end()) {

        bool it_shells_increased = false;

        auto it_targets = targets_.begin();

        while (it_targets != targets_.end() ) {


            if ( (*it_targets)->GetBounds().contains( it_shells->GetPosition()  ) ) {


                if ( (*it_targets)->GetState() == Target::State::ALIVE) {    

                    (*it_targets)->Blow();
                    tank0.UpdatePoints(1);

                }


                it_shells = tank_shells_0.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_targets;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }



    it_shells = tank_shells_1.begin();


    while (it_shells != tank_shells_1.end()) {

        bool it_shells_increased = false;

        auto it_targets = targets_.begin();

        while (it_targets != targets_.end() ) {


            if ( (*it_targets)->GetBounds().contains( it_shells->GetPosition()  ) ) {

                if ( (*it_targets)->GetState() == Target::State::ALIVE) {    

                    (*it_targets)->Blow();
                    tank1.UpdatePoints(1);

                }

                it_shells = tank_shells_1.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_targets;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }


}