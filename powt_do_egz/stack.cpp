#include <iostream>

typedef int elementtype;
typedef int position;

const int max_length = 10;

class Stack {
	protected:
		int S[max_length];
		position Top;
	public:
		Stack();
		void Push(elementtype x);
		void Pop();
		bool Empty();
		elementtype TopElem();
		void MakeNull();
};

Stack::Stack() {
	Top = -1;
}

void Stack::Push(elementtype x) {
	Top++;
	S[Top] = x;
}

void Stack::Pop() {
	Top--;
}

bool Stack::Empty() {
	return Top == -1;
}

elementtype Stack::TopElem() {
	return S[Top];
}

void Stack::MakeNull() {
	Top = -1;
}

int main(int args, char* argv[]) {
	return 0;
}
