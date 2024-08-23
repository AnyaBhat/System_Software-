#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <existing_file> <new_link>\n", argv[0]);
        return 1;
    }

    const char *old_path = argv[1];
    const char *new_path = argv[2];

    // Create a new hard link
    if (link(old_path, new_path) != 0) {
        perror("link");
        return 1;
    }

    printf("New hard link created: %s -> %s\n", new_path, old_path);

    // Unlink (delete) the new hard link
    if (unlink(new_path) != 0) {
        perror("unlink");
        return 1;
    }

    printf("Hard link %s has been unlinked successfully.\n", new_path);

    return 0;
}

