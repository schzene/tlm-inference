#include "LinearBeaver/linear-beaver.hpp"
#include "utils/emp-tool.h"
#include <iostream>
#include <random>
using namespace std;
using namespace sci;

int party, port = 32000;
string address = "127.0.0.1";
IOPack *iopack;
uint64_t a = 1;
uint64_t b = 1;
uint64_t c = 2;
LinearBeaver *prod;

void clean(vector<uint64_t *> &X) {
    for (auto ptr : X) {
        delete[] ptr;
    }
    X.clear();
}

vector<uint64_t *> matrix_multiplication(vector<uint64_t *> &X, size_t X_column,
                                         vector<uint64_t *> &Y, size_t Y_column) {
    assert(X_column == Y.size() || X_column == Y_column);
    vector<uint64_t *> Y_T;
    if (X_column == Y.size()) {
        Y_T = T(Y, Y_column);
    } else {
        Y_T = copy(Y, Y_column);
    }

    size_t i, j;
    vector<uint64_t *> Z = vector<uint64_t *>(X.size());
    for (i = 0; i < Z.size(); i++) {
        Z[i] = new uint64_t[Y_T.size()];
    }
    for (i = 0; i < X.size(); i++) {
        for (j = 0; j < Y_T.size(); j++) {
            Z[i][j] = sum(mul(X[i], Y_T[j], X_column), X_column);
        }
    }
    clean(Y_T);
    return Z;
}

vector<uint64_t *> matrix_mul(vector<uint64_t *> &X, size_t X_column,
                                         vector<uint64_t *> &Y, size_t Y_column) {
    size_t i, j, k;
    vector<uint64_t *> Z = vector<uint64_t *>(X.size());
    for (i = 0; i < Z.size(); i++) {
        Z[i] = new uint64_t[Y_column];
    }
    for (i = 0; i < X.size(); i++) {
        for (j = 0; j < Y_column; j++) {
            Z[i][j] = 0;
            for (k = 0; k < X_column; k++) {
                Z[i][j] += X[i][k] * Y[k][j];
            }
        }
    }
    return Z;
}

