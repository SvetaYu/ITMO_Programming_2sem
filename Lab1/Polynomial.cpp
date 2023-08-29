#include "Polynomial.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

Polynomial::Polynomial() {
    this->size = 0;
}

Polynomial::Polynomial(vector<int> coefficients) {
    int tempSize = coefficients.size();
    for (int i = 0; i < tempSize; i++) {
        this->coefficients.push_back(coefficients[i]);
    }
    this->size = tempSize;
}

Polynomial::~Polynomial() {
}

Polynomial::Polynomial(Polynomial &other) {
    for (int i = 0; i < other.size; i++) {
        this->coefficients.push_back(other.coefficients[i]);
    }
    this->size = other.size;
}

Polynomial &Polynomial::operator=(const Polynomial &other) {
    this->coefficients.clear();
    for (int i = 0; i < other.size; i++) {
        this->coefficients.push_back(other.coefficients[i]);
    }
    this->size = other.size;
    return *this;
}

bool Polynomial::operator==(const Polynomial &other) {
    if (this->size != other.size) {
        return false;
    }
    for (int i = 0; i < this->size; i++) {
        if (this->coefficients[i] != other.coefficients[i]) {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial &other) {
    return !(*this == other);
}

Polynomial Polynomial::operator+(int value) {
    Polynomial result(*this);
    if (size != 0) {
        result.coefficients[0] += value;
    } else {
        result.coefficients.push_back(value);
    }
    return result;
}

Polynomial Polynomial::operator+(const Polynomial &other) {
    Polynomial result;
    result.size = max(this->size, other.size);
    for (int i = 0; i < result.size; i++) {
        if (i >= this->size) {
            result.coefficients.push_back(other.coefficients[i]);
        } else if (i >= other.size) {
            result.coefficients.push_back(this->coefficients[i]);
        } else {
            result.coefficients.push_back(this->coefficients[i] + other.coefficients[i]);
        }
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial &other) {
    Polynomial result;
    result.size = max(this->size, other.size);
    for (int i = 0; i < result.size; i++) {
        if (i >= this->size) {
            result.coefficients.push_back(-other.coefficients[i]);
        } else if (i >= other.size) {
            result.coefficients.push_back(this->coefficients[i]);
        } else {
            result.coefficients.push_back(this->coefficients[i] - other.coefficients[i]);
        }
    }
    return result;
}

Polynomial Polynomial::operator-(int value) {
    Polynomial result(*this);
    if (size != 0) {
        result.coefficients[0] -= value;
    } else {
        result.coefficients.push_back(-value);
    }
    return result;
}

Polynomial Polynomial::operator+=(const Polynomial &other) {
    *this = *this + other;
    return *this;
}

Polynomial Polynomial::operator+=(int value) {
    *this = *this + value;
    return *this;
}

Polynomial Polynomial::operator-=(const Polynomial &other) {
    *this = *this - other;
    return *this;
}

Polynomial Polynomial::operator-=(int value) {
    *this = *this - value;
    return *this;
}

Polynomial Polynomial::operator++() {
    if (coefficients.empty()) {
        coefficients.push_back(0);
        size = coefficients.size();
    }
    coefficients[0]++;
    return *this;
}

Polynomial Polynomial::operator--() {
    if (coefficients.empty()) {
        coefficients.push_back(0);
        size = coefficients.size();
    }
    coefficients[0]--;
    return *this;
}

const Polynomial Polynomial::operator++(int value) {
    Polynomial temp(*this);
    if (coefficients.empty()) {
        coefficients.push_back(0);
        size = coefficients.size();
    }
    coefficients[0]++;
    return temp;
}

const Polynomial Polynomial::operator--(int value) {
    Polynomial temp(*this);
    if (coefficients.empty()) {
        coefficients.push_back(0);
        size = coefficients.size();
    }
    coefficients[0]--;
    return temp;
}

Polynomial Polynomial::operator*(int value) {
    Polynomial temp(*this);
    for (int i = 0; i < temp.size; i++) {
        temp.coefficients[i] *= value;
    }
    return temp;
}

Polynomial Polynomial::operator*(Polynomial &other) {
    Polynomial temp;
    while (this->size > other.size) {
        other.coefficients.push_back(0);
    }
    other.normalSize();
    while (this->size < other.size) {
        this->coefficients.push_back(0);
    }
    this->normalSize();
    karatsuba(this->coefficients, other.coefficients, 0, this->size, temp.coefficients);
    delete0(temp.coefficients);
    temp.normalSize();
    delete0(this->coefficients);
    this->normalSize();
    delete0(other.coefficients);
    other.normalSize();
    return temp;
}

Polynomial Polynomial::operator/(int value) {
    Polynomial temp(*this);
    for (int i = 0; i < temp.size; i++) {
        temp.coefficients[i] /= value;
    }
    return temp;
}

Polynomial Polynomial::operator*=(int value) {
    *this = *this * value;
    return *this;
}

Polynomial Polynomial::operator*=(Polynomial &other) {
    *this = *this * other;
    return *this;
}

Polynomial Polynomial::operator/=(int value) {
    *this = *this / value;
    return *this;
}

int &Polynomial::operator[](int index) {
    if (index < 0) {
        throw exception();
    }
    if (index >= coefficients.size()) {
        while (coefficients.size() <= index) {
            coefficients.push_back(0);
        }
        size = coefficients.size();
    }
    return coefficients[index];
}

void Polynomial::setCoefficients(int index, int value) {
    if (index < 0) {
        throw exception();
    }
    if (index >= coefficients.size()) {
        while (coefficients.size() <= index) {
            coefficients.push_back(0);
        }
        size = coefficients.size();
    }
    coefficients[index] = value;
}

void Polynomial::setCoefficients(vector<int> coefficients) {
    this->coefficients.clear();
    for (int i = 0; i < coefficients.size(); i++) {
        this->coefficients.push_back(coefficients[i]);
    }
    this->size = coefficients.size();
}

int Polynomial::getCoefficients(int index) {
    if (index >= size) {
        return 0;
    }
    if (index < 0) {
        throw exception();
    }
    return coefficients[index];
}

int Polynomial::getSize() {
    return size;
}

void Polynomial::normalSize() {
    size = coefficients.size();
}

void delete0(vector<int> &vector) {
    for (int i = vector.size() - 1; i >= 0; --i) {
        if (vector[i] == 0) {
            vector.pop_back();
        } else {
            break;
        }
    }
}

void karatsuba(vector<int> a, vector<int> b, int left, int right, vector<int> &c) {
    int mid = (right + left + 1) / 2;
    int n = right - left;
    if (n <= 5) {
        for (int i = 0; i < (2 * n - 1); i++) {
            c.push_back(0);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                c[i + j] += a[i + left] * b[j + left];
            }
        }
    } else {
        vector<int> a01;
        vector<int> b01;
        for (int i = 0; i < n / 2; ++i) {
            a01.push_back(a[left + i] + a[mid + i]);
            b01.push_back(b[left + i] + b[mid + i]);
        }
        if ((right - mid) < (mid - left)) {
            a01.push_back(a[mid - 1]);
            b01.push_back(b[mid - 1]);
        }
        vector<int> y;
        karatsuba(a01, b01, 0, a01.size(), y);
        vector<int> x;
        karatsuba(a, b, mid, right, x);
        vector<int> z;
        karatsuba(a, b, left, mid, z);
        for (int i = 0; i < 2 * n - 1; ++i) {
            c.push_back(0);
        }
        for (int i = 0; i < n; ++i) {
            if (i < x.size()) {
                if (n % 2 != 0) {
                    c[i + n + 1] += x[i];
                } else {
                    c[i + n] += x[i];
                }
                c[i + (n + 1) / 2] += -x[i];
            }
            if (i < y.size()) {
                c[i + (n + 1) / 2] += y[i];
            }
            if (i < z.size()) {
                c[i] += z[i];
                c[i + (n + 1) / 2] += -z[i];
            }
        }
    }
}

ostream &operator<<(ostream &os, Polynomial &polynomial) {
    string str = "";
    if (polynomial.getCoefficients(polynomial.getSize() - 1) < 0) {
        str += "-";
    }
    for (int i = polynomial.getSize() - 1; i > 0; i--) {
        if (polynomial.getCoefficients(i) != 0) {
            if (abs(polynomial.getCoefficients(i)) != 1) {
                char temp[1000];
                itoa(abs(polynomial.getCoefficients(i)), temp, 10);
                str += temp;
            }
            str += 'x';
            if (i != 1) {
                char temp[1000];
                itoa(i, temp, 10);
                str += "^";
                str += temp;
            }
        }
        if (polynomial.getCoefficients(i - 1) != 0) {
            if (polynomial.getCoefficients(i - 1) > 0) {
                str += "+";
            } else {
                str += "-";
            }
        }
    }
    if (polynomial.getCoefficients(0) != 0) {
        char temp[1000];
        itoa(abs(polynomial.getCoefficients(0)), temp, 10);
        str += temp;
    }
    str += "\n";
    if (str == "") {
        str = '0';
    }
    os << str;
    return os;
}

istream &operator>>(istream &is, Polynomial &polynomial) {
    string str;
    vector<int> arr;
    int coefficient = 1;
    int st = 0;
    int maxst = -1;
    is >> str;
    int i = 0;
    while (i < str.size()) {
        coefficient = 1;
        st = 0;
        if (str[i] == '-') {
            coefficient *= -1;
            i++;
        }
        if (str[i] == '+') {
            i++;
        }
        if (str[i] != 'x') {
            char temp[2] = {str[i], '\0'};
            bool check = false;
            if (coefficient < 0) {
                check = true;
            }
            coefficient = atoi(temp);
            if (i < str.size()) {
                i++;
            }
            while (i < str.size() && str[i] >= '0' && str[i] <= '9') {
                cout << str[i] << " str[i]" << endl;
                char temp[2] = {str[i], '\0'};
                coefficient = 10 * coefficient + atoi(temp);
                i++;
            }
            if (check) {
                coefficient *= -1;
            }
            if (i >= str.size()) {
                st = 0;
                arr[st] = coefficient;
            }
        }
        if (str[i] != 'x') {
            st = 0;
        } else {
            if (i < str.size()) {
                i++;
                if (str[i] == '^') {
                    i++;
                    while (i < str.size() && str[i] >= '0') {
                        char temp[2] = {str[i], '\0'};
                        st = 10 * st + atoi(temp);
                        i++;
                    }
                } else {
                    st = 1;
                }
            } else {
                st = 1;
                arr[st] = coefficient;
                break;
            }
        }
        if (maxst == -1) {
            maxst = st;
            while (arr.size() < maxst + 1) {
                arr.push_back(0);
            }
        }
        arr[st] = coefficient;
        polynomial.setCoefficients(arr);
    }
    return is;
}