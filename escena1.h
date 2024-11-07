class Escena1 {
public:
    Escena1(Personaje& personaje)
        : personaje(personaje), opcionSeleccionada(0), dialogoTerminado(false), fondoOpacidad(0) {

        if (!fondoTexture.loadFromFile("fondo.jpg")) {
            throw std::runtime_error("Error cargando la imagen de fondo de escena1");
        }
        fondoSprite.setTexture(fondoTexture);
        fondoSprite.setColor(sf::Color(255, 255, 255, fondoOpacidad));

        if (!backgroundMusic.openFromFile("background.ogg")) {
            throw std::runtime_error("Error cargando la música de fondo de escena1");
        }
        backgroundMusic.setLoop(true);
        backgroundMusic.play();

        if (!personajeTexture.loadFromFile("personaje.png")) {
            throw std::runtime_error("Error cargando el sprite del personaje");
        }
        personajeSprite.setTexture(personajeTexture);
        personajeSprite.setPosition(50, 300);

        if (!npcTexture.loadFromFile("npc.png")) {
            throw std::runtime_error("Error cargando el sprite de NPC");
        }
        npcSprite.setTexture(npcTexture);
        npcSprite.setPosition(600, 250);

        if (!font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Error cargando la fuente para el diálogo");
        }

        npcNameText.setFont(font);
        npcNameText.setString("Nanami");
        npcNameText.setCharacterSize(20);
        npcNameText.setFillColor(sf::Color::Yellow);
        npcNameText.setPosition(npcSprite.getPosition().x, npcSprite.getPosition().y - 30);

        preguntaText.setFont(font);
        preguntaText.setString("¿Qué deberíamos priorizar esta semana?\n");
        preguntaText.setCharacterSize(20);
        preguntaText.setFillColor(sf::Color::White);
        preguntaText.setPosition(50, 50);

        for (int i = 0; i < 3; ++i) {
            opcionesText[i].setFont(font);
            opcionesText[i].setCharacterSize(20);
            opcionesText[i].setFillColor(sf::Color::White);
            opcionesText[i].setPosition(50, 100 + i * 30);
        }
        opcionesText[0].setString("Comida");
        opcionesText[1].setString("Agua");
        opcionesText[2].setString("Medicina");

        // Nueva variable para mostrar la respuesta del NPC
        npcDialogo.setFont(font);
        npcDialogo.setString("");
        npcDialogo.setCharacterSize(20);
        npcDialogo.setFillColor(sf::Color::White);
        npcDialogo.setPosition(50, 200); 
    }

    void handleInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Up) {
        opcionSeleccionada = (opcionSeleccionada - 1 + 3) % 3;
    }
    else if (key == sf::Keyboard::Down) {
        opcionSeleccionada = (opcionSeleccionada + 1) % 3;
    }
    else if (key == sf::Keyboard::Enter) {
        if (opcionSeleccionada == 0) {
            personaje.agregarComida(1);
            npcDialogo.setString("Entiendo, lo anotaré! +1 Comida");
        }
        else if (opcionSeleccionada == 1) {
            personaje.agregarAgua(1);
            npcDialogo.setString("Entiendo, lo anotaré! +1 Agua");
        }
        else if (opcionSeleccionada == 2) {
            personaje.agregarMedicina(1);
            npcDialogo.setString("Entiendo, lo anotaré! +1 Medicina");
        }
        npcSprite.setTexture(npcTextureAlt);
    }
}

    void update() {
        if (fondoOpacidad < 255) {
            fondoOpacidad += 1; // Incrementar la opacidad gradualmente
            fondoSprite.setColor(sf::Color(255, 255, 255, fondoOpacidad));
        }

        for (int i = 0; i < 3; ++i) {
            if (i == opcionSeleccionada) {
                opcionesText[i].setFillColor(sf::Color::Yellow);
            }
            else {
                opcionesText[i].setFillColor(sf::Color::White);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(fondoSprite);
        window.draw(personajeSprite);
        window.draw(npcSprite);
        window.draw(npcNameText);
        window.draw(preguntaText);

        for (int i = 0; i < 3; ++i) {
            window.draw(opcionesText[i]);
        }

        window.draw(npcDialogo);
    }

private:
    Personaje& personaje;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;

    sf::Music backgroundMusic;

    sf::Texture personajeTexture;
    sf::Sprite personajeSprite;

    sf::Texture npcTexture;
    sf::Texture npcTextureAlt;
    sf::Sprite npcSprite;

    sf::Font font;
    sf::Text npcNameText;
    sf::Text preguntaText;
    sf::Text opcionesText[3];
    sf::Text npcDialogo; 
    int opcionSeleccionada;
    bool dialogoTerminado;
    int fondoOpacidad;
};
