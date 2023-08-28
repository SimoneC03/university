#include <iostream>

using namespace std;

template <typename T>
struct Node {
  T value;
  struct Node<T> *next;
};

template <typename T>
void insertHead(Node<T> **head, T value) {
  Node<T> *newNode = new Node<T>;
  if (newNode == NULL)
    exit(1);
  newNode->value = value;
  newNode->next = *head;
  *head = newNode;
}

template <typename T>
void insertEnd(Node<T> **head, int value) {
  Node<T> *newNode = new Node<T>;
  if(newNode == NULL) exit(1);
  newNode->value = value;
  if(*head == NULL) {
    *head = newNode;
    return;
  }
  Node<T> *current = *head;
  while(current->next != NULL) {
    current = current->next;
  }
  current->next = newNode;
}

template <typename T>
void removeElement(Node<T> **head, int value) {
  if(*head == NULL) 
    return;
  if((*head)->value == value) {
    Node<T> *toRemove = *head;
    *head = (*head)->next;
    free(toRemove);
    return;
  }
  for (Node<T> *current = *head; current->next != NULL; current = current->next)
    if(current->next->value == value) {
      Node<T> *toRemove = current->next;
      current->next = current->next->next;
      free(toRemove);
      return;
    }
}

template <typename T>
Node<T> *findElement(Node<T> **head, int value) {
  for(Node<T> *current = *head; current != NULL; current = current->next) {
    if(current->value == value) {
      return current;
    }
  }
  return NULL;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Node<T> *head) {
    int i = 0;
    for (Node<T> *current = head; current != NULL; current = current->next)
    {
        os << "List[" << i << "] = " << current->value << "\n";
        i++;
    }
    return os;
}

template <typename T>
void deallocateList(Node<T> **head) {
  if(*head == NULL)
    return;
  Node<T> *current = *head;
  while(current != NULL) {
    Node<T> *temp = current;
    current = current->next;
    free(temp);
  }
  *head = NULL;
}

int main()
{
    Node<int> *head = new Node<int>;
    insertHead(&head, 12);
    insertHead(&head, 13);
    removeElement(&head, 13);
    insertEnd(&head, 88);
    cout << head;
    int toFind = 88;
    cout << "Searching " << toFind << "...\n";
    Node<int> *found = findElement(&head, toFind);
    if(found != NULL) cout << "Value " << toFind << " found at " << &found << "!\n";
    else cout << "Value " << toFind << " not found\n";
    deallocateList(&head);
    return 0;
}