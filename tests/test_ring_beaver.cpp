#include "utils/emp-tool.h"
#include <LinearBeaver/linear-beaver.h>
#include <iostream>
#include <random>
using namespace std;
using namespace sci;

int party, port = 32000;
string address = "127.0.0.1";
IOPack *iopack;
uint64_t a;
uint64_t b;
uint64_t c;
LinearBeaver *prod;

vector<uint64_t*> matmul(vector<uint64_t*> &X, size_t X_column, vector<uint64_t*> &Y, size_t Y_column) {
    vector<uint64_t*> Z = vector<uint64_t*>(X.size());
    auto Y_T = T(Y, Y_column);
    for (int i = 0; i < Z.size(); i++) Z[i] = new uint64_t[Y_T.size()];
    size_t i, j, k;
    for (i = 0; i < X.size(); i++) {
        for (j = 0; j < Y_T.size(); j++) {
            Z[i][j] = sum(mul(X[i], Y_T[j], X_column), X_column);
        }
    }
    return Z;
}

void show(vector<uint64_t*> M, size_t column) {
    size_t i, j;
    for (i = 0; i < M.size(); i++) {
        for (j = 0; j< column; j++) {
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
}

void test_matrix_multiplication(vector<uint64_t*> &X, size_t X_column,
                                                                          vector<uint64_t*> &Y, size_t Y_column,
                                                                          uint64_t a, uint64_t b, uint64_t c) {
    size_t i, j;
    auto result_local = prod->matrix_multiplication(X, X_column, Y, Y_column, a, b, c);
    for (i = 0; i < result_local.size(); i++) {
        iopack->io->send_data(result_local[i], sizeof(uint64_t) * Y_column);
    }
    auto result_remote = vector<uint64_t*>(result_local.size());
    for(j = 0; j < result_remote.size(); j++) {
        result_remote[j] = new uint64_t[Y_column];
        iopack->io->recv_data(result_remote[j], sizeof(uint64_t) * Y_column);
    }

    for (i = 0; i < X.size(); i++) iopack->io->send_data(X[i], sizeof(uint64_t) * X_column);
    for (i = 0; i < Y.size(); i++) iopack->io->send_data(Y[i], sizeof(uint64_t) * Y_column);
    vector<uint64_t*> X_remote = vector<uint64_t*>(X.size());
    vector<uint64_t*> Y_remote = vector<uint64_t*>(Y.size());
    for (i = 0; i < X.size(); i++) {
        X_remote[i] = new uint64_t[X_column];
        iopack->io->recv_data(X_remote[i], sizeof(uint64_t) * X_column);
        for (j = 0; j < X_column; j++) X_remote[i][j] += X[i][j];
    }
    for (i = 0; i < Y.size(); i++) {
        Y_remote[i] = new uint64_t[Y_column];
        iopack->io->recv_data(Y_remote[i], sizeof(uint64_t) * Y_column);
        for (j = 0; j < Y_column; j++) Y_remote[i][j] += Y[i][j];
    }
    // show(X_remote, X_column);
    cout << "\n";
    auto Z = matmul(X_remote, X_column, Y_remote, Y_column);
    show(Z, Y_column);
    cout << "\n";
    for (i = 0; i < X.size(); i++) {
        for (j = 0; j < Y_column; j++) {
            cout << result_local[i][j] + result_remote[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl;
}

void test_vector_mul(uint64_t* x, uint64_t* y, size_t size) {
    size_t i;
    auto result_local = prod->vector_multiplication(x, y, size, a, b, c);
    iopack->io->send_data(result_local, sizeof(uint64_t) * size);
    auto result_remote = new uint64_t[size];
    iopack->io->recv_data(result_remote, sizeof(uint64_t) * size);
    for (i = 0; i < size; i++) result_local[i] += result_remote[i];

    iopack->io->send_data(x, sizeof(uint64_t) * size);
    iopack->io->send_data(y, sizeof(uint64_t) * size);
    auto x_remote = new uint64_t[size];
    auto y_remote = new uint64_t[size];
    iopack->io->recv_data(x_remote, sizeof(uint64_t) * size);
    iopack->io->recv_data(y_remote, sizeof(uint64_t) * size);

    cout << "result_beaver =\n";
    for (i = 0; i < size; i++) cout << result_local[i] << " ";
    cout << endl;

    cout << "reslt_common = \n";
    for (i = 0; i < size; i++) cout << (x[i] + x_remote[i]) * (y[i] + y_remote[i]) << " ";
    cout << endl;

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
    iopack = new IOPack(party, port, "127.0.0.1");// LinearBeaver *prod;
    // prod->matrix_multiplication(X, Y, a, b, c);
    prod = new LinearBeaver(party, iopack);

    // uint64_t *rand_x = new uint64_t[5];
    // uint64_t *rand_y = new uint64_t[5];
    size_t X_column = 3, Y_column = 5;
    vector<uint64_t*> rand_X = vector<uint64_t*>(3);
    vector<uint64_t*> rand_Y = vector<uint64_t*>(3);

    PRG128 prg;
    // prg.random_data(rand_x, sizeof(uint64_t) * 5);
    // prg.random_data(rand_y, sizeof(uint64_t) * 5);
    for (auto i = 0; i < 3; i++) {
        rand_X[i] = new uint64_t[X_column];
        rand_Y[i] = new uint64_t[Y_column];
        prg.random_data(rand_X[i], sizeof(uint64_t) * X_column);
        prg.random_data(rand_Y[i], sizeof(uint64_t) * Y_column);
    }
    cout << rand_X[0][0] << "\n";

    cout << "Test matumul" << endl;
    // test_vector_mul(rand_x, rand_y, 5);
    // delete[] rand_x;
    // delete[] rand_y;
    test_matrix_multiplication(rand_X, X_column, rand_Y, Y_column, a, b, c);
    for (auto i = 0; i < 3; i++) {
        delete[] rand_X[i];
        delete[] rand_Y[i];
    }
    rand_X.clear();
    rand_Y.clear();
    return 0;
}