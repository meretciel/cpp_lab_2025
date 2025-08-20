#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    unsigned int width = 800;
    unsigned int height = 600;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ width, height }), "Example 1");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window.close();
                }
            }
        }

        // Render
        window.clear(sf::Color(0xDFF2FE));

        // Display
        window.display();
    }
    return 0;
}