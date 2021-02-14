#include "libmx.h"

bool mx_file_exists(const char *filename) {
    int fd;

    if (!filename) {
        return 0;
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        close(fd);
        return 0;
    }
    close(fd);
    return 1;
}
