#include<SFML/Graphics.hpp>
#include<cmath>
#include "player.h"
using namespace sf;

int main() {
	enum class State{PAUSED,PLAYING,GAME_OVER,LEVELING_UP};
	State state = State::GAME_OVER;
	int wave = 0;

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	VideoMode vm(resolution.x, resolution.y);
	RenderWindow window(vm, "ZOMBIE-ARENA", Style::Fullscreen);

	View mainview(FloatRect(0, 0, resolution.x, resolution.y));

	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;
	window.setMouseCursorVisible(true);

	Player player;
	IntRect arena;

	
	Clock clock;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Return && state == State::PLAYING) {
					state = State::PAUSED;
				}
				else if(event.key.code == Keyboard::Return && state == State::PAUSED) {
					state = State::PLAYING;
					clock.restart();
				}
				else if(event.key.code == Keyboard::Return && state == State::GAME_OVER) {
					state = State::LEVELING_UP;
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}IntRect arena;
		arena.left = 0;
		arena.top = 0;
		arena.height = 500;
		arena.width = 500;
		int tilesize = 50;
		player.spawn(arena, resolution, tilesize);
		
		if (state == State::LEVELING_UP) {
			if (event.key.code == Keyboard::Num1) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num2) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num3) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num4) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num5) {
				state = State::PLAYING;
			}
			if (event.key.code == Keyboard::Num6) {
				state = State::PLAYING;
			}
			if (state == State::PLAYING) {
				wave++;
				arena.left = 0;
				arena.top = 0;
				arena.width = 500;
				arena.height = 500;
				int tilesize = 50;
				player.spawn(arena, resolution, tilesize);
				clock.restart();
			}
		}
		clock.restart();
		if (state == State::PLAYING) {
			Time dt = clock.restart();
			float dtAsSeconds = dt.asSeconds();
			mouseScreenPosition = Mouse::getPosition();
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainview);
			player.update(dtAsSeconds, Mouse::getPosition());
			Vector2f playerPosition(player.getCenter());
			// Set the main view to the player's current position (center)
			mainview.setCenter(player.getCenter());

		}
		if (state == State::PLAYING) {
			window.clear();
			window.setView(mainview);
			window.draw(player.getSprite());
		}
		window.display();
	}
	return 0;
}
