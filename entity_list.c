#include "entity_list.h"
#include <stdlib.h>
#include <stdio.h>

void entity_list_append(Entity_list* list, Entity* e)
{
    Entity_list_node* next = malloc(sizeof(Entity_list_node));
    if (next == NULL) {
        printf("Allocating memory for entity list element failed!\n");
        return;
    }
    next->entity = e;
    next->next = NULL;

    if (list->head == NULL) {
        list->head = next;
    }
    else {
        Entity_list_node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = next;
    }
}

void entity_list_remove(Entity_list* list, Entity* e)
{
    Entity_list_node* current = list->head;
    while (current->next != NULL) {
        Entity_list_node* next = current->next;
        if (next->entity == e) {
            current->next = next->next;
            break;
        }
        current = current->next;
    }
}

void entity_list_print(Entity_list* head)
{
    Entity_list_node* current = head->head;
    printf("Node = %f %f\n", current->entity->dimensions.x, current->entity->dimensions.y);
    while ((current = current->next) != NULL) {
        printf("Node = %f %f\n", current->entity->dimensions.x, current->entity->dimensions.y);
    }
}

void entity_list_destroy(Entity_list* list)
{
    Entity_list_node *current = list->head;
    while (current != NULL) {
        Entity_list_node *next = current->next;
        free(current);
        current = next;
    }
}