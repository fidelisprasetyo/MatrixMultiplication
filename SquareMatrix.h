#pragma once

#include <iomanip>
#include <stdlib.h>

#define RAND_RANGE 10

int getRandInt(int range) {
    return rand() % range;
}

class SquareMatrix {
public:
    SquareMatrix(int _size);
    void insertValues();
    void randomValues();
    void print() const;
    int getSize() const;
    std::vector<int>& operator [](int i);
private:
    int size;
    std::vector<std::vector<int>> m;
};

SquareMatrix::SquareMatrix(int _size) : size(_size) {
    m.resize(size);
    for(int i = 0; i < size; i++) {
        m[i].resize(size);
    }
}

void SquareMatrix::insertValues() {
    std::cout << "Enter " << size << " values per row (separated by spaces)\n";
    for(int row = 0; row < size; row++) {
            std::cout << "Row " << row << " values: ";
        for(int col = 0; col < size; col++) {
            std::cin >> m[row][col];
        }
    }
}

void SquareMatrix::randomValues() {
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            m[row][col] = getRandInt(RAND_RANGE);
        }
    }
}

void SquareMatrix::print() const {
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            std::cout << std::setw(3) << m[row][col] << ' ';
        }
        std::cout << '\n';
    }
}

int SquareMatrix::getSize() const {
    return size;
}

std::vector<int>& SquareMatrix::operator [](int i) {
    return m[i];
}