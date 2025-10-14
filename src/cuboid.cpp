#include <iostream>

class cuboid {
public:
  void set();
  void show();
  void cal_V();

private:
  int length;
  int width;
  int height;
  int V;
};

int main() {
  for (int i = 0; i < 3; i++) {
    cuboid c;
    c.set();
    c.cal_V();
    c.show();
  }
  return 0;
}

void cuboid::set() {
  std::cout << "请输入长方体的长、宽、高：" << std::endl;
  std::cin >> length >> width >> height;
}

void cuboid::cal_V() { V = length * width * height; }

void cuboid::show() { std::cout << "长方体的体积为：" << V << std::endl; }