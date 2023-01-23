#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int N;
  char w;
} Arguments;

typedef struct Node {
  char *value;
  struct Node *next;
} Node;

void insertString(Node **, char *);
void printList(Node **);
Arguments checkArgs(int, char **);
char *genString(int, char, char);
void fillList(Node **, int);
void deallocateList(Node **);
int listCharOccurrencies(Node **, char);

void main(int argc, char *argv[]) {
  Arguments arguments = checkArgs(argc, argv);
  int N = arguments.N;
  char w = arguments.w;
  Node *root = NULL;
  fillList(&root, N);
  printList(&root);
  printf("\nTotal \"%c\" occurrencies: %d\n", w, listCharOccurrencies(&root, w));
  deallocateList(&root);
}

Arguments checkArgs(int argc, char **argv) {
  int N = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  char w = (argv[2] != NULL) ? argv[2][0] : '-1';
  if (N >= 10 && N <= 20 && w >= 'a' && w <= 'z') {
    Arguments arguments = {N, w};
    printf("\nInsert: %d for N and '%c' for w\n\n", arguments.N, arguments.w);
    return arguments;
  }
  else {
    fprintf(stderr, "%s", "Invalid arguments\n");
    exit(0);
  }
}

char *genString(int length, char start, char end)
{
  char *str = malloc(sizeof(char) * length);
  int i;
  int st = (int)(start);
  int en = ((int)(end)) + 1;
  for (i = 0; i < length; i++)
    str[i] = (rand() % (en - st)) + st;
  return str;
}

// Insert a string at the end
void insertString(Node **root, char *value) {
  char *min = value;
  for (Node *current = *root; current != NULL; current = current->next)
    if(strcmp(min, current->value) > 0) {
      char *temp = min;
      min = current->value;
      current->value = temp;
    }
  Node *newNode = malloc(sizeof(Node));
  if (newNode == NULL)
    exit(1);
  newNode->value = min;
  if (*root == NULL) {
    *root = newNode;
    return;
  }
  newNode->next = *root;
  *root = newNode;
}

void printList(Node **root) {
  for (Node *current = *root; current != NULL; current = current->next)
    printf("%s\n", current->value);
}

void fillList(Node **root, int length) {
  for(int i = 0; i < length; i++) {
    int L = (rand() % (16 - 5)) + 5; // [5,15] interval
    char *string = genString(L, 'a', 'z');
    insertString(root, string);
  }
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

int listCharOccurrencies(Node **root, char c) {
  int j = 0;
  for (Node *current = *root; current != NULL; current = current->next)
    for (int i = 0; i < strlen(current->value); i++)
      if(current->value[i] == c)
        j++;
  return j;
}