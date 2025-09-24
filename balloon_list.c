#include "balloon_list.h"
#include <stdlib.h>
#include <stdio.h>

void balloon_list_append(Balloon_list *list, Balloon *b)
{
    Balloon_list_node* next = malloc(sizeof(Balloon_list_node));
    if (next == NULL) {
        printf("Allocating memory for balloon list element failed!\n");
        return;
    }
    next->balloon = b;
    next->next = NULL;

    if (list->head == NULL) {
        list->head = next;
    }
    else {
        Balloon_list_node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = next;
    }
}

void balloon_list_remove(Balloon_list *list, Balloon *b)
{
    Balloon_list_node* current = list->head;
    while (current->next != NULL) {
        Balloon_list_node* next = current->next;
        if (next->balloon == b) {
            current->next = next->next;
            break;
        }
        current = current->next;
    }
}

void balloon_list_print(Balloon_list *list)
{
    Balloon_list_node* current = list->head;
    printf("Balloon = %f %f\n", current->balloon->entity.dimensions.x, current->balloon->entity.dimensions.y);
    while ((current = current->next) != NULL) {
        printf("Balloon = %f %f\n", current->balloon->entity.dimensions.x, current->balloon->entity.dimensions.y);
    }
}

void balloon_list_destroy(Balloon_list *list)
{
    Balloon_list_node* current = list->head;
    while (current != NULL) {
        Balloon_list_node* next = current->next;
        free(current);
        current = next;
    }
}