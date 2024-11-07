#pragma once
#ifndef ESCENA2_H
#define ESCENA2_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "escena1.h"

class Escena2 : public Escena1 {
public:
    Escena2(Personaje& personaje)
        : Escena1(personaje), dialogoActual(0), tiempoDesdeUltimoTexto(0.f), dialogoCompletado(false), fase(1) {

        if (!npcTexture.loadFromFile("npc2.png")) {
            throw std::runtime_error("Error cargando el sprite de NPC2");
        }
        npcSprite.setTexture(npcTexture);

        inicializarDialogos();
        dialogoText.setString(dialogos[fase - 1][dialogoActual]);
    }

    void update() override {
        Escena1::update();

        
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
                std::cout << "Transici�n a la siguiente escena..." << std::endl;
            }
        }
    }

    void draw(sf::RenderWindow& window) override {
        Escena1::draw(window);
        if (!dialogoCompletado || fase < dialogos.size()) {
            window.draw(dialogoText);
        }
    }

    
    friend void ajustarRecursos(Escena2& escena, int comida, int agua, int medicina);

private:
    std::vector<std::vector<std::string>> dialogos;
    size_t dialogoActual;
    float tiempoDesdeUltimoTexto;
    bool dialogoCompletado;
    sf::Clock reloj;
    int fase;

    void inicializarDialogos() {
        dialogos = {
            {
                "NPC: �ltimamente, los susurros se han vuelto m�s claros...",
                "NPC: Anoche pens� que pod�a escuchar palabras... nombres incluso.",
                "NPC: Necesitamos contactar a otros grupos, asegurarnos de que estamos solos."
            },
            {
                "NPC: Pero hay m�s que me preocupa.",
                "NPC: Los recursos no durar�n para siempre; debemos ser estrat�gicos.",
                "NPC: Si recolectas m�s comida y agua, podremos resistir m�s tiempo."
            },
            {
                "NPC: ...Aunque, a veces, me pregunto si vale la pena.",
                "NPC: Sin esperanza, incluso los recursos se sienten insignificantes.",
                "NPC: Pero t� tienes el potencial de inspirar a los dem�s, de liderar."
            },
            {
                "NPC: Si decides liderar, recuerda cuidar de todos, no solo de ti mismo.",
                "NPC: Este lugar... podr�a ser nuestra salvaci�n o nuestra ruina.",
                "NPC: No te estoy pidiendo una respuesta ahora, solo pi�nsalo."
            }
        };
    }
};


void ajustarRecursos(Escena2& escena, int comida, int agua, int medicina) {
    escena.personaje.agregarComida(comida);
    escena.personaje.agregarAgua(agua);
    escena.personaje.agregarMedicina(medicina);
    std::cout << "Recursos actualizados: +"
        << comida << " comida, +" << agua << " agua, +" << medicina << " medicina.\n";
}

#endif // ESCENA2_H
