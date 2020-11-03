#include "shell.h"


Shell::Shell(sf::Vector2f position, sf::Vector2f v_speed, sf::Color color) : v_speed_(v_speed) {

    body_.setPosition(position);
    body_.setFillColor(color);
    body_.setRadius(3);
    body_.setOrigin({3,3});

}

void Shell::Render(sf::RenderWindow& l_window) const {

    l_window.draw(body_);
}


void Shell::Update(float time_diff) {

    body_.move( v_speed_ * time_diff );
}

sf::Vector2f Shell::GetPosition() const {

    return body_.getPosition();
}