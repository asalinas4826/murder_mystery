#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util.h"
#include "sprite.h"
#include "player.h"

#define INITIAL_HEIGHT 640
#define FLOOR_HEIGHT 32


enum mode {
	MOVE,
	NOTES
};

int main() {
	// SET UP WINDOW
	InitWindow(INITIAL_HEIGHT * ASPECT_RATIO, INITIAL_HEIGHT, "murder game");
	ASSERT(
		IsWindowReady(),
		"Failed to create window.\n"
	);
	printf("initalized window\n");

	SetTargetFPS(30);
	SetExitKey(KEY_NULL);

	// LOAD TEXTURES
	Texture2D scene_texture = LoadTexture("./resources/ui_demo.png");
	ASSERT(
			IsTextureReady(scene_texture),
			"Failed to load texture. \n"
	);

	Texture2D player_texture = LoadTexture("./resources/butler.png");
	ASSERT(
			IsTextureReady(player_texture),
			"Failed to load texture. \n"
	);

	Texture2D player_walk_texture = LoadTexture("./resources/butler_walk.png");

	Sprite scene = {
		scene_texture,
		1,
		240,
		135
	};

	Sprite player_sprite = {
		player_texture,
		1,
		25,
		35
	};

	Sprite player_walk = {
		player_walk_texture,
		5,
		25,
		35
	};

	Vector2 p_pos = {10.0f, scene.height - player_sprite.height - FLOOR_HEIGHT};
	Player player = {
		player_sprite,
		player_walk,
		p_pos,
		false
	};
	
	// INITIALIZE VARIABLES FOR LOOP
	enum mode mode = MOVE;

	Vector2 origin = {0.0f, 0.0f};
	Vector2 notes_pos = {180, 16};

	// MAIN GAME LOOP
	i32 frames = 0;
	while (!WindowShouldClose()) {
		// SET UP FOR DRAWING
		ClearBackground(BLACK);

		i32 screen_height = GetScreenHeight();
		i32 screen_width = GetScreenWidth();
		f32 scale = (f32) screen_height / scene.height;

		// DRAW COMPONENTS
		BeginDrawing();

		DrawBackground(&scene, origin, screen_height, screen_width, scale, frames);

		// GET MODE
		if (IsKeyPressed(KEY_I)) {
			mode = NOTES;
		}
		else if (IsKeyPressed(KEY_ESCAPE)) {
			mode = MOVE;
		}

		// DRAW PLAYER ACTION
		switch (mode) {
			case MOVE: {
				playerMove(&player, &scene, scale, frames);
				break;
			}
			case NOTES: {
				DrawTextEx(GetFontDefault(), "Hello world!", Vector2Scale(notes_pos, scale), 10, 1, WHITE); 
				drawPlayerIdle(&player, &scene, scale, frames);
				break;
			}
		}

		// END DRAWING AND INCREMENT FRAME COUNT
		EndDrawing();
		frames++;
	}

	// CLEAN UP
	UnloadTexture(scene.tex);
	CloseWindow();
	return 0;
}
