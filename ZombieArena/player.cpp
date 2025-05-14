
#include "player.h"
#include <cmath> // For atan2

Player::Player() {
    m_Speed = START_SPEED; // Set the initial speed of the player

    // Load player texture from file
    m_texture.loadFromFile("graphics/player.png");

    // Assign the texture to the player sprite
    m_sprite.setTexture(m_texture);

    // Set the sprite's origin to the center (25x25 for 50x50 texture)
    m_sprite.setOrigin(25, 25);
}
void Player::spawn(IntRect arena, Vector2f resolution, int tilesize) {
    // Copy arena bounds
    m_Arena.left = arena.left;
    m_Arena.top = arena.top;
    m_Arena.width = arena.width;
    m_Arena.height = arena.height;

    // Store the screen resolution
    m_Resolution = resolution;

    // Set initial position of the player to the center of the arena
    m_Position.x = arena.width / 2;
    m_Position.y = arena.height / 2;
}

// Returns the player's bounding rectangle (for collisions etc.)
FloatRect Player::getPosition() {
    return m_sprite.getGlobalBounds();
}

// Returns the exact center position of the player
Vector2f Player::getCenter() {
    return m_Position;
}

// Returns the player's sprite for rendering
Sprite Player::getSprite() {
    return m_sprite;
}

// Returns the current rotation (angle) of the player sprite
float Player::getRotation() {
    return m_sprite.getRotation();
}

// Movement controls: called when keys are pressed
void Player::moveLeft() { m_LeftPressed = true; }
void Player::moveRight() { m_RightPressed = true; }
void Player::moveUp() { m_UpPressed = true; }
void Player::moveDown() { m_DownPressed = true; }

// Stop movement: called when keys are released
void Player::stopLeft() { m_LeftPressed = false; }
void Player::stopRight() { m_RightPressed = false; }
void Player::stopUp() { m_UpPressed = false; }
void Player::stopDown() { m_DownPressed = false; }

// Update function: Moves the player and updates sprite rotation
void Player::update(float elapsedTime, Vector2i mousePosition) {
    // Move the player in the direction of the key pressed
    if (m_UpPressed)    m_Position.y -= m_Speed * elapsedTime;
    if (m_DownPressed)  m_Position.y += m_Speed * elapsedTime;
    if (m_LeftPressed)  m_Position.x -= m_Speed * elapsedTime;
    if (m_RightPressed) m_Position.x += m_Speed * elapsedTime;

    // Update sprite position to match logical position
    m_sprite.setPosition(m_Position);

    // Calculate rotation angle to face the mouse pointer
    float angle = (atan2(
        mousePosition.y - m_Resolution.y / 2,
        mousePosition.x - m_Resolution.x / 2
    ) * 180) / 3.141;

    // Apply rotation to sprite
    m_sprite.setRotation(angle);
}

