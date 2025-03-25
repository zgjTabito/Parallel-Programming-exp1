#include <iostream>
#include <windows.h>

using namespace std;

// ��ֹ�������Ż��� dummy ����
volatile int dummy = 0;

// ԭʼ�汾�����з���
int* Matrix_com(int** m, int* vec, int n) {
    int* sum = new int[n];
    for (int i = 0; i < n; i++) {
        sum[i] = 0;
        for (int j = 0; j < n; j++) {
            sum[i] += m[j][i] * vec[j]; // �з���
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

// ���ܲ��Ժ���
void benchmark(int n, int repeats, LARGE_INTEGER freq) {
    // �����ά����
    int** m = new int* [n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
    }

    // ��ʼ������ m[i][j] = i + j
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = i + j;
        }
    }

    // ��ʼ������ vec[i] = i
    int* vec = new int[n];
    for (int i = 0; i < n; i++) {
        vec[i] = i;
    }

    LARGE_INTEGER start, end;
    double time_com = 0.0, time_opt = 0.0;

    for (int i = 0; i < repeats; i++) {
        // ���� Matrix_com
        QueryPerformanceCounter(&start);
        for (int k = 0; k < 1000; k++) {
            int* result = Matrix_com(m, vec, n);
            dummy += result[0]; // ��ֹ�������Ż�
            delete[] result;
        }
        QueryPerformanceCounter(&end);
        time_com += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;

        // ���� Matrix_opt
        QueryPerformanceCounter(&start);
        for (int k = 0; k < 1000; k++) {
            int* result = Matrix_opt(m, vec, n);
            dummy += result[0]; // ��ֹ�������Ż�
            delete[] result;
        }
        QueryPerformanceCounter(&end);
        time_opt += (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    }

    // ���ƽ����ʱ
    time_com /= repeats;
    time_opt /= repeats;

    cout << "n = " << n << " | Matrix_com: " << time_com << " ms | Matrix_opt: " << time_opt << " ms" << endl;

    // �ͷ��ڴ�
    for (int i = 0; i < n; i++) {
        delete[] m[i];
    }
    delete[] m;
    delete[] vec;
}

int main() {
    cout << "Benchmarking Matrix_com vs. Matrix_opt using QueryPerformanceCounter..." << endl;

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq); // ��ȡ��ʱƵ��

    int repeats = 5; // �ظ�����
    for (int n = 100; n <= 1000; n += 100) {
        benchmark(n, repeats, freq);
    }

    return 0;
}
