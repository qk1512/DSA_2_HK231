#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <utility>
#include <algorithm>
#include <sstream>
using namespace std;

class Node
{
public:
    int weight;
    char c;
    int height;
    Node *left;
    Node *right;

    friend class HuffTree_AVL;

public:
    Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : height(1), weight(weight), c(c), left(left), right(right) {}
};

int height(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}

int balanceFactor(Node *node)
{
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

void updateHeight(Node *node)
{
    if (node != nullptr)
    {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

Node *balance(Node *node, int &count)
{
    // Update height of current node
    if(count >= 3) return node;

    updateHeight(node);

    // Get the balance factor to check if this node became unbalanced
    int balance = balanceFactor(node);

    // Left Heavy
    if (balance > 1)
    {
        if (balanceFactor(node->left) >= 0)
        {
            // Left Left Case
            count++;
            return rotateRight(node);
        }
        else
        {
            // Left Right Case
            node->left = rotateLeft(node->left);
            count += 2;
            if (count >= 4) return node;
            return rotateRight(node);
        }
    }

    // Right Heavy
    if (balance < -1)
    {
        if (balanceFactor(node->right) <= 0)
        {
            // Right Right Case
            count++;
            return rotateLeft(node);
        }
        else 
        {
            // Right Left Case
            node->right = rotateRight(node->right);
            count += 2;
            if (count >= 4) return node;
            return rotateLeft(node);
        }
    }

    // Node is still balanced
    return node;
}

Node *balanceTreeRecursive(Node *node, int &count)
{
    // Base case: empty tree or leaf node
    if (node == nullptr)
    {
        return nullptr;
    }

    if(count >= 3) return node;

    node = balance(node,count);

    // Balance the left subtree
    node -> left = balanceTreeRecursive(node->left, count);

    // Balance the right subtree
    node -> right = balanceTreeRecursive(node->right, count);

    // Balance the current node
    return balance(node,count);
}

bool compareNode(pair<Node*,int> temp_1, pair<Node*,int> temp_2)
{
    if (temp_1.first->weight != temp_2.first->weight)
    {
        return temp_1.first->weight > temp_2.first->weight;
    }
    else
    {
        if (temp_1.first->c == '*')
            return true;
        else if (temp_2.first->c == '*')
            return false;
        else if (temp_1.first->c == '\0' && temp_2.first->c == '\0'){
            return temp_1.second > temp_2.second;
        }
        else if (temp_1.first->c == '\0' && temp_2.first->c != '\0')
            return true;
        else if (temp_2.first->c == '\0' && temp_1.first->c != '\0')
            return false;
        else if (isupper(temp_1.first->c) && !(isupper(temp_2.first->c)))
            return true;
        else if (!isupper(temp_1.first->c) && isupper(temp_2.first->c))
            return false;
        else
            return temp_1.first->c > temp_2.first->c;
    }
}

Node *buildHuff(vector<pair<char, int>> freq)
{
    //* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
    vector<pair<Node*,int>> build;
    for (pair<char, int> pairs : freq)
    {
        build.push_back(make_pair(new Node(pairs.second, pairs.first),0));
    }

    int order_pushing = 0;
    while (build.size() > 1)
    {   
        int count = 0;
        Node *newNode = new Node(0);
        Node *temp_left = build.back().first;
        build.pop_back();
        Node *temp_right = build.back().first;
        build.pop_back();

        newNode->left = temp_left;
        newNode->right = temp_right;
        newNode->weight = temp_left->weight + temp_right->weight;
        newNode->height = height(newNode);
        order_pushing++;

        newNode = balanceTreeRecursive(newNode,count);
        newNode -> c = '*';
        build.push_back(make_pair(newNode,order_pushing));
        sort(build.begin(), build.end(), compareNode);
        newNode -> c = '\0';


        for (auto temp : build)
        {
            cout << "[" << temp.first->weight << "," << temp.first->c << "]";
        }
        cout << endl;

    }
    cout << endl;
    return build[0].first;
}


void printHuffmanTree(const Node *tree)
{
    if (tree == nullptr)
    {
        return;
    }
    if (tree->c)
        std::cout << "[" << tree->weight << "," << tree->c << "]";
    else
        std::cout << "[" << tree->weight << "]";

    if (tree->left != nullptr || tree->right != nullptr)
    {
        std::cout << "(";
        printHuffmanTree(tree->left);
        std::cout << ",";
        printHuffmanTree(tree->right);
        std::cout << ")";
    }
}

int main(){
    vector<pair<char, int>> v = {{'i', 9}, {'j', 6}, {'p', 5}, {'x', 3}, {'d', 3}, {'u', 2}, {'l', 2}, {'h', 2}, {'e', 2}, {'a', 2}, {'r', 1}, {'q', 1}, {'m', 1}};
    Node* result = buildHuff(v);
    printHuffmanTree(result);
    std::cout << std::endl;
    return 0;
}

