#ifndef TEXTBOX_H
#define TEXTBOX_H

typedef struct {
	char* text;
	u32 size; // total memory allocated
	u32 width; // chars in current line
	u32 max_width; // max chars per line
	Font font;
	f32 font_size;
} Textbox;

typedef struct {
	Textbox box;
	char* buffer;
} DialogueBox;

typedef struct {
	char* text;
	Rectangle bounds_one;
	Rectangle bounds_two;
} Sentence;

#endif
