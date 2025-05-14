
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie {
private:
    // Base stats for different zombie types
    const float BLOATER_SPEED = 20;
    const float CHASER_SPEED = 40;
    const float CRAWLER_SPEED = 10;

    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;

    Vector2f m_Position;   // Current position of the zombie
    Sprite m_Sprite;       // Sprite used for drawing
    Texture m_Texture;     // Texture to be applied to the sprite

    float m_Speed;         // Current speed
    float m_Health;        // Remaining health
    bool m_Alive = false;  // Status flag

public:
    // Get the bounding rectangle of the zombie (for collision detection)
    FloatRect getPosition();

    // Return the zombie's sprite for rendering
    Sprite getSprite();

    // Returns whether the zombie is alive
    bool isAlive();

    // Spawns a zombie at a location with a specific type and random seed
    void spawn(float startX, float startY, int type, int seed);

    // Updates the zombie position based on elapsed time and player location
    void update(float elapsedTime, Vector2f playerLocation);

    // Called when the zombie is hit; returns true if it dies
    bool hit();
};
