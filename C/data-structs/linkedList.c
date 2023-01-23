#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

void insertEnd(Node **, int);
void insertStart(Node **, int);
void printList(Node **);
void insertAfter(Node *, int);
void removeElement(Node **, int);
int listLength(Node **);
void deallocateList(Node **);

void main() {
  Node *root = NULL;
  insertStart(&root, 1);
  insertStart(&root, 2);
  insertEnd(&root, 3);
  insertAfter(root->next->next, 4);
  removeElement(&root, 4);
  printList(&root);
  printf("List length: %d\n", listLength(&root));
  deallocateList(&root);
}

void insertEnd(Node **root, int value) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL)
    exit(1);
  newNode->value = value;
  newNode->next = NULL;
  if (*root == NULL) {
    *root = newNode;
    return;
  }
  Node *current = *root;
  while (current->next != NULL)
    current = current->next;
  current->next = newNode;
}

void insertStart(Node **root, int value) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL)
    exit(1);
  newNode->value = value;
  newNode->next = *root;
  *root = newNode;
}

void insertAfter(Node *node, int value) {
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL)
    exit(1);
  newNode->value = value;
  newNode->next = node->next;
  node->next = newNode;
}

void printList(Node **root) {
  for (Node *current = *root; current != NULL; current = current->next)
    printf("%d\n", current->value);
}

void removeElement(Node **root, int value) {
  if(*root == NULL) 
    return;
  for (Node *current = *root; current != NULL; current = current->next)
    if(current->next->value == value) {
      Node *toRemove = current->next;
      current->next = current->next->next;
      free(toRemove);
    }
}

int listLength(Node **root) {
  if(*root == NULL)
    return 0;
  Node *current = *root;
  int c = 0;
  while(current != NULL) {
    c++;
    current = current->next;
  }
  return c;
}

void deallocateList(Node **root) {
  if(*root == NULL)
    return;
  Node *current = *root;
  while(current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }
  *root = NULL;
}