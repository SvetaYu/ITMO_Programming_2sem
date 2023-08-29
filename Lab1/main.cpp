#include <iostream>
#include "shapes.h"
#include <vector>
#include "Polynomial.h"

using namespace std;

int main()
{
    Polynomial pol2;
    Polynomial pol;
    Polynomial pol3;
    cin >> pol;
    cin >> pol2;
    pol3 = pol * pol2;
    cout << pol << endl;
    cout << pol2 << endl;
    cout << pol3;
    return 0;
}