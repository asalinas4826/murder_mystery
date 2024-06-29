#include "entity.h"

Entity loadStaticEntity(DynArray* textures, EntityParams* params) {
	Texture2D texture = LoadTexture(params->path_to_texture);
	ASSERT(
		IsTextureReady(texture),
		"Failed to load texture. \n"
	);
	PUSH(*textures, texture, sizeof(Texture2D));

	Sprite sprite = {
		.tex = texture,
		.fps = params->fps,
		.width = params->width,
		.height = params->height
	};

	params->pos.y -= sprite.height;
	Entity e = {
		.idle = sprite,
		.walk = sprite,
		.pos = params->pos,
		.flipped = params->flipped
	};

	return e;
}

void drawEntityIdle(Entity* e, Sprite* scene, i32 frame) {
	f32 scale = (f32) GetScreenHeight() / scene->height;
	DrawSprite(&(e->idle), e->flipped, scene, Vector2Scale(e->pos, scale), frame);
}

