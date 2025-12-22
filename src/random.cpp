#include<iostream>
#include<random>

int main(){
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> number_int(1,10);
    for(int i = 0; i < 10; i++){
        int random_number = number_int(gen); 
        std::cout << random_number << std::endl; 
    }
    return 0;
} 