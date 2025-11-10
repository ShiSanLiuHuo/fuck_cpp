#include<iostream>
#include<cmath>

namespace plane_geometry
{
    class point{
    public:
        point() :x_(0.0), y_(0.0){count_++;}
        point(double x, double y):x_(x), y_(y){count_++;}
        ~point() {count_--;}
        double get_x() const{return x_;}
        double get_y() const{return y_;}
        bool operator==(const point& other) const{
            return x_ == other.x_ && y_ == other.y_;
        }
        bool operator!=(const point& other) const{
            return !(*this == other);
        }
        static int get_count() {return count_;}
        void move(double dx, double dy){
            x_ += dx;
            y_ += dy;
        }
    private:
        double x_;
        double y_;
        static int count_;
    };
    class line{
    public:
        line(){count_++;}
        line(const point& p1, const point& p2) :p1_(p1), p2_(p2){count_++;}
        ~line(){count_--;}
        point get_p1() const{return p1_;}
        point get_p2() const{return p2_;}
        bool operator==(const line& other) const{
            return p1_ == other.p1_ && p2_ == other.p2_;
        }
        bool operator!=(const line& other) const{
            return !(*this == other);
        }
        static int get_count() {return count_;}

        double get_length() const{
            return std::sqrt(std::pow(p2_.get_x() - p1_.get_x(), 2) + std::pow(p2_.get_y() - p1_.get_y(), 2));
        }


        void move(double dx, double dy){
            p1_.move(dx, dy);
            p2_.move(dx, dy);
        }
        void rotate(double angle){
            double dx = p2_.get_x() - p1_.get_x();
            double dy = p2_.get_y() - p1_.get_y();
            p2_.move(dx * std::cos(angle) - dy * std::sin(angle), dx * std::sin(angle) + dy * std::cos(angle));
        }
        void scale(double factor){
            double dx = p2_.get_x() - p1_.get_x();
            double dy = p2_.get_y() - p1_.get_y();
            p2_.move(dx * factor, dy * factor);
        }
        void mirror(const point& p){
            p1_.move(2 * (p.get_x() - p1_.get_x()), 2 * (p.get_y() - p1_.get_y()));
            p2_.move(2 * (p.get_x() - p2_.get_x()), 2 * (p.get_y() - p2_.get_y()));
        }
        void mirror(const line& l) {
            auto A = l.get_p1();
            double ax = A.get_x(), ay = A.get_y();
            double dx = l.get_p2().get_x() - ax;
            double dy = l.get_p2().get_y() - ay;

            // 法向量
            double nx = -dy, ny = dx;
            double n2 = nx*nx + ny*ny;

            auto reflect = [&](point &P) {
                double px = P.get_x(), py = P.get_y();
                double t = ((ax - px) * nx + (ay - py) * ny) * 2 / n2;
                P.move(t * nx, t * ny);
            };

            reflect(p1_);
            reflect(p2_);
        }

    private:
        point p1_;
        point p2_;
        static int count_;
    };
    class circle{
    public:
        circle(){}
        circle(const point& center, double radius) :center_(center), radius_(radius){count_++;}
        ~circle(){count_--;}
        point get_center() const{return center_;}
        double get_radius() const{return radius_;}
        bool operator==(const circle& other) const{
            return center_ == other.center_ && radius_ == other.radius_;
        }
        bool operator!=(const circle& other) const{
            return !(*this == other);
        }
        static int get_count() {return count_;}

        double get_area() const{
            return M_PI * radius_ * radius_;
        }
        double get_circumference() const{
            return 2 * M_PI * radius_;
        }

        void move(double dx, double dy){
            center_.move(dx, dy);
        }
        void scale(double factor){
            radius_ *= factor;
        }

    private:
        point center_;
        double radius_;
        static int count_;
    };

    // TODO:
    class rectangle{
    public:
        rectangle(){count_++;}
        rectangle(const point& p1, const point& p2) :p1_(p1), p2_(p2){count_++;}
        ~rectangle(){count_--;}
        point get_p1() const{return p1_;}
        point get_p2() const{return p2_;}
        bool operator==(const rectangle& other) const{
            return p1_ == other.p1_ && p2_ == other.p2_;
        }
        bool operator!=(const rectangle& other) const{
            return !(*this == other);
        }
        static int get_count() {return count_;}

