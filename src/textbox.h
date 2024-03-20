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

#endif
