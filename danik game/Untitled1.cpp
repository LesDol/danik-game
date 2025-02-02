#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Library/UI.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "UI Example with Parallax");
    setlocale(LC_ALL, "Russian");

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("ArialRegular.ttf")) {
        return -1;
    }

    // Инициализация текстур для параллакса

	}
    

    return 0;
}

