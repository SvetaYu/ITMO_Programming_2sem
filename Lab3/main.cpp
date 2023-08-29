#include <iostream>
#include <vector>
#include <array>
#include "circular buffer.hpp"
#include "algorithms.hpp"

template<typename T>
bool foo(T value) {
    if (value < 0) {
        return false;
    }
    return true;
}

template<typename T>
bool foo2(T val1, T val2) {
    if (val1 < val2) {
        return true;
    }
    return false;
}

class human {
private:
public:
    std::string name;
    int age;
    int weight;
    int hight;

    human() = default;

    human(std::string name, int age, int weight, int hight) {
        this->name = name;
        this->age = age;
        this->hight = hight;
        this->weight = weight;
    }

    bool operator<(human &rhs) const {
        return age < rhs.age;
    }

    bool operator>(human &rhs) const {
        return age > rhs.age;
    }

    bool operator<(int rhs) const {
        return age < rhs;
    }

    bool operator>(int rhs) const {
        return age > rhs;
    }

    bool operator==(human &rhs) const {
        return age == rhs.age;
    }

    bool operator!=(human &rhs) const {
        return age != rhs.age;
    }

    bool operator==(int rhs) const {
        return age == rhs;
    }

    bool operator!=(int rhs) const {
        return age != rhs;
    }
};

int main() {
    std::vector<int> v = {-10, 3, 5};
    std::cout << all_of(v.begin(), v.end(), foo<int>) << "     all >0" << std::endl;
    std::cout << any_of(v.begin(), v.end(), foo<int>) << "     any >0" << std::endl;
    std::cout << none_of(v.begin(), v.end(), foo<int>) << "     all <0" << std::endl;
    std::cout << one_of(v.begin(), v.end(), foo<int>) << "     rovno 1 >0" << std::endl;
    std::cout << is_sorted(v.begin(), v.end(), foo2<int>) << "     sort" << std::endl;
    std::cout << is_partitioned(v.begin(), v.end(), foo<int>) << "     left >0 right <0" << std::endl;
    std::cout << *find_not(v.begin(), v.end(), -10) << "     !=-10" << std::endl;
    std::cout << *find_backward(v.begin(), v.end(), 5) << "     5 end" << std::endl;
    std::cout << is_palindrome(v.begin(), v.end()) << "     palindrom" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    human a("a", -10, -10, -10);
    human b("a", 1, 1, 1);
    human c("a", 5, 5, 5);
    human d("a", 14, 14, 14);
    human e("a", 80, 80, 80);
    std::array<human, 5> arr = {a, b, c, d, e};
    std::cout << all_of(arr.begin(), arr.end(), foo<human>) << "     all >0" << std::endl;
    std::cout << any_of(arr.begin(), arr.end(), foo<human>) << "     any >0" << std::endl;
    std::cout << none_of(arr.begin(), arr.end(), foo<human>) << "     all <0" << std::endl;
    std::cout << one_of(arr.begin(), arr.end(), foo<human>) << "     rovno 1 >0" << std::endl;
    std::cout << is_sorted(arr.begin(), arr.end(), foo2<human>) << "     sort" << std::endl;
    std::cout << is_partitioned(arr.begin(), arr.end(), foo<human>) << "     left >0 right <0" << std::endl;
    std::cout << (*find_not(arr.begin(), arr.end(), -10)).age << "     !=-10" << std::endl;
    std::cout << (*find_backward(arr.begin(), arr.end(), -10)).age << "     -10 c end" << std::endl;
    std::cout << is_palindrome(arr.begin(), arr.end()) << "     palindrom" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    circular_buffer<human> buf(7); //-8 8 4 -10 4 8 -8
    buf.push_back(human{"A", 4, 4, 4});
    buf.push_front(human{"A", 8, 8, 8});
    buf.push_back(human{"B", -10, -10, -10});
    buf.push_front(human{"A", -8, -8, -8});
    buf.push_front(human{"A", 7, 7, 7});
    buf.push_back(human{"B", 4, 4, 4});
    buf.push_back(human{"B", 8, 8, 8});
    buf.push_back(human{"B", -8, -8, -8});
    for (auto &it : buf)
    {
        std :: cout << it.age<< "   ";
    }
    std :: cout << std :: endl;
    std::cout << all_of(buf.begin(), buf.end(), foo<human>) << "     all >0" << std::endl;
    std::cout << any_of(buf.begin(), buf.end(), foo<human>) << "     any >0" << std::endl;
    std::cout << none_of(buf.begin(), buf.end(), foo<human>) << "     all <0" << std::endl;
    std::cout << one_of(buf.begin(), buf.end(), foo<human>) << "     rovno 1 >0" << std::endl;
    std::cout << is_sorted(buf.begin(), buf.end(), foo2<human>) << "     sort" << std::endl;
    std::cout << is_partitioned(buf.begin(), buf.end(), foo<human>) << "     left >0 right <0" << std::endl;
    std::cout << (*find_not(buf.begin(), buf.end(), -10)).age << "     !=-10" << std::endl;
    std::cout << (*find_backward(buf.begin(), buf.end(), -10)).age << "     -10 c end" << std::endl;
    std::cout << is_palindrome(buf.begin(), buf.end()) << "     palindrom" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    circular_buffer<char> buf2(10);
    std::cout << all_of(buf2.begin(), buf2.end(), foo<char>) << "     all >0" << std::endl;
    std::cout << any_of(buf2.begin(), buf2.end(), foo<char>) << "     any >0" << std::endl;
    std::cout << none_of(buf2.begin(), buf2.end(), foo<char>) << "     all <0" << std::endl;
    std::cout << one_of(buf2.begin(), buf2.end(), foo<char>) << "     rovno 1 >0" << std::endl;
    std::cout << is_sorted(buf2.begin(), buf2.end(), foo2<char>) << "     sort" << std::endl;
    std::cout << is_partitioned(buf2.begin(), buf2.end(), foo<char>) << "     left >0 right <0" << std::endl;
//    std::cout << (*find_not(buf.begin(), buf.end(), -10)).age << "     !=-10" << std::endl;
//    std::cout << (*find_backward(buf.begin(), buf.end(), -10)).age << "     -10 c end" << std::endl;
    std::cout << is_palindrome(buf2.begin(), buf2.end()) << "     palindrom" << std::endl;
    return 0;
}
