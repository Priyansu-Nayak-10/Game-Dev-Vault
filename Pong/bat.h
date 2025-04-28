// Ensure this header is included only once during compilation
#pragma once

// Include SFML's Graphics module for shapes and vectors
#include <SFML/Graphics.hpp>
using namespace sf;

// Class representing the Bat (paddle) in the Pong game
class Bat {
private:
   
    Vector2f m_position;  // Current position of the bat
    RectangleShape batshape; // Rectangle shape representing the bat
    float batspeed = 600.0f;  // Speed at which the bat moves (pixels per second)

    // Width and height of the bat
    float batwidth = 100;
    float batheight = 10;

    // Flags to track bat movement direction
    bool MovingLeft = false;
    bool MovingRight = false;

public:
    
    Bat(float x, float y);  // Constructor: Initializes the bat at a given (x, y) 

    FloatRect getPosition();  // Get the bounding rectangle of the bat (for collision detection

    RectangleShape getShape(); // Get the RectangleShape object (for rendering the bat

    void moveleft();    // Start moving the bat to the 

    void moveright(); // Start moving the bat to the 

    void stopleft();  // Stop moving the bat to the left

    void stopright(); // Stop moving the bat to the right

    void update(Time dt);  // Update the bat's position based on the current movement flags and elapsed time
};
