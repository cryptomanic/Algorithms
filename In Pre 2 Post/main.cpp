#include <iostream>

using namespace std;

void printPostOrder(int preorder[], int inorder[], int n) {

    int index = 0;
    for(int i = 0; i < n;i++) {
        if(inorder[i] == preorder[0]){
            index = i;
            break;
        }
    }

    if(index != 0)
        printPostOrder(preorder + 1, inorder, index);

    if(index != n-1)
        printPostOrder(preorder + index + 1, inorder + 1, n - index - 1);

    cout<<preorder[0]<<" ";
}

int main()
{
    int n = 0;
    cout<<"Enter number of nodes: ";
    cin>>n;

    int preorder[n], inorder[n];

    cout<<"Enter preorder traversal of a tree: ";
    for(int i = 0;i < n;i++)
        cin>>preorder[i];

    cout<<"Enter inorder traversal of the same tree: ";
    for(int i = 0;i < n;i++)
        cin>>inorder[i];

    printPostOrder(preorder, inorder, n);

    return 0;
}
