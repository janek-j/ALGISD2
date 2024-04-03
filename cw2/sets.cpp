#include <vector>
#include <iostream>

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
    int UniverseSize() const { return universeSize; }
    int Count() const { return count; };
    virtual void Insert (T element) = 0;
    virtual bool IsMember (T element) const = 0;
    virtual void Withdraw (T element) = 0;
};

class Odd_Visitor:public Visitor<int>
{
protected:
    bool IsDone_;
public:
    Odd_Visitor():IsDone_(false){};
    void Visit(int & element) { if (element%2==1) { IsDone_=true; } };
    bool IsDone() const override { return IsDone_; }
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
    bool IsFull () const { return ( Count()==UniverseSize()); };
    void Accept (Visitor<int> & v) {
        for (int i = 0; i < universeSize; i++) {
            if (array.at(i)) {
                v.Visit(i);
                if (v.IsDone()) {
                    break;
                }
            }
        }
    }
    void AcceptOdd (Odd_Visitor & v) {
        for (int i = 0; i < universeSize; i++) {
            if (array.at(i)) {
                v.Visit(i);
                if (v.IsDone()) {
                    break;
                }
            }
        }
    }
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


template<typename T>
class AddingVisitor: public Visitor<T> {
protected:
    int sum = 0;
public:
    void Visit(T &i) override {
        sum += i;
    }
    T Sum() const {
        return sum;
    }
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
    // Koniec zadania 1.1 //

    A.Insert(5);

    AddingVisitor<int> v_A;
    A.Accept(v_A);
    std::cout << "Suma elementow zbioru A: " << v_A.Sum() << std::endl;

    SetAsArray E = A * B;
    AddingVisitor<int> v_E;
    E.Accept(v_E);
    std::cout << "Suma elementow zbioru E: " << v_E.Sum() << std::endl;

    E.Withdraw(1);
    AddingVisitor<int> v_E_after_withdraw;
    E.Accept(v_E_after_withdraw);
    std::cout << "Suma elementow zbioru E po usunieciu 1: " << v_E_after_withdraw.Sum() << std::endl; // Wypisanie sumy
    //Koniec zadania 1.2
}

void zad2() {
    SetAsArray A(10), B(10), C(10), D(10), E(10);
    for(int i = 0; i < 10; i++) {
        if( i % 2 == 0 ) {
            A.Insert(i);
        } else {
            B.Insert(i);
        }
    }
    A.Wypisz();
    B.Wypisz();

    C = A + B;
    D = C - B;

    std::cout << "Zbior A";
    A.Wypisz();
    std::cout << "Zbior B";
    B.Wypisz();
    std::cout << "Zbior C";
    C.Wypisz();
    std::cout << "Zbior D";
    D.Wypisz();
    if(D == A) {
        std::cout << "Zbior D jest rowny zbiorowi A" << std::endl;
    }
    if(D <= A) {
        std::cout << "Zbior D zawiera sie w zbiorze A" << std::endl;
    }
    if(C == B) {
        std::cout << "Zbior C jest rowny zbiorowi B" << std::endl;
    }
    if(B <= C) {
        std::cout << "Zbior B zawiera sie w zbiorze C" << std::endl;
    }

    A.Insert(1);
    if(D == A) {
        std::cout << "Zbior D jest rowny zbiorowi A" << std::endl;
    }
    if(D <= A) {
        std::cout << "Zbior D zawiera sie w zbiorze A" << std::endl;
    }
    //nowa czesc testu
    AddingVisitor<int> v_A;
    A.Accept(v_A);
    std::cout << "Suma policzona przez wizytatora zbioru A: " << v_A.Sum() << std::endl;

    E = A*B;
    AddingVisitor<int> v_E;
    E.Accept(v_E);
    std::cout << "Suma policzona przez wizytatora zbioru E: " << v_E.Sum() << std::endl;

    E.Withdraw(1);
    AddingVisitor<int> v_E1;
    E.Accept(v_E1);
    std::cout << "Suma policzona przez wizytatora zbioru E: " << v_E1.Sum() << std::endl;



}

void zad3() {
    //klaska zrobiona
}
void zad4() {
    SetAsArray A(10), B(10), C(10), D(10), E(10);
    for(int i = 0; i < 10; i++) {
        if( i % 2 == 0 ) {
            A.Insert(i);
        } else {
            B.Insert(i);
        }
    }
    A.Wypisz();
    B.Wypisz();

    C = A + B;
    D = C - B;

    std::cout << "Zbior A";
    A.Wypisz();
    std::cout << "Zbior B";
    B.Wypisz();
    std::cout << "Zbior C";
    C.Wypisz();
    std::cout << "Zbior D";
    D.Wypisz();
    if(D == A) {
        std::cout << "Zbior D jest rowny zbiorowi A" << std::endl;
    }
    if(D <= A) {
        std::cout << "Zbior D zawiera sie w zbiorze A" << std::endl;
    }
    if(C == B) {
        std::cout << "Zbior C jest rowny zbiorowi B" << std::endl;
    }
    if(B <= C) {
        std::cout << "Zbior B zawiera sie w zbiorze C" << std::endl;
    }

    A.Insert(1);
    if(D == A) {
        std::cout << "Zbior D jest rowny zbiorowi A" << std::endl;
    }
    if(D <= A) {
        std::cout << "Zbior D zawiera sie w zbiorze A" << std::endl;
    }
    //nowa czesc testu
    AddingVisitor<int> v_A;
    A.Accept(v_A);
    std::cout << "Suma policzona przez wizytatora zbioru A: " << v_A.Sum() << std::endl;

    E = A*B;
    AddingVisitor<int> v_E;
    E.Accept(v_E);
    std::cout << "Suma policzona przez wizytatora zbioru E: " << v_E.Sum() << std::endl;

    E.Withdraw(1);
    AddingVisitor<int> v_E1;
    E.Accept(v_E1);
    std::cout << "Suma policzona przez wizytatora zbioru E: " << v_E1.Sum() << std::endl;

    Odd_Visitor odd_A;
    A.Accept(odd_A);
    std::cout << "Contains an odd number in A: " << (odd_A.IsDone() ? "Yes" : "No") << std::endl;

}

int main(int args, char* argv[]) {
    zad4();
    return 0;
}