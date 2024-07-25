#include "player.h"

Player loadPlayer(DynArray* textures, Vector2 pos) {
	Texture2D player_texture = LoadTexture("./resources/butler.png");
	ASSERT(
			IsTextureReady(player_texture),
			"Failed to load texture. \n"
	);
	PUSH(*textures, player_texture, sizeof(Texture2D));

	Texture2D player_walk_texture = LoadTexture("./resources/butler_walk.png");
	ASSERT(
			IsTextureReady(player_walk_texture),
			"Failed to load texture. \n"
	);
	PUSH(*textures, player_walk_texture, sizeof(Texture2D));

	Sprite player_sprite = {
		.tex = player_texture,
		.fps = 1,
		.width = 25,
		.height = 35
	};

	Sprite player_walk = {
		.tex = player_walk_texture,
		.fps = 5,
		.width = 25,
		.height = 35
	};

	pos.y -= player_sprite.height;
	Player player = {
		.idle = player_sprite,
		.walk = player_walk,
		.pos = pos,
		.flipped = false,
		.next_to_id = 0
	};

	return player;
}

void drawPlayerIdle(Player* player, Sprite* scene, i32 frame) {
	f32 scale = (f32) GetScreenHeight() / scene->height;
	DrawSprite(&(player->idle), player->flipped, scene, Vector2Scale(player->pos, scale), frame);
}

void playerMove(Player* player, Sprite* scene, i32 frame) {
	f32 scale = (f32) GetScreenHeight() / scene->height;
	if (IsKeyDown(KEY_D)) {
		player->pos.x += MOVE_SPEED;
		player->flipped = false;
		DrawSprite(&(player->walk), player->flipped, scene, Vector2Scale(player->pos, scale), frame);
	}
	else if (IsKeyDown(KEY_A)) {
		player->pos.x -= MOVE_SPEED;
		player->flipped = true;
		DrawSprite(&(player->walk), player->flipped, scene, Vector2Scale(player->pos, scale), frame);
	}
	else {
		drawPlayerIdle(player, scene, frame);
	}
}

bool isNextTo(Player* player, Entity* entity) {
	if ((player->pos.x + player->idle.width > entity->pos.x) && 
			(player->pos.x < entity->pos.x + entity->idle.width)) {
		return true;
	}
	return false;
}
