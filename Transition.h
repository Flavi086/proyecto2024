#pragma once
#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics.hpp>

class Transition {
public:
    virtual ~Transition() = default;
    virtual void execute(sf::RenderWindow& window) = 0; // Método puro para ejecutar la transición
};

#endif // TRANSITION_H
