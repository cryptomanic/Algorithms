#include <iostream>

using namespace std;

// class Point to represnt a point in 2D plane
class Point{
    private:
        // x and y coordinate of a point
        int x, y;

    public:
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }

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

bool common(int x1, int x2, int x3, int x4) {
    if(x3 > x2 or x4 < x1)
        return false;
    return true;
}

bool intersect(Point& fp, Point& sp, Point& tp, Point& fop) {
    int o1 = orientation(fp, sp, tp);
    int o2 = orientation(fp, sp, fop);
    int o3 = orientation(tp, fop, fp);
    int o4 = orientation(tp, fop, sp);

    if(o1 != o2 and o3 != o4)
        return true;

    bool xcommon = common(fp.getX(), sp.getX(), tp.getX(), fop.getX());
    bool ycommon = common(fp.getY(), sp.getY(), tp.getY(), fop.getY());

    if(xcommon and ycommon)
        return true;
    return false;
}

int main()
{
    int x1, y1, x2, y2;
    int x3, y3, x4, y4;
    cout<<"Coordinates of end points first line segment : ";
    cin>>x1>>y1>>x2>>y2;

    cout<<"Coordinates of end points first line segment : ";
    cin>>x3>>y3>>x4>>y4;

    Point fpoint(x1,y1);
    Point spoint(x2,y2);
    Point tpoint(x3,y3);
    Point fopoint(x4,y4);

    if(intersect(fpoint, spoint, tpoint, fopoint)) {
        cout<<"Line Segments intersect";
    } else {
        cout<<"Line segments do not intersect";
    }

    return 0;
}
