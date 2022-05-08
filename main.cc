#include <iostream>

struct Node {
  Node(int val = 0)
  : val(val)
  { }
  int val;
  Node* next;
};

void addNode(Node*& head, int val) {
  Node* p = new Node(val);
  p->next = head;
  head = p;
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

int main(int argc, char** argv) {
  Node* head;
  addNode(head, 3);
  addNode(head, 5);
  addNode(head, 2);
  addNode(head, 8);
  print(head);

  clear(head);
}