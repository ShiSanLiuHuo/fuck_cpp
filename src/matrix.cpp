#include <iostream>

class Matrix{
public:
    Matrix() = default;
    Matrix(int arr[2][3]){
        for(int i=0;i<2;i++){
            for(int j=0;j<3;j++){
                data[i][j] = arr[i][j];
            }
        }
    }

    Matrix operator+(const Matrix& other){
        Matrix result;
        for(int i = 0;i<2;i++){
            for (int j = 0;j < 3;j++){
                result.data[i][j] = this->data[i][j]+other.data[i][j];
            }
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os,const Matrix& M);
    friend std::istream& operator>>(std::istream&is,Matrix& M);
    
private:
    int data[2][3];
};

std::ostream& operator<<(std::ostream& os,const Matrix& M){
        for(int i = 0; i < 2;i++){
            for(int j=0; j < 3;j++){
                os<<M.data[i][j]<<" ";
            }
            os<<std::endl;
        }
        return os;
    }

    std::istream& operator>>(std::istream& is,Matrix& M){
        std::cout << "请输入2行3列的矩阵"<< std::endl;
        for(int i = 0; i < 2;i++){
            for(int j = 0; j< 3; j++){
                is>>M.data[i][j];
            }
        }
        return is;
    }

int main(){
    Matrix A;
    Matrix B;
    std::cin >> A >> B;
    Matrix C=A+B;
    std::cout << C;
    return 0;
}