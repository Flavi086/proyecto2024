#pragma once
#ifndef TRANSITION_H
#define TRANSITION_H

#include <SFML/Graphics.hpp>

class Transition {
public:
    virtual ~Transition() = default;
    virtual void execute(sf::RenderWindow& window) = 0; // M�todo puro para ejecutar la transici�n
};

#endif // TRANSITION_H
