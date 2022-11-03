// Author: Fidelis Prasetyo (fprasetyo@cpp.edu)
// Desc: for Project 1, CS3310 Fall, Cal Poly Pomona 
// github: https://github.com/fidelisprasetyo
// github repo: https://github.com/fidelisprasetyo/MatrixMultiplication

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "algo.h"
#include "SquareMatrix.h"

#define MAX_EXP 4 //7?
#define TEST_COUNT 10
#define PRINT_STATUS false

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // SANITY CHECK
    SquareMatrix A(4);
    SquareMatrix B(4);
    SquareMatrix C(4);
    A.autoFill('a');    // fill with sanity check matrix
    B.autoFill('b');    // fill with sanity check matrix
    std::cout << "--SANITY CHECK--\n";
    if(isMatrixValid(A, B)) {
        std::cout << "Classic Multiplication Result:\n";
        C = classicMultiplication(A,B);
        C.print();
        C.clear();
        std::cout << "Divide and Conquer Result:\n";
        C = divideAndConquerMul(A,B);
        C.print();
        C.clear();
        std::cout << "Strassen Algorithm Result:\n";
        C = strassenAlgorithm(A,B);
        C.print();
        C.clear();
    }

    // RUNTIMES OBSERVATION
    std::cout << "\n--RUNTIMES OBSERVATION--\n";
    std::ofstream data;
    data.open("data.csv");

    auto total_runtime_classic = 0;
    auto total_runtime_div = 0;
    auto total_runtime_strassen = 0;

    int count = 0;      // number of tests performed
    int exp = 0;
    
    data << "Size, Classic, Divide and Conquer, Strassen\n";

    while(exp < MAX_EXP) {
        int size = 2 << exp;    // 2^exp
        SquareMatrix A(size);
        SquareMatrix B(size);
        SquareMatrix C(size);
        for(int t = 0; t < TEST_COUNT; t++) {
            A.autoFill();
            B.autoFill();
            if(isMatrixValid(A,B)) {
                count++;

                if(PRINT_STATUS) std::cout << "Status: Running Classic Multiplication [size = " << size << ", test #" << count << " ] .... ";
                auto start = std::chrono::high_resolution_clock::now();
                C = classicMultiplication(A,B);
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start).count();
                if(PRINT_STATUS) std::cout << "Done. [ Runtime = " << duration << " ms ]\n";

                total_runtime_classic += duration;
                C.clear();

                if(PRINT_STATUS) std::cout << "Status: Running Divide and Conquer Multiplication [size = " << size << ", test #" << count << " ] .... ";
                auto start1 = std::chrono::high_resolution_clock::now();
                C = divideAndConquerMul(A,B);
                auto stop1 = std::chrono::high_resolution_clock::now();
                auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1-start1).count();
                if(PRINT_STATUS) std::cout << "Done. [ Runtime = " << duration1 << " ms ]\n";

                total_runtime_div += duration1;
                C.clear();

                if(PRINT_STATUS) std::cout << "Status: Running Strassen Multiplication [size = " << size << ", test #" << count << " ] .... ";
                auto start2 = std::chrono::high_resolution_clock::now();
                C = strassenAlgorithm(A,B);
                auto stop2 = std::chrono::high_resolution_clock::now();
                auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2-start2).count();
                if(PRINT_STATUS) std::cout << "Done. [ Runtime = " << duration2 << " ms ]\n\n";

                total_runtime_strassen += duration2;

                data << size << ',' << duration << ',' << duration1 << ',' << duration2 << '\n';
                C.clear();

            }
        }
        exp++;
    }

    data.close();

    std::cout << "SUMMARY:\n";
    std::cout << "Max size = " << (2 << (MAX_EXP-1)) << " , Number of tests: " << count;
    std::cout << "\n  > Classic Multiplication Average Runtime: " << total_runtime_classic/ count << " ms";
    std::cout << "\n  > Divide and Conquer Multiplication Average Runtime: " << total_runtime_div/ count << " ms";
    std::cout << "\n  > Strassen Multiplication Average Runtime: " << total_runtime_strassen/ count << " ms";
    
    return 0;
}