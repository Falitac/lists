#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <random>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

thread_local auto mt = std::mt19937{ std::random_device{}() };

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

void remove(Node*& node) {
	if(!node) return;
	Node* tmp = node;
	node = node->next;
	delete tmp;
}

void insertSorted(Node*& head, int val) {
	add(head, -1);
	Node* it = head;
	while(it->next && it->next->val < val) {
		it = it->next;
	}
	add(it->next, val);
	remove(head);
}

Node* enqueue(Node*& head, int val) {
	if (!head) {
		add(head, val);
		return head;
	}

	Node* it = head;
	while (it->next) {
		it = it->next;
	}
	addAfter(it, val);

	return it;
}

void deleteElement(Node*& head, int val) {
	if (!head) return;

	if (head->val == val) {
		Node* nextNode = head->next;
		delete head;
		head = nextNode;
		return;
	}

	Node* it = head;
	while (it->next && it->next->val != val) {
		it = it->next;
	}

	Node* nextNode = it->next->next;
	delete it->next;
	it->next = nextNode;
}


void deleteAfter(Node* node) {
	if (!node || !node->next) {
		return;
	}
	Node* tmp = node->next->next;
	delete node->next;
	node->next = tmp;
}

void print(Node* head) {
	std::printf("H");
	while (head) {
		std::printf(" -> %d", head->val);
		head = head->next;
	}
	std::printf(" -> null\n");
}

void clear(Node* head) {
	while (head) {
		Node* p = head->next;
		delete head;
		head = p;
	}
}

void copyN(Node* head, int n) {
	if (n <= 0) {
		return;
	}
	if (!head) {
		return;
	}

	int listSize = 1;
	Node* lastElement = head;

	while (lastElement->next) {
		lastElement = lastElement->next;
		listSize++;
	}

	for (int i = 0; i < n * listSize; i++) {
		addAfter(lastElement, head->val);
		head = head->next;
		lastElement = lastElement->next;
	}
}

void copyValueNTimes(Node* head, int n) {
	if (!head) {
		return;
	}

	while (head->next) {
		head = head->next;
	}
	int val = head->val;
	for (int i = 0; i < n; i++) {
		addAfter(head, val);
		head = head->next;
	}
}

void sumConsecutiveN(Node*& head, int n) {
	if (n <= 1) {
		return;
	}
	if (!head) {
		return;
	}

	Node* p = head;
	for (int i = 1; p; i++) {
		if (!p->next) {
			return;
		}
		if (i % n == 0) {
			p = p->next;
			continue;
		}

		p->val += p->next->val;
		deleteAfter(p);
	}
}

void swapFirstLast(Node*& head) {
	if (!head || !head->next) {
		return;
	}

	Node* last = head;
	while (last->next->next) {
		last = last->next;
	}

	Node* tmp = head;
	head = last->next;
	last->next = tmp;
	head->next = tmp->next;
	tmp->next = nullptr;
}

void swapFirstTwo(Node*& head) {
	if (!head || !head->next) return;
	Node* tmp = head->next;
	head->next = tmp->next;
	tmp->next = head;
	head = tmp;
}

void swap(Node*& head) {
	if(!head && !head->next) return;
	Node* tmp = head->next;
	head->next = tmp->next;
	tmp->next = head;
	head = tmp;
}

void bubbleSort(Node*& head) {
	if(!head) return;

	add(head, -1);
	Node* it = head;
	Node* currentSorted = nullptr;
	for(;;) {
		Node* sortedPoint = nullptr;
		while(it->next->next) {
			if(it->next->next->val < it->next->val) {
				swap(it->next);
				sortedPoint = it->next;
			}
			if(currentSorted == it->next->next) break;
			it = it->next;
		}
		if(!sortedPoint) {
			break;
		}
		if(!it->next->next) {
			it = head;
			currentSorted = sortedPoint;
		}
	}
	remove(head);
}

