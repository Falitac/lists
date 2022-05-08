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

void deleteAfter(Node* node) {
  if(!node or !node->next) {
    return;
  }
  Node* tmp = node->next->next;
  delete node->next;
  node->next = tmp;
}

void print(Node* head) {
  std::printf("H");
  int i = 0;
  while(head) {
    std::printf("-> %d ", head->val);
    head = head->next;
    i++;
    if(i > 100) break;
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

void copyN(Node* head, int n) {
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

void sumConsecutiveN(Node*& head, int n) {
  if(n <= 1) {
    return;
  }
  if(!head) {
    return;
  }

  Node* p = head;
  for(int i = 1; p; i++) {
    if(!p->next) {
      return;
    }
    if(i % n == 0) {
      p = p->next;
      continue;
    }

    p->val += p->next->val;
    deleteAfter(p);
  }
}

int main(int argc, char** argv) {
  Node* head;

/*
  add(head, 4);
  add(head, 2);
  add(head, 7);
  copyN(head, 2);
  print(head);
  */

  add(head, -3);
  add(head, 5);
  add(head, 6);
  add(head, 1);
  add(head, 8);
  add(head, -2);
  add(head, 4);
  print(head);
  sumConsecutiveN(head, 3);
  print(head);

  clear(head);
}