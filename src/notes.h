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

void removeChar(Textbox* box, u32 idx);
void insertChar(Textbox* box, char c, u32 idx);
u32 lineIndex(i32 start, char* buffer);
u32 lineWidth(i32 start, char* buffer);
void cursorLeft(TextField* notes, char del);
void cursorRight(TextField* notes);
void drawTextField(TextField* notes, Vector2 pos);
void fillBuffer(TextField* notes);
void takeNotes(TextField* notes);

#endif
