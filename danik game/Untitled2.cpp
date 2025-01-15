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

    // Динамический массив объектов InteractionZone
    InteractionZone* interactionZones = new InteractionZone[3]{
        InteractionZone(&window, {100.0f, 100.0f}, {200.0f, 150.0f}),
        InteractionZone(&window, {300.0f, 100.0f}, {200.0f, 150.0f}),
        InteractionZone(&window, {500.0f, 100.0f}, {200.0f, 150.0f})
    };

    sf::Sprite player;  // Создаём спрайт игрока (пример, замените на ваш)
    // Пример для игрока: загрузка текстуры, установка позиции и т.д.

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

        window.clear();

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

