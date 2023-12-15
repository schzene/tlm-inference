#ifndef BEAVER_H
#define BEAVER_H
#include <cassert>
#include <cstdint>
#include <random>

using namespace std;

inline void add(uint64_t* v, uint64_t size, uint64_t& num) {
    for (size_t i = 0; i < size; i++) {
        v[i] = v[i] + num;
    }
}

inline void add(uint64_t& num, uint64_t* v, uint64_t size) {
    add(v, size, num);
}

inline void sub(uint64_t* v, uint64_t size, uint64_t& num) {
    for (size_t i = 0; i < size; i++) {
        v[i] = v[i] - num;
    }
}

inline void sub(uint64_t& num, uint64_t* v, uint64_t size) {
    for (size_t i = 0; i < size; i++) {
        v[i] = num - v[i];
    }
}

inline void mul(uint64_t* v, uint64_t size, uint64_t& num) {
    for (size_t i = 0; i < size; i++) {
        v[i] = v[i] * num;
    }
}

inline void mul(uint64_t& num, uint64_t* v, uint64_t size) {
    mul(v, size, num);
}

uint64_t* beaver() {
    random_device rd;
    uniform_int_distribution<> dist(0, 100);
    uint64_t* bv = new uint64_t[6];  // a1, a2, b1, b2, c1, c2, (a1 + a2) * (b1 + b2) = (c1 + c2);
    size_t j;
    for (char i = 0; i < 4; i++) {
        bv[i] = dist(rd);
    }
    auto result = (bv[0] + bv[1]) *(bv[2] + bv[3]);
    uniform_int_distribution<> dist1(0, result);
    bv[4] = dist1(rd);
    bv[5] = result - bv[4];
    return bv;
}
#endif