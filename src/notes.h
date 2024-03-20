#ifndef NOTES_H
#define NOTES_H

#include "util.h"
#include "textbox.h"

typedef struct {
	Textbox box;
	i32 idx;
	i32 cursor_offset;
	Vector2 cursor_pos;
} TextField;

i32 lineIndex(i32 start, Textbox* box);
void cursorLeft(TextField* notes);
void cursorRight(TextField* notes);
void drawTextField(TextField* notes, Vector2 pos);
void takeNotes(TextField* notes);

#endif
