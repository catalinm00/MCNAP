#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "NumeroR2.hpp"
#include "Complejo.hpp"
#include "Functor.hpp"


template <typename T>
void modulo(Complejo<T> c) {
    cout << c.mod() << endl;
}


using namespace std;

int main(int argc, char *argv[])
{
    // Prueba operador ()
    Complejo<double> e, f, g;
    e(1.0, 3.0);
    f(-11.0);
    g = e + f;
    cout << "g = " << g << endl;

    // Prueba iterador del vector
    vector< Complejo<double> > v;
    for (double i = 0; i < 10; i++)
    {
        v.push_back(Complejo(rand()*1.00, rand()*1.00));
    }
    //vector<Complejo<double>>::iterator it = v.begin();
    // while(it!=v.end()) {
    //     cout << *it << endl;
    //     it++;
    // }
    cout << "Usando iterador:" << std::endl;
    for(vector<Complejo<double>>::iterator it = v.begin(); it != v.end(); it++ ) {
        cout << *it << endl;
    }

    cout << "Usando bucle for-each:" << std::endl; 
    for ( auto num : v) { 
        cout << num << std::endl;
    }

    // Prueba for_each de c++
    cout << "Prueba for_each STL 1: " << endl;
    // 1. Funcion
    for_each(v.begin(), v.end(), [] (Complejo<double> c){
        modulo(c);
    });
    // 2. Functor
    cout << "Prueba for_each STL 2: " << endl;
    for_each(v.begin(),v.end(), Functor<double>());

    // Prueba sort de c++
    cout << "v antes de ordenacion: " << endl;
    for ( auto num : v) { 
        cout << num.mod() << std::endl;
    }
    cout << "Prueba sort STL: " << endl;
    // 1. Funcion
    sort(v.begin(), v.end(), [] (Complejo<double> a, Complejo<double> b){
        return b.mod() > a.mod();
    });
   // Prueba sort de c++
    cout << "v despues de ordenacion: " << endl;
    for ( auto num : v) { 
        cout << num.mod() << std::endl;
    }
}