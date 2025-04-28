// Ensure this header is included only once during compilation
#pragma once

// Include SFML's Graphics module for shapes and vectors
#include <SFML/Graphics.hpp>
using namespace sf;

// Class representing the Ball in the Pong game
class Ball {
private:
    
    Vector2f m_position;  // Current position of the ball
    CircleShape ballshape;   // Shape representing the ball
    float ballspeed = 800.0f;  // Speed of the ball (pixels per second)

    // Direction of the ball's movement on X and Y axes (normalized values)
    float DirectionX = 0.2f;
    float DirectionY = 0.2f;

public:
    
    Ball(float x, float y); // Constructor: Initializes the ball at a given (x, y) position

    FloatRect getPosition();  // Get the bounding rectangle of the ball (for collision detection)

    CircleShape getShape();  // Get the CircleShape object (for rendering the ball)

    void reboundsides(); // Reverse the ball's horizontal direction (when hitting side walls)

    void reboundbatortop();  // Reverse the ball's vertical direction (when hitting bat or top wall)

    void reboundbottom(); // Reset the ball's position to a fixed location (after missing the bat)

    void update(Time dt);   // Update the ball's position based on current direction and elapsed time

};
