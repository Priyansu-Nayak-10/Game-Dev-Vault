
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Player {
    const float START_SPEED = 200;  // Initial player movement speed (pixels/second)
    float m_Speed;                 // Current speed (can be changed if needed)

    Sprite m_sprite;              // Player sprite for rendering
    Texture m_texture;           // Texture loaded from file for the sprite

    Vector2f m_Position;         // Current position of the player in the world
    Vector2f m_Resolution;       // Screen resolution (used to calculate view center)

    IntRect m_Arena;             // Boundaries of the playable arena
    int m_TileSize;              // Size of each tile in the arena

    // Input flags for movement directions
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;

public:
    Player();  // Initializes player data (speed, sprite, etc.)

    // Initializes the player inside the arena with screen resolution and tile size
    void spawn(IntRect m_Arena, Vector2f m_Resolution, int m_TileSize);

    // Returns the player's bounding box (used for collision)
    FloatRect getPosition();

    // Returns the center point of the player (used for view/camera)
    Vector2f getCenter();

    // Returns the player's sprite for rendering
    Sprite getSprite();

    // Returns the rotation angle of the player sprite (facing direction)
    float getRotation();

    void moveRight();  // Start moving right
    void moveLeft();   // Start moving left
    void moveUp();     // Start moving up
    void moveDown();   // Start moving down

    void stopLeft();   // Stop moving left
    void stopRight();  // Stop moving right
    void stopUp();     // Stop moving up
    void stopDown();   // Stop moving down

    // Updates the player's position and rotation based on inputs and elapsed time
    void update(float elapsedTime, Vector2i mousePosition);
};
