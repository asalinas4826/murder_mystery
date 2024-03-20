#include "notes.h"

i32 lineIndex(i32 start, Textbox* box) {
	i32 width = 0;
	while (start >= 0 && box->text[start] != '\n') {
		width++;
		start--;
	}

	return width;
}

void cursorLeft(TextField* notes) {
	Textbox box = notes->box;
	if (notes->idx > 0) {
		char buff[2];
		buff[0] = box.text[notes->idx - 1];
		buff[1] = '\0';
		i32 char_width = MeasureText(buff, box.font_size);
		notes->cursor_pos.x -= char_width + 4;
		notes->idx--;

		if (notes->cursor_pos.x < 0) { // go up a line
			notes->cursor_pos.y -= box.font_size;
			notes->cursor_pos.x = 0;
			i32 i = notes->idx - 1;
			while (i >= 0 && box.text[i] != '\n') {
				buff[0] = box.text[i];
				buff[1] = '\0';
				notes->cursor_pos.x += MeasureText(buff, box.font_size) + 4;

				i--;
			}
		}
	}
}

void cursorRight(TextField* notes) {
	Textbox box = notes->box;
	if (box.text[notes->idx] != '\n' &&
			notes->idx < box.size) {
		char buff[2];
		buff[0] = box.text[notes->idx];
		buff[1] = '\0';
		i32 char_width = MeasureText(buff, box.font_size);
		notes->cursor_pos.x += char_width + 4;
		notes->idx++;
	}
	else if (notes->idx < box.size) {
		notes->idx++;
		notes->cursor_pos.x = 0;
		notes->cursor_pos.y += box.font_size;
	}
}

void drawTextField(TextField* notes, Vector2 pos) {
	Vector2 start_pos = Vector2Add(notes->cursor_pos, pos);
	start_pos.x -= notes->cursor_offset;
	Vector2 end_pos = {
		start_pos.x,
		start_pos.y + notes->box.font_size
	};
	
	DrawLineV(start_pos, end_pos, WHITE);
	DrawTextEx(notes->box.font, notes->box.text, pos, notes->box.font_size, 4, WHITE);
}

void takeNotes(TextField* notes) {
	char in = '\0';
	in = GetCharPressed();

	if (in != 0 && TextLength(notes->box.text) < notes->box.size - 1) { // chars
		notes->box.text[TextLength(notes->box.text) + 1] = notes->box.text[TextLength(notes->box.text)];
		notes->box.text[TextLength(notes->box.text)] = in;
		if (lineIndex(
					TextLength(notes->box.text), 
					&notes->box
				) >= notes->box.max_width) {
			notes->box.text[TextLength(notes->box.text) + 1] = notes->box.text[TextLength(notes->box.text)];
			notes->box.text[TextLength(notes->box.text)] = '\n';
			cursorRight(notes);
		}
		cursorRight(notes);
	}
	else if (IsKeyPressed(KEY_ENTER) && TextLength(notes->box.text) < notes->box.size - 1) { // \n
		notes->box.text[TextLength(notes->box.text) + 1] = notes->box.text[TextLength(notes->box.text)];
		notes->box.text[TextLength(notes->box.text)] = '\n';
		cursorRight(notes);
	}
	else if (IsKeyPressed(KEY_BACKSPACE) && TextLength(notes->box.text) > 0) { // backspace
		cursorLeft(notes);
		notes->box.text[TextLength(notes->box.text) - 1] = '\0';
	}
}
