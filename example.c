#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define SIZE 50

int main()
{

    // arrays

    int *arr = malloc(sizeof(int) * SIZE);

    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = i;
    }

    // print arr
    printf("Printing array: \n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d, \t", arr[i]);
    }

    // freeing
    free(arr);

    // linked lists

    typedef struct Node
    {
        int data;
        struct Node *next;
    } Node;

    Node *head = malloc(sizeof(Node));

    Node *current = head;

    for (int i = 0; i < SIZE; i++)
    {

        if (i == SIZE - 1)
        {
            current->data = i;
            current->next = NULL;
            break;
        }
        current->data = i;
        current->next = malloc(sizeof(Node));
        current = current->next;
    }

    // Printing linked lists
    printf("\nPrinting Linked Lists\n");
    for (Node *current = head; current != NULL; current = current->next)
    {
        printf("%d, \t", current->data);
    }

    // Free the linked list
    current = head;
    while (current != NULL)
    {
        Node *next_node = current->next;
        free(current);
        current = next_node;
    }
    printf("\n\n");

    return EXIT_SUCCESS;
}