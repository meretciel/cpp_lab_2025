#include <iostream>
#include <optional>
#include <random>
#include <SFML/Graphics.hpp>

#include "../../../third_party/install/include/SFML/System/Vector2.hpp"

static float norm2(const sf::Vector2f& v) {
    return v.x *  v.x + v.y * v.y;
}

int main(int argc, char* argv[]) {
    unsigned int width = 800;
    unsigned int height = 600;
    const float PI = 3.14159265358979323846f;
    const std::uint32_t bgColor = 0x8EF9FFFF;


    std::random_device rd{};
    std::mt19937 gen{rd()};

    // Values near the mean are the most likely. Standard deviation
    // affects the dispersion of generated values from the mean.
    std::normal_distribution<float> normDistr{0.0, 2.0};

    const unsigned int frameLimit = 60;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ width, height }), "Example 1");
    window.setFramerateLimit(frameLimit);

    float radius = 40.0f;
    sf::CircleShape circle(radius);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition({width / 2.0f, height / 2.0f});
    circle.setPointCount(60);


    unsigned long long frameCount = 0;
    unsigned long long lastCheckpoint = 0;

    while (window.isOpen())
    {
        ++frameCount;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            auto pos = sf::Vector2f(sf::Mouse::getPosition(window));
            auto diff = sf::Vector2f(pos) - circle.getPosition();
            if (norm2(diff) < radius * radius)
            {
                circle.setPosition(pos);
            }
        }

        // clear
        window.clear(sf::Color(bgColor));
        // Display
        window.draw(circle);
        window.display();
    }
    return 0;
}