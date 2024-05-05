#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "util.h"
#include "textbox.h"
#include "entity.h"

int loadDialogue(const char* path, Entity* e);
void parseDialogue(char* buffer, usize bytes_read, Sentence* sentence);

#endif
