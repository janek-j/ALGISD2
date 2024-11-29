#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
class Set {
private:
    int n; //Size of a set
    std::vector<T> set; //vector that represents a set.

public:
    Set(std::vector<T> _set, int _n): n(_n) { //constructor, resizing vector and initalizing self vector.
        set.resize(n);
        set = _set;
    }

    std::vector<T> get_set() const {
        return set;
    }
    void display_set() {
        std::cout << "Set: { ";
        for(const auto &element: set) {
            std::cout << element << " ";
        }
        std::cout << "}" << std::endl;
    }
    template<class U>
    friend bool operator == (const Set<U> &s1, const Set<U> &s2);

    template<class U>
    friend bool operator != (const Set<U> &s1, const Set<U> &s2);

};

template<class T>
bool operator == (const Set<T> &s1, const Set<T> &s2) {
    if(s1.n != s2.n) { return false; }

    std::vector<T> sorted_s1 = s1.set;
    std::vector<T> sorted_s2 = s2.set;

    std::sort(sorted_s1.begin(), sorted_s1.end());
    std::sort(sorted_s2.begin(), sorted_s2.end());

    for(int i = 0; i < s1.n; i++) {
        if(sorted_s1.at(i) != sorted_s2.at(i)) {
            return false;
        }
    }
    return true;
}

template<class T>
bool operator != (const Set<T>&s1, const Set<T>&s2) {
    return !(s1 == s2);
}

template<class T>
std::vector<std::pair<T, T>> calculate_cartesian_product(const Set<T> &s1, const Set<T> &s2) {
    std::vector<std::pair<T, T>> cartesian_product;


    std::vector<T> vec1 = s1.get_set();
    std::vector<T> vec2 = s2.get_set();

    for(const auto &el1: vec1) {
        for(const auto &el2: vec2) {
            cartesian_product.emplace_back(el1, el2);
        }
    }
    return cartesian_product;
}


void test_set() {
    std::vector<int> arr = {1,2,3,4,5};
    Set s1(arr, 5);
    Set s2(arr, 5);

    std::vector<std::pair<int, int>> cart_product = calculate_cartesian_product(s1, s2);


    s1.display_set();
    s2.display_set();

    std::cout << "Cartesian product: {";
    for(const auto &pair: cart_product) {
        std::cout << "(" << pair.first << "," << pair.second << ") ";
    }
    std::cout << "}" << std::endl;
}

int main(int args, char* argv[]) {
    test_set();
}
