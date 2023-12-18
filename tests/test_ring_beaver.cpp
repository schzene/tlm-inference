#include "LinearBeaver/linear-beaver.hpp"
#include "utils/emp-tool.h"
#include "utils/utils.h"
#include <iostream>
#include <random>
using namespace std;
using namespace sci;

int party, port = 32000;
string address = "127.0.0.1";
IOPack *iopack;
size_t dim1 = 3, dim2 = 3, dim3 = 5;
uint64_t a = 1;
uint64_t b = 1;
uint64_t c = 2;
LinearBeaver *prod;

uint64_t *matmul(uint64_t *X, uint64_t *Y, size_t dim1, size_t dim2, size_t dim3) {
    uint64_t *Y_T = T(Y, dim2, dim3);
    size_t i, j, k;
    uint64_t *Z = new uint64_t[dim1 * dim3];
    for (i = 0; i < dim1; i++) {
        for (j = 0; j < dim3; j++) {
            Z[i * dim3 + j] = dot(X + i * dim2, Y_T + j * dim2, dim2);
        }
    }
    delete[] Y_T;
    return Z;
}

void test_matrix_multiplication(uint64_t *X, uint64_t *Y,
                                size_t dim1, size_t dim2, size_t dim3,
                                uint64_t a, uint64_t b, uint64_t c) {
    size_t i;
    uint64_t num_rounds = iopack->get_rounds();
    uint64_t comm = iopack->get_comm();
    INIT_TIMER;
    START_TIMER;
    auto result_local = prod->matrix_multiplication(X, Y, dim1, dim2, dim3, a, b, c);
    STOP_TIMER("matmul");
    comm = iopack->get_comm() - comm;
    cout << "Bytes Sent:  " << comm << endl;
    num_rounds = iopack->get_rounds() - num_rounds;
    cout << "Num rounds:  " << num_rounds << endl;

    // iopack->io->send_data(result_local, sizeof(uint64_t) * dim1 * dim3);
    // auto result_remote = new uint64_t[dim1 * dim3];
    // iopack->io->recv_data(result_remote, sizeof(uint64_t) * dim1 * dim3);

    // iopack->io->send_data(X, sizeof(uint64_t) * dim1 * dim2);
    // iopack->io->send_data(Y, sizeof(uint64_t) * dim2 * dim3);
    // auto X_remote = new uint64_t[dim1 * dim3];
    // auto Y_remote = new uint64_t[dim2 * dim3];
    // iopack->io->recv_data(X_remote, sizeof(uint64_t) * dim1 * dim2);
    // iopack->io->recv_data(Y_remote, sizeof(uint64_t) * dim2 * dim3);
    // for (i = 0; i < dim1 * dim2; i++) {
    //     X_remote[i] += X[i];
    // }
    // for (i = 0; i < dim2 * dim3; i++) {
    //     Y_remote[i] += Y[i];
    // }
    // auto Z = matmul(X_remote, Y_remote, dim1, dim2, dim3);
    // delete[] X_remote;
    // delete[] Y_remote;

    // int error = 0;
    // for (i = 0; i < dim1 * dim3; i++) {
    //     error += (Z[i] - result_local[i] - result_remote[i]);
    // }
    // if (!error) {
    //     cout << "No error\n";
    // }

    // delete[] Z;
    // delete[] result_remote;
    delete[] result_local;
}

int main(int argc, char **argv) {
    ArgMapping amap;
    amap.arg("r", party, "Role of party: ALICE = 1; BOB = 2");
    amap.arg("p", port, "Port Number");
    amap.arg("a", a, "beaver a");
    amap.arg("b", b, "beaver b");
    amap.arg("c", c, "beaver c");
    amap.parse(argc, argv);

    iopack = new IOPack(party, port, "127.0.0.1"); // LinearBeaver *prod;
    prod = new LinearBeaver(party, iopack);

    // prepare data
    uint64_t *rand_X = new uint64_t[dim1 * dim2];
    uint64_t *rand_Y = new uint64_t[dim2 * dim3];

    // generate test data
    PRG128 prg;
    prg.random_data(rand_X, sizeof(uint64_t) * dim1 * dim2);
    prg.random_data(rand_Y, sizeof(uint64_t) * dim2 * dim3);
    for (size_t i = 0; i < dim1 * dim2; i++) {
        rand_X[i] %= 256;
    }
    for (size_t i = 0; i < dim2 * dim3; i++) {
        rand_Y[i] %= 256;
    }

    cout << "**********************************\n";
    cout << "Test matrix mul\n";
    cout << "**********************************\n";
    printf("matrix size: x(%ld*%ld), y(%ld*%ld)\n", dim1, dim2, dim2, dim3);
    test_matrix_multiplication(rand_X, rand_Y, dim1, dim2, dim3, a, b, c);
    delete[] rand_X;
    delete[] rand_Y;
    cout << "Test matrix mul end, data cleaned";
    cout << "\n**********************************\n";
    delete iopack;
    delete prod;
    return 0;
}