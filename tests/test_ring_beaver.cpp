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
uint64_t a = 3;
uint64_t b = 3;
uint64_t c = 5;
LinearBeaver *prod;

vector<uint64_t *> matmul(vector<uint64_t *> &X, size_t X_column, vector<uint64_t *> &Y, size_t Y_column)
{
}

void show(vector<uint64_t *> M, size_t column)
{
    size_t i, j;
    for (i = 0; i < M.size(); i++)
    {
        for (j = 0; j < column; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << "\n";
    }
}

void test_matrix_multiplication(vector<uint64_t *> &X, size_t X_column,
                                vector<uint64_t *> &Y, size_t Y_column,
                                uint64_t a, uint64_t b, uint64_t c)
{
    size_t i, j;
    auto result_local = prod->matrix_multiplication(X, X_column, Y, Y_column, a, b, c);
    for (i = 0; i < result_local.size(); i++)
    {
        iopack->io->send_data(result_local[i], sizeof(uint64_t) * Y_column);
    }
    auto result_remote = vector<uint64_t *>(result_local.size());
    for (j = 0; j < result_remote.size(); j++)
    {
        result_remote[j] = new uint64_t[Y_column];
        iopack->io->recv_data(result_remote[j], sizeof(uint64_t) * Y_column);
    }

    for (i = 0; i < X.size(); i++)
        iopack->io->send_data(X[i], sizeof(uint64_t) * X_column);
    for (i = 0; i < Y.size(); i++)
        iopack->io->send_data(Y[i], sizeof(uint64_t) * Y_column);
    vector<uint64_t *> X_remote = vector<uint64_t *>(X.size());
    vector<uint64_t *> Y_remote = vector<uint64_t *>(Y.size());
    for (i = 0; i < X.size(); i++)
    {
        X_remote[i] = new uint64_t[X_column];
        iopack->io->recv_data(X_remote[i], sizeof(uint64_t) * X_column);
        for (j = 0; j < X_column; j++)
            X_remote[i][j] += X[i][j];
    }
    for (i = 0; i < Y.size(); i++)
    {
        Y_remote[i] = new uint64_t[Y_column];
        iopack->io->recv_data(Y_remote[i], sizeof(uint64_t) * Y_column);
        for (j = 0; j < Y_column; j++)
            Y_remote[i][j] += Y[i][j];
    }
    // show(X_remote, X_column);
    cout << "\n";
    auto Z = matmul(X_remote, X_column, Y_remote, Y_column);
    show(Z, Y_column);
    cout << "\n";
    for (i = 0; i < X.size(); i++)
    {
        for (j = 0; j < Y_column; j++)
        {
            cout << result_local[i][j] + result_remote[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void test_vector_mul(uint64_t *x, uint64_t *y, size_t size)
{
}

int main(int argc, char **argv)
{
    ArgMapping amap;
    amap.arg("r", party, "Role of party: ALICE = 1; BOB = 2");
    amap.arg("p", port, "Port Number");
    amap.arg("a", a, "beaver a");
    amap.arg("b", b, "beaver b");
    amap.arg("c", c, "beaver c");
    amap.parse(argc, argv);
    // x 3*3 y 3*5
    iopack = new IOPack(party, port, "127.0.0.1"); // LinearBeaver *prod;

    prod = new LinearBeaver(party, iopack);

    size_t X_column = 3, Y_column = 5;
    vector<uint64_t *> rand_X = vector<uint64_t *>(3);
    vector<uint64_t *> rand_Y = vector<uint64_t *>(3);

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

    for (auto i = 0; i < 3; i++)
    {
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
    for (auto i = 0; i < 3; i++)
    {
        delete[] rand_X[i];
        delete[] rand_Y[i];
    }
    rand_X.clear();
    rand_Y.clear();
    return 0;
}