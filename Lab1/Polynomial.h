#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class Polynomial {
public:
    Polynomial();

    Polynomial(vector<int> coefficients);

    ~Polynomial();

    Polynomial(Polynomial &other);

    Polynomial &operator=(const Polynomial &other);

    bool operator==(const Polynomial &other);

    bool operator!=(const Polynomial &other);

    Polynomial operator+(const Polynomial &other);

    Polynomial operator-(const Polynomial &other);

    Polynomial operator+(int value);

    Polynomial operator-(int value);

    Polynomial operator+=(const Polynomial &other);

    Polynomial operator+=(int value);

    Polynomial operator-=(const Polynomial &other);

    Polynomial operator-=(int value);

    Polynomial operator++();

    Polynomial operator--();

    const Polynomial operator++(int value);

    const Polynomial operator--(int value);

    Polynomial operator*(int value);

    Polynomial operator*(Polynomial &other);

    Polynomial operator/(int value);

    Polynomial operator*=(int value);

    Polynomial operator*=(Polynomial &other);

    Polynomial operator/=(int value);

    int &operator[](int index);

    void setCoefficients(int index, int value);

    void setCoefficients(vector<int> coefficients);

    int getCoefficients(int index);

    int getSize();

    void normalSize();

private:
    vector<int> coefficients;
    int size = 0;
};

void delete0(vector<int> &vector);

void karatsuba(vector<int> a, vector<int> b, int left, int right, vector<int> &c);

ostream &operator<<(ostream &os, Polynomial &polynomial);

istream &operator>>(istream &is, Polynomial &polynomial);
