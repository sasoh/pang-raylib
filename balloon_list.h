#pragma once
#include "balloon.h"

typedef struct Balloon_list_node Balloon_list_node;
struct Balloon_list_node {
    Balloon* balloon;
    struct Balloon_list_node* next;
};

typedef struct {
    Balloon_list_node *head;
} Balloon_list;

void balloon_list_append(Balloon_list* list, Balloon* e);
void balloon_list_remove(Balloon_list* list, Balloon* e);
void balloon_list_print(Balloon_list* list);
void balloon_list_destroy(Balloon_list* list);