void test_matrix_multiplication(vector<uint64_t *> &X, size_t X_column,
                                vector<uint64_t *> &Y, size_t Y_column,
                                uint64_t a, uint64_t b, uint64_t c) {
    size_t i, j;
    uint64_t num_rounds = iopack->get_rounds();
    uint64_t comm = iopack->get_comm();
    auto result_local = prod->matrix_multiplication(X, X_column, Y, Y_column, a, b, c);
    comm = iopack->get_comm() - comm;
    cout << "Bytes Sent:  " << comm << endl;
    num_rounds = iopack->get_rounds() - num_rounds;
    cout << "Num rounds:  " << num_rounds << endl;

    for (i = 0; i < result_local.size(); i++) {
        iopack->io->send_data(result_local[i], sizeof(uint64_t) * Y_column);
    }
    auto result_remote = vector<uint64_t *>(result_local.size());
    for (j = 0; j < result_remote.size(); j++) {
        result_remote[j] = new uint64_t[Y_column];
        iopack->io->recv_data(result_remote[j], sizeof(uint64_t) * Y_column);
    }

    for (i = 0; i < X.size(); i++) {
        iopack->io->send_data(X[i], sizeof(uint64_t) * X_column);
    }
    for (i = 0; i < Y.size(); i++) {
        iopack->io->send_data(Y[i], sizeof(uint64_t) * Y_column);
    }
    vector<uint64_t*> X_remote = vector<uint64_t*>(X.size()), Y_remote = vector<uint64_t*>(Y.size());
    for (i = 0; i < X.size(); i++) {
        X_remote[i] = new uint64_t[X_column];
        iopack->io->recv_data(X_remote[i], sizeof(uint64_t) * X_column);
        for (j = 0; j < X_column; j++) {
            X_remote[i][j] += X[i][j];
        }
    }
    for (i = 0; i < Y.size(); i++) {
        Y_remote[i] = new uint64_t[Y_column];
        iopack->io->recv_data(Y_remote[i], sizeof(uint64_t) * Y_column);
        for (j = 0; j < Y_column; j++) {
            Y_remote[i][j] += Y[i][j];
        }
    }
    auto Z = matrix_multiplication(X_remote, X_column, Y_remote, Y_column);
    auto Z1 = matrix_mul(X_remote, X_column, Y_remote, Y_column);
    clean(X_remote);
    clean(Y_remote);

    for (i = 0; i < X.size(); i++) {
        for (j = 0; j < Y_column; j++) {
            cout << result_local[i][j] + result_remote[i][j] - Z[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for (i = 0; i < X.size(); i++) {
        for (j = 0; j < Y_column; j++) {
            cout << result_local[i][j] + result_remote[i][j] - Z1[i][j] << " ";
        }
        cout << "\n";
    }
    clean(Z);
    clean(Z1);
    clean(result_local);
    clean(result_remote);
}

void test_vector_mul(uint64_t *x, uint64_t *y, size_t size) {
    size_t i;
    uint64_t num_rounds = iopack->get_rounds();
    uint64_t comm = iopack->get_comm();
    auto result_local = prod->vector_multiplication(x, y, size, a, b, c);
    comm = iopack->get_comm() - comm;
    cout << "Bytes Sent:  " << comm << endl;
    num_rounds = iopack->get_rounds() - num_rounds;
    cout << "Num rounds:  " << num_rounds << endl;

    iopack->io->send_data(result_local, sizeof(uint64_t) * size);
    auto result_remote = new uint64_t[size];
    iopack->io->recv_data(result_remote, sizeof(uint64_t) * size);
    for (i = 0; i < size; i++)
        result_local[i] += result_remote[i];

    iopack->io->send_data(x, sizeof(uint64_t) * size);
    iopack->io->send_data(y, sizeof(uint64_t) * size);
    auto x_remote = new uint64_t[size];
    auto y_remote = new uint64_t[size];
    iopack->io->recv_data(x_remote, sizeof(uint64_t) * size);
    iopack->io->recv_data(y_remote, sizeof(uint64_t) * size);

    cout << "result error:\n";
    for (i = 0; i < size; i++) {
        cout << result_local[i] - (x[i] + x_remote[i]) * (y[i] + y_remote[i]) << " ";
    }
    cout << endl;
    delete[] result_local;
    delete[] result_remote;
    delete[] x_remote;
    delete[] y_remote;
}

int main(int argc, char **argv) {
    ArgMapping amap;
    amap.arg("r", party, "Role of party: ALICE = 1; BOB = 2");
    amap.arg("p", port, "Port Number");
    amap.arg("a", a, "beaver a");
    amap.arg("b", b, "beaver b");
    amap.arg("c", c, "beaver c");
    amap.parse(argc, argv);
    // x 3*3 y 3*5
    iopack = new IOPack(party, port, "127.0.0.1"); // LinearBeaver *prod;
    // prod->matrix_multiplication(X, Y, a, b, c);
    prod = new LinearBeaver(party, iopack);

    // prepare data
    size_t vector_size = 5;
    uint64_t *rand_x = new uint64_t[vector_size];
    uint64_t *rand_y = new uint64_t[vector_size];
    size_t X_row = 3, X_column = 3, Y_row = X_column, Y_column = 5;
    vector<uint64_t *> rand_X = vector<uint64_t *>(3);
    vector<uint64_t *> rand_Y = vector<uint64_t *>(3);

    // generate test data
    PRG128 prg;
    prg.random_data(rand_x, sizeof(uint64_t) * 5);
    prg.random_data(rand_y, sizeof(uint64_t) * 5);
    for (auto i = 0; i < X_row; i++) {
        rand_X[i] = new uint64_t[X_column];
        prg.random_data(rand_X[i], sizeof(uint64_t) * X_column);
        for (auto j = 0; j < X_column; j++) {
            rand_X[i][j] = rand_X[i][j] % 16384;
        }
    }
    for (auto i = 0; i < Y_row; i++) {
        rand_Y[i] = new uint64_t[Y_column];
        prg.random_data(rand_Y[i], sizeof(uint64_t) * Y_column);
        for (auto j = 0; j < Y_column; j++) {
            rand_Y[i][j] = rand_Y[i][j] % 16384;
        }
    }

    cout << "\n**********************************\n";
    cout << "Test vector mul\n";
    cout << "**********************************\n";
    cout << "vector size: " << vector_size << "\n";
    test_vector_mul(rand_x, rand_y, 5);
    delete[] rand_x;
    delete[] rand_y;
    cout << "Test vector mul end, data cleaned";
    cout << "\n**********************************\n";

    cout << "\n**********************************\n";
    cout << "Test matrix mul\n";
    cout << "**********************************\n";
    printf("matrix size: x(%ld*%ld), y(%ld*%ld)\n", X_row, X_column, Y_row, Y_column);
    test_matrix_multiplication(rand_X, X_column, rand_Y, Y_column, a, b, c);
    clean(rand_X);
    clean(rand_Y);
    cout << "Test matrix mul end, data cleaned";
    cout << "\n**********************************\n";
    delete iopack;
    delete prod;
    return 0;
}