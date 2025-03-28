#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// 防止优化用的全局变量
volatile int dummy = 0;

// 平凡求和
int sumN_com(int* a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// 多路链式求和
int sumN_opt2_no_unroll(int* a, int n) {
    int sumi[2] = { 0 };
    int sum = 0;
    for (int i = 0; i < n; i += 2) {
        for (int j = 0; j < 2; j++) {
            if (i + j < n) {
                sumi[j] += a[i + j];
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        sum += sumi[i];
    }
    volatile int dummy = sum; // 防止优化
    return sum;
}

// 不展开的多路求和 N = 4
int sumN_opt4_no_unroll(int* a, int n) {
    int sumi[4] = { 0 };
    int sum = 0;
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < 4; j++) {
            if (i + j < n) {
                sumi[j] += a[i + j];
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        sum += sumi[i];
    }
    volatile int dummy = sum; // 防止优化
    return sum;
}

// 递归求和（会修改原数组）
int sumN_recursion(int* a, int n) {
    for (int m = n; m > 1; m /= 2) {
        for (int i = 0; i < m / 2; i++) {
            a[i] = a[i * 2] + a[i * 2 + 1];
        }
    }
    return a[0];
}

// 测试函数1：平凡求和，执行 count 次
void test_sumN_com(int* a, int n, int count) {
    for (int i = 0; i < count; i++) {
        dummy += sumN_com(a, n);
    }
}

// 测试函数2：多路链式求和，执行 count 次
void test_sumN_optN(int* a, int n, int N, int count) {
    for (int i = 0; i < count; i++) {
        dummy += sumN_opt2_no_unroll(a, n);
        //dummy += sumN_opt4_no_unroll(a, n);
    }
}
// 测试函数3：递归求和，执行 count 次（每次复制数组，避免修改原始数据）
void test_sumN_recursion(int* a, int n, int count) {
    for (int i = 0; i < count; i++) {
        vector<int> temp(a, a + n); // 复制数组，防止破坏原数据
        dummy += sumN_recursion(temp.data(), n);
    }
}

int main() {
    const int n = 1 << 18;          // 数据规模，例如 2^14
    const int count = 10000;        // 每个算法执行次数
    const int opt_N = 2;            // 多路链式 N

    // 初始化数组
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = i % 100;
    }

    //cout << "开始执行 sumN_com..." << endl;
    //test_sumN_com(a, n, count);

    //cout << "开始执行 sumN_optN..." << endl;
    test_sumN_optN(a, n, 2, count);

    //cout << "开始执行 sumN_recursion..." << endl;
    //test_sumN_recursion(a, n, count);

    delete[] a;
    //cout << "测试完成。dummy = " << dummy << endl;
    return 0;
}
