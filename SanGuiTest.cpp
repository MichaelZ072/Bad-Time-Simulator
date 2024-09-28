#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
    // create the window
    RenderWindow window(VideoMode(800, 600), "My window");
    Vector2u windowSize = window.getSize();
    
    // font:
    


    // sans:
    // setting texture
    Texture sansDefTexture;
    if (!sansDefTexture.loadFromFile("assets/sansDefPos.png")) {
        cout << "Could not load enemy texture";
        return 1;
    };

    // setting sprite
    Sprite enemy;
    enemy.setTexture(sansDefTexture);

    // setting origin
    Vector2u sansTextureSize = sansDefTexture.getSize();
    enemy.setOrigin(sansTextureSize.x / 2.0f, 0);

    // position
    enemy.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 40)); // absolute position

    // scale
    enemy.setScale(0.7f, 0.7f);

    // speech bubble
    // setting texture
    Texture speechBubbleTexture;
    if (!speechBubbleTexture.loadFromFile("assets/speechBubble.png")) {
        cout << "Could not load speech bubble texture";
        return 1;
    };

    // setting texture
    Sprite speechBubble;
    speechBubble.setTexture(speechBubbleTexture);

    // setting origin
    Vector2u speechTextureSize = speechBubbleTexture.getSize();
    speechBubble.setOrigin(speechTextureSize.x / 2.0f, 0);

    // position
    speechBubble.setPosition(sf::Vector2f(windowSize.x - (windowSize.x / 5), windowSize.y / 20)); // absolute position

    // scale
    speechBubble.setScale(1.3f, 1.3f);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(Color::Black);

        // draw everything here...
        window.draw(enemy);
        window.draw(speechBubble);

        // end the current frame
        window.display();
    }

    return 0;
}