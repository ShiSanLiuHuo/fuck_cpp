#include<iostream>

void test(short val){
    std::cout<< "这是short的重载"<<std::endl;
}

void test(unsigned char val){
    std::cout<< "这是unsigned short的重载"<<std::endl;
}

void test(int val){
    std::cout<< "这是int的重载"<<std::endl;
}

int main(){
    char a = 2;
    test(a);
    return 0;
}