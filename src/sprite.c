#include "sprite.h"
#include <stdio.h>

void DrawSprite(Sprite* s, 
								bool flipped,
								Sprite* scene,
								Vector2 pos,
								i32 frame) {
	i32 texture_frame = 0;
	if (s->fps > 1) {
		texture_frame = (frame / s->fps) * s->height;
	}

	Rectangle src = {
		.x = 0,
		.y = texture_frame,
		.width = s->width,
		.height = s->height
	};

	f32 scale = (f32) GetScreenHeight() / scene->height;
	Rectangle dest = {
		.x = pos.x,
		.y = pos.y,
		.width = s->width * scale,
		.height = s->height * scale
	};

	if (flipped) {
		src.width *= -1;
	}

	if (scene != NULL) {
		dest.x += (GetScreenWidth() - (scene->width * scale)) / 2;
	}

	Vector2 origin = {0.0f, 0.0f};
	DrawTexturePro(s->tex, src, dest, origin, 0, WHITE);
}

void DrawBackground(Sprite* s, 
								Vector2 pos,
								i32 frame) {
	f32 scale = (f32) GetScreenHeight() / s->height;
	i32 offset = (GetScreenWidth() - (s->width * scale)) / 2;
	pos.x += offset;

	DrawSprite(s, false, s, pos, frame);
}
