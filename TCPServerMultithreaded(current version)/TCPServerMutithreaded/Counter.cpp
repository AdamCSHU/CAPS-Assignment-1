/*

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <map>

#define ITERATIONS 100
#define MAX_MATRIX_SIZE 1000

double PCFreq = 0.0;
LARGE_INTEGER li;
LARGE_INTEGER liStart;
LARGE_INTEGER liEnd;

void multiply(unsigned int, unsigned int,
    int**, int**, int**,
    unsigned int, unsigned int, unsigned int);

int main()
{
    std::vector<std::thread> threadVector;

    int** a, ** b, ** result;
    unsigned int i, j;
    unsigned int matrixSize;
    unsigned int nThreads;

    double elapsedTime, aggregateTime;
    std::map<unsigned int, double> timeMap;

    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";
    PCFreq = double(li.QuadPart) / 1000.0;
    aggregateTime = 0.0;

    srand(time(NULL));

    nThreads = std::thread::hardware_concurrency();
    std::cout << "Number of threads to be used: " << nThreads << std::endl;

    for (matrixSize = 1; matrixSize <= MAX_MATRIX_SIZE; matrixSize++)
    {
        aggregateTime = 0.0;

        a = new int* [matrixSize];
        for (i = 0; i < matrixSize; i++)
        {
            a[i] = new int[matrixSize];

            for (j = 0; j < matrixSize; j++)
            {
                a[i][j] = rand();
            }
        }

        b = new int* [matrixSize];
        for (i = 0; i < matrixSize; i++)
        {
            b[i] = new int[matrixSize];

            for (j = 0; j < matrixSize; j++)
            {
                b[i][j] = rand();
            }
        }

        result = new int* [matrixSize];
        for (i = 0; i < matrixSize; i++)
            result[i] = new int[matrixSize];

        for (int k = 0; k < ITERATIONS; k++)
        {
            for (i = 0; i < matrixSize; i++)
                for (j = 0; j < matrixSize; j++)
                    result[i][j] = 0;

            QueryPerformanceCounter(&liStart);

            for (i = 0; i < nThreads; i++)
            {
                threadVector.emplace_back(multiply, i, nThreads, a, b, result, matrixSize, matrixSize, matrixSize);
            }

            for (i = 0; i < nThreads; i++)
            {
                threadVector[i].join();
            }

            QueryPerformanceCounter(&liEnd);

            threadVector.clear();

            elapsedTime = double(liEnd.QuadPart - liStart.QuadPart) / PCFreq;
            aggregateTime += elapsedTime;
        }

        double averageTime = aggregateTime / ITERATIONS;
        std::cout << "Average time required for matrix " << matrixSize << " x " << matrixSize << " multiplication with " << nThreads << " threads: " << averageTime << " ms" << std::endl;

        timeMap.emplace(matrixSize, averageTime);

        //free all allocated memory

        for (i = 0; i < matrixSize; i++)
        {
            delete a[i];
        }
        delete a;

        for (i = 0; i < matrixSize; i++)
        {
            delete b[i];
        }
        delete b;

        for (i = 0; i < matrixSize; i++)
        {
            delete result[i];
        }
        delete result;
    }

    std::fstream timeFile("timeFile.csv", std::fstream::out);
    for (auto const& entry : timeMap)
        timeFile << entry.first << ", " << entry.second << std::endl;

    timeFile.close();

    timeMap.clear();

    return 0;
}

void multiply(unsigned int threadIndex, unsigned int nThreads,
    int** a, int** b, int** result, unsigned int row1,
    unsigned int col1, unsigned int col2)
{
    unsigned int startRow, rowCount, endRow;
    unsigned int residualRows;
    unsigned int r, c, in;
    unsigned int i;
    std::string str;

    rowCount = row1 / nThreads;
    residualRows = row1 % nThreads;

    startRow = 0;
    for (i = 0; i < threadIndex; i++)
    {
        startRow += rowCount;
        if (i < residualRows)
            startRow += 1;
    }

    if (threadIndex < residualRows)
        rowCount++;

    endRow = startRow + rowCount;

    /*
        str = "Thread id " + std::to_string(threadIndex) + ": start row: " + std::to_string(startRow) + "\n";
        str += "Thread id " + std::to_string(threadIndex) + ": end row: " + std::to_string(endRow) + "\n";
        str += "Thread id " + std::to_string(threadIndex) + ": row count: " + std::to_string(rowCount) + "\n";

        std::cout << str;
    

    for (r = startRow; r < endRow; r++)
        for (c = 0; c < col2; c++)
            for (in = 0; in < col1; in++)
                result[r][c] += a[r][in] * b[in][c];
}
*/
