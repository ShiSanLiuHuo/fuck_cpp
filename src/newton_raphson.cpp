#include <iostream>
using namespace std;
double f(double x);
double f1(double x);
int main() {
  double a;
  cin >> a;
  cout << f(a) << endl;
  cout << f1(a) << endl;
  cout << a-f(a)/f1(a) <<endl;
  return 0;
}
double f(double x){
  return 12*x*x*x-12*x*x-24*x;
}

double f1(double x){
  return 36*x*x-24*x-24;
}
