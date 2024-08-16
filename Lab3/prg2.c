#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 20

void display_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[1024];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
        if (++line_count >= LINES_PER_PAGE) {
            printf("\n-- More --\n");
            line_count = 0;
            getchar(); 
        }
    }

    if (line_count > 0) {
        printf("\n-- End of file --\n");
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ... fileN]\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        printf("\n=== %s ===\n", argv[i]);
        display_file(argv[i]);
    }

    return EXIT_SUCCESS;
}

