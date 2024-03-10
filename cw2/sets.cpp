#include <vector>


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
    SetAsArray (unsigned int n) : Set<int>(n), array(n, false) {
        unsigned int t = 0;
        count = 0;
        while(t != n) {
            array.at(t) = false;
            t++;
        }
    }
    void MakeNull() {
        count = 0;
    }
    void Insert (int element) {
        if(element >= 0 && !array[element]) {array.at(element) = true; count++; }
    }
    bool IsMember (int element) const {
        return array[element] == true && element >= 0;
    }
    void Withdraw (int element) {
        if(element >= 0 && array[element]) {
            array[element] = false;
        }
    }
    bool IsFull () const {return (Count()==UniverseSize());};
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
            SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator - (
            SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator * (
            SetAsArray const&, SetAsArray const&);
    friend bool operator == (
            SetAsArray const&, SetAsArray const&);
    friend bool operator <= (
            SetAsArray const&, SetAsArray const&);

    void Wypisz() const;
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

void task() {
    SetAsArray(3);
}

int main(int args, char* argv[]) {
    task();
    return 0;
}
