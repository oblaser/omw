/*
author          Oliver Blaser
date            25.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

#include <iostream>

using std::cout;
using std::endl;

namespace
{
    class B
    {
    public:
        B() : m_x(0) { cout << "B ctor" << endl; }
        B(const B& other) : m_x(other.x()) { cout << "B copy ctor" << endl; }
        B(int value) : m_x(value) { cout << "B assign ctor " << value << endl; }
        ~B() { cout << "B destructor" << endl; }
        
        void add(int val) { m_x += val; }
        int x() const { return m_x; }
        
    private:
        int m_x;
    };

    class D : public B
    {
    public:
        D() : B() { cout << "D ctor" << endl; }
        D(const D& other) : B(other) { cout << "D copy ctor" << endl; }
        D(int value) : B(value) { cout << "D assign ctor " << value << endl; }
        D(const B& other) : B(other) { cout << "D convert ctor" << endl; }
        ~D() { cout << "D destructor" << endl; }
        
        void print() const { cout << "x: " << x() << endl; }
    };

    void print(const B& b)  { cout << "  b.x: " << b.x() << endl; }
    void ref(B& b) { b.add(3); }
    void ptr(B* b) { b->add(5); }
    void ref_d(D& d) { d.add(3); d.print(); }
    void ptr_d(D* d) { d->add(5); d->print(); }
    void ref_cd(const D& d) { d.print(); }
    void ptr_cd(const D* d) { d->print(); }
}

int main()
{
    {
        cout << "--===# B #===--" << endl;
        B b;
        print(b);
        ref(b);
        print(b);
        ptr(&b);
        print(b);
        //ref_d(b); error
        ref_cd(b);
        print(b);
        //ptr_d(&b); error
        //ptr_cd(&b); error
        print(b);
    }
    
    {
        cout << "\n--===# const B #===--" << endl;
        B cb_data(1);
        const B& cb = cb_data;
        print(cb);
        ref_cd(cb);
        print(cb);
        //ptr_cd(&cb); error
        print(cb);
    }
    
    {
        cout << "\n--===# D #===--" << endl;
        D d;
        d.print();
        ref(d);
        d.print();
        ptr(&d);
        d.print();
        ref_d(d);
        ptr_d(&d);
    }
    
    {
        cout << "\n--===# const D #===--" << endl;
        D cd_data(9);
        const D& cd = cd_data;
        print(cd);
        ref_cd(cd);
        print(cd);
        ptr_cd(&cd);
        print(cd);
    }
    
    return 0;
}
