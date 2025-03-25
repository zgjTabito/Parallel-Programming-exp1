#include <iostream>
#include <vector>
#include <windows.h>  // 使用 QueryPerformanceCounter

using namespace std;

const vector<int> N_VALUES = { 2, 4 }; // 手动展开的 N

// 平凡求和
void sumN_com(int* a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
}

// 多路链式展开 N = 2
void sumN_opt2(int* a, int n) {
    int sum0 = 0, sum1 = 0;
    int i = 0;
    for (; i + 1 < n; i += 2) {
        sum0 += a[i];
        sum1 += a[i + 1];
    }
    if (i < n) sum0 += a[i];
    volatile int dummy = sum0 + sum1;
}

// 多路链式展开 N = 4
void sumN_opt4(int* a, int n) {
    int sum0 = 0, sum1 = 0, sum2 = 0, sum3 = 0;
    int i = 0;
    for (; i + 3 < n; i += 4) {
        sum0 += a[i];
        sum1 += a[i + 1];
        sum2 += a[i + 2];
        sum3 += a[i + 3];
    }
    for (; i < n; ++i) {
        sum0 += a[i];
    }
    volatile int dummy = sum0 + sum1 + sum2 + sum3;
}

// 递归求和
int sumN_recursion(int* a, int n) {
    for (int m = n; m > 1; m /= 2) {
        for (int i = 0; i < m / 2; i++) {
            a[i] = a[i * 2] + a[i * 2 + 1];
        }
    }
    return a[0];
}

// 通用计时器
template <typename Func>
double benchmark(Func func, int* a, int n, int iterations, int repeats) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    double total_time_ms = 0.0;

    for (int i = 0; i < repeats; i++) {
        LARGE_INTEGER start, end;
        QueryPerformanceCounter(&start);
        for (int j = 0; j < iterations; j++) {
            func(a, n);
        }
        QueryPerformanceCounter(&end);
        double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        total_time_ms += elapsed;
    }

    return total_time_ms / repeats;
}

int main() {
    cout << "n, sumN_com (ms), sumN_recursion (ms), ";
    for (int N : N_VALUES) {
        cout << "sumN_opt" << N << " (ms), ";
    }
    cout << endl;

    int repeats = 5;

    for (int k = 1; k <= 20; k++) {
        int n = 1 << k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = i % 100;
        }

        int* arr = a.data();

        // 平凡求和
        double time_com = benchmark(sumN_com, arr, n, 10000, repeats);

        // 递归求和
        vector<int> a_copy = a;
        double time_rec = benchmark(sumN_recursion, a_copy.data(), n, 10000, repeats);

        cout << n << ", " << time_com << ", " << time_rec << ", ";

        // 多路链式求和（具体展开）
        for (int N : N_VALUES) {
            double time_opt = 0.0;
            if (N == 2) {
                time_opt = benchmark(sumN_opt2, arr, n, 10000, repeats);
            } else if (N == 4) {
                time_opt = benchmark(sumN_opt4, arr, n, 10000, repeats);
            }
            cout << time_opt << ", ";
        }

        cout << endl;
    }

    return 0;
}
