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

typedef struct {
	char* text;
	u32 size; // total memory allocated
	u32 width; // chars in current line
	u32 max_width; // max chars per line
	Font font;
	f32 font_size;
} Textbox;

void takeNotes(Textbox* notes) {
	char in = '\0';
	in = GetCharPressed();

	if (in != 0 && TextLength(notes->text) < notes->size - 1) { // chars
		notes->text[TextLength(notes->text) + 1] = notes->text[TextLength(notes->text)];
		notes->text[TextLength(notes->text)] = in;
		notes->width++;
		if (notes->width >= notes->max_width) {
			notes->text[TextLength(notes->text) + 1] = notes->text[TextLength(notes->text)];
			notes->text[TextLength(notes->text)] = '\n';
			notes->width = 0;
		}
	}
	else if (IsKeyPressed(KEY_ENTER) && TextLength(notes->text) < notes->size - 1) { // \n
		notes->text[TextLength(notes->text) + 1] = notes->text[TextLength(notes->text)];
		notes->text[TextLength(notes->text)] = '\n';
		notes->width = 0;
	}
	else if (IsKeyPressed(KEY_BACKSPACE) && TextLength(notes->text) > 0) { // backspace
		notes->text[TextLength(notes->text) - 1] = '\0';
		if (notes->width > 0) {
			notes->width--;
		}
		else {
			i32 i = TextLength(notes->text) - 1; // last '\n' char
			while (i >= 0 && notes->text[i] != '\n') {
				notes->width++;
				i--;
			}
		}
	}
}

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

	Textbox notes = {
		malloc(200 * sizeof(char)),
		200,
		0,
		GetScreenWidth() / 60,
		GetFontDefault(),
		20,
	};
	notes.text[0] = '\0';
	SetTextLineSpacing(20);

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
				takeNotes(&notes);
				drawPlayerIdle(&player, &scene, scale, frames);
				break;
			}
			default: {}
		}

		DrawTextEx(notes.font, notes.text, Vector2Scale(notes_pos, scale), notes.font_size, 4, WHITE); 

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
	free(notes.text);
	UnloadTexture(scene.tex);
	CloseWindow();
	return 0;
}
