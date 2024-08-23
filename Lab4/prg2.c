#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    struct stat sb;
    int ret = stat(argv[1], &sb);
    if (ret) {
        perror("stat");
        return 1;
    }

    printf("File information of %s\n", argv[1]);
    printf("SIZE              : %lld bytes\n", (long long)sb.st_size);
    printf("DEVICE            : %ld\n", (long)sb.st_dev);
    printf("INODE             : %ld\n", (long)sb.st_ino);
    printf("MODE              : %o\n", (unsigned int)sb.st_mode);
    printf("ACCESS TIME       : %s", ctime(&sb.st_atime));
    printf("MODIFICATION TIME : %s", ctime(&sb.st_mtime));

    return 0;
}

