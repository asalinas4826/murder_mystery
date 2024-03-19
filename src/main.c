#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util.h"
#include "sprite.h"

#define INITIAL_HEIGHT 640

int main() {
	InitWindow(INITIAL_HEIGHT * ASPECT_RATIO, INITIAL_HEIGHT, "murder game");
	ASSERT(
		IsWindowReady(),
		"Failed to create window.\n"
	);
	printf("initalized window\n");

	SetTargetFPS(30);

	Texture2D scene_texture = LoadTexture("./resources/demo_scene.png");
	ASSERT(
			IsTextureReady(scene_texture),
			"Failed to load texture. \n"
	);

	Texture2D player_texture = LoadTexture("./resources/butler.png");
	ASSERT(
			IsTextureReady(player_texture),
			"Failed to load texture. \n"
	);

	Sprite scene = {
		scene_texture,
		6,
		160,
		144
	};

	Sprite player = {
		player_texture,
		1,
		25,
		35
	};

	i32 frames = 0;
	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();

		i32 screen_height = GetScreenHeight();
		i32 screen_width = GetScreenWidth();

		f32 scale = (f32) screen_height / scene.height;

		Vector2 pos = {0.0f, 0.0f};
		DrawBackground(&scene, pos, screen_height, screen_width, scale, frames);

		pos.x += 50;
		DrawSprite(&player, &scene, pos, screen_height, screen_width, scale, frames);

		EndDrawing();
		frames++;
	}

	UnloadTexture(scene.tex);

	CloseWindow();
	return 0;
}
