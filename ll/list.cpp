#include "list.h"

void appendToList(List* list, ListNode* node) {
    assert(List && node);
    if (list->head == NULL) {
        head = node;
    } else {
        tail->next = node;
    }

    tail = node;
    tail->next = NULL;
}

ListNode* extractHead(List* list) {
    ListNode* result;

    assert(list);
    if (list->head == NULL) {
       return NULL;
    }
    assert(list->tail);

    result = list->head;

    if (list->tail == list->head) {
       list->tail = list->head = NULL;
    } else {
        list->head = list->head->next;
    }

    result->next = NULL;
    return result;
}
