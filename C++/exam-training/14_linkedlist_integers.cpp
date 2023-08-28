#include <iostream>

using namespace std;

struct Node {
  int value;
  struct Node *next;
};


void insertHead(Node **head, int value) {
  Node *newNode = new Node;
  if (newNode == NULL)
    exit(1);
  newNode->value = value;
  newNode->next = *head;
  *head = newNode;
}

void insertEnd(Node **head, int value) {
  Node *newNode = new Node;
  if(newNode == NULL) exit(1);
  newNode->value = value;
  if(*head == NULL) {
    *head = newNode;
    return;
  }
  Node *current = *head;
  while(current->next != NULL) {
    current = current->next;
  }
  current->next = newNode;
}

void removeElement(Node **head, int value) {
  if(*head == NULL) 
    return;
  if((*head)->value == value) {
    Node *toRemove = *head;
    *head = (*head)->next;
    free(toRemove);
    return;
  }
  for (Node *current = *head; current->next != NULL; current = current->next)
    if(current->next->value == value) {
      Node *toRemove = current->next;
      current->next = current->next->next;
      free(toRemove);
      return;
    }
}

Node *findElement(Node **head, int value) {
  for(Node *current = *head; current != NULL; current = current->next) {
    if(current->value == value) {
      return current;
    }
  }
  return NULL;
}

std::ostream &operator<<(std::ostream &os, Node *head) {
    int i = 0;
    for (Node *current = head; current != NULL; current = current->next)
    {
        os << "List[" << i << "] = " << current->value << "\n";
        i++;
    }
    return os;
}

void deallocateList(Node **head) {
  if(*head == NULL)
    return;
  Node *current = *head;
  while(current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}

int main()
{
    Node *head = new Node;
    insertHead(&head, 12);
    insertHead(&head, 13);
    removeElement(&head, 13);
    insertEnd(&head, 88);
    cout << head;
    int toFind = 88;
    cout << "Searching " << toFind << "...\n";
    Node *found = findElement(&head, toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << &found << "!\n";
    else cout << "Value " << toFind << " not found\n";
    deallocateList(&head);
    return 0;
}