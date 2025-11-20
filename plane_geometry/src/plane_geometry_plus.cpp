#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/***********************
 * 抽象基类 Shape
 ************************/
class Shape {
public:
    virtual double area() const = 0;       // 纯虚函数：面积
    virtual double perimeter() const = 0;  // 纯虚函数：周长
    virtual void draw() const = 0;         // 纯虚函数：绘制
    virtual ~Shape() {                     // 虚析构
        cout << "[Shape] 析构函数调用\n";
    }
};

/***********************
 * 虚基类 Polygon（多边形）
 * Square、EquilateralTriangle、RegularHexagon 都属于多边形
 ************************/
class Polygon : public virtual Shape {
protected:
    int sides; // 边数
public:
    Polygon(int s) : sides(s) {}
};

/***********************
 * 圆形 Circle
 ************************/
class Circle : public Shape {
private:
    double r;
public:
    Circle(double radius) : r(radius) {}

    double area() const override {
        return 3.1415926 * r * r;
    }

    double perimeter() const override {
        return 2 * 3.1415926 * r;
    }

    void draw() const override {
        cout << "绘制一个圆，半径 = " << r << endl;
    }

    ~Circle() {
        cout << "[Circle] 析构函数调用\n";
    }
};

/***********************
 * 正三角形 EquilateralTriangle
 ************************/
class EquilateralTriangle : public Polygon {
protected:
    double a;  // 边长
public:
    EquilateralTriangle(double side)
        : Polygon(3), a(side) {}

    double area() const override {
        return sqrt(3) / 4 * a * a;
    }

    double perimeter() const override {
        return 3 * a;
    }

    void draw() const override {
        cout << "绘制一个正三角形，边长 = " << a << endl;
    }

    ~EquilateralTriangle() {
        cout << "[EquilateralTriangle] 析构函数调用\n";
    }
};

/***********************
 * 平行四边形 Parallelogram（继承 Shape）
 ************************/
class Parallelogram : public Shape {
protected:
    double a, b, h;
public:
    Parallelogram(double A, double B, double H)
        : a(A), b(B), h(H) {}

    double area() const override {
        return a * h;
    }

    double perimeter() const override {
        return 2 * (a + b);
    }

    void draw() const override {
        cout << "绘制平行四边形，底边 = " << a << "，另一边 = " << b << endl;
    }

    // 提供公开接口，使其可被多态使用
    using Shape::area;
    using Shape::perimeter;
    using Shape::draw;

    ~Parallelogram() {
        cout << "[Parallelogram] 析构函数调用\n";
    }
};

/***********************
 * 正方形 Square（从 Polygon 公有继承）
 ************************/
class Square : public Polygon {
private:
    double a;
public:
    Square(double side)
        : Polygon(4), a(side) {}

    double area() const override {
        return a * a;
    }

    double perimeter() const override {
        return 4 * a;
    }

    void draw() const override {
        cout << "绘制一个正方形，边长 = " << a << endl;
    }

    ~Square() {
        cout << "[Square] 析构函数调用\n";
    }
};

/***********************
 * 正六边形 RegularHexagon
 ************************/
class RegularHexagon : public Polygon {
private:
    double a;
public:
    RegularHexagon(double side)
        : Polygon(6), a(side) {}

    double area() const override {
        return 3 * sqrt(3) / 2 * a * a;
    }

    double perimeter() const override {
        return 6 * a;
    }

    void draw() const override {
        cout << "绘制一个正六边形，边长 = " << a << endl;
    }

    ~RegularHexagon() {
        cout << "[RegularHexagon] 析构函数调用\n";
    }
};

/***********************
 * 主函数：体现多态
 ************************/
int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Circle(3.0));
    shapes.push_back(new EquilateralTriangle(4.0));
    shapes.push_back(new Parallelogram(5.0, 3.0, 4.0));
    shapes.push_back(new Square(2.0));
    shapes.push_back(new RegularHexagon(3.0));

    for (auto s : shapes) {
        s->draw();
        cout << "面积 = " << s->area() << endl;
        cout << "周长 = " << s->perimeter() << endl;
        cout << "---------------------------\n";
    }

    // 释放内存触发多态析构
    for (auto s : shapes) {
        delete s;
    }

    return 0;
}