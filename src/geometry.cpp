#include<iostream>

class Shape{
public:
    virtual void printArea() {};
    virtual ~Shape(){};
};

class Circle : public Shape{
public:
    Circle(double r) : r_(r) {};

    void printArea() override{
        std::cout << "圆的面积:" <<std::endl;
       std::cout << 3.14*r_*r_<<std::endl;
    }

private:
    double r_;
};

class Rectangle : public Shape{
public:
    Rectangle(double w,double h):w_(w),h_(h) {};

    void printArea() override{
        std::cout << "矩形的面积:" <<std::endl;
        std::cout <<w_*h_<<std::endl;
    }

private:
    double w_,h_;
};

class Triangle : public Shape{
public:
    Triangle(double b, double h):b_(b),h_(h) {};

    void printArea() override{
        std::cout << "三角形的面积:" << std::endl;
        std::cout << 0.5*b_*h_<< std::endl;
    }

private:
    double b_,h_;
};

int main(){
    Circle c(1);
    Rectangle r(2,3);
    Triangle t(1,2);
    c.printArea();
    r.printArea();
    t.printArea();
}
