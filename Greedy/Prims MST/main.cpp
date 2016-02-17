#include <iostream>
#include <vector>
#include <list>
using namespace std;

void MinHeapify(vector<pair<int,int> > &heap, int index) {

    int minimum = heap[index].first;
    int in = index;

    if(2*index + 1 < heap.size() and heap[2*index+1].first < minimum) {
        minimum = heap[2*index+1].first;
        in = 2*index + 1;
    }

    if(2*index + 2 < heap.size() and heap[2*index+2].first < minimum) {
        minimum = heap[2*index+2].first;
        in = 2*index + 2;
    }

    if(index != in) {
        swap(heap[index], heap[in]);
        MinHeapify(heap, in);
    }

}

void  Insert(vector<pair<int,int> > &heap, pair<int,int> val) {
    heap.push_back(val);
    int i = heap.size()-1;
    int i_papa =  (i-1)/2;

    while(i != 0) {
        if(heap[i_papa].first > heap[i].first) {
            swap(heap[i_papa], heap[i]);
            i = i_papa;
            i_papa = (i-1)/2;
        }
        else{
            break;
        }
    }
}

pair<int,int> Pop(vector<pair<int,int> > &heap) {
    pair<int,int> top = heap[0];
    swap(heap[0], heap[heap.size()-1]);
    heap.pop_back();
    MinHeapify(heap, 0);
}

bool Empty(vector<pair<int,int> > &heap) {
    if(heap.size() == 0)
        return true;
    return false;
}

int PrimsMST(vector<vector<pair<int,int> > > &graph, int start = 0) {
    vector<pair<int,int> > heap;
    vector<bool> visited(graph.size(), false);
    Insert(heap, make_pair(0, start));
    int answer = 0;

    while(not Empty(heap)) {
        pair<int,int> temp = Pop(heap);
        if(not visited[temp.second]) {
            visited[temp.second] = true;
            answer += temp.first;
        }

        for(int i = 0;i < graph[temp.second].size();i++) {
            if(not visited[graph[temp.second][i].second]) {
                Insert(heap, graph[temp.second][i]);
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

    vector<list<pair<int,int> > > graph(N);

    int E;
    cout<<"Enter number of edges: ";
    cin>>E;

    int n1, n2, e;
    for(int i = 0;i < E;i++) {
        cin>>n1>>n2>>e;
        graph[n1].push_back(make_pair(e, n2));
        cout<<i<<" ";
        graph[n2].push_back(make_pair(e, n1));
    }

    //cout<<"Answer: "<<PrimsMST(graph);
    return 0;
}
