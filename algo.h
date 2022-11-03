// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 1, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/MatrixMultiplication

#pragma once

#include <math.h>   // ceil & floor
#include "SquareMatrix.h"

#define LEAF_SIZE 50

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
    SquareMatrix C(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            C[i][j] = 0;
            for(int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}    

SquareMatrix divideAndConquerMul(SquareMatrix& A, SquareMatrix& B) {
    SquareMatrix C(A.size());

    // base case: when the quadrant only contains 1 element
    if(A.size() == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }
    // recursive case: divide into quadrants
    else {
        int quadrant_size = A.size() / 2;

        // initiate the quadrants
        SquareMatrix A_00(quadrant_size); SquareMatrix B_00(quadrant_size); SquareMatrix C_00(quadrant_size);
        SquareMatrix A_01(quadrant_size); SquareMatrix B_01(quadrant_size); SquareMatrix C_01(quadrant_size);
        SquareMatrix A_10(quadrant_size); SquareMatrix B_10(quadrant_size); SquareMatrix C_10(quadrant_size);
        SquareMatrix A_11(quadrant_size); SquareMatrix B_11(quadrant_size); SquareMatrix C_11(quadrant_size);

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
        C_00 = divideAndConquerMul(A_00, B_00) + divideAndConquerMul(A_01, B_10);    // C_00 = (A_00 * B_00) + (A_01 * B_10)
        C_01 = divideAndConquerMul(A_00, B_01) + divideAndConquerMul(A_01, B_11);    // C_01 = (A_00 * B_01) + (A_01 * B_11)
        C_10 = divideAndConquerMul(A_10, B_00) + divideAndConquerMul(A_11, B_10);    // C_10 = (A_10 * B_00) + (A_11 * B_10)
        C_11 = divideAndConquerMul(A_10, B_01) + divideAndConquerMul(A_11, B_11);    // C_11 = (A_10 * B_01) + (A_11 * B_11)

        // combine into 1 matrix
        for(int i = 0; i < quadrant_size; i++) {
            for(int j = 0; j < quadrant_size; j++) {
                C[i][j] = C_00[i][j];
                C[i][j + quadrant_size] = C_01[i][j];
                C[i + quadrant_size][j] = C_10[i][j];
                C[i + quadrant_size][j + quadrant_size] = C_11[i][j];
            }
        }
    }
    return C;
}

SquareMatrix strassenAlgorithm(SquareMatrix& A, SquareMatrix& B) {
    SquareMatrix C(A.size());

    // base case: when the quadrant only contains 1 element
    if(A.size() == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }
    // recursive case: divide into quadrants
    else {
        int quadrant_size = A.size() / 2;

        // initiate the quadrants
        SquareMatrix A_00(quadrant_size); SquareMatrix B_00(quadrant_size); SquareMatrix C_00(quadrant_size);
        SquareMatrix A_01(quadrant_size); SquareMatrix B_01(quadrant_size); SquareMatrix C_01(quadrant_size);
        SquareMatrix A_10(quadrant_size); SquareMatrix B_10(quadrant_size); SquareMatrix C_10(quadrant_size);
        SquareMatrix A_11(quadrant_size); SquareMatrix B_11(quadrant_size); SquareMatrix C_11(quadrant_size);

        SquareMatrix P0(quadrant_size);
        SquareMatrix P1(quadrant_size);
        SquareMatrix P2(quadrant_size);
        SquareMatrix P3(quadrant_size);
        SquareMatrix P4(quadrant_size);
        SquareMatrix P5(quadrant_size);
        SquareMatrix P6(quadrant_size);

        SquareMatrix temp0(quadrant_size);
        SquareMatrix temp1(quadrant_size);
        SquareMatrix temp2(quadrant_size);
        SquareMatrix temp3(quadrant_size);
        SquareMatrix temp4(quadrant_size);
        SquareMatrix temp5(quadrant_size);
        SquareMatrix temp6(quadrant_size);
        SquareMatrix temp7(quadrant_size);
        SquareMatrix temp8(quadrant_size);
        SquareMatrix temp9(quadrant_size);

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

        temp0 = B_01 - B_11;
        temp1 = A_00 + A_01;
        temp2 = A_10 + A_11;
        temp3 = B_10 - B_00;
        temp4 = A_00 + A_11;
        temp5 = B_00 + B_11;
        temp6 = A_01 - A_11;
        temp7 = B_10 + B_11;
        temp8 = A_00 - A_10;
        temp9 = B_00 + B_01;

        // multiply the quadrants
        P0 = strassenAlgorithm(A_00, temp0);
        P1 = strassenAlgorithm(temp1, B_11);
        P2 = strassenAlgorithm(temp2, B_00);
        P3 = strassenAlgorithm(A_11, temp3);
        P4 = strassenAlgorithm(temp4, temp5);
        P5 = strassenAlgorithm(temp6, temp7);
        P6 = strassenAlgorithm(temp8, temp9);

        C_00 = P3 + P4 + P5 - P1;
        C_01 = P0 + P1;
        C_10 = P2 + P3;
        C_11 = P0 - P2 + P4 - P6;

        // combine into 1 matrix
        for(int i = 0; i < quadrant_size; i++) {
            for(int j = 0; j < quadrant_size; j++) {
                C[i][j] = C_00[i][j];
                C[i][j + quadrant_size] = C_01[i][j];
                C[i + quadrant_size][j] = C_10[i][j];
                C[i + quadrant_size][j + quadrant_size] = C_11[i][j];
            }
        }
    }
    return C;
}