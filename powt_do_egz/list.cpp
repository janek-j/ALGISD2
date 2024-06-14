#include <iostream>

typedef int position;
typedef int elementtype;
const int max_length = 10;
struct List {
	elementtype elements[max_length];
	position last = 0;
};
position FIRST(List &l) { return 0; }
position END(List &l) { return l.last + 1; }
position Next(position p) { if(p >= 0) { return p+1; } return -1; }
position Locate(List &l, elementtype x) {
	int index = -1;
	for(int i = 0; i < l.last; i++) {
		if(l.elements[i] == x) { index = i; }
	}
	return index;
}
elementtype Retrieve(List &l, position p) {
	int element = -1000;
	if(p >= 0 && p <= l.last) { return l.elements[p]; }
	return element;
}
bool Insert(List &l, elementtype x, position p) {
	if(p < 0 || p > l.last) { return false; }
	for(int i = l.last; i >= p; i--) {
		l.elements[i+1] = l.elements[i];
	}
	l.elements[p] = x;
	l.last++;
	return true;
}

bool Delete(List &l, position p) {
	if(p < 0 || p > l.last) { return false; }
	for(int i = p; i < l.last; i++) {
		l.elements[i] = l.elements[i+1];
	}
	l.last--;
	return true;
}
void print_list(List &l) {
	std::cout << "List: ";
	for(int i = 0; i < l.last; i++) {
		if(i < l.last-1) { std::cout << l.elements[i] << ", "; }
		else { std::cout << l.elements[i]; }
	}
	std::cout << std::endl;
}

void check_implementation() {
	List l;
	Insert(l, 1, 0);
	Insert(l, 2, 1);
	print_list(l);
	
}
int main(int args, char* argv[]) {
	std::cout << "List" << std::endl;
	check_implementation();
	return 0;
}
