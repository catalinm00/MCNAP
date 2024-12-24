#include <iostream>
#include <stdio.h>
#include "Complejo.hpp"

template <typename T>
class Functor
{
public:
    void operator()(Complejo<T> &c) { cout << c.mod() << endl; }
};