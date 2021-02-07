#include "libmx.h"

void swap_data(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    t_list *head = NULL;
    t_list *t = NULL;

    for (t = lst; t != NULL; t = t->next) {
        for (head = t->next; head != NULL; head = head->next) {
            if (cmp(t->data, head->data) > 0) {
                swap_data(&t->data, &head->data);
            }
        }
    }
    return lst;
}
