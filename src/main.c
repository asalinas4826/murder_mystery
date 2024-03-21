#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "util.h"
#include "sprite.h"
#include "player.h"
#include "notes.h"

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
	ASSERT(
			IsTextureReady(player_walk_texture),
			"Failed to load texture. \n"
	);

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
	Vector2 notes_pos = {185, 16};

	Textbox box = {
		malloc(200 * sizeof(char)),
		200,
		0,
		GetScreenWidth() / 60,
		GetFontDefault(),
		20,
	};
	box.text[0] = '\0';
	// Textbox box = {
	// 	"hi, this is a box \nmes\nsage", // char[]
	// 	27, // total size allocated, including '\0'
	// 	0, // current line width
	// 	GetScreenWidth() / 60, // max line width
	// 	GetFontDefault(), // font
	// 	20 // font_size
	// };
	SetTextLineSpacing(20);

	Vector2 c_pos = {0.0f, 0.0f};
	TextField notes = {
		box,
		malloc((box.size + 25) * sizeof(char)), // char buffer
		0, // cursor idx
		0, // buffer idx
		3, // cursor offset
		c_pos // cursor position
	};
	for (u32 i = 0; i < box.size + 25; i++) {
		notes.buffer[i] = '\0';
	}

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

		// DRAW PLAYER ACTION
		switch (mode) {
			case MOVE: {
				playerMove(&player, &scene, scale, frames);
				break;
			}
			case NOTES: {
				// takeNotes(&box);
				if (IsKeyPressed(KEY_RIGHT)) {
					cursorRight(&notes);
					if (notes.idx < notes.box.size && 
							notes.box.text[notes.idx] != '\0') {
						notes.idx++;
						printf("idx: %d\n", notes.idx);
					}
				}
				else if (IsKeyPressed(KEY_LEFT)) {
					cursorLeft(&notes, '\0');
					if (notes.idx > 0) notes.idx--;
					printf("idx: %d\n", notes.idx);
				}
				else {
					takeNotes(&notes);
				}
				drawPlayerIdle(&player, &scene, scale, frames);
				break;
			}
			default: {}
		}

		drawTextField(&notes, Vector2Scale(notes_pos, scale));

		// GET INPUT MODE
		if (IsKeyPressed(KEY_I)) {
			mode = NOTES;
		}
		else if (IsKeyPressed(KEY_ESCAPE)) {
			mode = MOVE;
		}

		// END DRAWING AND INCREMENT FRAME COUNT
		EndDrawing();
		frames++;
	}

	// CLEAN UP
	free(notes.box.text);
	free(notes.buffer);
	UnloadTexture(scene.tex);
	CloseWindow();
	return 0;
}
