#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    unsigned int width = 800;
    unsigned int height = 600;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ width, height }), "Example 1");
    window.setFramerateLimit(60);
    const std::uint32_t color1 = 0x8EF9FFFF;
    const std::uint32_t color2 = 0xE9D4FFFF;
    std::uint32_t bgColor = color1;

    while (window.isOpen())
    {
        // Event-based handling
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

        // State-based handling: This is more suitable for continuous monitoring.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::R) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
        {

            if (bgColor == color1)
            {
                std::cout << "change color to " << color2 << "\n";
                bgColor = color2;
            } else
            {
                std::cout << "change color to " << color1 << "\n";
                bgColor = color1;
            }

        }

        // Render
        window.clear(sf::Color(bgColor));

        // Display
        window.display();
    }
    return 0;
}