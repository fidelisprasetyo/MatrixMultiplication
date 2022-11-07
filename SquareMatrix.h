// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 1, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/MatrixMultiplication

#pragma once

#include <iomanip>
#include <stdlib.h>

#define RAND_RANGE 100

int getRandInt(int range) {
    return rand() % range;
}

class SquareMatrix {
public:
    // member functions
    SquareMatrix(int _size);
    void autoFill();
    void autoFill(char key);
    void clear();
    void print() const;
    int size() const;
public:
    // operator overloads
    int& operator()(size_t row, size_t col) {
        return m[row][col];
    }
    int operator()(size_t row, size_t col) const {
        return m[row][col];
    }
    SquareMatrix& operator+=(const SquareMatrix& other) {
        for(int row = 0; row < n; row++) {
            for(int col = 0; col < n; col++) {
                m[row][col] += other(row, col);
            }
        }
        return *this;
    }
    SquareMatrix& operator-=(const SquareMatrix& other) {
        for(int row = 0; row < n; row++) {
            for(int col = 0; col < n; col++) {
                m[row][col] -= other(row, col);
            }
        }
        return *this;
    }
    friend SquareMatrix operator+(SquareMatrix lhs, const SquareMatrix& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend SquareMatrix operator-(SquareMatrix lhs, const SquareMatrix& rhs) {
        lhs -= rhs;
        return lhs;
    }
private:
    int n;
    std::vector<std::vector<int>> m;
};

// constructor which receives the size of the matrix
SquareMatrix::SquareMatrix(int _size) : n(_size) {
    m.resize(n);
    for(int i = 0; i < n; i++) {
        m[i].resize(n);
    }
}

// autofill with random int
void SquareMatrix::autoFill() {
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            m[row][col] = getRandInt(RAND_RANGE);
        }
    }
}

// for Sanity check purposes
void SquareMatrix::autoFill(char key) {
    if (key == 'a' && n == 4) {
        m = {{2,0,-1,6}, {3,7,8,0}, {-5,1,6,-2}, {8,0,1,7}};
    }
    else if (key == 'b' && n == 4) {
        m = {{0,1,6,3}, {-2,8,7,1}, {2,0,-1,0}, {9,1,6,-2}};
    }
    else {
        SquareMatrix::autoFill();
    }
}

// fill with zeroes
void SquareMatrix::clear() {
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            m[row][col] = 0;
        }
    }
}

// display the matrix
void SquareMatrix::print() const {
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            std::cout << std::setw(3) << m[row][col] << ' ';
        }
        std::cout << '\n';
    }
}

// return the size of the matrix
int SquareMatrix::size() const {
    return n;
}