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
    Node *Left;
    Node *Right;
};
typedef Node *PNode;
class BinaryTree {
protected:
    PNode T;
public:
    BinaryTree();
    ~BinaryTree();
    PNode PARENT(PNode n, PNode T);
    PNode LEFT_MOST_CHILD(PNode n);
    PNode RIGHT_SIBLING(PNode n);
    Telement GetLabel(PNode n);
    PNode BuildTree1(int n);
    void BuildTree(int n);
    PNode ROOT();
    void MAKENULL(PNode p);
};
BinaryTree::BinaryTree() {
    T = nullptr; //tworzy puste drzewo.
}
BinaryTree::~BinaryTree() {
    MAKENULL(T);
}
void BinaryTree::MAKENULL(PNode p) {
    if(p != nullptr) {
        if(p -> Right != nullptr) {
            MAKENULL(p->Right);
        }
        if(p -> Left != nullptr) {
            MAKENULL(p -> Left);
        }
        delete p;
        p = nullptr;
    }
}

PNode BinaryTree::ROOT() {
    return T;
}


int main(int args, char* argv[]) {
    return 0;
}