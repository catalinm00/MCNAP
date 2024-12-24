#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
/* El código desarrollado en la Actividad 2 debe funcionar con el siguiente programa principal */
/* donde size() es el método que permite obtener la dimensión de la Tabla                        */

/* Si el código está correcto mostrará lo siguiente */
/* Tabla 1: [ 83 86 77 15 93 35 86 92 49 21 ]       */
/* Tabla 2: [ 62 27 90 59 63 ]                      */
/* Tabla 3: [ 62 27 90 59 63 ]                      */
/* Tabla 4: [ 83 86 77 15 93 35 86 92 49 21 ]       */
class Tabla
{
private:
  int sz;
  int *elem;

public:
  Tabla() : sz{10}, elem{new int[10]} {}
  Tabla(int n) : sz{n}, elem{new int[n]} {}
  Tabla(const Tabla &t) : sz{t.sz}, elem{new int[sz]}
  {
    for (int i = 0; i < sz; ++i)
    {
      elem[i] = t.elem[i];
    }
  }
  ~Tabla()
  {
    delete[] elem;
  }
  int &operator[](int i) { return elem[i]; }
  inline int size() const { return sz; }

  Tabla &operator=(const Tabla &t)
  {
    sz = t.sz;
    elem = new int[sz];
    for (int i = 0; i < sz; i++)
    {
      elem[i] = t.elem[i];
    }
    return *this;
  }

  friend std::ostream& operator<<(std::ostream &os, const Tabla &t)
  {
    os << "[ ";
    for (int i = 0; i < t.sz; i++)
    {
      os << t.elem[i] << " ";
    }
    os << "]" << std::endl;
    return os;
  }

  int *begin()
  {
    return elem;
  }

  int *end()
  {
    return begin() + sz;
  }
};

using namespace std;
int main()
{

  Tabla t1;
  Tabla t2(5);

  for (int i = 0; i < t1.size(); i++)
  {
    t1[i] = rand() % 100;
  }
  cout << "Tabla 1: " << t1;
  for (int i = 0; i < t2.size(); i++)
  {
    t2[i] = rand() % 100;
  }
  cout << "Tabla 2: " << t2;
  Tabla t3(t2);
  cout << "Tabla 3: " << t3;
  Tabla t4(5);
  t4 = t1;
  cout << "Tabla 4: " << t4;
}
