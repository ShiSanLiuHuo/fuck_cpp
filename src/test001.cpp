#include <iostream>
#include <algorithm>
#include <iterator>

double my_abs(double x){
    return x >= 0 ? x : -x;
}

template<class InputIterator,class OutputIterator>
void Mytransform_abs(InputIterator first,InputIterator last,OutputIterator result){
    for(;first != last;first++,result++){
        *result = (*first >=0)? *first:-*first;
    }
}

int main() {
    Mytransform_abs(
        std::istream_iterator<double>(std::cin),
        std::istream_iterator<double>(),
        std::ostream_iterator<double>(std::cout, "\n")
    );

    return 0;
}