        double get_area() const{
            return (p2_.get_x() - p1_.get_x()) * (p2_.get_y() - p1_.get_y());
        }
        double get_perimeter() const{
            return 2 * (p2_.get_x() - p1_.get_x() + p2_.get_y() - p1_.get_y());
        }

        void move(double dx, double dy){
            p1_.move(dx, dy);
            p2_.move(dx, dy);
        }
        void scale(double factor){
            double dx = p2_.get_x() - p1_.get_x();
            double dy = p2_.get_y() - p1_.get_y();
            p2_.move(dx * factor, dy * factor);
        }
        void rotate(double angle){
            double dx = p2_.get_x() - p1_.get_x();
            double dy = p2_.get_y() - p1_.get_y();
            p2_.move(dx * std::cos(angle) - dy * std::sin(angle), dx * std::sin(angle) + dy * std::cos(angle));
        }
        void mirror(const point& p){
            p1_.move(2 * (p.get_x() - p1_.get_x()), 2 * (p.get_y() - p1_.get_y()));
            p2_.move(2 * (p.get_x() - p2_.get_x()), 2 * (p.get_y() - p2_.get_y()));
        }
    private:
        point p1_;
        point p2_;

        static int count_;
    };

    class triangle{
    public:
        triangle(){}
        triangle(const point& p1, const point& p2, const point& p3) :p1_(p1), p2_(p2), p3_(p3){count_++;}
        ~triangle(){count_--;}
        point get_p1() const{return p1_;}
        point get_p2() const{return p2_;}
        point get_p3() const{return p3_;}
        bool operator==(const triangle& other) const{
            return p1_ == other.p1_ && p2_ == other.p2_ && p3_ == other.p3_;
        }
        bool operator!=(const triangle& other) const{
            return !(*this == other);
        }
        static int get_count() {return count_;}

        double get_area() const{
            return 0.5 * std::abs((p2_.get_x() - p1_.get_x()) * (p3_.get_y() - p1_.get_y()) - (p3_.get_x() - p1_.get_x()) * (p2_.get_y() - p1_.get_y()));
        }
        double get_perimeter() const{
            return line(p1_, p2_).get_length() + line(p2_, p3_).get_length() + line(p3_, p1_).get_length();
        }


        void move(double dx, double dy){
            p1_.move(dx, dy);
            p2_.move(dx, dy);
            p3_.move(dx, dy);
        }
        void scale(double factor){
            double dx_2 = p2_.get_x() - p1_.get_x();
            double dy_2 = p2_.get_y() - p1_.get_y();
            p2_.move(dx_2 * factor, dy_2 * factor);
            double dx_3 = p3_.get_x() - p1_.get_x();
            double dy_3 = p3_.get_y() - p1_.get_y();
            p3_.move(dx_3 * factor, dy_3 * factor);
        }
        void rotate(double angle){
            double dx_2 = p2_.get_x() - p1_.get_x();
            double dy_2 = p2_.get_y() - p1_.get_y();
            p2_.move(dx_2 * std::cos(angle) - dy_2 * std::sin(angle), dx_2 * std::sin(angle) + dy_2 * std::cos(angle));
            double dx_3 = p3_.get_x() - p1_.get_x();
            double dy_3 = p3_.get_y() - p1_.get_y();
            p3_.move(dx_3 * std::cos(angle) - dy_3 * std::sin(angle), dx_3 * std::sin(angle) + dy_3 * std::cos(angle));
        }
        void mirror(const point& p){
            double dx_2 = p2_.get_x() - p1_.get_x();
            double dy_2 = p2_.get_y() - p1_.get_y();
            p2_.move(2 * (p.get_x() - p2_.get_x()), 2 * (p.get_y() - p2_.get_y()));
            double dx_3 = p3_.get_x() - p1_.get_x();
            double dy_3 = p3_.get_y() - p1_.get_y();
            p3_.move(2 * (p.get_x() - p3_.get_x()), 2 * (p.get_y() - p3_.get_y()));
        }
    private:
        point p1_;
        point p2_;
        point p3_;
        static int count_;
    };

