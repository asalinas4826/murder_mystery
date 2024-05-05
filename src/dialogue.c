#include "dialogue.h"

int loadDialogue(const char* path, Entity* e) {
	FILE* dialogue_file = fopen(path, "r");
	if (dialogue_file == NULL) {
		printf("Dialogue does not exist or cannot be opened\n");
		return 1;
	}
	DYN_ARRAY(sentences, sizeof(Sentence));

	usize bytes_read;
	while (!feof(dialogue_file)) {
		bytes_read = fread(e->dialogue, sizeof(char), DIALOGUE_BUFF_SIZE, dialogue_file);
		if (bytes_read == 0 && !feof(dialogue_file)) {
			printf("Failed to read dialogue file\n");
			return 1;
		}
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


