
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
 
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
 
    // Load a sprite to display
    const sf::Texture texture("/home/ryan/Downloads/light-gbm-sampling.png");
    sf::Sprite sprite(texture);
 
    // Create a graphical text to display
    const sf::Font font("/usr/share/fonts/truetype/iosevka/Iosevka-Regular.ttc");
    sf::Text text(font, "Hello SFML", 50);
 
    // Load a music to play
    sf::Music music("/home/ryan/Downloads/sound-effect-test.wav");
 
    // Play the music
    music.play();
 
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
 
        // Clear screen
        window.clear();
 
        // Draw the sprite
        window.draw(sprite);
 
        // Draw the string
        window.draw(text);
 
        // Update the window
        window.display();
    }
}