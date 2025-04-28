// Include SFML libraries for graphics and audio
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>   // For creating HUD text
#include "bat.h"     // Custom Bat class
#include "ball.h"    // Custom Ball class

using namespace sf;  // Use SFML namespace

int main() {
    // Create a window with 960x540 resolution and title "Pong"
    VideoMode vm(960, 540);
    RenderWindow window(vm, "Pong");

    // Load background texture and set up the sprite
    Texture texturebg;
    texturebg.loadFromFile("graphics/background.png");
    Sprite background;
    background.setTexture(texturebg);
    background.setPosition(0, 0);

    // Load font for text display
    Font font;
    font.loadFromFile("fonts/DS-DIGI.TTF");

    // Create "Press Enter to Start" message text
    Text message;
    message.setFont(font);
    message.setString("Press Enter to Start");
    message.setFillColor(Color::White);
    message.setPosition(960 / 2.0f, 540 / 2.0f);

    // Center the text origin
    FloatRect textrect = message.getLocalBounds();
    message.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);

    // HUD (Heads-Up Display) for score and lives
    Text hud;
    hud.setFont(font);
    hud.setPosition(20, 20);
    hud.setCharacterSize(30);
    hud.setFillColor(Color::White);

    // Load sound effect for Game Over
    SoundBuffer pongsound;
    pongsound.loadFromFile("sound/gv.wav");
    Sound gv;
    gv.setBuffer(pongsound);

    // Create the bat (paddle) and ball objects
    Bat bat(960 / 2, 540 - 20);
    Ball ball(960 / 2.0f, 200);

    int score = 0;    // Initial score
    int lives = 3;    // Initial lives

    Clock clock;      // Clock to manage time per frame
    bool paused = true; // Start the game paused

    // Main game loop
    while (window.isOpen()) {

        // Measure time since last frame
        Time dt = clock.restart();

        // Close window if Escape key pressed
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Poll and process window events (like closing window)
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Unpause the game when Enter key is pressed
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
        }

        // Only update game logic when not paused
        if (!paused) {
            // Update HUD with current score and lives
            std::stringstream ss;
            ss << "Score " << score << " Lives " << lives;
            hud.setString(ss.str());

            // Handle bat movement based on key presses
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                bat.moveleft();
            }
            else {
                bat.stopleft();
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                bat.moveright();
            }
            else {
                bat.stopright();
            }

            // Update positions of bat and ball
            bat.update(dt);
            ball.update(dt);

            // Ball collision with left or right walls
            if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > 960) {
                ball.reboundsides();
            }

            // Ball collision with top wall
            if (ball.getPosition().top < 0) {
                ball.reboundbatortop();
                score++; // Increase score
            }

            // Ball falls below the bottom of the screen
            if (ball.getPosition().top > 540) {
                ball.reboundbottom();
                lives--; // Decrease lives

                if (lives < 1) {
                    paused = true;  // Pause the game
                    ss.str("");     // Clear previous HUD text
                    ss.clear();
                    hud.setString("Game Over!!!");
                    gv.play();      // Play Game Over sound
                    score = 0;
                    lives = 3;
                }
            }

            // Ball collision with the bat
            if (ball.getPosition().intersects(bat.getPosition())) {
                ball.reboundbatortop();
            }
        }

        // Clear the window before drawing
        window.clear();

        // Draw background, ball, HUD, bat, and message if paused
        window.draw(background);
        window.draw(ball.getShape());
        if (paused) {
            window.draw(message);
        }
        window.draw(hud);
        window.draw(bat.getShape());

        // Display everything drawn
        window.display();
    }

    return 0;
}
