#include <iostream>

struct Node {
  Node(int val = 0)
  : val(val)
  , next(nullptr)
  { }
  int val;
  Node* next;
};

void add(Node*& head, int val) {
  Node* p = new Node(val);
  p->next = head;
  head = p;
}

void addAfter(Node* node, int val) {
  node->next = new Node(val);
}

void print(Node* head) {
  std::printf("H");
  while(head) {
    std::printf("-> %d ", head->val);
    head = head->next;
  }
  std::printf("-> null\n");
}

void clear(Node* head) {
  while(head) {
    Node* p = head->next; 
    std::printf("Usuwam %d\n", head->val);
    delete head;
    head = p;
  }
}

void copyNTimes(Node* head, int n) {
  if(n <= 0) {
    return;
  }
  if(!head) {
    return;
  }

  int listSize = 1;
  Node* lastElement = head;

  while(lastElement->next) {
    lastElement = lastElement->next;
    listSize++;
  }

  for(int i = 0; i < n * listSize; i++) {
    addAfter(lastElement, head->val);
    head = head->next;
    lastElement = lastElement->next;
  }

  std::printf("Size = %d\n", listSize);
}

int main(int argc, char** argv) {
  Node* head;

  add(head, 4);
  add(head, 2);
  add(head, 7);
  copyNTimes(head, 2);
  print(head);

  clear(head);
}