// Include the Bat class header
#include "bat.h"

// Constructor to initialize the bat's position, size, color, and placement
Bat::Bat(float x, float y) {
    m_position.x = x;
    m_position.y = y;

    // Define the bat's shape and appearance
    batshape.setSize(Vector2f(batwidth, batheight));
    batshape.setFillColor(Color::Cyan);
    batshape.setPosition(m_position);
}

// Return the global bounds of the bat (used for collision detection)
FloatRect Bat::getPosition() {
    return batshape.getGlobalBounds();
}

// Return the actual shape object (used for drawing)
RectangleShape Bat::getShape() {
    return batshape;
}

// Start moving the bat to the left if it's not at the left edge
void Bat::moveleft() {
    if (m_position.x > 0) {
        MovingLeft = true;
    }
}

// Start moving the bat to the right if it's not at the right edge
void Bat::moveright() {
    if (m_position.x + batshape.getSize().x < 960) {
        MovingRight = true;
    }
}

// Stop moving the bat to the left
void Bat::stopleft() {
    MovingLeft = false;
}

// Stop moving the bat to the right
void Bat::stopright() {
    MovingRight = false;
}

// Update bat's position based on current movement direction and elapsed time
void Bat::update(Time dt) {
    if (MovingLeft) {
        // Move left but don't go outside the window
        if (m_position.x > 0) {
            m_position.x -= batspeed * dt.asSeconds();
        }
    }

    if (MovingRight) {
        // Move right but don't go outside the window
        if (m_position.x + batshape.getSize().x < 960) {
            m_position.x += batspeed * dt.asSeconds();
        }
    }

    // Update the bat's shape position after moving
    batshape.setPosition(m_position);
}
