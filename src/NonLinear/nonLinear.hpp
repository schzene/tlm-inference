#include "LinearBeaver/linear-beaver.hpp"

inline uint64_t max(uint64_t *vec; szie_t size) {
    uint64_t max_num =  vec[0];
    for (size_t i = 1; i < size; i++) {
        if (max_num < vec[i]) {
            max_num = vec[i];
        }
    }
    return vec[i];
}

class NonLinear {
public:
    int party;
    sci::IOPack *iopack;
    LinearBeaver *linear;
    std::random_device rd;
    std::uniform_int_distribution<> dist(0, 100);

    NonLinear(int party_, sci::IOPack *iopack_) : iopack(iopack_) {
        assert(party_ == sci::PUBLIC || party_ == sci::ALICE || party_ == sci::BOB);
        this->party = party_;
        this->linear = new LinearBeaver(party, iopack);
    }

    uint64_t *softmax(uint64_t *input, int size) {
        uint64_t random = dist(rd);
        uint64_t* temp = new uint64_t[size];
        for (size_t i = 0; i < size; i++) {
            temp[i] = input[i] + random;
        }
        uint64_t* remote;
        if (party == sci::ALICE) {
            
        }
    }

    uint64_t *inverse_square(uint64_t *input, size_t size, unsigned int iter = 14) {
        return nullptr
    }
}