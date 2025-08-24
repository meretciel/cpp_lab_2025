#include <iostream>
#include <optional>
#include <random>
#include <SFML/Graphics.hpp>

static float norm2(const sf::Vector2f& v) {
    return v.x *  v.x + v.y * v.y;
}

int main(int argc, char* argv[]) {
    unsigned int width = 800;
    unsigned int height = 600;
    const float PI = 3.14159265358979323846f;

    std::random_device rd{};
    std::mt19937 gen{rd()};

    // Values near the mean are the most likely. Standard deviation
    // affects the dispersion of generated values from the mean.
    std::normal_distribution<float> normDistr{0.0, 2.0};

    const unsigned int frameLimit = 60;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ width, height }), "Example 1");
    window.setFramerateLimit(frameLimit);

    sf::CircleShape circle(40.0f);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition({width / 2.0f, height / 2.0f});
    circle.setPointCount(60);

    std::vector<std::unique_ptr<sf::CircleShape>> childShapes;
    std::vector<float> directions(6, 1.0f);

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

        // Render
        window.clear(sf::Color(0xC9DEED));

        if (frameCount - lastCheckpoint >= 3 * frameLimit)
        {
            lastCheckpoint = frameCount;
            // std::cout << "frameCount: " << frameCount << ", result: " << frameCount / frameLimit << "\n";
            if (circle.getFillColor() == sf::Color::Blue)
            {
                circle.setFillColor(sf::Color::Red);
                if (childShapes.empty())
                {
                    for (auto i = 0; i < 6; ++i)
                    {
                        auto newShape = std::make_unique<sf::CircleShape>(10);
                        newShape->setFillColor(sf::Color::Yellow);
                        newShape->setOrigin(newShape->getGeometricCenter());
                        newShape->setPosition(circle.getPosition() + 10.0f * sf::Vector2f{std::cos(PI / 3.f * i), std::sin(PI / 3.f * i) });
                        childShapes.push_back(std::move(newShape));
                    }
                }

            } else
            {
                circle.setFillColor(sf::Color::Blue);
            }
        }

        auto dx = normDistr(gen);
        auto dy = normDistr(gen);
        circle.move({dx, dy});

        for (auto i = 0; i < childShapes.size(); ++i)
        {
            auto& target = childShapes.at(i);
            auto v = target->getPosition() - circle.getPosition();

            target->move(v * directions[i]);
            auto distance2 = norm2(v);
            // std::cout << "i=" << i << ", d2: " << distance2 << "\n";
            if (distance2 <= 1600)
            {
                directions[i] = 0.005f;
            } else if (distance2 >= 8100)
            {
                directions[i] = -0.01f;
            }

        }

        // Display
        window.draw(circle);

        for (const auto& item : childShapes)
        {
            window.draw(*item);
        }

        window.display();
    }
    return 0;
}