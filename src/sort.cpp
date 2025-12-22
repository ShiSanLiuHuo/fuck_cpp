#include <iostream>
#include <string>

// 堆化
template<typename T>
void heapify(T* A, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && A[l] > A[largest])
        largest = l;
    if (r < n && A[r] > A[largest])
        largest = r;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

template<typename T>
void sort(T* A, int n) {
    // 堆排列
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}

template<typename T>
void print(T* A, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 整型测试
    int a[10] = { 1, 4, 77, 6, 5, 54, 3, 222, 99, 33 };
    sort<int>(a, 10);
    print(a,10);

    // 字符串测试
    std::string b[10] = {
        "a",      "csdn", "github", "git",  "bing",
        "google", "mac",  "iphone", "ipad", "Apple"
    };
    sort<std::string>(b, 10);
    print(b,10);
}