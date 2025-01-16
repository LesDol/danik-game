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
	 setlocale(LC_ALL, "Russian");
    // ������������ ������ �������� InteractionZone
sf::Font globalFont;
sf::Texture globalTexture;

if (!globalFont.loadFromFile("ArialRegular.ttf") || !globalTexture.loadFromFile("animation/tile.png")) {
    std::cerr << "������ �������� ��������.\n";
    return -1;
}

// ������� ������� � �������
InteractionZone* interactionZones = new InteractionZone[3]{
    InteractionZone(&window, {100.0f, 100.0f}, {200.0f, 150.0f}),
    InteractionZone(&window, {300.0f, 100.0f}, {200.0f, 150.0f}),
    InteractionZone(&window, {500.0f, 100.0f}, {200.0f, 150.0f})
};

    // ������ ������
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("animation/tile.png")) {  // �������� �� �������� ���� � ��������
        std::cerr << "������ �������� �������� ������!" << std::endl;
        return -1;
    }

    sf::Sprite player;
    player.setTexture(playerTexture);
    player.setPosition(400.0f, 300.0f);  // ������������� ��������� ������� ������
    player.setScale(0.5f, 0.5f);         // ������������ ������ ������, ���� �����

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

        // ���������� �������
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.move(0.0f, -0.5f);  // �������� �����
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.move(0.0f, 0.5f);  // �������� ����
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.move(-0.5f, 0.0f);  // �������� �����
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.move(0.5f, 0.0f);  // �������� ������
        }

        window.clear();

        // ���������� ������
        window.draw(player);

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

