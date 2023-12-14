#ifndef BEAVER_H
#define BEAVER_H
#include <cassert>
#include <cstdint>
#include <random>
#include <vector>
using namespace std;

vector<uint64_t> operator+(vector<uint64_t>& v, uint64_t& num) {
    auto result = vector<uint64_t>(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = v[i] + num;
    }
    return result;
}

vector<uint64_t> operator+(uint64_t& num, vector<uint64_t>& v) {
    return v + num;
}

vector<uint64_t> operator-(vector<uint64_t>& v, uint64_t& num) {
    auto result = vector<uint64_t>(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = v[i] - num;
    }
    return result;
}

vector<uint64_t> operator-(uint64_t& num, vector<uint64_t>& v) {
    auto result = vector<uint64_t>(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = num - v[i];
    }
    return result;
}

vector<uint64_t> operator*(vector<uint64_t>& v, uint64_t& num) {
    auto result = vector<uint64_t>(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = v[i] * num;
    }
    return result;
}

vector<uint64_t> operator*(uint64_t& num, vector<uint64_t>& v) {
    return v * num;
}

vector<uint64_t> operator/(vector<uint64_t>& v, uint64_t& num) {
    auto result = vector<uint64_t>(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = v[i] / num;
    }
    return result;
}

vector<uint64_t> operator/(uint64_t& num, vector<uint64_t>& v) {
    auto result = vector<uint64_t>(v.size());
    for (size_t i = 0; i < v.size(); i++) {
        result[i] = num / v[i];
    }
    return result;
}

uint64_t* beaver() {
    random_device rd;
    uniform_int_distribution<> dist(0, RAND_MAX / 2);
    uint64_t* bv = new uint64_t[6];  // a1, a2, b1, b2, c1, c2, (a1 + a2) * (b1 + b2) = (c1 + c2);
    size_t j;
    for (char i = 0; i < 5; i++) {
        bv[i] = dist(rd);
    }
    bv[5] = (bv[0] + bv[1]) *(bv[2] + bv[3]) - bv[4];
    return bv;
}
#endif