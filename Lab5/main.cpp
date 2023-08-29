#include <cstdlib>
#include <list>
#include <set>
#include <string>
#include "Allocator.hpp"

class test {
public:
    char ch;
    int i;
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    allocator<int> alloc(3, std::vector<size_t>{128, 20, 64}, std::vector<size_t>{10, 10, 10});
    allocator<std::string> allocStr(2, std::vector<size_t>{16, 64}, std::vector<size_t>{5, 10});
    allocator<test> allocClass(2, std::vector<size_t>{16, 64}, std::vector<size_t>{3, 3});
    std::list<std::string, allocator<std::string>> l(allocStr);
    std::vector<test, allocator<test>> v(allocClass);
    std::set<int, std::less<>, allocator<int>> s(alloc);

    v.push_back(test{'a', 1});
    v.push_back(test{'b', 2});
    v.push_back(test{'c', 3});
    v.push_back(test{'d', 4});
    v.push_back(test{'e', 5});
    v.push_back(test{'f', 6});
    std::cout << "VECTOR:" << std::endl;
    for (auto &i: v) {
        std::cout << i.ch << "  " << i.i << std::endl;
    }
    v.pop_back();
    v.pop_back();
    v.pop_back();
    std::cout << "VECTOR:" << std::endl;
    for (auto &i: v) {
        std::cout << i.ch << "  " << i.i << std::endl;
    }
    std::cout << std::endl;

    s.insert(5);
    s.insert(12);
    s.insert(0);
    s.insert(-55);
    s.insert(22);
    s.insert(18);
    std::cout << "SET:" << std::endl;
    for (auto i: s) {
        std::cout << i << std::endl;
    }
    s.erase(12);
    s.erase(22);
    std::cout << "SET:" << std::endl;
    for (auto &i: s) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;

    l.push_front("00");
    l.push_back("11");
    l.push_front("--");
    l.push_back("++");
    l.push_front("88");
    std::cout << "LIST:" << std::endl;
    for (auto &i: l) {
        std::cout << i << std::endl;
    }
    l.pop_back();
    l.pop_front();
    l.pop_front();
    std::cout << "LIST:" << std::endl;
    for (auto &i: l) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;

    return 0;
}