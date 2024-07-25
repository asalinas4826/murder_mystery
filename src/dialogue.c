#include "dialogue.h"

static int readBytes(FILE* file, char* buffer) {
	usize bytes_read;
	while (!feof(file)) {
		bytes_read = fread(buffer, sizeof(char), DIALOGUE_BUFF_SIZE, file);
		if (bytes_read == 0 && !feof(file)) return 1;
	}

	return 0;
}

int loadDialogue(const char* path, Entity* e) {
	FILE* dialogue_file = fopen(path, "r");
	if (dialogue_file == NULL) {
		printf("Dialogue does not exist or cannot be opened.\n");
		return 1;
	}

	if (readBytes(dialogue_file, e->dialogue)) {
		printf("Dialogue file could not be read.\n");
		return 1;
	}

	fclose(dialogue_file);
	return 0;
}

void parseDialogue(char* buffer, usize bytes_read, Sentence* sentence) {
	for (usize i = 0; i < bytes_read; i++) {
		printf("%c", buffer[i]);
	}

	printf("\n");
}


