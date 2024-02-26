//
// Created by Janek on 26/02/2024.
//

#include <iostream>
#include <vector>

class Container
{protected:
    Container (){};
public:
    virtual unsigned int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
    virtual void MakeNull() = 0;
};

template <typename T>
class PriorityQueue : public Container {
public:
    virtual void Enqueue (T element) = 0;
    virtual T  FindMin () const = 0;
    virtual T DequeueMin () = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T> {
protected:
    int count;
    std::vector<T> data;
public:
    BinaryHeap (unsigned int n);
    ~BinaryHeap (){;};
    void MakeNull();
    void Enqueue (T element);
    T FindMin () const;
    T DequeueMin ();
    bool IsEmpty () const;
    bool IsFull () const ;
    unsigned int Count() const {return count;}
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void PrintHeap() const;
    void PrintMin();
};

template<typename T>
void BinaryHeap<T>::PrintHeap() const {
    if (IsEmpty()) {
        std::cout << "Kopiec jest pusty." << std::endl;
        return;
    }
    int levelLimit = 1;
    int itemsPrinted = 0;

    for (int i = 0; i < count; ++i) {
        std::cout << data[i] << " ";
        ++itemsPrinted;
        if (itemsPrinted == levelLimit) {
            std::cout << std::endl;
            levelLimit *= 2;
            itemsPrinted = 0;
        }
    }
    std::cout << std::endl;
}

template<typename T>
void BinaryHeap<T>::PrintMin() {
    std::cout << data.at(0) << std::endl;
}

template<typename T>
bool BinaryHeap<T>::IsEmpty() const {
    return count == 0;
}

template<typename T>
int BinaryHeap<T>::leftChild(int i) {
    return 2 * i + 1;
}

template<typename T>
int BinaryHeap<T>::rightChild(int i) {
    return 2 * i + 2;
}

template<typename T>
BinaryHeap<T>::BinaryHeap(unsigned int n) {
    count = 0;
    data.reserve(n);
}

template<typename T>
void BinaryHeap<T>::MakeNull() { count = 0; data.clear(); }

template<typename T>
T BinaryHeap<T>::FindMin() const {
    if(count > 0) {
        return data.at(0);
    }
    return -123411;
}

template<typename T>
bool BinaryHeap<T>::IsFull() const {
    return false;
}

template<typename T>
int BinaryHeap<T>::parent(int i) {
    return (i - 1) / 2;
}

template<typename T>
void BinaryHeap<T>::Enqueue(T element) {
    data.push_back(element);
    count++;
    int i = count - 1; //indeks nowo dodanego elementu
    while (i != 0 && data[parent(i)] > data[i]) {

        std::swap(data[i], data[parent(i)]); //zamien miejscami jak jak nowy element jest mniejszy niz jego rodic.
        i = parent(i); //przesun w gore do rodzica
    }
}
template<typename T>
T BinaryHeap<T>::DequeueMin() {
    if(count <= 0) { throw std::out_of_range("Kopiec jest pusty.");}
    T minElement = data.at(0);
    // Przenieś ostatni element do korzenia
    data[0] = data[count - 1];
    count--;
    data.pop_back(); //usun ostatni element
    int i = 0; // Rozpocznij od korzenia
    while (true) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;
        if (left < count && data[left] < data[smallest]) {
            smallest = left;
        }
        if (right < count && data[right] < data[smallest]) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        std::swap(data[i], data[smallest]);
        i = smallest;
    }
    return minElement;
}

void testPriorityQueue() {
    std::cout << "Test dla kopca o maksymalnej wielkości 10" << std::endl;
    BinaryHeap<int> heap(10);

    std::cout << "Sprawdzenie, czy kopiec jest pusty: " << std::boolalpha << heap.IsEmpty() << std::endl;

    heap.Enqueue(5);
    std::cout << "Sprawdzenie po dodaniu 5: " << heap.IsEmpty() << std::endl;
    heap.PrintHeap();
    std::cout << "\n";
    heap.PrintMin();
    heap.Enqueue(6);
    heap.PrintHeap();
    heap.PrintMin();

    heap.Enqueue(8);
    heap.PrintHeap();
    heap.PrintMin();

    heap.Enqueue(3);
    heap.PrintHeap();
    heap.PrintMin();

    heap.Enqueue(9);
    heap.PrintHeap();
    heap.PrintMin();

    heap.Enqueue(2);
    heap.PrintHeap();
    heap.PrintMin();

    heap.Enqueue(1);
    heap.PrintHeap();
    heap.PrintMin();

    heap.DequeueMin();
    heap.PrintHeap();
    heap.PrintMin();

    heap.DequeueMin();
    heap.PrintHeap();
    heap.PrintMin();

    heap.MakeNull();
    std::cout << "Sprawdzenie po MakeNull: " << heap.IsEmpty() << std::endl;
}

int main(int args, char* argv[]) {
    testPriorityQueue();
    return 0;
}

