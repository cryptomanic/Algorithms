#include <iostream>
#include <vector>

using namespace std;

class Matrix{
    vector<vector<int> > A;
    int dim;

    public:
        Matrix(int n) : A(n, vector<int>(n)) {
            dim = n;
        }
        int dimension() { return dim; }

        void GetInput();
        Matrix operator+(Matrix &);
        Matrix operator-(Matrix &);
        Matrix operator*(Matrix &);
        Matrix firstPart();
        Matrix secondPart();
        Matrix thirdPart();
        Matrix fourthPart();
        Matrix Merge(Matrix&, Matrix&, Matrix&);
        friend ostream& operator<<(ostream&, Matrix&);
};

void Matrix::GetInput() {
    cout << "Enter " << dim << "X" << dim << " matrix: \n";
    for(int i = 0;i < dim;i++) {
        for(int j = 0;j < dim;j++) {
            cin>>A[i][j];
        }
    }
}

Matrix Matrix::operator+(Matrix& B) {
    Matrix ans(dim);
    for(int i = 0;i < dim;i++) {
        for(int j = 0;j < dim;j++) {
            ans.A[i][j] = A[i][j] + B.A[i][j];
        }
    }
    return ans;
}

Matrix Matrix::operator-(Matrix& B) {
    Matrix ans(dim);
    for(int i = 0;i < dim;i++) {
        for(int j = 0;j < dim;j++) {
            ans.A[i][j] = A[i][j] - B.A[i][j];
        }
    }
    return ans;
}

Matrix Matrix::operator*(Matrix& B) {
    Matrix ans(dim);
    for(int i = 0;i < dim;i++) {

        for(int j = 0;j < dim;j++){
            int sum = 0;
            for(int k = 0;k < dim;k++) {
                sum += A[i][k]*B.A[k][j];
            }
            ans.A[i][j] = sum;
        }
    }
    return ans;
}

Matrix Matrix::firstPart() {
    Matrix ans(dim/2);
    for(int i = 0;i < dim/2;i++){
        for(int j = 0;j < dim/2;j++){
            ans.A[i][j] = A[i][j];
        }
    }
    return ans;
}

Matrix Matrix::secondPart() {
    Matrix ans(dim/2);
    for(int i = 0;i < dim/2;i++){
        for(int j = 0;j < dim/2;j++){
            ans.A[i][j] = A[i][j + dim/2];
        }
    }
    return ans;
}

Matrix Matrix::thirdPart() {
    Matrix ans(dim/2);
    for(int i = 0;i < dim/2;i++){
        for(int j = 0;j < dim/2;j++){
            ans.A[i][j] = A[i + dim/2][j];
        }
    }
    return ans;
}

Matrix Matrix::fourthPart() {
    Matrix ans(dim/2);
    for(int i = 0;i < dim/2;i++){
        for(int j = 0;j < dim/2;j++){
            ans.A[i][j] = A[i + dim/2][j + dim/2];
        }
    }
    return ans;
}

Matrix Matrix::Merge(Matrix& B, Matrix& C, Matrix& D){
    Matrix ans(2*dim);

    for(int i = 0;i < dim;i++){
        for(int j = 0;j < dim;j++){
            ans.A[i][j] = A[i][j];
        }
    }

    for(int i = 0;i < dim;i++){
        for(int j = dim;j < 2*dim;j++){
            ans.A[i][j] = B.A[i][j-dim];
        }
    }

    for(int i = dim;i < 2*dim;i++){
        for(int j = 0;j < dim;j++){
            ans.A[i][j] = C.A[i-dim][j];
        }
    }

    for(int i = dim;i < 2*dim;i++){
        for(int j = dim;j < 2*dim;j++){
            ans.A[i][j] = D.A[i-dim][j-dim];
        }
    }
    return ans;
}

ostream& operator<<(ostream& out, Matrix& mat) {
    for(int i = 0;i < mat.dimension();i++){
        for(int j = 0;j < mat.dimension();j++){
            out<<mat.A[i][j]<<" ";
        }
        out<<endl;
    }
}
Matrix Strassen(Matrix A, Matrix B) {

    if(A.dimension() == 1)
        return A*B;

    Matrix a = A.firstPart();
    Matrix b = A.secondPart();
    Matrix c = A.thirdPart();
    Matrix d = A.fourthPart();

    Matrix e = B.firstPart();
    Matrix f = B.secondPart();
    Matrix g = B.thirdPart();
    Matrix h = B.fourthPart();

    Matrix P1 = Strassen(a, f-h);
    Matrix P2 = Strassen(a+b, h);
    Matrix P3 = Strassen(c+d, e);
    Matrix P4 = Strassen(d, g-e);
    Matrix P5 = Strassen(a+d, e+h);
    Matrix P6 = Strassen(b-d, g+h);
    Matrix P7 = Strassen(a-c, e+f);

    Matrix C11 = P5+P4-P2+P6;
    Matrix C12 = P1+P2;
    Matrix C21 = P3+P4;
    Matrix C22 = P1+P5-P3-P7;

    return C11.Merge(C12, C21, C22);
}

int main()
{
    int N = 0;
    cout<<"Dimension of matrix: ";
    cin>>N;

    Matrix A(N), B(N);

    cout<<"Matrix A:\n";
    A.GetInput();

    cout<<"Matrix B:\n";
    B.GetInput();

    Matrix C = Strassen(A, B);

    cout<<"Product of A and B :\n";
    cout<<C;

    /*Matrix C = A.firstPart();
    Matrix D = A.secondPart();
    Matrix E = A.thirdPart();
    Matrix F = A.fourthPart();

    cout<<C;
    cout<<D;
    cout<<E;
    cout<<F;*/
    cout<<endl<<endl;
    Matrix verify = A*B;
    cout<<verify;

    return 0;
}
