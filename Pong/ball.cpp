// Include the Ball class header
#include "ball.h"

// Constructor: Initializes the ball's position, radius, color, and placement
Ball::Ball(float x, float y) {
    m_position.x = x;
    m_position.y = y;

    // Define the ball's shape and appearance
    ballshape.setRadius(10);
    ballshape.setFillColor(Color::Green);
    ballshape.setPosition(m_position);
}

// Return the global bounds of the ball (used for collision detection)
FloatRect Ball::getPosition() {
    return ballshape.getGlobalBounds();
}

// Return the actual shape object (used for drawing)
CircleShape Ball::getShape() {
    return ballshape;
}

// Reverse the ball's horizontal direction (when it hits side walls)
void Ball::reboundsides() {
    DirectionX = -DirectionX;
}

// Reverse the ball's vertical direction (when it hits bat or top wall)
void Ball::reboundbatortop() {
    DirectionY = -DirectionY;
}

// Reset the ball's position (when it misses the bat and touches the bottom)
void Ball::reboundbottom() {
    m_position.x = 500;
    m_position.y = 300;
}

// Update ball's position based on current movement direction and elapsed time
void Ball::update(Time dt) {
    m_position.x += DirectionX * ballspeed * dt.asSeconds();
    m_position.y += DirectionY * ballspeed * dt.asSeconds();

    // Update the ball's shape position
    ballshape.setPosition(m_position);
}
