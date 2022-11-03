// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 1, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/MatrixMultiplication

#pragma once

#include <iomanip>
#include <stdlib.h>

#define RAND_RANGE 10

int getRandInt(int range) {
    return rand() % range;
}

class Matrix {
public:
    Matrix(size_t size) : n(size) {

    }
    void autoFill() {
        for(size_t row = 0; row < n; row++) {
            for(size_t col = 0; col < n; col++) {
                m[row][col] = getRandInt(RAND_RANGE);
            }
        }
    }
private:
    int n;
    std::vector<std::vector<int>> m;
}