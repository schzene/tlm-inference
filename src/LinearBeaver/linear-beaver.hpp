#ifndef LINEAR_BEAVER_H
#define LINEAR_BEAVER_H
#include "LinearBeaver/beaver.h"
#include "utils/io_pack.h"
#include <numeric>
#include <vector>

inline uint64_t sum(uint64_t *v, size_t size) {
    return std::accumulate(v, v + size, 0);
}

inline std::vector<uint64_t *> T(std::vector<uint64_t *> M, size_t column) {
    auto row = M.size();
    size_t i, j;
    std::vector<uint64_t *> result = std::vector<uint64_t *>(column);
    for (i = 0; i < column; i++) {
        result[i] = new uint64_t[row];
    }
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            result[j][i] = M[i][j];
        }
    }
    return result;
}

inline std::vector<uint64_t *> copy(std::vector<uint64_t *> M, size_t column) {
    size_t i, j;
    std::vector<uint64_t *> result = std::vector<uint64_t *>(M.size());
    for (i = 0; i < result.size(); i++) {
        result[i] = new uint64_t[column];
    }
    for (i = 0; i < result.size(); i++) {
        for (j = 0; j < column; j++) {
            result[i][j] = M[i][j];
        }
    }
    return result;
}

uint64_t *add(uint64_t *v1, uint64_t *v2, size_t size) {
    auto result = new uint64_t[size];
    for (size_t i = 0; i < size; i++) {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

uint64_t *mul(uint64_t *v1, uint64_t *v2, size_t size) {
    auto result = new uint64_t[size];
    for (size_t i = 0; i < size; i++) {
        result[i] = v1[i] * v2[i];
    }
    return result;
}

class LinearBeaver {
public:
    int party;
    sci::IOPack *iopack;

    LinearBeaver(int party_, sci::IOPack *iopack_) : iopack(iopack_) {
        assert(party_ == sci::PUBLIC || party_ == sci::ALICE || party_ == sci::BOB);
        this->party = party_;
    };

    ~LinearBeaver(){};

    uint64_t *vector_multiplication(uint64_t *x, uint64_t *y, size_t size,
                                    uint64_t a, uint64_t b, uint64_t c) {
        uint64_t *s = new uint64_t[size];
        uint64_t *t = new uint64_t[size];
        size_t i;
        for (i = 0; i < size; i++) {
            s[i] = x[i];
            t[i] = y[i];
        }
        sub(s, size, a);
        sub(t, size, b);
        iopack->io->send_data(s, sizeof(uint64_t) * size);
        iopack->io->send_data(t, sizeof(uint64_t) * size);

        uint64_t *s1 = new uint64_t[size];
        uint64_t *t1 = new uint64_t[size];
        iopack->io->recv_data(s1, sizeof(uint64_t) * size);
        iopack->io->recv_data(t1, sizeof(uint64_t) * size);

        for (i = 0; i < size; i++) {
            s[i] += s1[i];
            t[i] += t1[i];
            s1[i] = s[i];
            t1[i] = t[i];
        }

        mul(t, size, a);             // at
        mul(s, size, b);             // bs
        auto st = mul(s1, t1, size); // st
        for (i = 0; i < size; i++) {
            s[i] = s[i] + t[i] + c; // at + bs + c;
        }
        delete[] t;
        delete[] s1;
        delete[] t1;
        if (party == sci::ALICE) {
            for (i = 0; i < size; i++) {
                s[i] = s[i] + st[i]; // at + bs + c + st;
            }
        }
        delete[] st;
        return s;
    };

    std::vector<uint64_t *> matrix_multiplication(std::vector<uint64_t *> X, size_t X_column,
                                                  std::vector<uint64_t *> Y, size_t Y_column,
                                                  uint64_t a, uint64_t b, uint64_t c) {
        assert(X_column == Y.size() || X_column == Y_column);
        std::vector<uint64_t *> Y_T;
        if (X_column == Y.size()) {
            Y_T = T(Y, Y_column);
        } else {
            Y_T = copy(Y, Y_column);
        }

        size_t i, j;
        std::vector<uint64_t *> Z = std::vector<uint64_t *>(X.size());
        for (i = 0; i < Z.size(); i++) {
            Z[i] = new uint64_t[Y_T.size()];
        }
        for (i = 0; i < X.size(); i++) {
            for (j = 0; j < Y_T.size(); j++) {
                Z[i][j] = sum(vector_multiplication(X[i], Y_T[j], X_column, a, b, c), X_column);
            }
        }
        for (auto ptr : Y_T) {
            delete[] ptr;
        }
        Y_T.clear();
        return Z;
    }
};
#endif