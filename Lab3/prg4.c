#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1 // We will read one character at a time

void copy_file(const char *source_path, const char *dest_path) {
    FILE *source_file = fopen(source_path, "r");
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    FILE *dest_file = fopen(dest_path, "w");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file);
        exit(EXIT_FAILURE);
    }

    int ch; // `int` is used to handle EOF properly

    // Read character-by-character from source and write to destination
    while ((ch = fgetc(source_file)) != EOF) {
        fputc(ch, dest_file);
    }

    // Close the files
    fclose(source_file);
    fclose(dest_file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <dest_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    copy_file(argv[1], argv[2]);

    return EXIT_SUCCESS;
}

