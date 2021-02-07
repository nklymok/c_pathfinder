#include "libmx.h"

int mx_list_size(t_list *list) {
    int count;

    for(count = 0; list; list = list->next, count++);
    return count;
}

/*#include <stdio.h>
int main() {
    char *data1 = (char *) malloc(sizeof(char) * 5);
    data1[0] = 'c';
    data1[1] = 'o';
    data1[2] = 'd';
    data1[3] = '1';
    data1[4] = '\0';
    t_list *list = mx_create_node(data1);
    list->next = mx_create_node(data1);
    list->next->next = mx_create_node(data1);
    list->next->next->next = mx_create_node(data1);
    list->next->next->next->next = mx_create_node(data1);
    printf("size : %d\n", mx_list_size(list));
}*/
