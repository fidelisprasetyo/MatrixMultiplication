#pragma once

#include <math.h>   // ceil & floor
#include "SquareMatrix.h"

bool isPowerOfTwo(int n) {
    if (n == 0) {
        return false;
    }
    return (ceil(log2(n)) == floor(log2(n)));
}

bool isMatrixValid(const SquareMatrix& A, const SquareMatrix& B) {
    if(A.size() != B.size() || !isPowerOfTwo(A.size()) || !isPowerOfTwo(B.size())) {
        return false;
    }
    return true;
}

SquareMatrix classicMultiplication(SquareMatrix& A, SquareMatrix& B) {
    int n = A.size();
    SquareMatrix Prod(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            Prod[i][j] = 0;
            for(int k = 0; k < n; k++) {
                Prod[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return Prod;
}    

SquareMatrix divideAndConquerMul(SquareMatrix& A, SquareMatrix& B) {
    SquareMatrix Prod(A.size());

    // base case: when the quadrant only contains 1 element
    if(A.size() == 1) {
        Prod[0][0] = A[0][0] * B[0][0];
    }
    // recursive case: divide into quadrants
    else {
        int quadrant_size = A.size() / 2;

        // initiate the quadrants
        SquareMatrix Prod_00(quadrant_size);
        SquareMatrix Prod_01(quadrant_size);
        SquareMatrix Prod_10(quadrant_size);
        SquareMatrix Prod_11(quadrant_size);
        SquareMatrix A_00(quadrant_size);
        SquareMatrix A_01(quadrant_size);
        SquareMatrix A_10(quadrant_size);
        SquareMatrix A_11(quadrant_size);
        SquareMatrix B_00(quadrant_size);
        SquareMatrix B_01(quadrant_size);
        SquareMatrix B_10(quadrant_size);
        SquareMatrix B_11(quadrant_size);

        // fill the quadrants
        for(int i = 0; i < quadrant_size; i++) {
            for(int j = 0; j < quadrant_size; j++) {
                A_00[i][j] = A[i][j];
                A_01[i][j] = A[i][j + quadrant_size];
                A_10[i][j] = A[i + quadrant_size][j];
                A_11[i][j] = A[i + quadrant_size][j + quadrant_size];

                B_00[i][j] = B[i][j];
                B_01[i][j] = B[i][j + quadrant_size];
                B_10[i][j] = B[i + quadrant_size][j];
                B_11[i][j] = B[i + quadrant_size][j + quadrant_size];
            }
        }

        // multiply the quadrants
        Prod_00 = divideAndConquerMul(A_00, B_00) + divideAndConquerMul(A_01, B_10);    // Prod_00 = (A_00 * B_00) + (A_01 * B_10)
        Prod_01 = divideAndConquerMul(A_00, B_01) + divideAndConquerMul(A_01, B_11);    // Prod_01 = (A_00 * B_01) + (A_01 * B_11)
        Prod_10 = divideAndConquerMul(A_10, B_00) + divideAndConquerMul(A_11, B_10);    // Prod_10 = (A_10 * B_00) + (A_11 * B_10)
        Prod_11 = divideAndConquerMul(A_10, B_01) + divideAndConquerMul(A_11, B_11);    // Prod_11 = (A_10 * B_01) + (A_11 * B_11)

        // combine into 1 matrix
        for(int i = 0; i < quadrant_size; i++) {
            for(int j = 0; j < quadrant_size; j++) {
                Prod[i][j] = Prod_00[i][j];
                Prod[i][j + quadrant_size] = Prod_01[i][j];
                Prod[i + quadrant_size][j] = Prod_10[i][j];
                Prod[i + quadrant_size][j + quadrant_size] = Prod_11[i][j];
            }
        }
    }

    return Prod;
}