#include <SDL.h>
#include "Game.h"
#include "Graphics.h"
#include "Input.h"

namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	Graphics graphics;
	SDL_Event event;
	Input input;
	_player = AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, 100, 100, 100);
	_player.setupAnimations();
	_player.playAnimation("RunLeft");

	int LAST_UPDATE_TIME = SDL_GetTicks();

	while (true) {
		// clear input from keys on a new frame
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				if (event.key.repeat == 0) {
					input.keyUpEvent(event);
				}
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	_player.draw(graphics, 100, 100);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	_player.update(elapsedTime);
}