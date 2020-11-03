#pragma once

#include <SFML/Graphics.hpp>

#include "shell.h"

class Tank {

    public:

        Tank() = default;

        Tank(sf::Vector2f position, 
            sf::Color color = sf::Color::Red, 
            sf::Color color1 = sf::Color::Red, 
            sf::Color color2 = sf::Color::Red) ;
        
        void Render(sf::RenderWindow& l_window);        
        void Update(float time_diff);
        
        void Move(int) ;
        void Stop() ;
        void Rotate(float angle) ;

        Shell Fire() ;

        sf::Vector2f GetPosition() const ;
        float GetRotation() const ;
        
        sf::FloatRect GetBounds() const;

        void UpdatePoints(int points = 1);
        int GetPoints() const ;


        void SetPosition(const sf::Vector2f& position ) ;
        void SetRotation(float angle) ;
        void SetPoints(int points) ;


        void RestartShootingTimer() ;
        int GetElapsedTimeForShooting() const ;

    protected:

        sf::RectangleShape corpus_;
        sf::RectangleShape gun_;
        sf::CircleShape tower_;

        int speed_ = 0;
        float angle_ = 0;

        int points_ = 0;

        sf::Clock shooting_timer_;
};





