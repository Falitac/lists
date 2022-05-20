#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

thread_local auto mt = std::mt19937{std::random_device{}()};

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
    std::printf(" -> %d", head->val);
    head = head->next;
    i++;
    if(i > 100) break;
  }
  std::printf(" -> null\n");
}

void clear(Node* head) {
  while(head) {
    Node* p = head->next; 
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
  Node* fast = head->next;
  dest1 = head;
  head = nullptr;
  while(fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  std::printf("I got on %d\n", slow->val);
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

void mergeSorter(Node*& source1, Node*& source2, Node*& dest) {
  if(!source1 && !source2) return;

  add(dest, 0); // might be any value
  Node* p = dest;
  for(;;) {
    if(!source1) {
      p->next = source2;
      source2 = nullptr;
      break;
    }
    if(!source2) {
      p->next = source1;
      source1 = nullptr;
      break;
    }
    
    if(source1->val < source2->val) {
      Node* tmp = source1->next;
      source1->next = nullptr;
      p->next = source1;
      source1 = tmp;
    } else {
      Node* tmp = source2->next;
      source2->next = nullptr;
      p->next = source2;
      source2 = tmp;
    }
    p = p->next;
  }
  Node* tmp = dest->next;
  delete dest;
  dest = tmp;
}

void sortHelper(Node* left, Node* right) {
  if(!left->next) {
    Node* h1{}, *h2{};
    splitInHalf(left, h1, h2);
    sortHelper(h1, h2);
  }
  Node *tmp = nullptr;
  mergeSorter(left, right, tmp);
  left = tmp;
  if(!right->next) {
    Node* h1{}, *h2{};
    splitInHalf(right, h1, h2);
    sortHelper(h1, h2);
  }
  tmp = nullptr;
  mergeSorter(left, right, tmp);
  left = tmp;
}

void sort(Node*& head) {
  Node* left, *right;
  left = right = nullptr;
  sortHelper(head, right);
}

// rewrite this shiiii
void merge2(Node*& H, Node*& H1, Node*& H2) {
	if (H1 == NULL && H2 != NULL) {
		H = H2;
		H2 = NULL;
	}
	if (H1 != NULL && H2 == NULL) {
		H = H1;
		H1 = NULL;
	}
	if (H1 != NULL && H2 != NULL) {
		Node* T = NULL;
		Node* p = NULL;
		while (H1 && H2) {
			if (H1->val < H2->val) {
				p = H1;
				H1 = H1->next;
				if (H == NULL) {
					H = p;
					T = p;
				}
				else {
					T->next = p;
					T = p;
				}
			}
			else {
				p = H2;
				H2 = H2->next;
				if (H == NULL) {
					H = p;
					T = p;
				}
				else {
					T->next = p;
					T = p;
				}
			}
			}
		if (H1 == NULL) {
			T->next = H2;
			H2 = NULL;
    }
		else {
			T->next = H1;
			H1 = NULL;
		}
	}
}

template<class T>
class Stack {
  struct Node {
    T val;
    Node* next;
    Node(const T& value) 
    : val(value)
    , next(nullptr)
    { }
  };
  Node* head = nullptr;

public:
  int errors = 0;

  ~Stack() {
    while(head) {
      Node* tmp = head->next;
      delete head;
      head = tmp;
    }
  }

  T top() {
    if(!head) {
      errors = -1;
      return -1;
    }
    return head->val;
  }

  void push(const T& value) {
    Node* tmp = new Node(value);
    tmp->next = head;
    head = tmp;
  }

  void pop() {
    if(!head) return;
    Node* tmp = head->next;
    delete head;
    head = tmp;
  }

};

int main(int argc, char** argv) {
  Stack<int> stack;
  stack.push(3);
  stack.push(4);
  stack.push(8);
  stack.pop();
  std::cout << "Stack top: " << stack.top() << std::endl;
  return 0;
}

int main1(int argc, char** argv) {
  Node* head = nullptr;

  int n = 10;
  if(argc >= 2) {
    n = std::atoi(argv[1]);
  }

  auto randRange = std::uniform_int_distribution(-100, 100);

  for(int i = 0; i < n; i++) {
    auto num = randRange(mt);
    enqueue(head, 10 - i);
  }
  print(head);

  std::puts("Head:");
  print(head);

  sort(head);
  std::puts("Head:");
  print(head);

  clear(head);
}