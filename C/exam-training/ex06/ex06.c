#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char word[100];
  unsigned int count;
} Row;

typedef struct Node {
  Row value;
  struct Node *next;
} Node;

unsigned int readN(char **);
Node *readFile(char *);
void insertEnd(Node **, Row);
void printList(Node **);
void resetCharArray(char[], int);
void filterList(Node **, int);

void filterList(Node **root, int n) {
  Node *current = *root;
  while(current->next != NULL) {
    if(current->next->value.count < n) {
      Node *temp = current->next;
      current->next = current->next->next;
      free(temp);
    }
    else
      current = current->next;
  }
  current = *root;
  if(current->value.count < n) {
    Node *temp = current;
    *root = current->next;
    free(current);
  }
}

void resetCharArray(char arr[], int length) {
  for(int i = 0; i < length; i++)
    arr[i] = '\0';
}

void printList(Node **root) {
  printf("\nList:\n");
  for(Node *current = *root; current != NULL; current = current->next)
    printf("Word: %s, Count: %u\n", current->value.word, current->value.count);
}

void insertEnd(Node **root, Row value) {
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

Node *readFile(char *name) {
  Node *root = NULL;
  FILE *file = fopen(name, "r");
  if(file == NULL) {
    fprintf(stderr, "Error during opening the file");
    exit(1);
  }
  char *word = malloc(sizeof(char) * 100);
  char row[1000];
  int rowIndex = 0;
  unsigned int wordCounter = 0;
  int spacesIndex = -1;
  while(1) {
    char c = fgetc(file);
    row[rowIndex] = c;
    if(c == ' ' || c == '\n' || feof(file)) {
      if(wordCounter == 0) {
        for(int ii = 0; ii < rowIndex; ii++)
          word[ii] = row[ii];
        wordCounter++;
      } else {
        int tempLength = rowIndex - (spacesIndex + 1);
        char toCompare[tempLength];
        int iii = 0;
        for(int ii = spacesIndex+1; ii < rowIndex; ii++) {
          toCompare[iii] = row[ii];
          iii++;
        }
        if(strcmp(word, toCompare) == 0) {
          wordCounter++;
        }
      }
      spacesIndex = rowIndex;
    }
    rowIndex++;
    if(c == '\n' || feof(file)) {
      Row toInsert;
      strcpy(toInsert.word, word);
      toInsert.count = wordCounter;
      insertEnd(&root, toInsert);
      rowIndex = 0;
      wordCounter = 0;
      resetCharArray(word, 100);
      if(feof(file))
        break;
    }
  }
  fclose(file);
  return root;
}

unsigned int readN(char **argv) {
  int n = (argv[1] != NULL) ? atoi(argv[1]) : -1;
  if(n > 0) {
    return n;
  }
  else {
    fprintf(stderr, "\nInvalid argument\n");
    exit(1);
  }
}

void main(int argc, char **argv) {
  unsigned int n = readN(argv);
  Node *root = readFile("input.txt");
  printList(&root);
  filterList(&root, n);
  printList(&root);
}