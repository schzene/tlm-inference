#include <LinearBeaver/linear-beaver.h>
#include "utils/emp-tool.h"
#include <iostream>
#include <random>
using namespace std;
using namespace sci;

int party, port = 32000;
string address = "127.0.0.1";
IOPack *iopack;

void test_matrix_multiplication(vector<vector<uint64_t>> &X,
                                vector<vector<uint64_t>> &Y,
                                uint64_t a, uint64_t b, uint64_t c)

{
    LinearBeaver *prod;
    prod->matrix_multiplication(X, Y, a, b, c);
}

int main(int argc, char **argv)
{
    // x 3*3 y 3*5
    ;
    uint64_t *rand_x = new uint64_t[5];
    uint64_t *rand_y = new uint64_t[5];

    PRG128 prg;
    prg.random_data(rand_x, sizeof(uint64_t));
    prg.random_data(rand_y, sizeof(uint64_t));
    cout << &rand_y << endl;
    cout << "Test matumul" << endl;
    return 0;
}