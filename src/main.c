#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "util.h"
#include "sprite.h"
#include "player.h"
#include "notes.h"
#include "dialogue.h"

#define INITIAL_HEIGHT 640
#define FLOOR_HEIGHT 32

enum mode {
	MOVE,
	NOTES,
	DIALOGUE
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
	DYN_ARRAY(textures, 0);
	Texture2D scene_texture = LoadTexture("./resources/ui_demo.png");
	ASSERT(
			IsTextureReady(scene_texture),
			"Failed to load texture. \n"
	);
	PUSH(textures, scene_texture, sizeof(Texture2D));

	Texture2D player_texture = LoadTexture("./resources/butler.png");
	ASSERT(
			IsTextureReady(player_texture),
			"Failed to load texture. \n"
	);
	PUSH(textures, player_texture, sizeof(Texture2D));

	Texture2D player_walk_texture = LoadTexture("./resources/butler_walk.png");
	ASSERT(
			IsTextureReady(player_walk_texture),
			"Failed to load texture. \n"
	);
	PUSH(textures, player_walk_texture, sizeof(Texture2D));

	Texture2D npc_texture = LoadTexture("./resources/mr_rochester.png");
	ASSERT(
		IsTextureReady(npc_texture),
		"Failed to load texture. \n"
	);
	PUSH(textures, npc_texture, sizeof(Texture2D));

	// SCENE SETUP
	Sprite scene = {
		scene_texture,
		1,
		240,
		135
	};

	Sprite npc_sprite = {
		npc_texture,
		1,
		19,
		27
	};

	Vector2 n_pos = {60.0f, scene.height - npc_sprite.height - FLOOR_HEIGHT};
	Entity mr_rochester = {
		npc_sprite,
		npc_sprite,
		n_pos,
		false,
	};


	// PLAYER SETUP
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

	// INITIALIZE NOTES COMPONENT
	Textbox box = {
		malloc(200 * sizeof(char)), 
		200, // total size allocated
		0, // starting index
		GetScreenWidth() / 60, // max line width
		GetFontDefault(), // font
		20, // font size
	};
	box.text[0] = '\0';
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

	// LOAD DIALOGUE
	if (loadDialogue("./example.txt", &mr_rochester)) return 1;

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

		drawEntityIdle(&mr_rochester, &scene, scale, frames);

		// DRAW PLAYER ACTION
		switch (mode) {
			case MOVE: {
				playerMove(&player, &scene, scale, frames);
				break;
			}
			case NOTES: {
				if (IsKeyPressed(KEY_RIGHT)) {
					cursorRight(&notes);
					if (notes.idx < notes.box.size && 
							notes.box.text[notes.idx] != '\0') {
						notes.idx++;
						// printf("idx: %d\n", notes.idx);
					}
				}
				else if (IsKeyPressed(KEY_LEFT)) {
					cursorLeft(&notes, '\0');
					if (notes.idx > 0) notes.idx--;
					// printf("idx: %d\n", notes.idx);
				}
				else {
					takeNotes(&notes);
				}
				drawPlayerIdle(&player, &scene, scale, frames);
				break;
			}
			case DIALOGUE: {
				drawPlayerIdle(&player, &scene, scale, frames);
				for (usize i = 0; i < DIALOGUE_BUFF_SIZE; i++) {
					printf("%c", mr_rochester.dialogue[i]);
				}
				printf("\n");
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
		else if (mode == MOVE &&
				isNextTo(&player, &mr_rochester) && 
				IsKeyPressed(KEY_E)) {
			mode = DIALOGUE;
		}
		else if (mode == DIALOGUE &&
				IsKeyPressed(KEY_ESCAPE)) {
			mode = MOVE;
		}

		// END DRAWING AND INCREMENT FRAME COUNT
		EndDrawing();
		frames++;
	}

	// CLEAN UP
	free(notes.box.text);
	free(notes.buffer);
	for (u32 i = 0; i < textures.size; i++) {
		UnloadTexture(GET(textures, Texture2D, i));
	}
	FREE(textures);
	CloseWindow();
	return 0;
}
