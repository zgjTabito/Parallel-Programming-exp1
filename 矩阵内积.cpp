#include <iostream>
#include <windows.h>

using namespace std;

// 防止编译器优化的 dummy 变量
volatile int dummy = 0;

// 原始版本：按行访问
int* Matrix_com(int** m, int* vec, int n) {
    int* sum = new int[n];
    for (int i = 0; i < n; i++) {
        sum[i] = 0;
        for (int j = 0; j < n; j++) {
            sum[i] += m[j][i] * vec[j]; // 行访问
        }
    }
    return sum;
}

int* Matrix_opt(int** m, int* vec, int n) {
    int* sum = new int[n];
    for (int i = 0; i < n; i++) {
        sum[i] = 0;
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            sum[i] += m[j][i] * vec[j];
        }
    }
    return sum;
}

// 性能测试函数
void benchmark(int n, int repeats, LARGE_INTEGER freq) {
    // 分配二维矩阵
    int** m = new int* [n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
    }

    // 初始化矩阵 m[i][j] = i + j
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = i + j;
        }
    }

    // 初始化向量 vec[i] = i
    int* vec = new int[n];
    for (int i = 0; i < n; i++) {
        vec[i] = i;
    }

    LARGE_INTEGER start, end;
    double time_com = 0.0, time_opt = 0.0;

    for (int i = 0; i < repeats; i++) {
        // 测试 Matrix_com
        QueryPerformanceCounter(&start);
        for (int k = 0; k < 1000; k++) {
            int* result = Matrix_com(m, vec, n);
            dummy += result[0]; // 防止编译器优化
            delete[] result;
        }
        QueryPerformanceCounter(&end);
        time_com += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;

        // 测试 Matrix_opt
        QueryPerformanceCounter(&start);
        for (int k = 0; k < 1000; k++) {
            int* result = Matrix_opt(m, vec, n);
            dummy += result[0]; // 防止编译器优化
            delete[] result;
        }
        QueryPerformanceCounter(&end);
        time_opt += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    }

    // 输出平均耗时
    time_com /= repeats;
    time_opt /= repeats;

    cout << "n = " << n << " | Matrix_com: " << time_com << " ms | Matrix_opt: " << time_opt << " ms" << endl;

    // 释放内存
    for (int i = 0; i < n; i++) {
        delete[] m[i];
    }
    delete[] m;
    delete[] vec;
}

int main() {
    cout << "Benchmarking Matrix_com vs. Matrix_opt using QueryPerformanceCounter..." << endl;

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq); // 获取计时频率

    int repeats = 5; // 重复次数
    for (int n = 100; n <= 1000; n += 100) {
        benchmark(n, repeats, freq);
    }

    return 0;
}
