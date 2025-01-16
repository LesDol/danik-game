#include <SFML/Graphics.hpp> 
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "Zone.h"  // Подключаем файл с классом InteractionZone

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Interaction Zones");
	 setlocale(LC_ALL, "Russian");
    // Динамический массив объектов InteractionZone
sf::Font globalFont;
sf::Texture globalTexture;

if (!globalFont.loadFromFile("ArialRegular.ttf") || !globalTexture.loadFromFile("animation/tile.png")) {
    std::cerr << "Ошибка загрузки ресурсов.\n";
    return -1;
}

// Передаём ресурсы в объекты
InteractionZone* interactionZones = new InteractionZone[3]{
    InteractionZone(&window, {100.0f, 100.0f}, {200.0f, 150.0f}),
    InteractionZone(&window, {300.0f, 100.0f}, {200.0f, 150.0f}),
    InteractionZone(&window, {500.0f, 100.0f}, {200.0f, 150.0f})
};

    // Создаём игрока
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("animation/tile.png")) {  // Замените на реальный путь к текстуре
        std::cerr << "Ошибка загрузки текстуры игрока!" << std::endl;
        return -1;
    }

    sf::Sprite player;
    player.setTexture(playerTexture);
    player.setPosition(400.0f, 300.0f);  // Устанавливаем начальную позицию игрока
    player.setScale(0.5f, 0.5f);         // Масштабируем спрайт игрока, если нужно

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Обрабатываем события для каждого объекта зоны взаимодействия
            for (int i = 0; i < 3; ++i) {
                interactionZones[i].handleEvent(event);
            }
        }

        // Управление игроком
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0.0f, -0.5f);  // Движение вверх
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0.0f, 0.5f);  // Движение вниз
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-0.5f, 0.0f);  // Движение влево
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(0.5f, 0.0f);  // Движение вправо
        }

        window.clear();

        // Отображаем игрока
        window.draw(player);

        // Обновляем каждый объект InteractionZone
        for (int i = 0; i < 3; ++i) {
            interactionZones[i].update(player);
            interactionZones[i].render();  // Отображаем все зоны
        }

        window.display();
    }

    delete[] interactionZones;  // Освобождаем память для динамического массива

    return 0;
}

