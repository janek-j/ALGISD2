#include <iostream>

typedef int Telement;

struct Node {
	Node *left;
	Node *right;
	Telement info;
};

typedef Node *PNode;

class BinaryTree {
	protected:
		PNode T;
	public:
		BinaryTree();
		~BinaryTree();
		void MakeNull(PNode P);
		PNode Root();
		PNode Parent(PNode p, PNode T);
		PNode Parent1(PNode p, PNode T);
		PNode left_most_child(PNode p);
		PNode right_sibling(PNode p);
		Telement GetLabel(PNode p);
		void pre_order(PNode t);
		void in_order(PNode t);
		void post_order(PNode t);
};

BinaryTree::BinaryTree() {
	T = nullptr;
} 

void BinaryTree::MakeNull(PNode p) {
	if(p != nullptr) {
		if(p->left != nullptr) { MakeNull(p -> left); }
		if(p -> right != nullptr) { MakeNull(p -> right);  }
		delete p;
		p = nullptr;
	}
}

BinaryTree::~BinaryTree() { MakeNull(T); }
PNode BinaryTree::Root() { return T; }

PNode BinaryTree::Parent(PNode p, PNode T) {
	if(p == nullptr) { return nullptr; }
	return Parent1(p, T);
}

PNode BinaryTree::Parent1(PNode p, PNode T) {
	if(T -> left == p || T -> right == p) { return T; }
	PNode tmp1 = nullptr;
	PNode tmp2 = nullptr;
	if(T -> left != nullptr) { tmp1 = Parent1(p, T->left); }
	if(T -> right != nullptr) { tmp2 = Parent1(p, T->right); }
	return (tmp1 != nullptr) ? tmp1 : tmp2;

}

PNode BinaryTree::left_most_child(PNode p) {
	return p -> left;
}

PNode BinaryTree::right_sibling(PNode p) { 
	PNode tmp = Parent(p, T);
	if(tmp -> left == p) { 
		return tmp -> right;
	} else {
		return nullptr;
	}
	 
}

Telement BinaryTree::GetLabel(PNode p) {
	if(p != nullptr) {
		return p -> info;
	} else {
		return -34134;	
	}
}

void BinaryTree::pre_order(PNode t) { //porzadek wzdluzny
	if(t != nullptr) {
		std::cout << t->info;
		pre_order(t->left);
		pre_order(t->right);
	}
}

void BinaryTree::post_order(PNode t) {
	if(t != nullptr) {
		post_order(t->left);
		post_order(t->right);
		std::cout << t->info;

	}
}

void BinaryTree::in_order(PNode t) {
	if(t != nullptr) {
		in_order(t->left);
		std::cout << t->info;
		in_order(t->right);
	}
}



void create_and_test_tree() {
	BinaryTree tree;
}
	
int main(int args, char* argv[]) {
	create_and_test_tree();
	return 0;
}
