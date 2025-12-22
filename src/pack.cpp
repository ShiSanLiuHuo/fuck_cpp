#include <iostream>

void printArgs() {
    std::cout << "解包完成！" << std::endl;
}

template<typename T, typename... Args>
void printArgs(T first, Args... args) {
    std::cout << first << std::endl;
    printArgs(args...);
}

int main() {
    // 测试
    printArgs(1, 2, "three", '4');
    printArgs();
    printArgs('1');
}