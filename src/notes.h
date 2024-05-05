#ifndef NOTES_H
#define NOTES_H

#include "util.h"
#include "textbox.h"

typedef struct {
	Textbox box;
	char* buffer;
	i32 idx;
	i32 buffer_idx;
	i32 cursor_offset;
	Vector2 cursor_pos;
} TextField;

void cursorLeft(TextField* notes, char del);
void cursorRight(TextField* notes);
void drawTextField(TextField* notes, Vector2 pos);
void takeNotes(TextField* notes);

#endif
