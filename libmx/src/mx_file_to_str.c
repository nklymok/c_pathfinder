#include "libmx.h"

char *mx_file_to_str(const char *filename) {
    char buf[80];
    int byte_count = 0;
    int size = 0;
    int fd;

    if (!filename) {
        return NULL;
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    byte_count = read(fd, &buf, sizeof(buf));
    while (byte_count != 0) {
        size += byte_count;
        byte_count = read(fd, &buf, sizeof(buf));
    }
    close(fd);
    char *result = mx_strnew(size);
    fd = open(filename, O_RDONLY);
    byte_count = read(fd, result, size);
    close(fd);
    return result;
}
