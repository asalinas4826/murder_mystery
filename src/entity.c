#include "entity.h"

void drawEntityIdle(Entity* e, Sprite* scene, f32 scale, i32 frame) {
	i32 screen_height = GetScreenHeight();
	i32 screen_width = GetScreenWidth();
	DrawSprite(&(e->idle), e->flipped, scene, Vector2Scale(e->pos, scale), screen_height, screen_width, scale, frame);
}

void entityMove(Entity* e, Sprite* scene, f32 scale, i32 frame) {
	i32 screen_height = GetScreenHeight();
	i32 screen_width = GetScreenWidth();
	if (IsKeyDown(KEY_D)) {
		e->pos.x += MOVE_SPEED;
		e->flipped = false;
		DrawSprite(&(e->walk), e->flipped, scene, Vector2Scale(e->pos, scale), screen_height, screen_width, scale, frame);
	}
	else if (IsKeyDown(KEY_A)) {
		e->pos.x -= MOVE_SPEED;
		e->flipped = true;
		DrawSprite(&(e->walk), e->flipped, scene, Vector2Scale(e->pos, scale), screen_height, screen_width, scale, frame);
	}
	else {
		drawEntityIdle(e, scene, scale, frame);
	}
}
