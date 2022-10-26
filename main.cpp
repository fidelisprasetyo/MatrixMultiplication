#include <iostream>
#include <vector>

class Matrix {
public:
    Matrix(int n) : size(n) {
        m.resize(size);
        for(int i = 0; i < size; i++) {
            m[i].resize(size);
        }
        InsertValues();
    }
    void InsertValues() {
        for(int row = 0; row < size; row++) {
            for(int col = 0; col < size; col++) {
                std::cout << "Insert [" << row << ']' << '[' << col << "] value: ";
                std::cin >> m[row][col];
            }
        }
    }
    void PrintMatrix() {
        for(int row = 0; row < size; row++) {
            for(int col = 0; col < size; col++) {
                std::cout << m[row][col] << ' ';
            }
            std::cout << '\n';
        }
    }
private:
    int size;
    std::vector<std::vector<int>> m;
};

int main() {
    Matrix M1(4);
    M1.PrintMatrix();
    return 0;
}