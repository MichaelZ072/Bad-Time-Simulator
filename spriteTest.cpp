#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

int main()
{
    std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Texture Loading Example");

    // Load a texture
    sf::Texture texture;
    if (!texture.loadFromFile("./sprites/actSpriteIdle.png")) {
        // Handle error
        return -1;
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display what was drawn
        window.display();
    }

    return 0;
}
