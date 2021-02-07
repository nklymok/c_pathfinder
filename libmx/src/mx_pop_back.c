#include "libmx.h"

void mx_pop_back(t_list **list) {
    t_list *head;

    if (!list || !(*list))
        return;
    head = *list;
    if (!head->next) {
        free(head);
        *list = NULL;
        return;
    }
    while (head->next->next)
        head = head->next;
    free(head->next);
    head->next = NULL;
}
