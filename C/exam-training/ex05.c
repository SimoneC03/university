#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int N;
  char v, w;
} Arguments;

typedef struct Node {
  char value;
  struct Node *next;
} Node;

Arguments checkArgs(int, char **);
size_t isVowel(char);
void push(Node **, char);
char pop(Node **);
void printStack(Node **);

void printStack(Node **root) {
  for(Node *current = *root; current != NULL; current = current->next)
    printf("%c\n", current->value); 
}

char pop(Node **root) {
  if(*root == NULL) {
    printf("Stack is empty");
    return '-1';
  }
  for(Node *current = *root; current != NULL; current = current->next)
    if(current->next == NULL) {
      char temp = current->value;
      *root = NULL;
      return temp;
    } else if(current->next->next == NULL) {
      char temp = current->next->value;
      current->next = NULL;
      return temp;
    }
}

void push(Node **root, char value) {
  Node *newNode = malloc(sizeof(Node));
  if(newNode == NULL)
    exit(1);
  newNode->next = NULL;
  newNode->value = value;
  if(*root == NULL) {
    *root = newNode;
    return;
  }
  Node *current = *root;
  while(current->next != NULL)
    current = current->next;
  current->next = newNode;
}

size_t isVowel(char c) {
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ? 1 : 0;
}

Arguments checkArgs(int argc, char *argv[]) {
  int N = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  char v = (argv[2] != NULL) ? argv[2][0] : '-1';
  char w = (argv[3] != NULL) ? argv[3][0] : '-1';
  if(N >= 5 && N <= 9 && v >= 'a' && v <= 'z' && w >= 'a' && w <= 'z' && isVowel(v) && !isVowel(w)) {
    Arguments args = {N, v, w};
    return args;
  }
  else {
    fprintf(stderr, "Invalid arguments\n");
    exit(1);
  }
}

void main(int argc, char **argv) {
  Arguments args = checkArgs(argc, argv);
  Node *root = NULL;
  push(&root, 't');
  pop(&root);
  push(&root, 'b');
  push(&root, 't');
  pop(&root);
  printStack(&root);
}