#include"player.h"

Player::Player() {
	p_texture.loadFromFile("graphics/player.png");
	p_sprite.setTexture(p_texture);
	p_sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tilesize) {
	Arena.left = arena.left;
	Arena.top = arena.top;
	Arena.width = arena.width;
	Arena.height = arena.height;

	Resolution.x = resolution.x;
	Resolution.y = resolution.y;

	Position.x = arena.width / 2;
	Position.y = arena.height / 2;

	
}
FloatRect Player::getPosition() {
	return p_sprite.getGlobalBounds();
}
Vector2f Player::getCenter() {
	return Position;
}
Sprite Player::getSprite() {
	return p_sprite;
}
void Player::update(float elapsedTime, Vector2i mousePosition) {
	p_sprite.setPosition(Position);
	float angle = (atan2(mousePosition.y - Resolution.y / 2, mousePosition.x - Resolution.x / 2) * 180) / 3.141;
	p_sprite.setRotation(angle);
}
