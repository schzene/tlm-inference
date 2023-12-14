#include "linear-beaver.h"
#include <string>

LinearBeaver::LinearBeaver(int party_, sci::NetIO *io_) : party(party_),
                                                          io(io_) {}

vector<uint64_t> LinearBeaver::vector_multiplication(vector<uint64_t> &x, vector<uint64_t> &y,
                                                     uint64_t a, uint64_t b, uint64_t c)
{
    assert(x.size() == y.size());

    auto s_local = x - a;
    auto t_local = y - b;
    for (auto i : s_local)
    {
        io->send_data(&i, sizeof(i));
    }
    for (auto i : t_local)
    {
        io->send_data(&i, sizeof(i));
    }
    vector<uint64_t> s_remote = vector<uint64_t>(s_local.size());
    vector<uint64_t> t_remote = vector<uint64_t>(t_local.size());
    for (size_t i = 0; i < s_remote.size(); i++)
    {
        io->recv_data(&s_remote[i], sizeof(uint64_t));
    }
    for (size_t i = 0; i < t_remote.size(); i++)
    {
        io->recv_data(&t_remote[i], sizeof(uint64_t));
    }
    auto s = s_local + s_remote;
    auto t = t_local + t_remote;

    auto at = t * a, bs = s * b, st = s * t;
    auto result = at + bs;
    result = result + c;
    if (party == sci::ALICE)
    {
        return result + st;
    }
    else if (party == sci::BOB)
    {
        return result;
    }
}

vector<vector<uint64_t>> LinearBeaver::matrix_multiplication(vector<vector<uint64_t>> &X,
                                                             vector<vector<uint64_t>> &Y,
                                                             uint64_t a, uint64_t b, uint64_t c)
{
    auto Y_T = T(Y);
    size_t i, j, k;
    vector<vector<uint64_t>> Z = vector<vector<uint64_t>>(X.size());
    for (i = 0; i < Z.size(); i++)
    {
        Z[i] = vector<uint64_t>(Y_T.size());
    }
    for (i = 0; i < X.size(); i++)
    {
        for (j = 0; j < Y_T.size(); j++)
        {
            Z[i][j] = sum(vector_multiplication(X[i], Y[j], a, b, c));
        }
    }
    return Z;
}