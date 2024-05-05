#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "util.h"
#include "sprite.h"

typedef struct {
	Sprite idle;
	Sprite walk;
	Vector2 pos;
	bool flipped;
	u16 next_to_id;
} Player;


void drawPlayerIdle(Player* player, 
										Sprite* scene, 
										f32 scale, 
										i32 frame);

void playerMove(Player* player, 
								Sprite* scene, 
								f32 scale, 
								i32 frame);

bool isNextTo(Player* player, Entity* entity);

#endif
