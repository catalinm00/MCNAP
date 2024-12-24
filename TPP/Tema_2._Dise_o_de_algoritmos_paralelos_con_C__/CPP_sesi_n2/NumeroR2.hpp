#ifndef NUMEROR2_HPP
#define NUMEROR2_HPP
template <typename T>
class NumeroR2
{
private:
    T x;
    T y;
protected:
    T getX() const { return x; }
    T getY() const { return y; }
    void setX(T value) { x = value; }
    void setY(T value) { y = value; }
public:
    NumeroR2() : x{0}, y{0} {}
    NumeroR2(T x, T y) : x{x}, y{y} {}
    NumeroR2(const NumeroR2& other) : x{other.x}, y{other.y} {}
    
    friend std::ostream &operator<<(std::ostream &os, const NumeroR2<T> r2)
    {
        return os << "(" << r2.x << ", " << r2.y << ")";
    }

    NumeroR2<T> &operator+=(const NumeroR2<T> &nr2)
    {
        x += nr2.x;
        y += nr2.y;
        return *this;
    }

    NumeroR2<T> &operator-=(const NumeroR2<T> &nr2)
    {
        x -= nr2.x;
        y -= nr2.y;
        return *this;
    }

    NumeroR2<T> operator+(const NumeroR2<T> &nr2)
    {
        return NumeroR2(this->x + nr2.x, this->y + nr2.y);
    }

    NumeroR2<T> operator-(const NumeroR2<T> &nr2)
    {
        return NumeroR2(this->x - nr2.x, this->y - nr2.y);
    }

    NumeroR2<T> &operator++()
    {
        x++;
        y++;
        return *this;
    }

    NumeroR2<T> &operator--()
    {
        x--;
        y--;
        return *this;
    }

    NumeroR2<T> operator++(int)
    {
        NumeroR2 temp(x, y);
        x++;
        y++;
        return temp;
    }

    NumeroR2<T> operator--(int)
    {
        NumeroR2 temp(x, y);
        x--;
        y--;
        return temp;
    }

    NumeroR2<T> &operator=(const NumeroR2 &other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
};
#endif