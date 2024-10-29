#include <stdio.h>

// 1MB
#define FILESIZE (1<<20)

unsigned char* interpret_char(char*, int*, unsigned char*);

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
		p = interpret_char(program, &i, p);
	}

	printf("\n");

	return 0;
}

unsigned char* interpret_char(char* program, int* i, unsigned char* p) {
	char c = program[*i];

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
		case '[': {
			int i0 = ++(*i);
			int ilast;
			while (*p) {
				while (program[*i] != ']') {
					p = interpret_char(program, i, p);
					(*i)++;
				}
				ilast = *i;
				*i = i0;
				(*p)--;
			}
			*i = ilast;
			break;
		}
		case ']': {
			return p;
		}
		// debug
		case '@': {
			printf(" %d", *p);
			break;
		}
		default: {
			break;
		}
	}

	return p;
}

