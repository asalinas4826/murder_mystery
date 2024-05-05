#include "player.h"

void drawPlayerIdle(Player* player, Sprite* scene, f32 scale, i32 frame) {
	i32 screen_height = GetScreenHeight();
	i32 screen_width = GetScreenWidth();
	DrawSprite(&(player->idle), player->flipped, scene, Vector2Scale(player->pos, scale), screen_height, screen_width, scale, frame);
}

void playerMove(Player* player, Sprite* scene, f32 scale, i32 frame) {
	i32 screen_height = GetScreenHeight();
	i32 screen_width = GetScreenWidth();
	if (IsKeyDown(KEY_D)) {
		player->pos.x += MOVE_SPEED;
		player->flipped = false;
		DrawSprite(&(player->walk), player->flipped, scene, Vector2Scale(player->pos, scale), screen_height, screen_width, scale, frame);
	}
	else if (IsKeyDown(KEY_A)) {
		player->pos.x -= MOVE_SPEED;
		player->flipped = true;
		DrawSprite(&(player->walk), player->flipped, scene, Vector2Scale(player->pos, scale), screen_height, screen_width, scale, frame);
	}
	else {
		drawPlayerIdle(player, scene, scale, frame);
	}
}

bool isNextTo(Player* player, Entity* entity) {
	if ((player->pos.x + player->idle.width > entity->pos.x) && 
			(player->pos.x < entity->pos.x + entity->idle.width)) {
		return true;
	}
	return false;
}
