#include "libmx.h"

//
// put everything from previous buffer until delimiter, continue to while
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *buf;
    int bytecount_sum = 0;
    int bytecount = 0;
    int pos = 0;

    // reads the buffer into given pointer until delim
    // if there's delim, return how many bytes were moved from buffer
    if (buf && mx_strlen(buf) > 0) {
        for (int i = 1; i < mx_strlen(buf); i++) {
            if (buf[i] != delim) {
                (*lineptr)[pos] = buf[i];
                pos++;
                bytecount_sum++;
            } else
                return bytecount_sum;
        }
    }
    // delete prev buffer if necessary and create new buffer
    if (buf) mx_strdel(&buf);
    buf = mx_strnew(buf_size);
    bytecount = read(fd, buf, buf_size);
    // if error reading, return -1
    if (bytecount == -1) return -2;
    if (bytecount == 0) return -1;
    bytecount_sum += bytecount;
    // reads the bytes into given pointer until delim or EOF
    while (bytecount != 0 && bytecount != -1) {
        for (int i = 0; i < bytecount; i++) {
            if (buf[i] != delim) {
                (*lineptr)[pos] = buf[i];
                pos++;
            } else {
                // if there's delim, put \0 instead.
                // also, save the buffer, so it can be used next time.
                (*lineptr)[pos] = '\0';
                char *new_buf = mx_strndup(&buf[i], buf_size - i);
                mx_strdel(&buf);
                buf = mx_strdup(new_buf);
                free(new_buf);
                return bytecount_sum - bytecount + i;
            }
        }
        bytecount = read(fd, buf, buf_size);
        bytecount_sum += bytecount;
    }
    return bytecount_sum;
}
