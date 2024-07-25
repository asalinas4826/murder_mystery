#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "util.h"
#include "sprite.h"
#include "player.h"
#include "notes.h"
#include "dialogue.h"

enum mode {
	MOVE,
	NOTES,
	DIALOGUE
};

void setUpWindow() {
	InitWindow(INITIAL_HEIGHT * ASPECT_RATIO, INITIAL_HEIGHT, "murder game");
	ASSERT(
		IsWindowReady(),
		"Failed to create window.\n"
	);
	printf("initalized window\n");

	SetTargetFPS(30);
	SetExitKey(KEY_NULL);
}

Sprite loadScene(DynArray* textures, char* pathname) {
	Texture2D scene_texture = LoadTexture(pathname);
	ASSERT(
			IsTextureReady(scene_texture),
			"Failed to load texture. \n"
	);
	PUSH(*textures, scene_texture, sizeof(Texture2D));

	Sprite scene = {
		.tex = scene_texture,
		.fps = 1,
		.width = 240,
		.height = 135
	};

	return scene;
}

i32 getFloorPos(i32 scene_height) {
	return scene_height - FLOOR_HEIGHT;
}

int main() {
	setUpWindow();

	DYN_ARRAY(textures, sizeof(Texture2D));
	Sprite scene = loadScene(&textures, "./resources/ui_demo.png");

	i32 floor_pos = getFloorPos(scene.height);

	Vector2 p_pos = {10.0f, floor_pos};
	Player player = loadPlayer(&textures, p_pos);

	Vector2 rochester_pos = {60.0f, floor_pos};
	EntityParams rochester_params = {
		.fps = 1,
		.width = 19,
		.height = 27,
		.pos = rochester_pos,
		.flipped = false,
		.path_to_texture = "./resources/mr_rochester.png"
	};
	Entity mr_rochester = loadStaticEntity(&textures, &rochester_params);

	Vector2 n_pos = {120.0f, floor_pos};
	EntityParams old_man_params = {
		.fps = 1,
		.width = 19,
		.height = 27,
		.pos = n_pos,
		.flipped = true,
		.path_to_texture = "./resources/mr_rochester.png"
	};
	Entity old_man = loadStaticEntity(&textures, &old_man_params);

	DYN_ARRAY(entity_list, sizeof(Entity));

	if (loadDialogue("./example.txt", &mr_rochester)) return 1;
	PUSH(entity_list, mr_rochester, sizeof(Entity));

	if (loadDialogue("./example_2.txt", &old_man)) return 1;
	PUSH(entity_list, old_man, sizeof(Entity));

	for (u16 i = 0; i < entity_list.size; i++) {
		(GET(entity_list, Entity, i)).id = i;
	}


	// INITIALIZE VARIABLES FOR LOOP
	enum mode mode = MOVE;

	Vector2 origin = {0.0f, 0.0f};
	Vector2 notes_pos = {185, 16};


	// INITIALIZE NOTES COMPONENT
	Textbox box = {
		.text = malloc(200 * sizeof(char)), 
		.size = 200, // total size allocated
		.width = 0, // starting index
		.max_width = GetScreenWidth() / 60,
		.font = GetFontDefault(),
		.font_size = 20,
	};
	box.text[0] = '\0';
	SetTextLineSpacing(20);

	Vector2 c_pos = {0.0f, 0.0f};
	TextField notes = {
		.box = box,
		.buffer = malloc((box.size + 25) * sizeof(char)), // char buffer
		.idx = 0, // cursor idx
		.buffer_idx = 0,
		.cursor_offset = 3,
		.cursor_pos = c_pos
	};
	for (u32 i = 0; i < box.size + 25; i++) {
		notes.buffer[i] = '\0';
	}


	// MAIN GAME LOOP
	i32 frames = 0;
	while (!WindowShouldClose()) {
		// SET UP FOR DRAWING
		ClearBackground(BLACK);

		// DRAW COMPONENTS
		BeginDrawing();

		DrawBackground(&scene, origin, frames);

		for (u16 i = 0; i < entity_list.size; i++) {
			drawEntityIdle(GET_PTR(entity_list, Entity, i), &scene, frames);
		}

		// DRAW PLAYER ACTION
		switch (mode) {
			case MOVE: {
				playerMove(&player, &scene, frames);
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
				drawPlayerIdle(&player, &scene, frames);
				break;
			}
			case DIALOGUE: {
				drawPlayerIdle(&player, &scene, frames);
				printf("%d\n", player.next_to_id);
				for (u16 i = 0; i < entity_list.size; i++) {
					Entity* e = GET_PTR(entity_list, Entity, i);
					if (e->id == player.next_to_id) {
						for (u16 j = 0; j < DIALOGUE_BUFF_SIZE; j++) {
							printf("%c", e->dialogue[j]);
						}

						printf("\n");
					}
				}
				break;
			}
			default: {}
		}

		f32 scale = (f32) GetScreenHeight() / scene.height;
		drawTextField(&notes, Vector2Scale(notes_pos, scale));

		// GET INPUT MODE
		if (IsKeyPressed(KEY_I)) {
			mode = NOTES;
		}
		else if (IsKeyPressed(KEY_ESCAPE)) {
			mode = MOVE;
		}
		else if (mode == MOVE &&
				IsKeyPressed(KEY_E)) {
			for (u16 i = 0; i < entity_list.size; i++) {
				if (isNextTo(&player, GET_PTR(entity_list, Entity, i))) {
					mode = DIALOGUE;
					player.next_to_id = (GET(entity_list, Entity, i)).id;
				}
			}
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
	FREE(entity_list);
	CloseWindow();
	return 0;
}
