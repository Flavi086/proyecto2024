#pragma once
#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <string>

class Personaje {
public:

    Personaje()
        : comida(5), agua(5), medicina(1) {

        if (!font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Error cargando la fuente");
        }

        configurarTexto(comidaText, "Comida: " + std::to_string(comida), sf::Color::White, 650, 50);
        configurarTexto(aguaText, "Agua: " + std::to_string(agua), sf::Color::White, 650, 70);
        configurarTexto(medicinaText, "Medicina: " + std::to_string(medicina), sf::Color::White, 650, 90);

    }

    int getComida() const { return comida; }
    int getAgua() const { return agua; }
    int getMedicina() const { return medicina; }
   

    void agregarComida(int cantidad) {
        comida += cantidad;
        actualizarTexto(comidaText, "Comida: " + std::to_string(comida));
    }

    void agregarAgua(int cantidad) {
        agua += cantidad;
        actualizarTexto(aguaText, "Agua: " + std::to_string(agua));
    }

    void agregarMedicina(int cantidad) {
        medicina += cantidad;
        actualizarTexto(medicinaText, "Medicina: " + std::to_string(medicina));
    }


    void draw(sf::RenderWindow& window) {
        window.draw(comidaText);
        window.draw(aguaText);
        window.draw(medicinaText);

    }

private:
    int comida;
    int agua;
    int medicina;


    sf::Font font;
    sf::Text comidaText;
    sf::Text aguaText;
    sf::Text medicinaText;
 
    void configurarTexto(sf::Text& text, const std::string& str, sf::Color color, float x, float y) {
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(20);
        text.setFillColor(color);
        text.setPosition(x, y);
    }

    void actualizarTexto(sf::Text& text, const std::string& str) {
        text.setString(str);
    }
};

#endif // PERSONAJE_H