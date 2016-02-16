#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// representation of node
/* x : x coordinate
   y : y coordinate
   next : pointer to the next node
   prev : pointer to previous node
*/
struct Node{
    int x;
    int y;
    Node* next = nullptr;
    Node* prev = nullptr;
};

// representation of circular doubly linked list
class CDoublyLL {
    public:
        // pointer to the first node
        Node* head;
        // pointer to the last node
        Node* tail;
        // number of elements in linked list
        int length;
        // initialization
        CDoublyLL() : head(nullptr), tail(nullptr), length(0) { }
        // function to add node after tail and before head
        void add_node(int,int);
        // display linked list
        void display() {
            Node* temp = head;
            cout<<"("<<head->x<<","<<head->y<<") ";
            temp = temp->next;
            while(temp != head) {
                cout<<"("<<temp->x<<","<<temp->y<<") ";
                temp = temp->next;
            }
            cout<<endl;
        }
        // return the first half of linked list
        CDoublyLL firstHalf();
        // return the second half of linked list
        CDoublyLL secondHalf();
        // calculate the left most point i.e point with least x coordinate
        Node* leftMost() {
            Node* temp = head->next;
            Node* ans = head;
            while(temp != head) {
                if(temp->x < ans->x) {
                    ans = temp;
                }
                temp = temp->next;
            }
            return ans;
        }
        // calculate the right most point i.e point with maximum x coordinate
        Node* rightMost() {
            Node* temp = head->next;
            Node* ans = head;
            while(temp != head) {
                if(temp->x > ans->x) {
                    ans = temp;
                }
                temp = temp->next;
            }
            return ans;
        }
};


void CDoublyLL::add_node(int xc, int yc) {
    Node* node = new Node;
    node->x = xc;
    node->y = yc;
    // one node is added to the circular doubly linked list
    length++;

    if(head == nullptr) {
        head = node;
        head->next = head;
        head->prev = head;
        tail = head;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
        tail->next = head;
        head->prev = tail;
    }
}

CDoublyLL CDoublyLL::firstHalf() {
    CDoublyLL ob;
    Node* root = head;
    for(int i = 0;i < length/2;i++){
        ob.add_node(root->x, root->y);
        root = root->next;
    }
    return ob;
}

CDoublyLL CDoublyLL::secondHalf(){
    CDoublyLL ob;
    Node* root = head;
    int i;

    for(i = 0;i < length/2;i++){
        root = root->next;
    }

    for( ;i < length;i++){
        ob.add_node(root->x, root->y);
        root = root->next;
    }
    return ob;
}

/*3 points will be 1. collinear if area of triangle is zero
                   2. clockwise if area of triangle without taking modulus is negative
                   3. anticlockwise if area of triangle without taking modulus is positive*/

/*counter clockwise return +1
  clockwise return -1
  linear return 0*/

int orientation(Node* p1, Node* p2, Node* p3) {

    int x1 = p1->x;
    int x2 = p2->x;
    int x3 = p3->x;
    int y1 = p1->y;
    int y2 = p2->y;
    int y3 = p3->y;

    int temp = (x1-x2)*(y2-y3)-(x2-x3)*(y1-y2);

    if(temp == 0)
        return 0;

    if(temp > 0)
        return 1;

    return -1;
}

CDoublyLL ConvexHull(CDoublyLL hull) {

    if(hull.length <= 2) {
        return hull;
    }

    // get the left half nodes of hull
    CDoublyLL lefthull = hull.firstHalf();
    // // get the right half nodes of hull
    CDoublyLL righthull = hull.secondHalf();
    // recursively find the convex hull of left half points
    lefthull = ConvexHull(lefthull);
    // recursively find the convex hull of right half points
    righthull = ConvexHull(righthull);

    // Merging Steps

    // left1 and right1 form the top edge
    // left2 and right2 form the bottom edge
    Node* left1;
    Node* left2;
    Node* right1;
    Node* right2;

    // initialize left1 and left2 to the rightmost point of lefthull
    left1 = left2 = lefthull.rightMost();
    // initialize right1 and right2 to the leftmost point of righthull
    right1 = right2 = righthull.leftMost();

    // find the top edge
    while(orientation(left1, right1, right1->next) > 0 or
          orientation(right1, left1, left1->prev) < 0) {

          while (orientation(left1, right1, right1->next) > 0) {
                right1 = right1->next;
          }

          while (orientation(right1, left1, left1->prev) < 0) {
                left1 = left1->prev;
          }
    }


    // finding bottom edge
    while(orientation(left2, right2, right2->prev) < 0 or
          orientation(right2, left2, left2->next) > 0) {

          while (orientation(left2, right2, right2->prev) < 0) {
                right2 = right2->prev;
          }

          while (orientation(right2, left2, left2->next) > 0) {
                left2 = left2->next;
          }
    }


    // deleting nodes between left1 and left2 while moving clockwise
    if(left1 != left2) {
        while(left1->next != left2) {
            left1->next = left1->next->next;
            left1->next->prev = left1;
        }
    }

    // deleting nodes between right2 and right1 while moving clockwise
    if(right1 != right2) {
        while(right2->next != right1) {
            right2->next = right2->next->next;
            right2->next->prev = right2;
        }
    }

    // for storing the answer
    CDoublyLL solution;

    // merging left and right hull
    left1->next = right1;
    right1->prev = left1;

    right2->next = left2;
    left2->prev = right2;

    // fill the solution with all points of convex hull in clockwise direction
    solution.add_node(left1->x, left1->y);
    while(right1 != left1) {
        solution.add_node(right1->x, right1->y);
        right1 = right1->next;
    }

    return solution;
}

int main()
{
    int N, x, y;

    // for storing inputs in text file
    ofstream outfile;
    outfile.open("allpoints.txt");
    outfile << "xcoor" << " " <<"ycoor" << endl;

    cout<<"Enter number of points in the plane (>=3): ";
    cin>>N;

    cout<<"Enter "<<N<<" points in the plane: \n";
    CDoublyLL ob;

    vector<pair<int,int> > A(N);
    for(int i = 0;i < N;i++){
        cout<<"Point "<<i+1<<" : ";
        cin>>x>>y;
        A[i] = make_pair(x, y);
        outfile << x << " " << y << endl;
    }

    sort(A.begin(), A.end());

    for(int i = 0;i < N;i++) {
        ob.add_node(A[i].first, A[i].second);
    }

    outfile.close();

    // store solution in ob
    ob = ConvexHull(ob);

    // storing outputs in text file
    ofstream outfile2;
    outfile2.open("selectedpoints.txt");
    outfile2 << "xcoor" << " " <<"ycoor" << endl;

    Node* temp = ob.head;
    outfile2 << ob.head->x <<" " << ob.head->y << endl;
    temp = temp->next;
    while(temp != ob.head) {
        outfile2 << temp->x <<" " << temp->y << endl;
        temp = temp->next;
    }
    outfile2.close();

    // display the convex hull
    ob.display();

    return 0;
}
