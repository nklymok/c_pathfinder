#include "libmx.h"

void mx_pop_front(t_list **list) {
    t_list *head_to_remove;
    t_list *new_head;

    if (!list || !*list)
        return;
    head_to_remove = *list;
    new_head = head_to_remove->next;
    free(head_to_remove);
    head_to_remove = NULL;
    *list = new_head;
}

/*#include <stdio.h>
int main() {
    char *data1 = (char *) malloc(sizeof(char) * 5);
    data1[0] = 'c';
    data1[1] = 'o';
    data1[2] = 'd';
    data1[3] = '1';
    data1[4] = '\0';
    char *data2 = (char *) malloc(sizeof(char) * 5);
    data2[0] = 'c';
    data2[1] = 'o';
    data2[2] = 'd';
    data2[3] = '2';
    data2[4] = '\0';
    t_list *list = mx_create_node(data1);
    list->next = mx_create_node(data2);
    printf("before deleteion\n");
    for (t_list *head = list; head; head = head->next) {
        printf("%s ", (char *)head->data);
    }
    mx_pop_front(&list);
    printf("\nafter deleteion\n");
    for (t_list *head = list; head; head = head->next) {
        printf("%s ", (char *)head->data);
    }
}*/
