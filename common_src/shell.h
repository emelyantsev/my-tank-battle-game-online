#pragma once

#include <SFML/Graphics.hpp>

class Shell {

    public:

        Shell(sf::Vector2f position, sf::Vector2f speed, sf::Color color = sf::Color::Yellow);
        void Update(float time_diff);
        void Render(sf::RenderWindow& l_window) const;

        sf::Vector2f GetPosition() const ;


    private:

        sf::CircleShape body_;
        sf::Vector2f v_speed_ ;
};
