#include "libmx.h"

bool mx_file_is_empty(const char *filename) {
    char* buf;
    int fd;
    bool result = true;

    if (mx_file_exists(filename)) {
        fd = open(filename, O_RDONLY);
        buf = mx_strnew(1);
        read(fd, buf, 1);
        if(buf && mx_strlen(buf) > 0) result = false;
    }
    mx_strdel(&buf);
    return result;
}
