#pragma once
#ifndef BACKSTORY_H
#define BACKSTORY_H

#include <SFML/Graphics.hpp>
#include <string>

class Backstory {
public:
    Backstory() {
  
        if (!backgroundTexture.loadFromFile("backstory.png")) {
            throw std::runtime_error("Error cargando la imagen de fondo de backstory");
        }
        backgroundSprite.setTexture(backgroundTexture);

        if (!font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Error cargando la fuente");
        }

        storyText.setFont(font);
        storyText.setString("El dia 31 de Octubre del 2024.\n\nSucedío una gran Catástrofe que lo cambio todo.\n\n La gente comenzo a volverse loca poco a poco.\n\n No sabes muy bien como ocurrío. \n\n Tu nombre es Ren, y estás seguro.. \n\n A tu lado encontraras a Nanami. \n\n Conoceran las nuevas leyes de este mundo \n\n Todas tus decisiones tendrán repercusiones. \n\n Asi que piensalo dos veces si deseas ayudar  \n\n O  si vale la pena ser egoista.. \n\n Espero tomes las mejores decisiones...");
        storyText.setCharacterSize(30);
        storyText.setFillColor(sf::Color::White);
        storyText.setPosition(100, 600); 
    }

    void update() {
       
        if (storyText.getPosition().y > -storyText.getGlobalBounds().height) {
            float deltaY = -0.1f; 
            storyText.move(0, deltaY);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(backgroundSprite);
        window.draw(storyText); 
    }

    bool isFinished() {
 
        return storyText.getPosition().y <= -storyText.getGlobalBounds().height;
    }

private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text storyText;
};

#endif // BACKSTORY_H