// C++ program to implement optimized delete in BST.
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int result;
    struct Node *left, *right;
};

// A utility function to create a new BST node
Node *newNode(int item)
{
    Node *temp = new Node;
    temp->result = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->result);
        inorder(root->right);
    }
}

/* A utility function to insert a new node with given result in
 * BST */
Node *insert(Node *node, int result)
{
    // TODO TODO TODO  TODO TODO TODO
    if (node == nullptr)
    {
        //queueTime.push(result);
        return newNode(result);
    }
    else
    {
        if (result >= node->result)
        {
            node->right = insert(node->right, result);
        }
        else if(result < node -> result)
        {
            node->left = insert(node->left, result);
        }
    }
    return node;
}

/* Given a binary search tree and a result, this function
deletes the result and returns the new root */
Node *findMin(Node *node)
{
    while (node && node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node *findMax(Node* node){
    while(node -> right != nullptr){
        node = node -> right;
    }
    return node;
}

Node *remove_recursive(Node *node, int result)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (result > node->result)
    {
        node->right = remove_recursive(node->right, result);
    }
    else if (result < node->result)
    {
        node->left = remove_recursive(node->left, result);
    }
    else
    {   
        if(node -> left == nullptr && node -> right == nullptr) return nullptr;
        else if (node->left == nullptr)
        {
            Node *temp = findMin(node -> right);
            node -> result = temp -> result;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node *temp = node->left;
            delete node;
            return temp;
        }
        else{
            // Node with two children: Get the in-order successor (smallest in the right subtree)
            Node *temp = findMin(node->right);

            // Copy the in-order successor's value to this node
            node->result = temp->result;

            // Delete the in-order successor
            node->right = remove_recursive(node -> right, temp->result);
        }
        
    }

    return node;
}

// Driver Code
int main()
{
    /* Let us create following BST
            50
        /	 \
        30	 70
        / \ / \
    20 40 60 80 */
    Node *root = NULL;
    
    int arr[] = {23,11,17,11,11,17};
    int n = sizeof(arr)/sizeof(int);

    
    for(int i = 0 ; i < n; i++){
        root = insert(root,arr[i]);
    }

    inorder(root);
    cout << endl;

    /* for(int i = 0; i < 2;i++){
        root = remove_recursive(root,arr[i]);
        Node* temp = findMin(root -> right);
        cout << temp->result << " ";
        cout << root->result << endl;
    } */

    root = remove_recursive(root,23);
    cout << root -> right -> result << " " << root -> result << endl;
    root = remove_recursive(root,11);
    cout << root -> right -> result << " " << root -> result << endl;
    //cout << endl << root -> result << endl;
    inorder(root);

    return 0;
}
