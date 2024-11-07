#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "backstory.h"
#include "personaje.h"
#include "escena1.h"
#include "FadeTransition.h" 

enum class GameState {
    MENU,
    BACKSTORY,
    JUEGO,
    SALIR
};

void handleMenuInput(GameState& gameState);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu de Juego con SFML");
    GameState gameState = GameState::MENU;

    sf::Texture menuFondoTexture;
    if (!menuFondoTexture.loadFromFile("menu_fondo.png")) {
        std::cerr << "Error cargando la imagen del fondo del menú\n";
        return -1;
    }
    sf::Sprite menuFondoSprite(menuFondoTexture);
    menuFondoSprite.setScale(
        window.getSize().x / menuFondoSprite.getLocalBounds().width,
        window.getSize().y / menuFondoSprite.getLocalBounds().height
    );

    sf::Music menuMusic;
    if (!menuMusic.openFromFile("menu_music.ogg")) {
        std::cerr << "Error cargando la música del menú\n";
        return -1;
    }
    menuMusic.setLoop(true);
    menuMusic.play();

    Backstory backstory;
    Personaje personaje;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error cargando la fuente\n";
        return -1;
    }

    sf::Text startText("Iniciar", font, 50);
    sf::Text exitText("Salir", font, 50);
    startText.setPosition(350, 200);
    exitText.setPosition(350, 300);

    int selectedOption = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (gameState == GameState::MENU) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedOption = (selectedOption - 1 + 2) % 2;
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        selectedOption = (selectedOption + 1) % 2;
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        if (selectedOption == 0) {
                            gameState = GameState::BACKSTORY;
                        }
                        else if (selectedOption == 1) {
                            gameState = GameState::SALIR;
                        }
                    }
                }
            }
        }

        if (gameState == GameState::SALIR) {
            window.close();
        }

        window.clear();

        if (gameState == GameState::MENU) {
            window.draw(menuFondoSprite);
            startText.setFillColor(selectedOption == 0 ? sf::Color::Yellow : sf::Color::White);
            exitText.setFillColor(selectedOption == 1 ? sf::Color::Yellow : sf::Color::White);
            window.draw(startText);
            window.draw(exitText);
        }
        else if (gameState == GameState::BACKSTORY) {
            backstory.update();
            backstory.draw(window);

            if (backstory.isFinished()) {
                // Añadimos la transición antes de cambiar a la escena del juego
                FadeTransition fade;
                fade.execute(window);

                gameState = GameState::JUEGO;
                menuMusic.stop();
            }
        }
        else if (gameState == GameState::JUEGO) {
            static Escena1 escena1(personaje);

            if (event.type == sf::Event::KeyPressed) {
                escena1.handleInput(event.key.code);
            }

            escena1.update();
            escena1.draw(window);
            personaje.draw(window);
        }

        window.display();
    }
    return 0;
}
// error LNK1168 - Eliminar el archivo ejecutable manualmente: Si el archivo no se puede sobrescribir, 
// eliminar el archivo test project.exe manualmente en la carpeta x64\Debug y luego compila de nuevo.