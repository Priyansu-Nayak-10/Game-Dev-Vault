#include<SFML/Graphics.hpp>
#include "player.h"
using namespace sf;

int main() {
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	VideoMode vm(resolution.x, resolution.y);
	RenderWindow window(vm, "ZOMBIE-ARENA", Style::Fullscreen);

	View mainview(FloatRect(0, 0, resolution.x, resolution.y));

	Player player;
	IntRect arena;

	arena.left = 0;
	arena.top = 0;
	arena.height = 500;
	arena.width = 500;
	int tilesize = 50;

	player.spawn(arena, resolution, tilesize);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		
		mainview.setCenter(player.getCenter());

		window.clear();
		window.setView(mainview);
		window.draw(player.getSprite());
		window.display();
	}
	return 0;
}