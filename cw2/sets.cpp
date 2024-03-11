#include <vector>
#include <iostream>
#include <stdbool.h>

template <typename T>
class Visitor
{
public:
    virtual void Visit (T & element) =0;
    virtual bool IsDone () const
    { return false; }
};

template <typename T>
class Container
{protected:
    Container (){};
public:
    virtual int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
    virtual void MakeNull() = 0;
    virtual void Accept (Visitor<T> & v)=0;
};

template <typename T>
class Set : public virtual Container<T>
{
protected:
    int count;
    int universeSize;
public:
    Set (int n) : universeSize (n) {}
    int UniverseSize() const {return universeSize;}
    int Count() const {return count;};
    virtual void Insert (T element)=0;
    virtual bool IsMember (T element) const=0;
    virtual void Withdraw (T element)=0;
};


class SetAsArray : public Set<int>
{
    std::vector<bool> array;
public:
    SetAsArray (unsigned int n) : Set<int>(n), array(n, false) { //zlozonosc O(n), inicjuje zbior wartosciami false
        unsigned int t = 0;
        count = 0;
        while(t != n) {
            array.at(t) = false;
            t++;
        }
    }
    void MakeNull() {
        std::fill(array.begin(), array.end(), false);
        count = 0;
    }
    void Insert (int element) {
        if(element >= 0 && !array[element]) {
            array.at(element) = true;
            count++;
        }
    }
    bool IsMember (int element) const {
        return array[element] == true && element >= 0;
    }
    void Withdraw (int element) {
        if(element >= 0 && array[element]) {
            array[element] = false;
            count--;
        }
    }
    bool IsFull () const {return ( Count()==UniverseSize()); };
    void Accept (Visitor<int> & v) {
        for(int i = 0; i < universeSize; i++) {
            if(array[i]) {
                v.Visit(i);
                if(v.IsDone()) {
                    break;
                }
            }
        }
    }
    //friend- funkcja uzyska prawo dostepu do prywatnych elementow danej klasy.

    friend SetAsArray operator + (
            SetAsArray const& z1, SetAsArray const& z2) {
        int n = z1.universeSize;
        SetAsArray result(n);
        for(int i = 0; i < n; i++) {
            if(z1.array.at(i) || z2.array.at(i)) {
                result.Insert(i);
            }
        }
        return result;
    }

    friend SetAsArray operator - (
            SetAsArray const& z1, SetAsArray const& z2) {
        int n = z1.universeSize;
        SetAsArray result(n);
        for(int i = 0; i < n; i++) {
            if(z1.array.at(i) && !z2.array.at(i)) {
                result.Insert(i);
            }
        }
        return result;
    }

    friend SetAsArray operator * (
            SetAsArray const& z1, SetAsArray const& z2) {
        int n = z1.universeSize;
        SetAsArray result(n);
        for(int i = 0; i < n; i++) {
            if(z1.array.at(i) && z2.array.at(i)) {
                result.Insert(i);
            }
        }
        return result;
    }
    friend bool operator == (
            SetAsArray const& z1, SetAsArray const& z2) {
        if(z1.array.size() != z2.array.size()) { return false; }
        for(int i = 0; i < z1.array.size(); i++) {
            if(z1.array.at(i) != z2.array.at(i)) {
                return false;
            }
        }
        return true;
    }
    friend bool operator <= (
            SetAsArray const& z1, SetAsArray const& z2) {
        for(int i = 0;i < z1.array.size(); i++) {
            if(z1.array.at(i) && !z2.array.at(i)) {
                return false;
            }
        }
        return true;
    }

    void Wypisz() const {
        std::cout << std::endl;
        for(int i = 0; i < array.size(); i++) {
            if(array.at(i)) { std::cout << i << std::endl; }
        }
        std::cout << std::endl;
    }
};

class Odd_Visitor:public Visitor<int>
{
protected:
    bool IsDone_;
public:
    Odd_Visitor():IsDone_(false){};
    void Visit(int & element) {if (element%2==1) IsDone_=true;
    };
    bool IsDone() const override { return IsDone_; }
};

void Zadanie_zbiory_1() {
    SetAsArray A(10), B(10), C(10), D(10);
    for (int i = 0; i < 10; i += 2) {
        A.Insert(i);
    }
    for(int i = 1; i < 10; i += 2) {
        B.Insert(i);
    }
    C = A + B;
    D = C - B;
    std::cout << "A: ";
    A.Wypisz();
    std::cout << "B: ";
    B.Wypisz();
    std::cout << "C: ";
    C.Wypisz();
    std::cout << "D: ";
    D.Wypisz();

    std::cout << "D == A: " << (D == A ? "true" : "false") << std::endl;
    std::cout << "D <= A: " << (D <= A ? "true" : "false") << std::endl;
    std::cout << "C == B: " << (C == B ? "true" : "false") << std::endl;
    std::cout << "B <= C: " << (B <= C ? "true" : "false") << std::endl;

    A.Insert(1);
    std::cout << "Po dodaniu jedynki:" << std::endl;
    std::cout << "D == A: " << (D == A ? "true" : "false") << std::endl;
    std::cout << "D <= A: " << (D <= A ? "true" : "false") << std::endl;
}

int main(int args, char* argv[]) {
    Zadanie_zbiory_1();
    return 0;
}
