#include <iostream>
#include <vector>

template<typename T>
class MultiSet {
    public:
        std::vector<T> array; //wektor multizbioru
        int count; //liczba elementow w zbiorze
        MultiSet(unsigned int n);
        void Insert(T element);
        bool IsMember(T element) const;
        void Withdraw(T element);
        int getSize() const;
        void printMultiSet() const;
};

template<typename T>
MultiSet<T>::MultiSet(unsigned int n) {
    array.resize(n);
    count = 0;
    for(unsigned int i = 0; i < n; i++) { array.at(i) = 0; }
} //wypelnia array zerami. Ustawia count na 0.

template<typename T>
void MultiSet<T>::Insert(T element) {
    array.at(element)++;
    count++;
}
template<typename T>
bool MultiSet<T>::IsMember(T element) const {
    return array.at(element) > 0;
}


template<typename T>
int MultiSet<T>::getSize() const{
    return array.size();
}

template<typename T>
void MultiSet<T>::printMultiSet() const {
    int set_size = getSize();
    std::cout << std::endl;
    for(int i = 0; i < set_size; i++) {
        std::cout << "Element: " << i << " wystepuje: " << array.at(i) << " razy." << std::endl;
    }
    std::cout << std::endl;
}

template<typename T>
void MultiSet<T>::Withdraw(T element) {
    //usuwa element z multizbioru.
    if(element >= 0 && IsMember(element)) {
        array.at(element)--;
        count--;
    } 
}

template<typename T>
class Visitor: public MultiSet<T> {
    public:
        static int countEven(const MultiSet<T> &multiSet) {
            int count = 0;
            for(int i = 0; i < multiSet.getSize(); i++) {
                if(multiSet.array.at(i) % 2 == 0 && multiSet.IsMember(i)) {
                    count += multiSet.array.at(i);
                }
            }
            return count;
        }
};

int main(void) {
    MultiSet<int> set(5);
    set.Insert(2);
    set.printMultiSet();
    set.Withdraw(0);
    set.printMultiSet();
    int counterEven = Visitor<int>::countEven(set);
    std::cout << std::endl;
    std::cout << counterEven << std::endl;
    return 0;
}   