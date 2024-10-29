#include <stdio.h>

// 1MB
#define FILESIZE (1<<20)

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(stderr, "filepath to interpret required.\n");
		return 1;
	}

	char* filepath = argv[1];
	FILE* file = fopen(filepath, "r");

	if (!file) {
		fprintf(stderr, "error opening file.\n");
		return 1;
	}

	char program[FILESIZE];
	int bytes = fread(program, 1, FILESIZE, file);

	printf("%s\n", program);

	fclose(file);

	unsigned char mem[30000];
	unsigned char* p = mem;

	for (int i = 0; i < bytes; i++) {
		char c = program[i];

		switch (c) {
			case '+': {
				(*p)++;
				break;
			}
			case '-': {
				(*p)--;
				break;
			}
			case '>': {
				p++;
				break;
			}
			case '<': {
				p--;
				break;
			}
			case ',': {
				// TODO getchar
				break;
			}
			case '.': {
				putchar(*p);
				break;
			}
			// debug
			case '@': {
				printf("%d", *p);
				break;
			}
			default: {
				break;
			}
		}
	}

	printf("\n");

	return 0;
}
