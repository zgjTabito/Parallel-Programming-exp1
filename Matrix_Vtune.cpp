#include <iostream>

using namespace std;

void Matrix_com(int** m, int* vec, int* sum, int n) {
    for (int i = 0; i < n; i++) {
        sum[i] = 0;
        for (int j = 0; j < n; j++) {
            sum[i] += m[j][i] * vec[j]; // 行访问
        }
    }
    return;
}
void Matrix_opt(int** m, int* vec, int* sum, int n) {
    for (int i = 0; i < n; i++) {
        sum[i] = 0;
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            sum[i] += m[j][i] * vec[j];
        }
    }
    return;
}




int main() {
    const int N = 1000;         // 矩阵规模
    const int REPEATS = 1000;   // 执行次数

    // 动态申请二维数组 matrix[N][N]
    int** matrix = new int* [N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    int* vector = new int[N];
    int* result = new int[N];

    // 初始化矩阵 m[i][j] = i + j
    for (int i = 0; i < N; ++i) {
        vector[i] = i;  // 简单初始化向量
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = i + j;
        }
    }

    // 执行 1000 次算法
    for (int t = 0; t < REPEATS; ++t) {
        //Matrix_com(matrix, vector, result, N);
        Matrix_opt(matrix, vector, result, N);
    }

    // 输出一个结果，防止被优化
    cout << "result[0] = " << result[0] << endl;

    // 释放内存
    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] vector;
    delete[] result;

    return 0;
}
