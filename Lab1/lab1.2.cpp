#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
class Polynomial
{
public:
    Polynomial()
    {
        this->coefficients = NULL;
        this->size = 0;
    }
    Polynomial(int size, int coefficients[])
    {
        this->coefficients = new int[size];
        for (int i = 0; i < size; i++)
        {
            this->coefficients[i] = coefficients[i];
        }
        this->size = size;
    }
    Polynomial(vector<int> coefficients)
    {
        int size = coefficients.size();
        this->coefficients = new int[size];
        for (int i = 0; i < size; i++)
        {
            this->coefficients[i] = coefficients[i];
        }
        this->size = size;
    }
    ~Polynomial()
    {
        delete[] coefficients;
    }
    Polynomial(Polynomial &other)
    {
        this->coefficients = new int[other.size];
        for (int i = 0; i < other.size; i++)
        {
            this->coefficients[i] = other.coefficients[i];
        }
        this->size = other.size;
    }
    Polynomial operator=(const Polynomial &other)
    {
        delete[] coefficients;
        this->coefficients = new int[other.size];
        for (int i = 0; i < other.size; i++)
        {
            this->coefficients[i] = other.coefficients[i];
        }
        this->size = other.size;
        return *this;
    }
    bool operator==(const Polynomial &other)
    {
        if (this->size != other.size)
        {
            return false;
        }
        for (int i = 0; i < this->size; i++)
        {
            if (this->coefficients[i] != other.coefficients[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Polynomial &other)
    {
        if (this->size != other.size)
        {
            return true;
        }
        for (int i = 0; i < this->size; i++)
        {
            if (this->coefficients[i] != other.coefficients[i])
            {
                return true;
            }
        }
        return false;
    }
    Polynomial operator+(const Polynomial &other)
    {
        Polynomial result;
        result.size = max(this->size, other.size);
        result.coefficients = new int[result.size];
        for (int i = 0; i < result.size; i++)
        {
            if (i >= this->size)
            {
                result.coefficients[i] = other.coefficients[i];
            }
            else if (i >= other.size)
            {
                result.coefficients[i] = this->coefficients[i];
            }
            else
            {
                result.coefficients[i] = this->coefficients[i] + other.coefficients[i];
            }
        }
        return result;
    }
    Polynomial operator-(const Polynomial &other)
    {
        Polynomial result;
        result.size = max(this->size, other.size);
        result.coefficients = new int[result.size];
        for (int i = 0; i < result.size; i++)
        {
            if (i >= this->size)
            {
                result.coefficients[i] = -other.coefficients[i];
            }
            else if (i >= other.size)
            {
                result.coefficients[i] = this->coefficients[i];
            }
            else
            {
                result.coefficients[i] = this->coefficients[i] - other.coefficients[i];
            }
        }
        return result;
    }
    Polynomial operator+=(const Polynomial &other)
    {
        Polynomial result;
        result.size = max(this->size, other.size);
        result.coefficients = new int[result.size];
        for (int i = 0; i < result.size; i++)
        {
            if (i >= this->size)
            {
                result.coefficients[i] = other.coefficients[i];
            }
            else if (i >= other.size)
            {
                result.coefficients[i] = this->coefficients[i];
            }
            else
            {
                result.coefficients[i] = this->coefficients[i] + other.coefficients[i];
            }
        }
        *this = result;
        return *this;
    }
    Polynomial operator-=(const Polynomial &other)
    {
        Polynomial result;
        result.size = max(this->size, other.size);
        result.coefficients = new int[result.size];
        for (int i = 0; i < result.size; i++)
        {
            if (i >= this->size)
            {
                result.coefficients[i] = -other.coefficients[i];
            }
            else if (i >= other.size)
            {
                result.coefficients[i] = this->coefficients[i];
            }
            else
            {
                result.coefficients[i] = this->coefficients[i] - other.coefficients[i];
            }
        }
        *this = result;
        return *this;
    }
    Polynomial operator++()
    {
        this->coefficients[0]++;
        return *this;
    }
    Polynomial operator--()
    {
        this->coefficients[0]--;
        return *this;
    }
    Polynomial operator++(int value)
    {
        Polynomial temp(*this);
        this->coefficients[0]++;
        return temp;
    }
    Polynomial operator--(int value)
    {
        Polynomial temp(*this);
        this->coefficients[0]--;
        return temp;
    }
    Polynomial operator*(int value)
    {
        Polynomial temp(*this);
        for (int i = 0; i < temp.size; i++)
        {
            temp.coefficients[i] *= value;
        }
        return temp;
    }
    Polynomial operator/(int value)
    {
        Polynomial temp(*this);
        for (int i = 0; i < temp.size; i++)
        {
            temp.coefficients[i] /= value;
        }
        return temp;
    }
    Polynomial operator*=(int value)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coefficients[i] *= value;
        }
        return *this;
    }
    Polynomial operator/=(int value)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coefficients[i] /= value;
        }
        return *this;
    }
    int &operator[](int index)
    {
        return coefficients[index];
    }
    void setCoefficients(int index, int value)
    {
        coefficients[index] = value;
    }
    void setCoefficients(int *coefficients)
    {
        this->coefficients = coefficients;
    }
    int getCoefficients(int index)
    {
        return coefficients[index];
    }
    void setSize(int size)
    {
        this->size = size;
    }
    int getSize()
    {
        return size;
    }

