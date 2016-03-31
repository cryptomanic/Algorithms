#include <iostream>
#include <vector>
#include <array>

using namespace std;

// data structure to store information of each node
struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* baap = nullptr;
    int score = 0;
    bool bit;
    char symbol;
};

/* Condition : left and right subtree of a node at given index must be min heap
  Result : whole tree with root at given index will satisfy min heap property after applying Min Heapify
*/
void MinHeapify(int index,vector<Node*> &A){

    //  whether heap is empty or not
    if(A.size() == 0) {
        cerr<<"Heap is empty"<<endl;
        return;
    }

    // minimum value and its index
    int minim = A[index]->score;
    int i = index;

    // compare minimum value with root of left subtree
    if(2*index + 1 < A.size() && A[2*index + 1]->score < minim){
        minim = A[2*index + 1]->score;
        i = 2*index + 1;
    }

    // compare minimum value with root of right subtree
    if(2*index + 2 < A.size() && A[2*index + 2]->score < minim){
        minim = A[2*index + 2]->score;
        i = 2*index + 2;
    }

    // compare index of minimum value node with the given index
    if(i != index){
        swap(A[i],A[index]);
        MinHeapify(i,A);
    }
}

// convert vector A to Min Heap
void buildMinHeap(vector<Node*> &A){
    // elements with index greater than (A.size()/2) - 1 will be leaves
    for(int i = (A.size()/2) - 1;i >= 0 ;i--){
        MinHeapify(i,A);
    }
}

// Add element to the min heap
void addElement(Node* value,vector<Node*> &A ){
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
        if(A[i_baap]->score > A[i]->score)
            swap(A[i],A[i_baap]);
        else
            break;

        i = i_baap;
    }
}

// delete root node from the heap
Node* PopElement(vector<Node*> &A){
    // check whether heap is empty or not
    if(A.size() == 0) {
        cerr<<"Heap is Empty"<<endl;
        return nullptr;
    }

    // index of last node
    int sz = A.size() - 1;

    // store the root node value to return later
    Node* popE = A[0];

    // swap root and last element
    swap(A[0],A[sz]);

    // delete last element
    A.pop_back();

    // bring back heap property
    if(A.size() != 0)
        MinHeapify(0,A);

    return popE;
}

// show binary representation of a given symbol
void showcode(Node* node) {
    if(node->baap != nullptr) {
        showcode(node->baap);
        cout<<node->bit;
    }
}

int main()
{
    // number of distinct symbol
    int n;
    cout<<"Enter number of distinct symbol : ";
    cin>>n;

    // array of pointer to root node of tree
    vector<Node*> minHeap(n);
    vector<Node*> temp(n);

    // store symbol and its frequency
    char symbol[n];
    int score[n];

    cout<<"Enter symbol and their frequency\n";

    for(int i=0;i<n;i++) {
        cin>>symbol[i]>>score[i];
    }

     // populate minHeap and temp vector
     for(int i =  0;i < n;i++) {
        Node* node = new Node;
        node->symbol = symbol[i];
        node->score = score[i];
        minHeap[i] = node;
        temp[i] = node;
     }

    // conversion of minHeap vector to min Heap
    buildMinHeap(minHeap);

    // algorithm to create huffman tree
    for(int i = 0; i < n-1 ;i++) {
        Node* left = PopElement(minHeap);
        Node* right = PopElement(minHeap);

        Node* node  = new Node;
        node->left = left;
        node->right = right;
        node->score = left->score + right->score;

        left->baap = right->baap = node;
        left->bit = false;
        right->bit = true;

        addElement(node, minHeap);
    }

    cout<<"Symbol with their binary representation\n";
    for(int i = 0;i < n;i++) {
        cout<<symbol[i]<<" : ";
        showcode(temp[i]);

        cout<<endl;
    }

    return 0;
}
