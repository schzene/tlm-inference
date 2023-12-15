#include <LinearBeaver/linear-beaver.h>
#include <string>

// uint64_t *LinearBeaver::vector_multiplication(uint64_t *x, uint64_t *y, size_t size,
//                                               uint64_t a, uint64_t b, uint64_t c) {
//     auto s = new uint64_t[size], t = new uint64_t[size];
//     size_t i;
//     for (i = 0; i < size; i++) {
//         s[i] = x[i];
//         t[i] = y[i];
//     }
//     sub(s, size, a);
//     sub(t, size, b);
//     iopack->io->send_data(s, sizeof(uint64_t) * size);
//     iopack->io->send_data(t, sizeof(uint64_t) * size);

//     uint64_t *s1 = new uint64_t[size];
//     uint64_t *t1 = new uint64_t[size];
//     iopack->io->recv_data(s1, sizeof(uint64_t) * size);
//     iopack->io->recv_data(t1, sizeof(uint64_t) * size);

//     for (i = 0; i < size; i++) {
//         s[i] += s1[i];
//         t[i] += t1[i];
//         s1[i] = s[i];
//         t1[i] = t[i];
//     }

//     mul(t, size, a);             // at
//     mul(s, size, b);             // bs
//     auto st = mul(s1, t1, size); // st
//     for (i = 0; i < size; i++) {
//         s[i] = s[i] + t[i] + c; // at + bs + c;
//     }
//     delete[] t;
//     delete[] s1;
//     delete[] t1;
//     if (party == sci::ALICE) {
//         for (i = 0; i < size; i++) {
//             s[i] = s[i] + st[i]; // at + bs + c + st;
//         }
//     }
//     delete[] st;
//     return s;
// }

// vector<vector<uint64_t>> LinearBeaver::matrix_multiplication(vector<uint64_t *> &X, size_t x_column,
//                                                              vector<uint64_t *> &Y, size_t y_column,
//                                                              uint64_t a, uint64_t b, uint64_t c) {
//     auto Y_T = T(Y);
//     size_t i, j, k;
//     vector<vector<uint64_t>> Z = vector<vector<uint64_t>>(X.size());
//     for (i = 0; i < Z.size(); i++) {
//         Z[i] = vector<uint64_t>(Y_T.size());
//     }
//     for (i = 0; i < X.size(); i++) {
//         for (j = 0; j < Y_T.size(); j++) {
//             Z[i][j] = sum(vector_multiplication(X[i], Y[j], a, b, c));
//         }
//     }
//     return Z;
// }