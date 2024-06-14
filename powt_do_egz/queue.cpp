#include <iostream>

const int max_length = 10;

typedef int elementtype;
typedef int position;


class Queue {
	protected:
		elementtype elements[max_length];
		position Front;
		position Rear;
	public:
		Queue();
		int AddOne(int i);
		bool empty();
		void Enqueue(elementtype x);
		void Dequeue();
		elementtype FrontElem();
		
};

Queue::Queue() {
	Front = 0;
	Rear = max_length - 1;
}

int Queue::AddOne(int i) {
	return (i + 1) % max_length;
}

bool Queue::empty() {
	return AddOne(Rear) == Front;
}

void Queue::Enqueue(elementtype x) {
	if(AddOne(AddOne(Rear) != Front)) {
		Rear = AddOne(Rear);
		elements[Rear] = x;		
	}
}

void Queue::Dequeue() {
	if(!empty()) {
		Front = AddOne(Front);
	}
}	

elementtype Queue::FrontElem() {
	if(!empty()) {
		return elements[Front];
	}
	return -124131;
}

int main(int args, char* argv[]) {
	return 0;
}
