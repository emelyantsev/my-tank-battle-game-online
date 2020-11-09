#include "tank.h"
#include "utils.h"

#define _USE_MATH_DEFINES
#include <math.h>


#include <iostream>


#include "network_game.h"

Tank::Tank(sf::Vector2f position, sf::Color color, sf::Color color1, sf::Color color2, NetworkGame * p_game) : p_game_(p_game) {

    corpus_.setSize( {20,10} );
    corpus_.setOrigin( {10,5} );
    corpus_.setFillColor(color);
    corpus_.setPosition(position);

    tower_.setRadius(5);
    tower_.setOrigin( {5, 5} );
    tower_.setPosition(position);
    tower_.setFillColor( color1 );
    
    gun_.setSize( {15, 2} );
    gun_.setOrigin( {0, 1} );
    gun_.setPosition(position);
    gun_.setFillColor( color2 );
}


void Tank::Render(sf::RenderWindow& l_window) {

    l_window.draw(corpus_);
    l_window.draw(tower_);
    l_window.draw(gun_);    
}


void Tank::Move(int speed) {
    
    speed_ = speed;
}

void Tank::Stop() {
    
    speed_ = 0;
}

void Tank::Rotate(float angle) {


    sf::RectangleShape new_corpus(corpus_);
    new_corpus.rotate(angle);


    if (   &(p_game_->tank0) != this   &&         
           Collisions::IsRectangleShapesIntersecting(p_game_->tank0.corpus_ , new_corpus ) ) 
    {

        Stop();
        return;
    }

    if (   &(p_game_->tank1) != this   &&         
           Collisions::IsRectangleShapesIntersecting(p_game_->tank1.corpus_ , new_corpus ) ) 
    {

        Stop();
        return;
    }
    
    corpus_.rotate(angle);
    gun_.rotate(angle);
    angle_ = corpus_.getRotation();
}


void Tank::Update(float time_diff) {

    float vx = cos (angle_ * M_PI/180) * speed_ * time_diff;
    float vy = sin (angle_ * M_PI/180) * speed_ * time_diff;

    sf::Vector2f new_position = GetPosition() + sf::Vector2f(vx, vy);

    if (!p_game_->getField().contains(new_position)) {

        Stop();
        return;
    }


    sf::RectangleShape new_corpus(corpus_);
    new_corpus.move(vx, vy);


    if (   &(p_game_->tank0) != this   &&         
           Collisions::IsRectangleShapesIntersecting(p_game_->tank0.corpus_ , new_corpus ) ) 
    {

        Stop();
        return;
    }

    if (   &(p_game_->tank1) != this   &&         
           Collisions::IsRectangleShapesIntersecting(p_game_->tank1.corpus_ , new_corpus ) ) 
    {

        Stop();
        return;
    }


    corpus_.move(vx, vy);
    tower_.move(vx, vy);
    gun_.move(vx, vy);
}


sf::Vector2f Tank::GetPosition() const {

    return corpus_.getPosition();
}

float Tank::GetRotation() const {
    
    return corpus_.getRotation();
}

sf::FloatRect Tank::GetBounds() const {

    return corpus_.getGlobalBounds();
}


void Tank::UpdatePoints(int points) { 
    
    points_ += points;
}

int Tank::GetPoints() const {

    return points_; 
}



Shell Tank::Fire() {

    float angle_ = corpus_.getRotation();

    float sx = cos (angle_ * M_PI/180) * 15 ;
    float sy = sin (angle_ * M_PI/180) * 15 ;

    sf::Vector2f new_shell_position( { corpus_.getPosition().x + sx, corpus_.getPosition().y + sy }) ;


    float vx = cos (angle_ * M_PI/180) * 50.0 ;
    float vy = sin (angle_ * M_PI/180) * 50.0 ;


    return Shell(new_shell_position, {vx, vy});

}


void Tank::SetPosition(const sf::Vector2f& position ) {

    corpus_.setPosition(position);
    tower_.setPosition(position);
    gun_.setPosition(position);
}

void Tank::SetRotation(float angle) {

    corpus_.setRotation(angle);
    gun_.setRotation(angle);
}

void Tank::SetPoints(int points) {
    
    points_ = points;   
}


int Tank::GetElapsedTimeForShooting() const {

    return shooting_timer_.getElapsedTime().asMilliseconds();
}

void Tank::RestartShootingTimer() {

    shooting_timer_.restart();
}