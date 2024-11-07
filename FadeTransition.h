#pragma once
#ifndef FADE_TRANSITION_H
#define FADE_TRANSITION_H

#include "Transition.h"

class FadeTransition : public Transition {
public:
    void execute(sf::RenderWindow& window) override {
        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 0)); 

        sf::Clock clock;
        float duration = 1.5f; // Duración de la transición

        while (clock.getElapsedTime().asSeconds() < duration) {
            float alpha = 255 * (clock.getElapsedTime().asSeconds() / duration);
            overlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));

            window.clear();
            window.draw(overlay);
            window.display();
        }
    }
};

#endif // FADE_TRANSITION_H
