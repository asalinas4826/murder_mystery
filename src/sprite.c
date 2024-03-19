#include "sprite.h"
#include <stdio.h>

void DrawSprite(Sprite* s, 
								Sprite* scene,
								Vector2 pos,
								i32 screen_height, 
								i32 screen_width,
								f32 scale,
								i32 frame) {
	i32 texture_frame = (frame / s->fps) * s->height;

	Rectangle src = {
		0,
		texture_frame,
		s->width,
		s->height
	};

	Rectangle dest = {
		pos.x,
		pos.y,
		s->width * scale,
		s->height * scale
	};

	if (scene != NULL) {
		dest.x += (screen_width - (scene->width * scale)) / 2;
	}

	Vector2 origin = {0.0f, 0.0f};
	DrawTexturePro(s->tex, src, dest, origin, 0, WHITE);
}

void DrawBackground(Sprite* s, 
								Vector2 pos,
								i32 screen_height, 
								i32 screen_width,
								f32 scale,
								i32 frame) {
	i32 offset = (screen_width - (s->width * scale)) / 2;
	pos.x += offset;
	DrawSprite(s, NULL, pos, screen_height, screen_width, scale, frame);
}
