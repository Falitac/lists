#include <iostream>
#include <vector>
#include <algorithm>

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

Node* enqueue(Node*& head, int val) {
  if(!head) {
    add(head, val);
    return head;
  }

  Node* it = head;
  while(it->next) {
    it = it->next;
  }
  addAfter(it, val);

  return it;
}

void deleteElement(Node*& head, int val) {
  if(!head) return;

  if(head->val == val) {
    Node* nextNode = head->next;
    delete head;
    head = nextNode;
    return;
  }

  Node* it = head;
  while(it->next and it->next->val != val) {
    it = it->next;
  }

  Node* nextNode = it->next->next;
  delete it->next;
  it->next = nextNode;
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
}

void copyValueNTimes(Node* head, int n) {
  if(!head) {
    return;
  }

  while(head->next) {
    head = head->next;
  }
  int val = head->val;
  for(int i = 0; i < n; i++) {
    addAfter(head, val);
    head = head->next;
  }
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

void swapFirstLast(Node*& head) {
  if(!head or !head->next) {
    return;
  }

  Node* last = head;
  while(last->next->next) {
    last = last->next;
  }

  Node* tmp = head;
  head = last->next;
  last->next = tmp;
  head->next = tmp->next;
  tmp->next = nullptr;
}

void swapFirstTwo(Node*& head) {
  if(!head || !head->next) return;
  Node* tmp = head->next;
  head->next = tmp->next;
  tmp->next = head;
  head = tmp;
}

void removeBefore(Node*& head, int val) {
  if(!head or !head->next) {
    return;
  }
  add(head, 0); // Push
  Node* it = head;

  while(it->next->next and it->next->next->val != val) {
    it = it->next;
  }

  Node* nextNode = it->next->next;
  delete it->next;
  it->next = nextNode;

  nextNode = head->next; // Pop
  delete head;
  head = nextNode;
}

void reverse(Node*& head) {
  if(!head) return;

  Node* newHead = nullptr;
  Node* it = head;
  while(it) {
    add(newHead, it->val);
    it = it->next;
  }
  clear(head);

  head = newHead;
}

Node* reverseRec(Node* head) {
  if(!head || !head->next) return head;
  auto result = reverseRec(head->next);
  head->next->next = head;
  head->next = nullptr;
  return result;
}

void reverse2(Node*& head) {
  head = reverseRec(head);
}

void reverse3(Node*& head) {
  Node* prev = nullptr, *it = head;
  while(it) {
    Node* tmp = it->next;
    it->next = prev;
    prev = it;
    it = tmp;
  }
  head = prev;
}

//omg, dunno
void splitEachTwo(Node*& source, Node*& dest1, Node*& dest2) {
  if(dest1)  return;
  if(dest2)  return;
  if(!source) return;

  Node* it = source;
  Node** switcher = new Node* [2];
  switcher[0] = nullptr;
  switcher[1] = nullptr;
  for(int i = 0; ; i++) {
    int index =  i % 2;
    if(!it) return;
    switcher[index] = enqueue(switcher[index], it->val);
    it = it->next;
    if(!dest1) dest1 = switcher[0];
    if(!dest2) dest2 = switcher[1];
  }
  delete [] switcher;
}

void splitInHalf(Node*& head, Node*& dest1, Node*& dest2) {
  if(!head) {
    return;
  }

  Node* slow = head;
  Node* fast = head;
  dest1 = head;
  head = nullptr;
  while(fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  dest2 = slow->next;
  slow->next = nullptr;
}

void mergeHalf(Node*& source1, Node*& source2, Node*& dest) {
  if(!source1 && !source2) return;
  if(!source1) {
    dest = source2;
    source2 = nullptr;
    return;
  }
  if(!source2) {
    dest = source1;
    source1 = nullptr;
    return;
  }

  dest = source1;
  while(source1->next) {
    source1 = source1->next;
  }
  source1->next = source2;
  source1 = source2 = nullptr;
}

int main(int argc, char** argv) {
  Node* head = nullptr;

  auto nums = std::vector<int>{
    -3,
    5,
    6,
    1,
    8,
    -2,
    4,
  };
  std::reverse(nums.begin(), nums.end());
  for(auto num : nums) {
    enqueue(head, num);
  }
  print(head);

  Node* h1 = nullptr;
  Node* h2 = nullptr;

  splitInHalf(head, h1, h2);
  print(h1);
  print(h2);
  print(head);

  mergeHalf(h1, h2, head);
  print(h1);
  print(h2);
  print(head);

  clear(head);
}