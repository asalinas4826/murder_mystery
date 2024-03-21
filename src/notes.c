#include "notes.h"

void insertChar(Textbox* box, char c, u32 idx) {
	u32 len = TextLength(box->text);
	if (len >= box->size - 1) {
		return;
	}

	for (u32 i = len + 1; i > idx; i--) {
		box->text[i] = box->text[i - 1];
	}
	box->text[idx] = c;
}

void removeChar(Textbox* box, u32 idx) {
	u32 len = TextLength(box->text);

	if (len <= 0) {
		return;
	}

	for (u32 i = idx; i < len - 1; i++) {
		box->text[i] = box->text[i + 1];
	}
	box->text[len - 1] = '\0';
}

u32 lineIndex(i32 start, char* buffer) {
	u32 width = 0;
	while (start >= 0 && buffer[start] != '\n') {
		width++;
		start--;
	}

	return width;
}

u32 lineWidth(i32 start, char* buffer) {
	while (buffer[start] != '\n' && buffer[start] != '\0') {
		start++;
	}

	return lineIndex(start - 1, buffer);
}

void cursorLeft(TextField* notes, char del) {
	if (notes->buffer_idx <= 0) {
		return;
	}
	notes->buffer_idx--;
	printf("%c\n", notes->buffer[notes->buffer_idx]);

	char buff[2];
	if (del != '\0') {
		buff[0] = del;
	}
	else {
		buff[0] = notes->buffer[notes->buffer_idx];
	}
	
	buff[1] = '\0';
	i32 char_width = MeasureText(buff, notes->box.font_size);
	notes->cursor_pos.x -= char_width + 4;

	if (notes->cursor_pos.x < 0) { // go up a line
		notes->cursor_pos.y -= notes->box.font_size;
		notes->cursor_pos.x = 0;
		i32 i = notes->buffer_idx - 1;
		bool user_defined = lineWidth(notes->buffer_idx, notes->buffer) < notes->box.max_width - 1;
		printf("%d\n", notes->box.max_width);
		printf("w: %d, u: %d\n", lineWidth(notes->buffer_idx, notes->buffer), user_defined);
		while (i >= 0 && notes->buffer[i] != '\n') {
			buff[0] = notes->buffer[i];
			buff[1] = '\0';
			notes->cursor_pos.x += MeasureText(buff, notes->box.font_size) + 4;

			i--;
		}
		if (!user_defined && del == '\0') {
			notes->idx++;
		}
		else if (!user_defined) {
			cursorLeft(notes, '\0');
		}
	}

	printf("buff: %d\n", notes->buffer_idx);
}

void cursorRight(TextField* notes) {
	if (notes->buffer[notes->buffer_idx] == '\0') {
		return;
	}
	if (notes->buffer[notes->buffer_idx] == '\n') {
		notes->cursor_pos.x = 0;
		notes->cursor_pos.y += notes->box.font_size;

		bool user_defined = lineWidth(notes->buffer_idx, notes->buffer) < notes->box.max_width - 1;
		// printf("w: %d, u: %d\n", lineWidth(notes->buffer_idx, notes->buffer), user_defined);

		printf("here\n");
		notes->buffer_idx++;
		if (!user_defined) {
			notes->idx--;
		}

	}
	else {
		char buff[2];
		buff[0] = notes->buffer[notes->buffer_idx];
		buff[1] = '\0';
		i32 char_width = MeasureText(buff, notes->box.font_size);
		notes->cursor_pos.x += char_width + 4;
		notes->buffer_idx++;
	}

	printf("%c\n", notes->buffer[notes->buffer_idx]);
	printf("buff: %d\n", notes->buffer_idx);
}

void drawTextField(TextField* notes, Vector2 pos) {
	Vector2 start_pos = Vector2Add(notes->cursor_pos, pos);
	start_pos.x -= notes->cursor_offset;
	Vector2 end_pos = {
		start_pos.x,
		start_pos.y + notes->box.font_size
	};
	
	DrawLineV(start_pos, end_pos, WHITE);
	DrawTextEx(notes->box.font, notes->buffer, pos, notes->box.font_size, 4, WHITE);
}

void fillBuffer(TextField* notes) {
	// clear buffer
	u32 j = 0;
	while (notes->buffer[j] != '\0') {
		notes->buffer[j] = '\0';
		j++;
	}
	// fill buffer w/ new values
	j = 0;
	u32 i = 0;
	u32 width = 0;

	while (notes->box.text[i] != '\0') {
		width++;
		if (notes->box.text[i] == '\n') {
			// printf("new line");
			width = 0;
		}
		else if (width >= notes->box.max_width) {
			// printf("line wrap\n");
			notes->buffer[j] = '\n';
			width = 0;
			j++;
		}
		notes->buffer[j] = notes->box.text[i];

		j++;
		i++;
	}
	notes->buffer[j] = '\0';
}

void takeNotes(TextField* notes) {
	char in = '\0';
	in = GetCharPressed();

	if (in != 0 && TextLength(notes->box.text) < notes->box.size - 1) { // chars
		insertChar(&(notes->box), in, notes->idx);
		fillBuffer(notes);
		cursorRight(notes);
		notes->idx++;

		bool user_defined = lineWidth(notes->buffer_idx - 1, notes->buffer) < notes->box.max_width - 1;
		if (!user_defined && notes->buffer[notes->buffer_idx - 1] == '\n') {
			notes->idx++;
		}

		if (notes->cursor_pos.x == 0) {
			cursorRight(notes);
		}
		printf("idx: %d\n", notes->idx);
	}
	else if (IsKeyPressed(KEY_ENTER) && TextLength(notes->box.text) < notes->box.size - 1) { // \n
		insertChar(&(notes->box), '\n', notes->idx);
		fillBuffer(notes);
		cursorRight(notes);
		notes->idx++;

		printf("idx: %d\n", notes->idx);
	}
	else if (IsKeyPressed(KEY_BACKSPACE) && TextLength(notes->box.text) > 0) { // backspace
		notes->idx--;
		char del = notes->box.text[notes->idx];

		removeChar(&(notes->box), notes->idx);
		fillBuffer(notes);
		cursorLeft(notes, del);
		printf("idx: %d\n", notes->idx);
	}
}
