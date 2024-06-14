#include <iostream>

typedef int elementtype;

struct celltype {
	elementtype element;
	celltype* next;
};

typedef celltype *position;

class List {
	protected:
		position l;
	public:
	List();
	~List();
	void Insert(elementtype x, position p);
	void Delete(elementtype x, position p);
	void print_list();
	position Locate(elementtype x);
	position First();
	position End();
	position Next(position p);
	position Previous(position p);
	elementtype Retrieve(position p);
	
	
	
};

List::List() {
	l = new celltype;
	l -> next = nullptr;
}
List::~List() {
	position tmp;
	while(l -> next != nullptr) {
		tmp = l -> next;
		l->next->next = l->next;
		delete tmp;
	}
	delete l;
}

void List::Insert(elementtype x, position p) {
	position tmp = p->next;
	p->next = new celltype;
	p->next->element = x;
	p->next->next = tmp;	
}

void List::Delete(elementtype x, position p) {
	position tmp = p -> next;
	p->next = p -> next -> next;
	delete tmp;
}

void List::print_list() {
	position tmp = l;
	std::cout << "List contains: ";
	while(tmp -> next != nullptr) {
		std::cout << tmp->next->element << ", ";
		tmp = tmp -> next;
	}
}

position List::Locate(elementtype x) {
	position tmp = l;
	while(tmp -> next != nullptr) {
		if (tmp -> next -> element == x) { return tmp; }
		tmp = tmp -> next;
	}
	return tmp;
}


position List::First() {
	return l;
}

position List::End() {
	position tmp = l;
	while(tmp -> next != nullptr) {
		tmp = tmp -> next;
	}
	return tmp;	
}

elementtype List::Retrieve(position p) {
	if(p -> next != nullptr) {
		return p->next->element;
	}
	return -1134133411;
}

position List::Next(position p) {
	return p->next;
}

position List::Previous(position p) {
	position tmp = l;
	while(tmp -> next != p) {
		tmp = tmp -> next;	
	}
	return tmp;
}



int main(int args, char* argv[]) {
	return 0;
}
