#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *head = *list;
    for (; head->next; head = head->next);
    head->next = mx_create_node(data);
}

/*#include <stdio.h>
int main(void) {
    char *data1 = (char *) malloc(sizeof(char) * 5);
    data1[0] = 'c';
    data1[1] = 'o';
    data1[2] = 'd';
    data1[3] = '1';
    data1[4] = '\0';
    t_list *list = mx_create_node(data1);
    char *data2 = (char *) malloc(sizeof(char) * 5);
    data2[0] = 'c';
    data2[1] = 'o';
    data2[2] = 'd';
    data2[3] = '2';
    data2[4] = '\0';
    mx_push_back(&list, data2);
    for (t_list *head = list; head; head = head->next) {
        printf("%s ", (char *)head->data);
    }
}*/
