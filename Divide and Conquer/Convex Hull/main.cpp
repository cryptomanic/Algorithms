#include <iostream>

using namespace std;

struct Node{
    int x;
    int y;
    Node* next = nullptr;
    Node* prev = nullptr;
};

class CDoublyLL {
    public:
        Node* head;
        Node* tail;
        int length;
        CDoublyLL() : head(nullptr), length(0) { }
        void add_node(int,int);
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
        CDoublyLL firstHalf();
        CDoublyLL secondHalf();

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

    if(hull.length <= 3) {
        return hull;
    }

    CDoublyLL lefthull = hull.firstHalf();
    CDoublyLL righthull = hull.secondHalf();

    lefthull = ConvexHull(lefthull);
    righthull = ConvexHull(righthull);

    // finding top edge
    Node* left1; Node* left2;
    Node* right1; Node* right2;

    left1 = left2 = lefthull.rightMost();
    right1 = right2 = righthull.leftMost();

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

    if(left1 != left2) {
        while(left1->next != left2) {
            left1->next = left1->next->next;
            left1->next->prev = left1;
        }
    }

    if(right1 != right2) {
        while(right2->next != right1) {
            right2->next = right2->next->next;
            right2->next->prev = right2;
        }
    }

    CDoublyLL solution;

    left1->next = right1;
    right1->prev = left1;

    left2->next = right2;
    right2->prev = left2;

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

    //ofstream outfile;
    //outfile.open("allpoints.txt");
    //outfile << "xcoor" << " " <<"ycoor" << endl;

    cout<<"Enter number of points in the plane (>=3): ";
    cin>>N;

    cout<<"Enter "<<N<<" points in the plane: \n";
    CDoublyLL ob;

    for(int i = 0;i < N;i++){
        cout<<"Point "<<i+1<<" : ";
        cin>>x>>y;
        ob.add_node(x, y);
        //outfile << x << " " << y << endl;
    }

    //outfile.close();
    ConvexHull(ob).display();

    return 0;
}
