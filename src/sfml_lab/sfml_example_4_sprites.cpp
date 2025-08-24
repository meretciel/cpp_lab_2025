#include <iostream>
#include <optional>
#include <random>
#include <SFML/Graphics.hpp>

static float norm2(const sf::Vector2f& v) {
    return v.x *  v.x + v.y * v.y;
}




class Car {
private:
    sf::Sprite _sprite;

    explicit Car(
        sf::Sprite&& sprite):
            _sprite(std::move(sprite)) {}

public:


    static Car create(unsigned int w_width, unsigned w_height, std::vector<sf::Texture>& textures) {
        std::string filepath;

        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::uniform_real_distribution<float> uniform_dist(0, 1);
        std::uniform_int_distribution<size_t> index_dist(0, textures.size());
        auto index = index_dist(gen);
        auto sprite = sf::Sprite(textures[index]);
        auto rx = uniform_dist(gen);
        auto ry = uniform_dist(gen);

        auto [width, height] = textures[index].getSize();
        std::cout << "index = " << index << ", rx = " << rx << ", ry = " << ry << ", w=" << width << ", h=" << height << "\n";
        sprite.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(width), static_cast<int>(height)}));
        sprite.setOrigin({width / 2.0f, height / 2.0f});
        sprite.setPosition({w_width * uniform_dist(gen), w_height * uniform_dist(gen)});

        return Car(std::move(sprite));
    }

    const sf::Sprite& getSprite() const { return _sprite;}
    sf::Sprite& getSprite() { return _sprite;}
};


int main(int argc, char* argv[]) {
    unsigned int width = 800;
    unsigned int height = 600;


    const unsigned int frameLimit = 60;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ width, height }), "Example 1");
    window.setFramerateLimit(frameLimit);

    // Create car textures
    const std::string carTextureFiles[] = {
        "resources/red-car.png",
        "resources/yellow-car.png",
        "resources/green-car.png",
    };


    std::vector<sf::Texture> carTextures;
    carTextures.reserve(3);
    for (auto i = 0; i < 3; ++i)
    {
        sf::Texture texture;
        auto filepath = carTextureFiles[i];

        if (!texture.loadFromFile(filepath))
        {
            std::cout << "Failed to load file: " << filepath << "\n";
            exit(1);
        }

        std::cout << "Successfully loaded texture file: " << filepath << "\n";

        carTextures.push_back(std::move(texture));
    }

    std::vector<Car> sprites;
    sprites.reserve(10);

    auto& texture = carTextures[0];
    sf::Sprite spriteProbe(texture);
    auto [w, h] = texture.getSize();
    spriteProbe.setOrigin({w / 2.f, h / 2.f});
    spriteProbe.setPosition({width / 2.f, height / 2.f});


    for (auto i = 0; i < 10; ++i)
    {
        sprites.push_back(Car::create(width, height, carTextures));
    }


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

        // Display
        for (const auto& car : sprites)
        {
            window.draw(car.getSprite());
        }
        window.draw(spriteProbe);

        window.display();
    }
    return 0;
}