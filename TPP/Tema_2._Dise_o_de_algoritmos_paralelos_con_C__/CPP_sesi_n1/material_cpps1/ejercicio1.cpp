#include <stdio.h>
#include <iostream>

using namespace std;

void function1(int *p)
{
    *p = 100;
}

void function2(int &r)
{
    r = 200;
}

void function(int *p)
{
    *p = 800;
}

void function(int &r)
{
    r = 900;
}

int main()
{   
    // 1.
    cout << "Hola mundo." << endl;
    // 2.
    int e;
    int *p = &e;
    int &r = e;

    e = 2;
    printf("----- Asignamos valor desde la variable tipo entero ------\n");
    printf("Mostrando valor usando variable entero: %d\n", e);
    printf("Mostrando el valor usando un puntero: %d\n", *p);
    printf("Mostrando el valor usando una referencia: %d\n", r);
    *p = 3;
    printf("----- Asignamos valor desde el puntero ------\n");
    printf("Mostrando valor usando variable entero: %d\n", e);
    printf("Mostrando el valor usando un puntero: %d\n", *p);
    printf("Mostrando el valor usando una referencia: %d\n", r);
    r = 5;
    printf("----- Asignamos valor desde la referencia ------\n");
    printf("Mostrando valor usando variable entero: %d\n", e);
    printf("Mostrando el valor usando un puntero: %d\n", *p);
    printf("Mostrando el valor usando una referencia: %d\n", r);

    // 3.

    printf("Func1:\n");
    function1(p);
    printf("Valor de p: %d\n", *p);

    printf("Func2:\n");
    function2(r);
    printf("Valor de r: %d\n", r);



    printf("Sobrecarga:\n");
    function(r);
    printf("Valor de r: %d\n", r);
    function(p);
    printf("Valor de p: %d\n", *p);

    return 0;
}
