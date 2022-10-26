#pragma once

class SquareMatrix {
public:
    SquareMatrix(int _size) : size(_size) {
        m.resize(size);
        for(int i = 0; i < size; i++) {
            m[i].resize(size);
        }
    }
    void insertValues() {
        std::cout << "Enter " << size << " values per row (separated by spaces)\n";
        for(int row = 0; row < size; row++) {
                std::cout << "Row " << row << " values: ";
            for(int col = 0; col < size; col++) {
                std::cin >> m[row][col];
            }
        }
    }
    void printMatrix() const {
        for(int row = 0; row < size; row++) {
            for(int col = 0; col < size; col++) {
                std::cout << m[row][col] << ' ';
            }
            std::cout << '\n';
        }
    }
    int getSize() const {
        return size;
    }
private:
    int size;
    std::vector<std::vector<int>> m;
};