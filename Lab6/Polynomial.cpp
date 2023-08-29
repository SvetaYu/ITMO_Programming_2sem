#include <iostream>

namespace my {
    constexpr long long pow(const int x, const int d) {
        long long k;
        if (d == 0)
            return 1;
        if (d == 1)
            return x;
        if (d == 2)
            return x * x;
        if (d % 2 == 0) {
            k = my::pow(x, d / 2);
            return k * k;
        } else {
            k = my::pow(x, (d - 1) / 2);
            return k * k * d;
        }
    }
}

template<size_t S>
class Polynomial {
public:
    constexpr Polynomial() = default;

    constexpr Polynomial(const int coefficients[S]) {
        for (int i = 0; i < S; i++) {
            this->coefficients[i] = coefficients[i];
        }
    }

    ~Polynomial() = default;

    constexpr long long operator()(const int x) const {
        long long sum = 0;
        long long st = 1;
        for (int i = 0; i < S; ++i) {

            sum += my::pow(x, i) * coefficients[i];
//            sum += st * coefficients[i];
            st *= x;

        }
        return sum;
    }

private:
    int coefficients[S];
};
