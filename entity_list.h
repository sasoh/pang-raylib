#pragma once
#include "entity.h"

typedef struct {
    Entity* entity;
    struct Entity_list_node* next;
} Entity_list_node;

typedef struct {
    Entity_list_node* head;
} Entity_list;

void entity_list_append(Entity_list* list, Entity* e);
void entity_list_remove(Entity_list* list, Entity* e);
void entity_list_print(Entity_list* list);
void entity_list_destroy(Entity_list* list);