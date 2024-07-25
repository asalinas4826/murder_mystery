#ifndef ENTITY_H
#define ENTITY_H

#include "util.h"
#include "sprite.h"

#define DIALOGUE_BUFF_SIZE 1024

typedef struct {
	Sprite idle;
	Sprite walk;
	Vector2 pos;
	bool flipped;
	u16 id;
	char dialogue[DIALOGUE_BUFF_SIZE];
} Entity;

typedef struct {
	i32 fps;
	i32 width;
	i32 height;
	Vector2 pos;
	bool flipped;
	char* path_to_texture;
} EntityParams;

Entity loadStaticEntity(DynArray* textures, EntityParams* params);

void drawEntityIdle(Entity* e, 
										Sprite* scene, 
										i32 frame);

#endif
