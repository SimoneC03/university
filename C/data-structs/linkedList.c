#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int value;
  struct Node *next;
} Node;

void insertEnd(Node **, int);
void printList(Node **);

void main()
{
  Node *root = NULL;
  insertEnd(&root, 8);
  insertEnd(&root, 9);
  insertEnd(&root, 10);
  printList(&root);
}

void insertEnd(Node **root, int value)
{
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL)
  {
    exit(1);
  }
  newNode->value = value;
  newNode->next = NULL;
  if (*root == NULL)
  {
    *root = newNode;
    return;
  }
  Node *current = *root;
  while(current->next != NULL) {
    current = current->next; 
  }
  current->next = newNode;
}

void printList(Node **root)
{
  for (Node *current = *root; current != NULL; current = current->next)
  {
    printf("%d\n", current->value);
  }
}