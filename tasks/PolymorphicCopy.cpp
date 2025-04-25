#include <iostream>

class A {
public:
    A() = default;

    virtual A* copy() const {
        return new A(*this);
    }

    virtual void print() {
        std::cout << "class A" <<std::endl;
    }
    
    virtual ~A() = default;
};

class B : public A { 
    public: 
    B() = default;
    
    A* copy() const override{
        return new B(*this);
    }

    void print() override{
        std::cout << "class B" <<std::endl;
    }

};

A* copy(const A* obj) {
    return obj->copy();
}

int main () {
    A* obj = new B;
    A* obj2 = copy(obj);
    A* obj3 = new A;

    obj->print();
    obj2->print();
    
    obj3->print();

    return 0;
}