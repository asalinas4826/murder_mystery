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
	char dialogue[DIALOGUE_BUFF_SIZE];
} Entity;

void drawEntityIdle(Entity* e, 
										Sprite* scene, 
										f32 scale, 
										i32 frame);

void entityMove(Entity* e, 
								Sprite* scene, 
								f32 scale, 
								i32 frame);

#endif
