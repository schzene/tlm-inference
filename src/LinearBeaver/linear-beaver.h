#ifndef LINEAR_BEAVER_H
#define LINEAR_BEAVER_H
#include "BuildingBlocks/aux-protocols.h"
#include "BuildingBlocks/truncation.h"
#include "BuildingBlocks/value-extension.h"
#include "beaver.h"

#include <numeric>

inline uint64_t sum(vector<uint64_t> v)
{
    return accumulate(v.begin(), v.end(), 0);
}

inline vector<vector<uint64_t>> T(vector<vector<uint64_t>> M)
{
    auto row = M.size(), column = M[0].size();
    size_t i, j;
    vector<vector<uint64_t>> result = vector<vector<uint64_t>>(column);
    for (i = 0; i < column; i++)
    {
        result[i] = vector<uint64_t>(row);
    }
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            result[j][i] = M[i][j];
        }
    }
    return result;
}

vector<uint64_t> operator+(vector<uint64_t> &v1, vector<uint64_t> &v2)
{
    assert(v1.size() == v2.size());
    auto result = vector<uint64_t>(v1.size());
    for (size_t i = 0; i < v1.size(); i++)
    {
        result[i] = v1[i] + v2[i];
    }
    return result;
}

vector<uint64_t> operator*(vector<uint64_t> &v1, vector<uint64_t> &v2)
{
    assert(v1.size() == v2.size());
    auto result = vector<uint64_t>(v1.size());
    for (size_t i = 0; i < v1.size(); i++)
    {
        result[i] = v1[i] * v2[i];
    }
    return result;
}

class LinearBeaver
{
public:
    int party;
    sci::NetIO *io;

    LinearBeaver(int party_, sci::NetIO *io_);

    ~LinearBeaver(){};

    vector<uint64_t> vector_multiplication(vector<uint64_t> &x, vector<uint64_t> &y,
                                           uint64_t a, uint64_t b, uint64_t c);

    vector<vector<uint64_t>> matrix_multiplication(vector<vector<uint64_t>> &X,
                                                   vector<vector<uint64_t>> &Y,
                                                   uint64_t a, uint64_t b, uint64_t c);
};
#endif