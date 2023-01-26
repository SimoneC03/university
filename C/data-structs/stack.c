#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

void push(Node **, int);
void printStack(Node **);
int pop(Node **);
int stackLength(Node **);
void deallocateStack(Node **);
int isEmpty(Node **);

void main() {
  Node *root = NULL;
  push(&root, 3);
  push(&root, 4);
  push(&root, 5);
  push(&root, 6);
  pop(&root);
  printf("\nStack elements: \n\n");
  printStack(&root);
  printf("\nStack length: %d\n", stackLength(&root));
  deallocateStack(&root);
}

int isEmpty(Node **root) {
  if(*root == NULL)
    return 1;
  else
    return -1;
}

void push(Node **root, int value) {
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
void printStack(Node **root) {
  for (Node *current = *root; current != NULL; current = current->next)
    printf("%d\n", current->value);
}

int pop(Node **root) {
  if(*root == NULL) 
    return -1;
  for (Node *current = *root; current != NULL; current = current->next)
    if(current->next->next == NULL) {
      int temp = current->next->value;
      current->next = NULL;
      return temp;
    }
}

int stackLength(Node **root) {
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

void deallocateStack(Node **root) {
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