private:
    int *coefficients;
    int size;
};
ostream &operator<<(ostream &os, Polynomial &polynomial)
{
    string str = "";
    if (polynomial.getCoefficients(polynomial.getSize() - 1) < 0)
    {
        str += "-";
    }
    for (int i = polynomial.getSize() - 1; i > 0; i--)
    {
        if (polynomial.getCoefficients(i) != 0)
        {
            if (abs(polynomial.getCoefficients(i)) != 1)
            {
                char temp[1000];
                itoa(abs(polynomial.getCoefficients(i)), temp, 10);
                str += temp;
            }
            str += 'x';
            if (i != 1)
            {
                char temp[1000];
                itoa(i, temp, 10);
                str += "^";
                str += temp;
            }
        }
        if (polynomial.getCoefficients(i - 1) != 0)
        {
            if (polynomial.getCoefficients(i - 1) > 0)
            {
                str += "+";
            }
            else
            {
                str += "-";
            }
        }
    }
    if (polynomial.getCoefficients(0) != 0)
    {
        char temp[1000];
        itoa(abs(polynomial.getCoefficients(0)), temp, 10);
        str += temp;
    }
    str += "\n";
    if (str == "")
    {
        str = '0';
    }
    os << str;
    return os;
}
istream &operator>>(istream &is, Polynomial &polynomial)
{
    string str;
    int *arr;
    int coefficient = 1;
    int st = 0;
    int maxst = -1;
    is >> str;
    int i = 0;
    while (i < str.size())
    {
        coefficient = 1;
        st = 0;
        if (str[i] == '-')
        {
            coefficient *= -1;
            i++;
        }
        if (str[i] == '+')
        {
            i++;
        }
        if (str[i] != 'x')
        {
            char temp[2] = {str[i], '\0'};
            coefficient *= atoi(temp);
            if (i < str.size())
            {
                i++;
            }
            else
            {
                st = 0;
                arr[st] = coefficient;
                break;
            }
        }
        if (str[i] != 'x')
        {
            st = 0;
        }
        else
        {
            if (i < str.size())
            {
                i++;
                if (str[i] == '^')
                {
                    i++;
                    while (i < str.size() && str[i] >= '0')
                    {
                        char temp[2] = {str[i], '\0'};
                        st = 10 * st + atoi(temp);
                        i++;
                    }
                }
                else
                {
                    st = 1;
                }
            }
            else
            {
                st = 1;
                arr[st] = coefficient;
                break;
            }
        }
        if (maxst == -1)
        {
            maxst = st;
            arr = new int[maxst + 1];
            polynomial.setCoefficients(arr);
            for (int j = 0; j < maxst + 1; j++)
            {
                arr[j] = 0;
            }
        }
        arr[st] = coefficient;
    }
    polynomial.setSize(maxst + 1);
    return is;
}
int main()
{
    Polynomial pol;
    cin >> pol;
    cout << pol;
    return 0;
}