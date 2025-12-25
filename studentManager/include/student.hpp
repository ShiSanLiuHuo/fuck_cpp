#ifndef STUDENT_HPP
#define STUDENT_HPP 

#include <iostream>
#include <cstring>

class Student {
public:
    Student();
    Student(
        const int id,
        const char* name,
        const char* gender,
        const int age,
        const char* major,
        const double score
    );
    ~Student();

    // 获取私有成员
    int getId() const {return id_;};
    const char* getName() const {return name_;};
    const char* getGender() const {return gender_;};
    int getAge() const {return age_;};
    const char* getMajor() const {return major_;};
    double getScore() const {return score_;};
    Student* getNext() const {return next_student_;};

    // 修改
    void setId(const int id);
    void setName(const char* name);
    void setGender(const char* gender);
    void setAge(const int age);
    void setMajor(const char* major);
    void setScore(const double score);
    void setNext(Student* next) {next_student_ = next;};

    // 显示
    void display() const;

    // 输入
    void inputStudent();

    // 重载流运算符
    friend std::ostream& operator<<(std::ostream& os, const Student& s);

private:
    int id_;                // 学号
    char name_[30];         // 姓名
    char gender_[10];       // 性别
    int age_;               // 年龄
    char major_[50];        // 专业
    double score_;          // 成绩
    Student* next_student_; // 链表指针
};

#endif //STUDENT_HPP