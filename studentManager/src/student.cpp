#include "student.hpp"
#include <iostream>
#include <cstring>

// 默认构造函数
Student::Student() : id_(0), age_(0), score_(0.0), next_student_(nullptr) {
    strcpy(name_, "");
    strcpy(gender_, "");
    strcpy(major_, "");
}

// 带参数构造函数
Student::Student(
    const int id,
    const char* name,
    const char* gender,
    const int age,
    const char* major,
    const double score
) : id_(id), age_(age), score_(score), next_student_(nullptr) {
    strncpy(name_, name, 29);
    name_[29] = '\0';
    strncpy(gender_, gender, 9);
    gender_[9] = '\0';
    strncpy(major_, major, 49);
    major_[49] = '\0';
}

// 析构函数
Student::~Student() {
    // 链表节点由StudentList管理
}

void Student::setId(const int id) {
    id_ = id;
}

void Student::setName(const char* name) {
    strncpy(name_, name, 29);
    name_[29] = '\0';
}

void Student::setGender(const char* gender) {
    strncpy(gender_, gender, 9);
    gender_[9] = '\0';
}

void Student::setAge(const int age) {
    age_ = age;
}

void Student::setMajor(const char* major) {
    strncpy(major_, major, 49);
    major_[49] = '\0';
}

void Student::setScore(const double score) {
    score_ = score;
}

void Student::display() const {
    std::cout << "学号: " << id_ << std::endl;
    std::cout << "姓名: " << name_ << std::endl;
    std::cout << "性别: " << gender_ << std::endl;
    std::cout << "年龄: " << age_ << std::endl;
    std::cout << "专业: " << major_ << std::endl;
    std::cout << "成绩: " << score_ << std::endl;
    std::cout << "------------------------" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << "学号: " << s.id_ << std::endl;
    os << "姓名: " << s.name_ << std::endl;
    os << "性别: " << s.gender_ << std::endl;
    os << "年龄: " << s.age_ << std::endl;
    os << "专业: " << s.major_ << std::endl;
    os << "成绩: " << s.score_ << std::endl;
    return os;
}

void Student::inputStudent() {
    std::cout << "请输入学生信息：" << std::endl;
    
    std::cout << "学号: ";
    std::cin >> id_;
    std::cin.ignore();
    
    std::cout << "姓名: ";
    std::cin.getline(name_, 30);
    
    std::cout << "性别: ";
    std::cin.getline(gender_, 10);
    
    std::cout << "年龄: ";
    std::cin >> age_;
    std::cin.ignore();
    
    std::cout << "专业: ";
    std::cin.getline(major_, 50);
    
    std::cout << "成绩: ";
    std::cin >> score_;
    std::cin.ignore();
}