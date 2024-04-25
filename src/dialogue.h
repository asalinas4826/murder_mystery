#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "util.h"
#include "textbox.h"

int loadDialogue(const char* path);
void parseDialogue(char* buffer, usize bytes_read, Sentence* sentence);

#endif
