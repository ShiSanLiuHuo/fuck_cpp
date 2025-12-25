#ifndef STUDENT_LIST_HPP
#define STUDENT_LIST_HPP

#include <iostream>
#include "student.hpp"

class StudentList {
public:
    StudentList();
    ~StudentList();

    // 基本操作
    bool isEmpty() const { return head == nullptr; }
    int getCount() const { return count; }
    
    // 学生管理功能
    bool isExist(const int id) const;
    void appendStudent(const Student& s);
    void insertStudent(const Student& s, int position);
    bool deleteStudent(const int id);
    Student* searchStudent(const int id) const;
    void searchStudentByName(const char* name) const;
    void displayAll() const;
    void sortByScore(bool ascending = true);
    void sortById(bool ascending = true);
    void clear();
    
    // 文件操作
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

private:
    Student* head;
    Student* tail;
    int count;
};

#endif // STUDENT_LIST_HPP