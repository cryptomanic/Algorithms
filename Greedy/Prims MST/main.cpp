#include <iostream>
#include <vector>
#include <list>
using namespace std;

/*Condition : left and right subtree of a node at given index must be min heap
  Result : whole tree with root at given index will satisfy min heap property after applying Min Heapify
*/

void MinHeapify(vector<pair<int,int> > &heap, int index) {

    // minimum value and its index
    int minimum = heap[index].first;
    int in = index;

    // compare minimum value with root of left subtree
    if(2*index + 1 < heap.size() and heap[2*index+1].first < minimum) {
        minimum = heap[2*index+1].first;
        in = 2*index + 1;
    }

    // compare minimum value with root of right subtree
    if(2*index + 2 < heap.size() and heap[2*index+2].first < minimum) {
        minimum = heap[2*index+2].first;
        in = 2*index + 2;
    }

    // compare index of minimum value node with the given index
    if(index != in) {
        swap(heap[index], heap[in]);
        MinHeapify(heap, in);
    }

}

// Add element to the min heap
void  Insert(vector<pair<int,int> > &heap, pair<int,int> val) {
    // add element at the end of vector heap
    heap.push_back(val);
    // index of new element
    int i = heap.size()-1;
    // for storing parent index of new element
    int i_papa =  (i-1)/2;

    // while property of min heap is not restored
    while(i != 0) {
        // compare new element with its parent
        if(heap[i_papa].first > heap[i].first) {
            // swap if parent is greater than child
            swap(heap[i_papa], heap[i]);
            // modify child and parent index
            i = i_papa;
            i_papa = (i-1)/2;
        }
        else{
            break;
        }
    }
}

// remove and return the top element
pair<int,int> Pop(vector<pair<int,int> > &heap) {
    // store value of top to be returned later
    pair<int,int> top = heap[0];
    // swap first and last element of heap
    swap(heap[0], heap[heap.size()-1]);
    // remove last element
    heap.pop_back();
    // restore min heap property
    MinHeapify(heap, 0);
    return top;
}

// check whether heap is empty or not
bool Empty(vector<pair<int,int> > &heap) {
    if(heap.size() == 0)
        return true;
    return false;
}

// prim's algorithm to find minimum cost spanning tree
int PrimsMST(vector<list<pair<int,int> > > &graph, int start = 0) {
    // min heap
    vector<pair<int,int> > heap;
    // to mark visited nodes
    vector<bool> visited(graph.size(), false);
    // insert start node
    Insert(heap, make_pair(0, start));
    // storing the answer
    int answer = 0;
    // while heap is not empry
    while(not Empty(heap)) {
        // pop element from heap
        pair<int,int> temp = Pop(heap);
        // if element is not visited
        if(not visited[temp.second]) {
            // mark visited
            visited[temp.second] = true;
            // add edge weight to the result
            answer += temp.first;
        }
        // insert all nodes(which are not visited yet) directly attached to temp.second into the heap
        list<pair<int, int> >::iterator it = graph[temp.second].begin();
        for( ;it !=  graph[temp.second].end();it++) {
            if(not visited[(*it).second]) {
                Insert(heap, *it);
            }
        }
    }

    return answer;
}

int main()
{
    int N;
    cout<<"Enter number of nodes: ";
    cin>>N;

    // adjacency linked list representation of graph
    vector<list<pair<int,int> > > graph(N);

    int E;
    cout<<"Enter number of edges: ";
    cin>>E;

    // n1 and n2 are endpoints of an edge whose weight is e
    int n1, n2, e;
    for(int i = 0;i < E;i++) {
        cin>>n1>>n2>>e;
        // graph is undirected
        graph[n1].push_back(make_pair(e, n2));
        graph[n2].push_back(make_pair(e, n1));
    }

    cout<<"Minimum Cost Spanning Tree: "<<PrimsMST(graph);
    return 0;
}
