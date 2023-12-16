
#ifndef LINEAR_BEARVER_UNIFORM_H__
#define LINEAR_BEARVER_H__

#ifdef USE_EIGEN
#include <Eigen/Dense>
#endif

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

uint64_t prime_mod;
uint64_t moduloMask;
uint64_t moduloMidPt;

typedef std::vector<uint64_t> uint64_1D;
typedef std::vector<std::vector<uint64_t>> uint64_2D;

// 求除数的倒数，然后执行乘法计算。（涉及的都是明文除法和明文乘法）
uint64_t *rec_approx() {}

#endif