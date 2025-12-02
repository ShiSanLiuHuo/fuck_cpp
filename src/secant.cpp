#include<iostream>

double f(double x){
  return 12*x*x*x-12*x*x-24*x;
}

int main(){
    int n;
    double x0,x1;
    std::cin >> n;
    std::cin >> x0 >> x1;
    double a[n+1];
    a[0] = x0;
    a[1] = x1;
    for(int i = 0; i < n;i++){
        a[i+2] = a[i+1] - (a[i+1]-a[i])/( f(a[i+1]) - f(a[i]) )*f(a[i+1]);
        std::cout << a[i+2] << std::endl;
    }
    return 0;
}