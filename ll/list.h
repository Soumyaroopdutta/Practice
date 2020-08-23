#pragma once
#include <iostream.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
    union {
        struct ListNode* child;
        struct ListNode* prev;
    }
} ListNode;

typedef struct List {
    struct ListNode* head;
    struct ListNode* tail;
} List;

void appendToList(struct List* list, struct ListNode* node);
struct ListNode* extractHead(struct List* list);
