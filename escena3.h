#pragma once
#ifndef ESCENA3_H
#define ESCENA3_H

#include "escena2.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Escena3 : public Escena2 {
public:
    Escena3(Personaje& personaje)
        : Escena2(personaje), fase(1), dialogoActual(0), dialogoCompletado(false), tiempoDesdeUltimoTexto(0.f) {

        if (!npcTexture.loadFromFile("npc3.png")) {
            throw std::runtime_error("Error cargando el sprite de NPC para Escena3");
        }
        npcSprite.setTexture(npcTexture);

        dialogos = {
            { "NPC: Parece que la situaci�n se ha vuelto a�n m�s complicada...",
              "NPC: Hemos perdido contacto con algunos refugios.",
              "NPC: Necesitamos encontrar suministros, pero tambi�n mantenernos seguros." },

            { "NPC: Algunas personas est�n empezando a hablar de un lugar seguro al norte...",
              "NPC: Pero es un viaje largo y peligroso.",
              "NPC: Tal vez deber�amos considerar otras opciones antes de tomar una decisi�n tan dr�stica." },

            { "NPC: He o�do rumores sobre un grupo que se organiza para hacer frente a esta situaci�n.",
              "NPC: Quiz� podr�amos unirnos a ellos o al menos averiguar m�s sobre sus planes.",
              "NPC: No podemos seguir en este caos sin un plan concreto." },

            { "NPC: Es dif�cil saber en qui�n confiar en estos tiempos...",
              "NPC: Pero juntos tenemos m�s posibilidades de sobrevivir.",
              "NPC: La �ltima vez que baj� a la ciudad, algo me segu�a desde las sombras...",
              "NPC: Solo podemos mantenernos fuertes y cuidar uno del otro." },

            { "NPC: Me alegra que hayas llegado tan lejos conmigo.",
              "NPC: Pase lo que pase, recuerda que no est�s solo.",
              "NPC: Vamos, debemos seguir adelante."
            }
        };

        dialogoText.setFont(font);
        dialogoText.setCharacterSize(20);
        dialogoText.setFillColor(sf::Color::White);
        dialogoText.setPosition(50, 150);
        dialogoText.setString(dialogos[fase - 1][dialogoActual]);
    }

    ~Escena3() override {
        std::cout << "Escena3 finalizada. Liberando recursos de escena..." << std::endl;
    }

    void update() override {
        if (dialogoActual < dialogos[fase - 1].size() - 1 && !dialogoCompletado) {
            tiempoDesdeUltimoTexto += reloj.restart().asSeconds();
            if (tiempoDesdeUltimoTexto >= 2.f) {
                dialogoActual++;
                dialogoText.setString(dialogos[fase - 1][dialogoActual]);
                tiempoDesdeUltimoTexto = 0.f;
            }
        }
        else if (dialogoActual == dialogos[fase - 1].size() - 1) {
            dialogoCompletado = true;
        }
    }

    void handleInput(sf::Keyboard::Key key) override {
        if (dialogoCompletado) {
            if (key == sf::Keyboard::Enter && fase < dialogos.size()) {
                fase++;
                dialogoActual = 0;
                dialogoText.setString(dialogos[fase - 1][dialogoActual]);
                dialogoCompletado = false;
                tiempoDesdeUltimoTexto = 0.f;
            }
            else if (key == sf::Keyboard::Enter && fase == dialogos.size()) {
                std::cout << "Fin de Escena3. Transici�n a la siguiente escena..." << std::endl;
            }
        }
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(fondoSprite);
        window.draw(personajeSprite);
        window.draw(npcSprite);
        window.draw(npcNameText);

        if (opcionElegida) {
            window.draw(eleccionText);
        }

        window.draw(dialogoText);
    }

private:
    int fase;
    int dialogoActual;
    bool dialogoCompletado;
    float tiempoDesdeUltimoTexto;

    std::vector<std::vector<std::string>> dialogos;
    sf::Clock reloj;
};

#endif // ESCENA3_H
