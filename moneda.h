#pragma once
#ifndef JUEGO_DE_AZAR_H
#define JUEGO_DE_AZAR_H

#include <SFML/Graphics.hpp>
#include <random>
#include <string>
#include <iostream>

class JuegoDeAzar {
public:
    virtual ~JuegoDeAzar() = default;
    virtual void lanzar() = 0; // Método virtual puro
};

class Moneda : public JuegoDeAzar {
public:
    Moneda();

    void lanzar() override; 

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text resultadoText;
    sf::CircleShape monedaShape;

    std::string obtenerResultado();
    void manejarEventos();
};

Moneda::Moneda() : window(sf::VideoMode(800, 600), "Lanzamiento de Moneda") {
    font.loadFromFile("arial.ttf");
    resultadoText.setFont(font);
    resultadoText.setCharacterSize(24);
    resultadoText.setFillColor(sf::Color::White);
    resultadoText.setPosition(300, 500);

    monedaShape.setRadius(50.f);
    monedaShape.setFillColor(sf::Color::Yellow);
    monedaShape.setPosition(375, 275);
}

void Moneda::lanzar() {
    while (window.isOpen()) {
        manejarEventos();
        window.clear();
        window.draw(monedaShape);
        window.draw(resultadoText);
        window.display();
    }
}

std::string Moneda::obtenerResultado() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    return distrib(gen) ? "Cara: ¡Funcionó!" : "Sello: No funcionó";
}

void Moneda::manejarEventos() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
            resultadoText.setString(obtenerResultado());
        }
    }
}

#endif // JUEGO_DE_AZAR_H
