#ifndef COMPLEJO_HPP
#define COMPLEJO_HPP

#include <stdio.h>
#include <iostream>
#include <cmath>
#include "NumeroR2.hpp"

using namespace std;

template <typename T>
class Complejo : NumeroR2<T>
{
private:
    T module;
    void calculateModule()
    {
        module = sqrt(this->getX() * this->getX() + this->getY() * this->getY());
    }

public:
    Complejo();
    Complejo(T x, T y);
    Complejo(const Complejo &other);
    friend std::ostream &operator<<(std::ostream &os, Complejo &c)
    {
        return os << c.getX() << " + " << c.getY() << "i";
    }
    Complejo &operator+=(const Complejo c);
    Complejo &operator-=(const Complejo c);
    Complejo operator+(const Complejo c);
    Complejo operator-(const Complejo c);
    Complejo &operator++();
    Complejo &operator--();
    Complejo operator++(int);
    Complejo operator--(int);
    Complejo &operator=(const Complejo &other)
    {
        if (this != &other)
        {
            NumeroR2<T>::operator=(other);
            module = other.module;
        }
        return *this;
    }
    bool operator<(Complejo other) { return module < other.module; }
    bool operator>(Complejo other) { return module > other.module; }
    bool operator<=(Complejo other) { return module <= other.module; }
    bool operator>=(Complejo other) { return module <= other.module; }
    bool operator==(Complejo other) { return this->getX() == other.getX() && this->getY() == other.getY(); }
    bool operator!=(Complejo other) { return this->getX() != other.getX() || this->getY() != other.getY(); }
    void operator()(T x, T y)
    {
        this->setX(x);
        this->setY(y);
        calculateModule();
    }
    void operator()(T x)
    {
        this->setX(x);
        this->setY(0);
        calculateModule();
    }
    T mod() { return this->module; }
};

template <typename T>
Complejo<T>::Complejo() : NumeroR2<T>() { this->calculateModule(); }

template <typename T>
Complejo<T>::Complejo(T x, T y) : NumeroR2<T>(x, y)
{
    this->calculateModule();
}

template <typename T>
Complejo<T>::Complejo(const Complejo &other) : NumeroR2<T>(other) { this->calculateModule(); }

template <typename T>
Complejo<T> &Complejo<T>::operator+=(const Complejo c)
{
    NumeroR2<T>::operator+=(c);
    calculateModule();
    return *this;
}

template <typename T>
Complejo<T> &Complejo<T>::operator-=(const Complejo c)
{
    NumeroR2<T>::operator-=(c);
    calculateModule();
    return *this;
}

template <typename T>
Complejo<T> Complejo<T>::operator+(const Complejo c)
{
    return Complejo(this->getX() + c.getX(), this->getY() + c.getY());
}

template <typename T>
Complejo<T> Complejo<T>::operator-(const Complejo c)
{
    return Complejo(this->getX() - c.getX(), this->getY() - c.getY());
}

template <typename T>
Complejo<T> &Complejo<T>::operator++()
{
    NumeroR2<T>::operator++();
    calculateModule();
    return *this;
}

template <typename T>
Complejo<T> &Complejo<T>::operator--()
{
    NumeroR2<T>::operator--();
    calculateModule();
    return *this;
}

template <typename T>
Complejo<T> Complejo<T>::operator++(int)
{
    Complejo<T> temp(*this);
    NumeroR2<T>::operator++();
    calculateModule();
    return temp;
}

template <typename T>
Complejo<T> Complejo<T>::operator--(int)
{
    Complejo<T> temp(*this);
    NumeroR2<T>::operator--();
    calculateModule();
    return temp;
}

#endif