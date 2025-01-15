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
#include "Zone.h"  // ���������� ���� � ������� InteractionZone

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Interaction Zones");

    // ������������ ������ �������� InteractionZone
    InteractionZone* interactionZones = new InteractionZone[3]{
        InteractionZone(&window, {100.0f, 100.0f}, {200.0f, 150.0f}),
        InteractionZone(&window, {300.0f, 100.0f}, {200.0f, 150.0f}),
        InteractionZone(&window, {500.0f, 100.0f}, {200.0f, 150.0f})
    };

    sf::Sprite player;  // ������ ������ ������ (������, �������� �� ���)
    // ������ ��� ������: �������� ��������, ��������� ������� � �.�.

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // ������������ ������� ��� ������� ������� ���� ��������������
            for (int i = 0; i < 3; ++i) {
                interactionZones[i].handleEvent(event);
            }
        }

        window.clear();

        // ��������� ������ ������ InteractionZone
        for (int i = 0; i < 3; ++i) {
            interactionZones[i].update(player);
            interactionZones[i].render();  // ���������� ��� ����
        }

        window.display();
    }

    delete[] interactionZones;  // ����������� ������ ��� ������������� �������

    return 0;
}

