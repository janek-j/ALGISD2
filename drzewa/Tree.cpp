//
// Created by Janek on 25/02/2024.
//

// Drzewo - zbior elementow zwanych wierzcholkami, sposrod ktorych jeden wyrozniony nazywany jest korzeniem.

/*
 * Implementacja drzewa binarnego.
 */

#include <iostream>

typedef int Telement;
struct Node {
    Telement info;
    Node *left;
    Node *right;
};

typedef Node *PNode;
class BinaryTree {
protected:
    PNode T;
public:
    BinaryTree();
    ~BinaryTree();
    PNode PARENT1(PNode n, PNode T); //pomocnicza.
    PNode PARENT(PNode n, PNode T);
    PNode LEFT_MOST_CHILD(PNode n);
    PNode RIGHT_SIBLING(PNode n);
    Telement GetLabel(PNode n);
    PNode BuildTree1(int n);
    void BuildTree(int n);
    PNode ROOT();
    void MAKENULL(PNode p);
};

BinaryTree::BinaryTree() { //konstruktor tworzy puste drzewo.
    T = nullptr;
}

BinaryTree::~BinaryTree() { //destruktor usuwa wszystkie wezly drzewa.
    MAKENULL(T);
}

void BinaryTree::MAKENULL(PNode p) { //funkcja pomocnicza, zwalnia pamiec zajeta przez poddrzewo o korzeniu p
    if(p != nullptr) {
        if(p -> left != nullptr) { MAKENULL(p->left); }
        if(p -> right != nullptr) { MAKENULL(p -> right); }
        delete p;
        p = nullptr;
    }
}

PNode BinaryTree::ROOT() { return T; } //zwraca wezel, ktory jest korzeniem albo null gdy to jest drzewo puste.

PNode BinaryTree::PARENT1(PNode n, PNode T) {
    if(T -> left == n || T -> right == n) { return T; }
    PNode temp1 = nullptr;
    PNode temp2 = nullptr;
    if(T -> left != nullptr) { temp1 = PARENT1(n, T->left); }
    if(T -> right != nullptr) { temp2 = PARENT1(n, T->right); }
    return (temp1 != nullptr)?temp1:temp2;
}

PNode BinaryTree::PARENT(PNode n, PNode T) {
    if(n == T) { return nullptr; }
    return PARENT1(n, T);
}

PNode BinaryTree::LEFT_MOST_CHILD(PNode n) {
    return n -> left;
}

PNode BinaryTree::RIGHT_SIBLING(PNode n) {
    PNode tmp = PARENT(n, T);
    if(tmp -> left == n) { return tmp -> right; }
    return nullptr;
}

Telement BinaryTree::GetLabel(PNode n) {
    if(n != nullptr) { return n->info; }
    return -1341413;
}

int main() {
    BinaryTree bt;
    std::cout << bt.ROOT();
    return 0;
}