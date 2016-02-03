#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// class Point to represnt a point in 2D plane
class Point{
    private:
        // x and y coordinate of a point
        int x, y;

    public:
        Point(int x = 0, int y = 0) {
            this->x = x;
            this->y = y;
        }

        // modify x and y coordinate
        inline void setX(int x) {this->x = x;}
        inline void setY(int y) {this->y = y;}

        inline int getX() {return x;}
        inline int getY() {return y;}
};

/*3 points will be 1. collinear if area of triangle is zero
                   2. clockwise if area of triangle without taking modulus is negative
                   3. anticlockwise if area of triangle without taking modulus is positive*/

/*counter clockwise return +1
  clockwise return -1
  linear return 0*/

int orientation(Point& p1, Point& p2, Point& p3) {

    int x1 = p1.getX();
    int x2 = p2.getX();
    int x3 = p3.getX();
    int y1 = p1.getY();
    int y2 = p2.getY();
    int y3 = p3.getY();

    int temp = (x1-x2)*(y2-y3)-(x2-x3)*(y1-y2);

    if(temp == 0)
        return 0;

    if(temp > 0)
        return 1;

    return -1;
}

// naive method for finding convex hull
void JarvisMethod(vector<Point> & A) {

        ofstream outfile;
        outfile.open("selectedpoints.txt");
        outfile << "xcoor" << " " <<"ycoor" << endl;

        // number of points in the plane
        int N = A.size();
        // x coordinate of left most point
        int xmin = A[0].getX();
        // index of left most point
        int index = 0;

        // finding the left most point index
        for(int i = 1;i < N;i++) {
            if(A[i].getX() < xmin) {
                xmin = A[i].getX();
                index = i;
            }
        }

        // vector to store boundary points
        vector<Point> hull;
        // push leftmost point
        hull.push_back(A[index]);

        // index of left most point for future use
        int temp = index;

        // main work of jarvis approach
        do{
            for(int i = 0;i < N;i++) {
                int counter = 0;
                if(i != index) {
                    for(int j = 0;j < N;j++) {
                        if(j != i and j != index) {
                            if(orientation(A[index], A[i], A[j]) == -1)
                                break;
                            else counter++;
                        }
                    }
                }
                if(counter == N-2) {
                    index = i;
                    if(index != temp) {
                        hull.push_back(A[index]);
                    }
                    break;
                }
            }
        } while(index != temp);

        // display boundary points
        cout<<endl;
        for(int i = 0; i < hull.size();i++) {
            cout<<"("<<hull[i].getX()<<","<<hull[i].getY()<<") ";
            outfile << hull[i].getX() << " " << hull[i].getY() << endl;
        }
}

int main()
{
    int N, x, y;

    ofstream outfile;
    outfile.open("allpoints.txt");
    outfile << "xcoor" << " " <<"ycoor" << endl;

    cout<<"Enter number of points in the plane (>=3): ";
    cin>>N;

    vector<Point> A(N);
    cout<<"Enter "<<N<<" points in the plane: \n";

    for(int i = 0;i < N;i++){
        cout<<"Point "<<i+1<<" : ";
        cin>>x>>y;
        A[i].setX(x);
        A[i].setY(y);

        outfile << x << " " << y << endl;
    }

    outfile.close();
    JarvisMethod(A);

    return 0;
}
