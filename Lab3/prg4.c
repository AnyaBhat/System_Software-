#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *sourceFile, *destFile;
    int ch;

    // Check for the correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    // Open the source file in read mode
    sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Open the destination file in write mode
    destFile = fopen(argv[2], "w");
    if (destFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }

    // Copy character by character from source to destination
    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(ch, destFile);
    }

    // Close the files
    fclose(sourceFile);
    fclose(destFile);

    printf("File copied successfully.\n");

    return 0;
}
