#include <iostream>
#include <LinearBeaver/linear-beaver.h>
using namespace std;

int main() {
    auto b_v = beaver();
    cout << "a1 = " << b_v[0] << "\n";
    cout << "b1 = " << b_v[2] << "\n";
    cout << "c1 = " << b_v[4] << "\n\n";
    cout << "a2 = " << b_v[1] << "\n";
    cout << "b2 = " << b_v[3] << "\n";
    cout << "c2 = " << b_v[5] << "\n\n";
    delete[] b_v;
}