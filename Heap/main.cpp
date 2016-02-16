#include <iostream>
#include <vector>
#include <array>

using namespace std;

/*Condition : left and right subtree of a node at given index must be min heap
  Result : whole tree with root at given index will satisfy min heap property after applying Min Heapify
*/
void MinHeapify(int index,vector<int> &A){

    //  whether heap is empty or not
    if(A.size() == 0) {
        cerr<<"Heap is empty"<<endl;
        return;
    }

    // minimum value and its index
    int minim = A[index];
    int i = index;

    // compare minimum value with root of left subtree
    if(2*index + 1 < A.size() && A[2*index + 1] < minim){
        minim = A[2*index + 1];
        i = 2*index + 1;
    }

    // compare minimum value with root of right subtree
    if(2*index + 2 < A.size() && A[2*index + 2] < minim){
        minim = A[2*index + 2];
        i = 2*index + 2;
    }

    // compare index of minimum value node with the given index
    if(i != index){
        swap(A[i],A[index]);
        MinHeapify(i,A);
    }
}

// convert vector A to Min Heap
void buildMinHeap(vector<int> &A){
    // elements with index greater than (A.size()/2) - 1 will be leaves
    for(int i = (A.size()/2) - 1;i >= 0 ;i--){
        MinHeapify(i,A);
    }
}

// Add element to the min heap
void addElement(int value,vector<int> &A){
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
        if(A[i_baap] > A[i])
            swap(A[i],A[i_baap]);
        else
            break;

        i = i_baap;
    }
}

// delete root node from the heap
int PopElement(vector<int> &A){
    // check whether heap is empty or not
    if(A.size() == 0) {
        cerr<<"Heap is Empty"<<endl;
        return -1;
    }

    // index of last node
    int sz = A.size() - 1;

    // store the root node value to return later
    int popE = A[0];

    // swap root and last element
    swap(A[0],A[sz]);

    // delete last element
    A.pop_back();

    // bring back heap property
    if(A.size() != 0)
        MinHeapify(0,A);

    return popE;
}

// display heap : layer wise traversal
void printAll(vector<int> &A){
    for(int i = 0;i <  A.size();i++)
        cout<<A[i]<<" ";
    cout<<endl;
}

int main()
{
    vector<int> A{1,2,3,9,7,5,2,5,6};
    // covert vector A to min heap
    buildMinHeap(A);
    // add elements to min heap
    addElement(4,A);
    addElement(10,A);

    // this is heap sort bro
    for(int i = 0;i < 11;i++){
        cout<<PopElement(A)<<" ";
    }

    return 0;
}
