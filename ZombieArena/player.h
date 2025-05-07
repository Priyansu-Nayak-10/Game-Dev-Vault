#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	Vector2f Position;
	Texture p_texture;
	Sprite p_sprite;
	Vector2f Resolution;
	IntRect Arena;
	int TileSize;

public:
	Player();
	void spawn(IntRect Arena, Vector2f Resolution, int TileSize);
	FloatRect getPosition();
	Vector2f getCenter();
	Sprite getSprite();
	void update(float elapsedTime, Vector2i mousePosition);
	float getRotation();

	/*void moveleft();
	void moveright();
	void moveup();
	void movedown();
	void stopleft();
	void stopright();
	void stopup();
	void stopdown();*/
};