void removeBefore(Node*& head, int val) {
	if (!head || !head->next) {
		return;
	}
	add(head, 0); // Push
	Node* it = head;

	while (it->next->next && it->next->next->val != val) {
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
	if (!head) return;

	Node* newHead = nullptr;
	Node* it = head;
	while (it) {
		add(newHead, it->val);
		it = it->next;
	}
	clear(head);

	head = newHead;
}

Node* reverseRec(Node* head) {
	if (!head || !head->next) return head;
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
	while (it) {
		Node* tmp = it->next;
		it->next = prev;
		prev = it;
		it = tmp;
	}
	head = prev;
}

//omg, dunno
void splitEachTwo(Node*& source, Node*& dest1, Node*& dest2) {
	if (dest1)  return;
	if (dest2)  return;
	if (!source) return;

	Node* it = source;
	Node** switcher = new Node*[2];
	switcher[0] = nullptr;
	switcher[1] = nullptr;
	for (int i = 0; ; i++) {
		int index = i % 2;
		if (!it) return;
		switcher[index] = enqueue(switcher[index], it->val);
		it = it->next;
		if (!dest1) dest1 = switcher[0];
		if (!dest2) dest2 = switcher[1];
	}
	delete[] switcher;
}

void splitInHalf(Node*& head, Node*& dest1, Node*& dest2) {
	if (!head) {
		return;
	}

	Node* slow = head;
	Node* fast = head->next;
	dest1 = head;
	head = nullptr;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	dest2 = slow->next;
	slow->next = nullptr;
}

void mergeHalf(Node*& source1, Node*& source2, Node*& dest) {
	if (!source1 && !source2) return;
	if (!source1) {
		dest = source2;
		source2 = nullptr;
		return;
	}
	if (!source2) {
		dest = source1;
		source1 = nullptr;
		return;
	}

	dest = source1;
	while (source1->next) {
		source1 = source1->next;
	}
	source1->next = source2;
	source1 = source2 = nullptr;
}

void mergeSorter(Node*& source1, Node*& source2, Node*& dest) {
	if (!source1 && !source2) return;

	add(dest, 0); // might be any value
	Node* p = dest;
	for (;;) {
		if (!source1) {
			p->next = source2;
			source2 = nullptr;
			break;
		}
		if (!source2) {
			p->next = source1;
			source1 = nullptr;
			break;
		}

		if (source1->val < source2->val) {
			Node* tmp = source1->next;
			source1->next = nullptr;
			p->next = source1;
			source1 = tmp;
		}
		else {
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

void mergeSort(Node*& head) {
	if (head && head->next) {
		Node* head1 = nullptr;
		Node* head2 = nullptr;
		splitInHalf(head, head1, head2);
		print(head1);
		print(head2);
		mergeSort(head1);
		mergeSort(head2);
		mergeSorter(head1, head2, head);
	}
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
	unsigned size = 0;

public:

	~Stack() {
		while (pop());
	}

	T getTop() {
		if (!head) {
			throw std::runtime_error("No top value");
			return -1;
		}
		return head->val;
	}

	void push(const T& value) {
		Node* tmp = new Node(value);
		tmp->next = head;
		head = tmp;
		size++;
	}

	bool isEmpty() {
		if (!head) return false;
		return true;
	}

	unsigned getSize() {
		return size;
	}

	bool pop() {
		if (!head) return false;

		std::cout << "Usuwam: " << head->val << "\n";
		Node* tmp = head->next;
		delete head;
		head = tmp;
		size--;
		return true;
	}
};

// finnish him
template<class T>
class Queue {
	struct Node {
		T val;
		Node* next;
		Node(const T& value)
			: val(value)
			, next(nullptr)
		{ }
	};
	Node* back = nullptr;
	Node* front = nullptr;
	unsigned size = 0;

public:

	~Queue() {
		while (dequeue());
	}

	T getFront() {
		if (!front) {
			throw std::runtime_error("No top value");
		}
		return front->val;
	}

	void enqueue(const T& value) {
		Node* newNode = new Node(value);
		size++;

		if (!front) {
			back = front = newNode;
			return;
		}

		back->next = newNode;
		back = newNode;
	}

	bool dequeue() {
		if (!front) {
			return false;
		}
		std::cout << "Usuwam: " << front->val << "\n";

		Node* tmp = front->next;
		delete front;
		front = tmp;
		if (front == nullptr) {
			back = nullptr;
		}
		size--;
		return true;
	}

	bool isEmpty() {
		if (!front) return false;
		return true;
	}

	unsigned getSize() {
		return size;
	}

};

int mainStack(int argc, char** argv) {
	Stack<int> stack;
	stack.push(3);
	stack.push(4);
	stack.push(8);
	stack.pop();
	std::cout << "Stack top: " << stack.getTop() << std::endl;
	std::cout << "Stack size: " << stack.getSize() << std::endl;
	return 0;
}

int mainMergeSort(int argc, char** argv) {
	Node* head = nullptr;
	auto randRange = std::uniform_int_distribution<int>(-100, 100);

	for (int i = 0; i < 10; i++) {
		add(head, randRange(mt));
	}
	print(head);
	mergeSort(head);
	print(head);

	for (;;);
	return 0;
}

void heapify(int* arr, int heapSize, int i) {
	int left = 2 * i;
	int right = left + 1;
	int largest = i;

	if (left <= heapSize && arr[left] > arr[largest]) {
		largest = left;
	}
	if (right <= heapSize && arr[right] > arr[largest]) {
		largest = right;
	}
	if (largest != i) {
		std::swap(arr[i], arr[largest]);
		heapify(arr, heapSize, largest);
	}
}

void buildHeap(int* arr, int heapSize) {
	for (int i = heapSize / 2; i > 0; i--) {
		heapify(arr, heapSize, i);
	}
}

void heapSort(int* arr, int size) {
	int heapsize = size - 1;
	buildHeap(arr, heapsize);
	while (heapsize > 1) {
		std::swap(arr[1], arr[heapsize]);
		heapsize--;
		heapify(arr, heapsize, 1);
	}
}

// heapsort
int mainHeapSort(int argc, char** argv) {
	auto randRange = std::uniform_int_distribution<int>(1, 100);

	int arr[10];
	arr[0] = 0;
	for (int i = 1; i < ARRAY_SIZE(arr); i++) {
		arr[i] = randRange(mt);
	}
	heapSort(arr, ARRAY_SIZE(arr));

	for (int i = 0, j = 1; i < ARRAY_SIZE(arr); i++) {
		std::printf("%d ", arr[i]);
	}
	std::cin.get();
	return 0;
}

// Enqaueue + sort
int main1(int argc, char** argv) {
	Node* head = nullptr;

	int n = 10;
	if (argc >= 2) {
		n = std::atoi(argv[1]);
	}

	auto randRange = std::uniform_int_distribution<int>(-100, 100);

	for (int i = 0; i < n; i++) {
		auto num = randRange(mt);
		enqueue(head, 10 - i);
	}
	print(head);

	std::puts("Head:");
	print(head);

	mergeSort(head);
	std::puts("Head:");
	print(head);

	clear(head);
	return 0;
}

int main(int argc, char** argv) {
	Node* head = nullptr;

	int n = 10;
	if (argc >= 2) {
		n = std::atoi(argv[1]);
	}

	auto randRange = std::uniform_int_distribution<int>(-100, 100);

	for (int i = 0; i < n; i++) {
		auto num = randRange(mt);
		//add(head, i + 1);
		insertSorted(head, num);
	}
	print(head);

	//bubbleSort(head);
	//print(head);

	clear(head);
	return 0;
}