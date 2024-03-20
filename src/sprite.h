#ifndef SPRITE_H
#define SPRITE_H

#include "util.h"

typedef struct {
	Texture2D tex;
	i32 fps;
	i32 width;
	i32 height;
} Sprite;

void DrawSprite(Sprite* s, 
								bool flipped,
								Sprite* scene,
								Vector2 pos,
								i32 screen_height, 
								i32 screen_width,
								f32 scale,
								i32 frame);

void DrawBackground(Sprite* s,
										Vector2 pos,
										i32 screen_height,
										i32 screen_width,
										f32 scale,
										i32 frame);

#endif
