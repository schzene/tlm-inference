#include <iostream>
#include "LinearBeaver/linear-beaver.hpp"
using namespace std;

int main() {
    auto b_v = beaver();
    cout << "Alice: \n";
    printf("a=%ld b=%ld c=%ld\n", b_v[0], b_v[2], b_v[4]);
    cout << "\nBob: \n";
    printf("a=%ld b=%ld c=%ld\n", b_v[1], b_v[3], b_v[5]);
    delete[] b_v;
}