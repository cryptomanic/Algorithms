#include <iostream>
#include <vector>

using namespace std;

struct Node {
    // temporary minimum distance
    int dist;
    // node name
    int name;
    // parent
    int papa;
};

/*Condition : left and right subtree of a node at given index must be min heap
  Result : whole tree with root at given index will satisfy min heap property after applying Min Heapify
*/
void MinHeapify(int index,vector<Node> &A){

    //  whether heap is empty or not
    if(A.size() == 0) {
        cerr<<"Heap is empty"<<endl;
        return;
    }

    // minimum value and its index
    int minim = A[index].dist;
    int i = index;

    // compare minimum value with root of left subtree
    if(2*index + 1 < A.size() && A[2*index + 1].dist < minim){
        minim = A[2*index + 1].dist;
        i = 2*index + 1;
    }

    // compare minimum value with root of right subtree
    if(2*index + 2 < A.size() && A[2*index + 2].dist < minim){
        minim = A[2*index + 2].dist;
        i = 2*index + 2;
    }

    // compare index of minimum value node with the given index
    if(i != index){
        swap(A[i],A[index]);
        MinHeapify(i,A);
    }
}

// convert vector A to Min Heap
void buildMinHeap(vector<Node> &A){
    // elements with index greater than (A.size()/2) - 1 will be leaves
    for(int i = (A.size()/2) - 1;i >= 0 ;i--){
        MinHeapify(i,A);
    }
}

// Add element to the min heap
void addElement(Node value,vector<Node> &A){
    // add element at the end of vector A
    A.push_back(value);

    // index of last element
    int i = A.size() - 1;

    // for storing parent index
    int i_baap = 0;

    // check whether there is only one element in the heap
    while(i != 0){
        // parent of node whose index is i
        i_baap = (i-1)/2;

        // whether parent is greater than child
        if(A[i_baap].dist > A[i].dist)
            swap(A[i],A[i_baap]);
        else
            break;

        i = i_baap;
    }
}

// delete root node from the heap
Node PopElement(vector<Node> &A){

    // check whether heap is empty or not
    if(A.size() == 0) {
        cerr<<"Heap is Empty"<<endl;
        Node node;
        node.dist = node.name = -1;
        return node;
    }

    // index of last node
    int sz = A.size() - 1;

    // store the root node value to return later
    Node popE = A[0];

    // swap root and last element
    swap(A[0],A[sz]);

    // delete last element
    A.pop_back();

    // bring back heap property
    if(A.size() != 0)
        MinHeapify(0,A);

    return popE;
}

// whether node is visited or not
vector<bool> visited;
// parent of each node to know the actual path
vector<int> parent;
// minimum distance from starting node to all other nodes
vector<int> mdistance;

void dijkstra(int start, vector<pair<int,int> > g[]) {

    // priority queue
    vector<Node> pq;

    // initial element of priority queue
    Node node;
    node.dist = 0;
    node.name = start;
    node.papa = start;

    // put starting element to the queue
    addElement(node, pq);

    // Dijkstra Algorithm
    while(not (pq.size() == 0)) {
        // pop an element from the queue
        Node data = PopElement(pq);

        // check whether popped element is visited or not
        if(not visited[data.name]) {
            // mark popped element as visited
            visited[data.name] = true;
            // store the minimum distance for popped element
            mdistance[data.name] = data.dist;
            // parent of popped element
            parent[data.name] = data.papa;
            // for all neighbours of popped element
            for(int i = 0;i < g[data.name].size();i++) {
                // if neighbour is not visited
                if(not visited[(g[data.name][i]).first]) {
                    // put the neighbor in the queue
                    node.dist = data.dist + (g[data.name][i]).second;
                    node.name = (g[data.name][i]).first;
                    node.papa = data.name;
                    addElement(node, pq);
                }
            }
        }
    }
}

// show the shortest path from start node to end node
void showpath(int index) {
    if(parent[index] == index){
        cout<<index<<" ";
        return;
    }

    showpath(parent[index]);
    cout<<index<<" ";
}

int main()
{
    /*
       n : number of nodes in the graph
       m : number of edges in the graph
       s : start node
       e : end node
       w : edge weight
    */
    int n, m, s, e, w;
    cout << "Number of Nodes and Edges : ";
    cin >> n >> m;

    // data structure to store graph
    vector<pair<int,int> > g[n+1];

    // memory allocation
    visited = vector<bool>(n+1, false);
    parent = vector<int>(n+1);
    mdistance = vector<int>(n+1);

    // store data in the adjacency list
    for(int i = 0;i < m;i++) {
        cin >> s >> e >> w;
        g[s].push_back(make_pair(e,w));
        g[e].push_back(make_pair(s,w));
    }

    cout << "Enter the start node: ";
    cin >> s;

    dijkstra(s, g);

    for(int i = 1;i <= n;i++) {
        cout << "------------------------------------------\n";
        cout << "Minimum distance from " << s << " to " << i << " = " << mdistance[i] << endl;
        cout << "Actual path from " << s << " to " << i << " : ";
        showpath(i);
        cout << "\n------------------------------------------\n\n";
    }

    return 0;
}
