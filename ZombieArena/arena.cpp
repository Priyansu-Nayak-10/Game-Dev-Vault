
#include <SFML/Graphics.hpp>
#include "player.h"
#include <iostream> // For debugging (if needed)

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena) {
    const int TILE_SIZE = 50;         // Size of each tile (square)
    const int TILE_TYPES = 3;         // Number of different tile types (used for variation)
    const int VERTS_IN_QUAD = 4;      // Number of vertices in a single tile (quad)

    // Calculate how many tiles fit in the arena (horizontally and vertically)
    int worldWidth = arena.width / TILE_SIZE;
    int worldHeight = arena.height / TILE_SIZE;

    // Set the primitive type to quads (4 vertices per tile)
    rVA.setPrimitiveType(Quads);

    // Resize the VertexArray to hold all tiles
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    int currentVertex = 0; // Tracks the current vertex index in the array

    // Loop through each tile position
    for (int w = 0; w < worldWidth; w++) {
        for (int h = 0; h < worldHeight; h++) {
            // Define the 4 corners of the current quad (tile)
            rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
            rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
            rVA[currentVertex + 3].position = Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

            // Check if the tile is on the border (edges of the arena)
            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1) {
                // Border tile: Use a specific texture row (e.g., walls)
                rVA[currentVertex + 0].texCoords = Vector2f(0, TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE);
                rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, (TILE_TYPES + 1) * TILE_SIZE);
                rVA[currentVertex + 3].texCoords = Vector2f(0, (TILE_TYPES + 1) * TILE_SIZE);
            }
            else {
                // Inside tile: Randomly choose a tile type for variation
                srand((int)time(0) + h * w - h); // Seed randomness
                int mOrG = (rand() % TILE_TYPES); // Random index from 0 to TILE_TYPES-1
                int verticalOffset = mOrG * TILE_SIZE;

                // Assign texture coordinates for selected tile type
                rVA[currentVertex + 0].texCoords = Vector2f(0, verticalOffset);
                rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, verticalOffset);
                rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
                rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);
            }

            // Move to the next quad (tile)
            currentVertex += VERTS_IN_QUAD;
        }
    }

    // Return the size of a tile (used by caller for layout)
    return TILE_SIZE;
}
