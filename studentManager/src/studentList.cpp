#include "studentList.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

StudentList::StudentList() : head(nullptr), tail(nullptr), count(0) {}

StudentList::~StudentList() {
    clear();
}

bool StudentList::isExist(const int id) const {
    Student* current = head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

void StudentList::appendStudent(const Student& s) {
    Student* newStudent = new Student(s.getId(), s.getName(), s.getGender(), 
                                      s.getAge(), s.getMajor(), s.getScore());
    
    if (isEmpty()) {
        head = tail = newStudent;
    } else {
        tail->setNext(newStudent);
        tail = newStudent;
    }
    count++;
}

void StudentList::insertStudent(const Student& s, int position) {
    if (position < 0 || position > count) {
        std::cout << "无效的位置!" << std::endl;
        return;
    }
    
    if (position == count) {
        appendStudent(s);
        return;
    }
    
    Student* newStudent = new Student(s.getId(), s.getName(), s.getGender(), 
                                      s.getAge(), s.getMajor(), s.getScore());
    
    if (position == 0) {
        newStudent->setNext(head);
        head = newStudent;
    } else {
        Student* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->getNext();
        }
        newStudent->setNext(current->getNext());
        current->setNext(newStudent);
    }
    count++;
}

bool StudentList::deleteStudent(const int id) {
    if (isEmpty()) {
        return false;
    }
    
    Student* current = head;
    Student* previous = nullptr;
    
    while (current != nullptr) {
        if (current->getId() == id) {
            if (previous == nullptr) {
                // 删除头节点
                head = current->getNext();
                if (head == nullptr) {
                    tail = nullptr;
                }
            } else {
                previous->setNext(current->getNext());
                if (current == tail) {
                    tail = previous;
                }
            }
            delete current;
            count--;
            return true;
        }
        previous = current;
        current = current->getNext();
    }
    return false;
}

Student* StudentList::searchStudent(const int id) const {
    Student* current = head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

void StudentList::searchStudentByName(const char* name) const {
    Student* current = head;
    bool found = false;
    
    while (current != nullptr) {
        if (strcmp(current->getName(), name) == 0) {
            current->display();
            found = true;
        }
        current = current->getNext();
    }
    
    if (!found) {
        std::cout << "未找到姓名为 " << name << " 的学生" << std::endl;
    }
}

void StudentList::displayAll() const {
    if (isEmpty()) {
        std::cout << "学生列表为空!" << std::endl;
        return;
    }
    
    Student* current = head;
    int index = 1;
    while (current != nullptr) {
        std::cout << "学生 " << index << ":" << std::endl;
        current->display();
        current = current->getNext();
        index++;
    }
}

void StudentList::sortByScore(bool ascending) {
    if (count <= 1) return;
    
    for (int i = 0; i < count - 1; i++) {
        Student* current = head;
        for (int j = 0; j < count - i - 1; j++) {
            Student* next = current->getNext();
            bool shouldSwap = ascending ? 
                (current->getScore() > next->getScore()) : 
                (current->getScore() < next->getScore());
            
            if (shouldSwap) {
                // 交换数据
                Student temp(*current);
                current->setId(next->getId());
                current->setName(next->getName());
                current->setGender(next->getGender());
                current->setAge(next->getAge());
                current->setMajor(next->getMajor());
                current->setScore(next->getScore());
                
                next->setId(temp.getId());
                next->setName(temp.getName());
                next->setGender(temp.getGender());
                next->setAge(temp.getAge());
                next->setMajor(temp.getMajor());
                next->setScore(temp.getScore());
            }
            current = current->getNext();
        }
    }
}

void StudentList::sortById(bool ascending) {
    if (count <= 1) return;
    
    for (int i = 0; i < count - 1; i++) {
        Student* current = head;
        for (int j = 0; j < count - i - 1; j++) {
            Student* next = current->getNext();
            bool shouldSwap = ascending ? 
                (current->getId() > next->getId()) : 
                (current->getId() < next->getId());
            
            if (shouldSwap) {
                // 交换数据
                Student temp(*current);
                current->setId(next->getId());
                current->setName(next->getName());
                current->setGender(next->getGender());
                current->setAge(next->getAge());
                current->setMajor(next->getMajor());
                current->setScore(next->getScore());
                
                next->setId(temp.getId());
                next->setName(temp.getName());
                next->setGender(temp.getGender());
                next->setAge(temp.getAge());
                next->setMajor(temp.getMajor());
                next->setScore(temp.getScore());
            }
            current = current->getNext();
        }
    }
}

void StudentList::clear() {
    Student* current = head;
    while (current != nullptr) {
        Student* next = current->getNext();
        delete current;
        current = next;
    }
    head = tail = nullptr;
    count = 0;
}

void StudentList::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法打开文件 " << filename << std::endl;
        return;
    }
    
    Student* current = head;
    while (current != nullptr) {
        file << current->getId() << ","
             << current->getName() << ","
             << current->getGender() << ","
             << current->getAge() << ","
             << current->getMajor() << ","
             << current->getScore() << std::endl;
        current = current->getNext();
    }
    
    file.close();
    std::cout << "数据已保存到 " << filename << std::endl;
}

void StudentList::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法打开文件 " << filename << std::endl;
        return;
    }
    
    clear();
    
    int id, age;
    double score;
    char name[30], gender[10], major[50];
    char comma;
    
    while (file >> id >> comma) {
        file.getline(name, 30, ',');
        file.getline(gender, 10, ',');
        file >> age >> comma;
        file.getline(major, 50, ',');
        file >> score;
        file.ignore();
        
        appendStudent(Student(id, name, gender, age, major, score));
    }
    
    file.close();
    std::cout << "数据已从 " << filename << " 加载" << std::endl;
}