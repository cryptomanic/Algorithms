#include <iostream>

using namespace std;

int productOf(int X, int Y, int n) {

    if(n == 1) {
        return X & Y;
    }

    int A = X >> (n/2);
    int B = (A << n/2) ^ X;

    int C = Y >> (n/2);
    int D = (C << n/2) ^ Y;

    int AC = productOf(A, C, n/2);
    int BD = productOf(B, D, n/2);
    int ABCD;

    if(A + B >> n/2 || C + D >> n/2){
        ABCD = productOf(A + B, C + D, n);
    }
    else{
        ABCD = productOf(A + B, C + D, n/2);
    }

    return (AC << n) + BD + ((ABCD - AC - BD) << n/2);
}

int main()
{
    while(1) {
        int A,B;
        cout<<"Enter first number: ";
        cin>>A;
        cout<<"Enter second number: ";
        cin>>B;
        cout<<"Product = "<<productOf(A, B, 32)<<endl<<endl;
    }
    return 0;
}