    int point::count_ = 0;
    int line::count_ = 0;
    int circle::count_ = 0;
    int rectangle::count_ = 0;
    int triangle::count_ = 0;

    std::ostream& operator<<(std::ostream& os, const point& p){
        os << "(" << p.get_x() << ", " << p.get_y() << ")";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const line& l){
        os << "Line[" << l.get_p1() << ", " << l.get_p2() << "]";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const circle& c){
        os << "Circle[" << c.get_center() << ", " << c.get_radius() << "]";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const rectangle& r){
        os << "Rectangle[" << r.get_p1() << ", " << r.get_p2() << "]";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const triangle& t){
        os << "Triangle[" << t.get_p1() << ", " << t.get_p2() << ", " << t.get_p3() << "]";
        return os;
    }
}//  namespace plane_geometry

using namespace plane_geometry;

int main(){
    point p1(0, 0);
    point p2(1, 0);
    point p3(0, 1);
    point p4(1, 1);
    std::cout << "point count: " << p1.get_count() << std::endl;
    std::cout << "========" << std::endl;
    line l(p1, p2);
    std::cout << "line length: " << l.get_length() << std::endl;
    std::cout << "line count: " << l.get_count() << std::endl;
    std::cout << "========" << std::endl;
    circle c(p1, 1);
    std::cout << "circle area: " << c.get_area() << std::endl;
    std::cout << "circle circumference: " << c.get_circumference() << std::endl;
    std::cout << "circle count: " << c.get_count() << std::endl;
    std::cout << "========" << std::endl;
    rectangle r(p1, p4);
    std::cout << "rectangle area: " << r.get_area() << std::endl;
    std::cout << "rectangle perimeter: " << r.get_perimeter() << std::endl;
    std::cout << "rectangle count: " << r.get_count() << std::endl;
    std::cout << "========" << std::endl;
    triangle t(p1, p2, p3);
    std::cout << "triangle area: " << t.get_area() << std::endl;
    std::cout << "triangle perimeter: " << t.get_perimeter() << std::endl;
    std::cout << "triangle count: " << t.get_count() << std::endl;
    std::cout << "========" << std::endl;

    std::cout << "========" << std::endl;
    std::cout << " line change:" << std::endl;
    std::cout << "========" << std::endl;
    line l1(p1, p2);
    l1.move(1, 1);
    std::cout << l1 << std::endl;
    std::cout << "line length after move: " << l1.get_length() << std::endl;
    std::cout << "line count after move: " << l1.get_count() << std::endl;
    std::cout << "========" << std::endl;
    line l2(p1,p2);
    l2.scale(2);
    std::cout << l2 << std::endl;
    std::cout << "line length after scale: " << l2.get_length() << std::endl;
    std::cout << "line count after scale: " << l2.get_count() << std::endl;
    std::cout << "========" << std::endl;
    line l3(p1,p2);
    l3.mirror(p1);
    std::cout << l3 << std::endl;
    std::cout << "line length after mirror: " << l3.get_length() << std::endl;
    std::cout << "line count after mirror: " << l3.get_count() << std::endl;
    std::cout << "========" << std::endl;
    line l4(p1,p2);
    line l5(p1,p3);
    l4.mirror(l5);
    std::cout << l4 << std::endl;
    std::cout << "line length after mirror: " << l4.get_length() << std::endl;
    std::cout << "line count after mirror: " << l4.get_count() << std::endl;
    std::cout << "========" << std::endl;

    std::cout << "========" << std::endl;
    std::cout << " circle change:" << std::endl;
    std::cout << "========" << std::endl;
    circle c1(p1, 1);
    c1.move(1, 1);
    std::cout << c1 << std::endl;
    std::cout << "circle area after move: " << c1.get_area() << std::endl;
    std::cout << "circle circumference after move: " << c1.get_circumference() << std::endl;
    std::cout << "circle count after move: " << c1.get_count() << std::endl;
    std::cout << "========" << std::endl;
    circle c2(p1, 1);
    c2.scale(2);
    std::cout << c2 << std::endl;
    std::cout << "circle area after scale: " << c2.get_area() << std::endl;
    std::cout << "circle circumference after scale: " << c2.get_circumference() << std::endl;
    std::cout << "circle count after scale: " << c2.get_count() << std::endl;
    std::cout << "========" << std::endl;

    std::cout << "========" << std::endl;
    std::cout << " rectangle change:" << std::endl;
    std::cout << "========" << std::endl;
    rectangle r1(p1, p4);
    r1.move(1, 1);
    std::cout << r1 << std::endl;
    std::cout << "rectangle area after move: " << r1.get_area() << std::endl;
    std::cout << "rectangle perimeter after move: " << r1.get_perimeter() << std::endl;
    std::cout << "rectangle count after move: " << r1.get_count() << std::endl;
    std::cout << "========" << std::endl;
    rectangle r2(p1, p4);
    r2.scale(2);
    std::cout << r2 << std::endl;
    std::cout << "rectangle area after scale: " << r2.get_area() << std::endl;
    std::cout << "rectangle perimeter after scale: " << r2.get_perimeter() << std::endl;
    std::cout << "rectangle count after scale: " << r2.get_count() << std::endl;
    std::cout << "========" << std::endl;
    rectangle r3(p1, p4);
    r3.mirror(p1);
    std::cout << r3 << std::endl;
    std::cout << "rectangle area after mirror: " << r3.get_area() << std::endl;
    std::cout << "rectangle perimeter after mirror: " << r3.get_perimeter() << std::endl;
    std::cout << "rectangle count after mirror: " << r3.get_count() << std::endl;
    std::cout << "========" << std::endl;
    rectangle r4(p1, p4);
    r4.rotate(M_PI / 2);
    std::cout << r4 << std::endl;
    std::cout << "rectangle area after rotate: " << r4.get_area() << std::endl;
    std::cout << "rectangle perimeter after rotate: " << r4.get_perimeter() << std::endl;
    std::cout << "rectangle count after rotate: " << r4.get_count() << std::endl;
    std::cout << "========" << std::endl;

    std::cout << "========" << std::endl;
    std::cout << " triangle change:" << std::endl;
    std::cout << "========" << std::endl;
    triangle t1(p1, p2, p3);
    t1.move(1, 1);
    std::cout << t1 << std::endl;
    std::cout << "triangle area after move: " << t1.get_area() << std::endl;
    std::cout << "triangle perimeter after move: " << t1.get_perimeter() << std::endl;
    std::cout << "triangle count after move: " << t1.get_count() << std::endl;
    std::cout << "========" << std::endl;
    triangle t2(p1, p2, p3);
    t2.scale(2);
    std::cout << t2 << std::endl;
    std::cout << "triangle area after scale: " << t2.get_area() << std::endl;
    std::cout << "triangle perimeter after scale: " << t2.get_perimeter() << std::endl;
    std::cout << "triangle count after scale: " << t2.get_count() << std::endl;
    std::cout << "========" << std::endl;
    triangle t3(p1, p2, p3);
    t3.mirror(p1);
    std::cout << t3 << std::endl;
    std::cout << "triangle area after mirror: " << t3.get_area() << std::endl;
    std::cout << "triangle perimeter after mirror: " << t3.get_perimeter() << std::endl;
    std::cout << "triangle count after mirror: " << t3.get_count() << std::endl;
    std::cout << "========" << std::endl;
    triangle t4(p1, p2, p3);
    t4.rotate(M_PI / 2);
    std::cout << t4 << std::endl;
    std::cout << "triangle area after rotate: " << t4.get_area() << std::endl;
    std::cout << "triangle perimeter after rotate: " << t4.get_perimeter() << std::endl;
    std::cout << "triangle count after rotate: " << t4.get_count() << std::endl;
    std::cout << "========" << std::endl;
}
