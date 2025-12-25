#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <limits>
#include "student.hpp"
#include "studentList.hpp"

// 设置控制台编码为UTF-8
void setConsoleEncoding() {
    system("chcp 65001 > nul");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

// 清空输入缓冲区
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );
}

// 等待用户按键
void waitForEnter() {
    std::cout << "按回车键继续...";
    clearInputBuffer();
}

void displayMenu() {
    std::cout << "\n========== 学生管理系统 ==========" << std::endl;
    std::cout << "1. 添加学生" << std::endl;
    std::cout << "2. 显示所有学生" << std::endl;
    std::cout << "3. 按学号查找学生" << std::endl;
    std::cout << "4. 按姓名查找学生" << std::endl;
    std::cout << "5. 删除学生" << std::endl;
    std::cout << "6. 按成绩排序" << std::endl;
    std::cout << "7. 按学号排序" << std::endl;
    std::cout << "8. 保存到文件" << std::endl;
    std::cout << "9. 从文件加载" << std::endl;
    std::cout << "0. 退出系统" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "请选择操作: ";
}

int main() {
    // 设置控制台编码
    setConsoleEncoding();

    StudentList studentList;
    int choice;

    do {
        system("cls"); // 在显示菜单前清屏，避免闪烁
        displayMenu();

        if (!(std::cin >> choice)) {
            // 输入无效时清空缓冲区并跳过本次循环
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); // 清空输入缓冲区

        switch (choice) {
            case 1: {
                Student newStudent;
                newStudent.inputStudent();
                if (studentList.isExist(newStudent.getId())) {
                    std::cout << "学号已存在，添加失败!" << std::endl;
                } else {
                    studentList.appendStudent(newStudent);
                    std::cout << "学生添加成功!" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 2: {
                studentList.displayAll();
                waitForEnter();
                break;
            }
            case 3: {
                int id;
                std::cout << "请输入要查找的学号: ";
                if (!(std::cin >> id)) {
                    clearInputBuffer();
                    std::cout << "输入无效!" << std::endl;
                } else {
                    clearInputBuffer();
                    Student* found = studentList.searchStudent(id);
                    if (found != nullptr) {
                        std::cout << "找到学生:" << std::endl;
                        found->display();
                    } else {
                        std::cout << "未找到学号为 " << id
                                  << " 的学生" << std::endl;
                    }
                }
                waitForEnter();
                break;
            }
            case 4: {
                char name[30];
                std::cout << "请输入要查找的姓名: ";
                std::cin.getline(name, 30);
                studentList.searchStudentByName(name);
                waitForEnter();
                break;
            }
            case 5: {
                int id;
                std::cout << "请输入要删除的学号: ";
                if (!(std::cin >> id)) {
                    clearInputBuffer();
                    std::cout << "输入无效!" << std::endl;
                } else {
                    clearInputBuffer();
                    if (studentList.deleteStudent(id)) {
                        std::cout << "学生删除成功!" << std::endl;
                    } else {
                        std::cout << "未找到学号为 " << id
                                  << " 的学生" << std::endl;
                    }
                }
                waitForEnter();
                break;
            }
            case 6: {
                int order;
                std::cout << "排序方式: 1.升序 2.降序: ";
                if (!(std::cin >> order)
                    || (order != 1 && order != 2)) {
                    clearInputBuffer();
                    std::cout << "输入无效!" << std::endl;
                } else {
                    clearInputBuffer();
                    studentList.sortByScore(order == 1);
                    std::cout << "按成绩排序完成!" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 7: {
                int order;
                std::cout << "排序方式: 1.升序 2.降序: ";
                if (!(std::cin >> order)
                    || (order != 1 && order != 2)) {
                    clearInputBuffer();
                    std::cout << "输入无效!" << std::endl;
                } else {
                    clearInputBuffer();
                    studentList.sortById(order == 1);
                    std::cout << "按学号排序完成!" << std::endl;
                }
                waitForEnter();
                break;
            }
            case 8: {
                char filename[100];
                std::cout << "请输入文件名: ";
                std::cin.getline(filename, 100);
                studentList.saveToFile(filename);
                waitForEnter();
                break;
            }
            case 9: {
                char filename[100];
                std::cout << "请输入文件名: ";
                std::cin.getline(filename, 100);
                studentList.loadFromFile(filename);
                waitForEnter();
                break;
            }
            case 0: {
                std::cout << "感谢使用学生管理系统!" << std::endl;
                break;
            }
            default: {
                std::cout << "无效的选择，请重新输入!" << std::endl;
                waitForEnter();
                break;
            }
        }

    } while (choice != 0);

    return 0;
}