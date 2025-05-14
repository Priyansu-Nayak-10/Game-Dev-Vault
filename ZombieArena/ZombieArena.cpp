// Include SFML graphics and necessary headers
#include <SFML/Graphics.hpp>
#include "player.h"
#include "arena.h"
#include "zombie.h"
#include <cmath>

// Declare background creation and zombie horde functions
int createBackground(VertexArray& rVA, IntRect arena);
Zombie* createHorde(int numZombies, IntRect arena);

using namespace sf;

int main()
{  
    int wave = 0; // Game wave/level counter

    
    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING }; // Define the four possible game states
    State state = State::GAME_OVER; //initial state

    //-----------------------------------------------------------------------------------------------------------------
    // Set up the screen resolution and fullscreen window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

    // Create a view (camera) that follows the player
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    window.setView(mainView);
    //-----------------------------------------------------------------------------------------------------------------

    // Variables for managing zombies
    int numZombies;
    int numZombiesAlive;
    Zombie* zombies = nullptr;

    // Mouse position in world and screen space
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    window.setMouseCursorVisible(true);

    // Create player and arena
    Player player;
    IntRect arena;

    // Background setup
    VertexArray background;
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background_sheet.png");

    Clock clock;  // Clock for tracking time between frames

    // =================== MAIN GAME LOOP ===================
    while (window.isOpen())
    {
        // Handle all window events
        Event event;
        while (window.pollEvent(event))
        {
            // Toggle pause or start game depending on state
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
                    state = State::PLAYING;
                    clock.restart();
                }
                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }

                // Handle input during PLAYING (placeholder)
                if (state == State::PLAYING) {
                }
            }
        }

        // Exit the game if Escape is pressed
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Handle player movement with WASD keys
        if (state == State::PLAYING)
        {
            if (Keyboard::isKeyPressed(Keyboard::W)) player.moveUp();
            else player.stopUp();

            if (Keyboard::isKeyPressed(Keyboard::S)) player.moveDown();
            else player.stopDown();

            if (Keyboard::isKeyPressed(Keyboard::A)) player.moveLeft();
            else player.stopLeft();

            if (Keyboard::isKeyPressed(Keyboard::D)) player.moveRight();
            else player.stopRight();
        }

        // =================== LEVELING UP ===================
        if (state == State::LEVELING_UP)
        {
            // Handle level-up option keys (1–6)
            if (
                event.key.code == Keyboard::Num1 ||
                event.key.code == Keyboard::Num2 ||
                event.key.code == Keyboard::Num3 ||
                event.key.code == Keyboard::Num4 ||
                event.key.code == Keyboard::Num5 ||
                event.key.code == Keyboard::Num6  ) {
                state = State::PLAYING;
            }


            // Setup next wave after leveling up
            if (state == State::PLAYING) {
                wave++;
                arena.left = 0;
                arena.top = 0;
                arena.height = wave * 500;
                arena.width = wave * 500;
                int tilesize = 50;

                // Create new background and spawn player
                int tileSize = createBackground(background, arena);
                player.spawn(arena, resolution, tilesize);

                // Create new horde of zombies
                numZombies = wave * 3;
                delete[] zombies;
                zombies = createHorde(numZombies, arena);
                clock.restart();
            }
        }

        // =============== UPDATE GAME STATE =================
        if (state == State::PLAYING)
        {
            // Get elapsed time since last frame
            Time dt = clock.restart();
            float dtAsSeconds = dt.asSeconds();

            // Get mouse coordinates
            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            // Update player position and angle
            player.update(dtAsSeconds, Mouse::getPosition());

            // Get player location
            Vector2f playerPosition(player.getCenter());

            // Center the camera on player
            mainView.setCenter(player.getCenter());

            // Update all zombies
            for (int i = 0; i < numZombies; i++) {
                zombies[i].update(dtAsSeconds, playerPosition);
            }
        }

        // =================== RENDER FRAME ===================
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);

            // Draw background
            window.draw(background, &textureBackground);

            // Draw player
            window.draw(player.getSprite());

            // Draw each zombie
            for (int i = 0; i < numZombies; i++) {
                window.draw(zombies[i].getSprite());
            }
        }

        // Placeholder sections for other game states
        if (state == State::LEVELING_UP) {}
        if (state == State::PAUSED) {}
        if (state == State::GAME_OVER) {}

        // Display rendered frame
        window.display();
    }

    return 0;
}

// ================== ZOMBIE HORDE CREATION ===================
Zombie* createHorde(int numZombies, IntRect arena) {
    Zombie* zombies = new Zombie[numZombies];

    int maxX = arena.width - 20;
    int minX = arena.left + 20;
    int maxY = arena.height - 20;
    int minY = arena.top + 20;

    // Spawn each zombie randomly around arena edges
    for (int i = 0; i < numZombies; i++) {
        srand((int)time(0) * i);
        int side = (rand() % 4);
        float x, y;

        switch (side) {
        case 0: x = minX; y = (rand() % maxY) + minY; break;
        case 1: x = maxX; y = (rand() % maxY) + minY; break;
        case 2: y = minY; x = (rand() % maxX) + minX; break;
        case 3: y = maxY; x = (rand() % maxX) + minX; break;
        }

        // Choose random zombie type (0 = bloater, 1 = chaser, 2 = crawler)
        srand((int)time(0) * i * 2);
        int type = (rand() % 3);
        zombies[i].spawn(x, y, type, i);
    }

    return zombies;
}
