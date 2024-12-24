#include<stdio.h>
#include<iostream>
/* El código desarrollado en la Actividad 3 debe funcionar con el siguiente programa principal. */
/* Si el código está correcto mostrará lo siguiente */
/* a = ( 12, 0 )            */
/* b = ( 0, -11 )           */
/* c = ( 0, 0 )             */
/* d = ( 12, 0 )            */
/* a += b es ( 12, -11 )    */
/* c = ( 12, -22 )          */
/* c = b -a es ( -12, 0 )   */
/* c++ es ( -12, 0 )        */
/* ++c es ( -10, 2 )        */
/* ++a es ( 13, -10 )       */
/* a++ es ( 13, -10 )       */
/* --a es ( 13, -10 )       */
/* a-- es ( 13, -10 )       */
/* b = a-- es ( 0, -11 )    */
/* b = --a es ( 0, -11 )    */

class NumeroR2 {
  private:
    double x;
    double y;
  public:
    NumeroR2(): x{0}, y{0} {}
    NumeroR2(double x, double y): x{x}, y{y} {}
    NumeroR2(const NumeroR2& other): x{other.x}, y{other.y} {}

    friend std::ostream& operator<<(std::ostream& os, const NumeroR2 r2) {
      return os << "(" << r2.x << ", " << r2.y << ")";
    }

    NumeroR2& operator+=(const NumeroR2& nr2) {
      x += nr2.x;
      y += nr2.y;
      return *this;
    }

    NumeroR2& operator-=(const NumeroR2& nr2) {
      x -= nr2.x;
      y -= nr2.y;
      return *this;
    }

    NumeroR2 operator+(const NumeroR2& nr2) {
      return NumeroR2(this->x + nr2.x, this->y + nr2.y);
    }

    NumeroR2 operator-(const NumeroR2& nr2) {
      return NumeroR2(this->x - nr2.x, this->y - nr2.y);
    }

    NumeroR2& operator++() {
      x++;
      y++;
      return *this;
    }

    NumeroR2& operator--() {
      x--;
      y--;
      return *this;
    }

    NumeroR2 operator++(int) {
      NumeroR2 temp(x,y);
      x++;
      y++;
      return temp;
    }

    NumeroR2 operator--(int) {
      NumeroR2 temp(x,y);
      x--;
      y--;
      return temp;
    }

    NumeroR2& operator=(const NumeroR2& other) {
      x = other.x;
      y = other.y;
      return *this;
    }
};

using namespace std;

int main( int argc, char *argv[] ) {
  
  NumeroR2 a( 12.0, 0.0 ), b( 0.0, -11.0 ), c, d(a);
  
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "c = " << c << endl;
  cout << "d = " << d << endl;

  a += b;
  cout << "a += b es " << a << endl;

  c = a + b;
  cout << "c = a + b = " << c << endl;

  c = b - a;
  cout << "c = b - a = " << c << endl;

  cout << "c++ es " << c++ << endl;
  cout << "++c es " << ++c << endl;
  cout << "++a es " << ++a << endl;
  cout << "a++ es " << a++ << endl;
  cout << "--a es " << --a << endl;
  cout << "a-- es " << a-- << endl;

  cout << "b = a-- es " << b << endl;
  cout << "b = --a es " << b << endl;

}

