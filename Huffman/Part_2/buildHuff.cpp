#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>
#include <sstream>
using namespace std;

class Node{
public:
    int weight;
    char c;
    int height;
    Node* left;
    Node* right;
    
    friend class HuffTree_AVL;
public:
    Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr): height(1), weight(weight), c(c), left(left), right(right) {}
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
            if(count >= 2) return node;
            count += 2;
            node->left = rotateLeft(node->left);
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
            if(count >= 2) return node;
            count += 2;
            node->right = rotateRight(node->right);
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
    if (count >= 3)
        return node;
    
    node = balance(node,count);

    // Balance the left subtree
    node->left = balanceTreeRecursive(node->left, count);

    // Balance the right subtree
    node->right = balanceTreeRecursive(node->right, count);

    // Balance the current node
    return balance(node, count);
}

bool compareNode(Node *temp_1, Node *temp_2)
{
    if (temp_1->weight != temp_2->weight)
    {
        return temp_1->weight > temp_2->weight;
    }
    else
    {
        if (temp_1->c == '\0')
            return true;
        else if (temp_2->c == '\0')
            return true;
        else if (isupper(temp_1->c) && !(isupper(temp_2->c)))
            return true;
        else if (!isupper(temp_1->c) && isupper(temp_2->c))
            return false;
        else
            return temp_1->c > temp_2->c;
    }
}

Node *buildHuff(vector<pair<char, int>> freq)
{
    //* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
    vector<Node *> build;
    for (pair<char, int> pairs : freq)
    {
        build.push_back(new Node(pairs.second, pairs.first));
    }

    while (build.size() > 1)
    {
        int count = 0;
        Node *newNode = new Node('\0');
        Node *temp_left = build.back();
        build.pop_back();
        Node *temp_right = build.back();
        build.pop_back();

        newNode->left = temp_left;
        newNode->right = temp_right;
        newNode->weight = temp_left->weight + temp_right->weight;
        newNode->height = height(newNode);

        newNode = balanceTreeRecursive(newNode,count);
        build.push_back(newNode);
        sort(build.begin(), build.end(), compareNode);
    }

    return build[0];
}

//*********** code bên dưới không bận tâm ***************************
bool areHuffmanTreesEqual(const Node* tree1, const Node* tree2);
void printHuffmanTree(const Node* tree);
std::string huffmanTreeToString(const Node* tree) ;
int main()
{
    //* test 1
    {
        vector<pair<char, int>> v = {{'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0', 
                                 new Node(2, 'c'),
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 1 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 1 \n";
    }

    //* test 2
    {
        vector<pair<char, int>> v = {{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 2 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 2 \n";
    }

    //* test 3
    {
        vector<pair<char, int>> v = {{'d',6}, {'c', 3}, {'b', 1}, {'a', 1}};
        Node* root = new Node(5, '\0',
                                new Node(2, '\0',
                                    new Node(1, 'a'),
                                    new Node(1, 'b')),
                                new Node(11, '\0',
                                    new Node(3, 'c'),
                                    new Node(6, 'd')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 3 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 3 \n";
    }
    
    //* test 4
    {
        vector<pair<char, int>> v = {{'d',5}, {'c', 3}, {'b', 1}, {'a', 1}};
        Node* root = new Node(2, '\0',
                                new Node(10, '\0',
                                    new Node(5, 'd'),
                                    new Node(1, 'a')),
                                new Node(5, '\0',
                                    new Node(1, 'b'),
                                    new Node(3, 'c')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 4 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 4 \n";
    }


    //* test 5
    {
        vector<pair<char, int>> v = {{'d',5}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(2, '\0',
                                new Node(4, '\0',
                                    new Node(2, 'c'),
                                    new Node(1, 'a')),
                                new Node(9, '\0',
                                    new Node(1, 'b'),
                                    new Node(5, 'd')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 5 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 5 \n";
    }


    //* test 6
    {
        vector<pair<char, int>> v = {{'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        Node* root = new Node(4, '\0',
                                new Node(7, '\0',
                                    new Node(3, 'd'),
                                    new Node(2, 'c')),
                                new Node(14, '\0',
                                    new Node(2, '\0',
                                        new Node(1, 'a'),
                                        new Node(1, 'b')),
                                    new Node(10, 'e')));
        Node* result = buildHuff(v);
        if(! areHuffmanTreesEqual(root, result))
        {
            cout << "fail test 6 \n";
            cout << "result     = ";printHuffmanTree(root);cout << "\n";
            cout << "output_you = ";printHuffmanTree(result);cout << "\n";
        }
        else cout << "pass test 6 \n";
    }

    // //* test 7
    {
        vector<pair<char, int>> v = {{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[24]([10,e],[20,f]))";
        
        if(output_you != result)
        {
            cout << "fail test 7 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 7 \n";
    }

    // //* test 8
    {
        vector<pair<char, int>> v = {{'g', 20},{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[34]([24]([10,e],[20,f]),[20,g]))";
        
        if(output_you != result)
        {
            cout << "fail test 8 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 8 \n";
    }


    // //* test 9
    {
        vector<pair<char, int>> v = {{'h', 21}, {'g', 20},{'f', 20}, {'e', 10},{'d',3}, {'c', 2}, {'b', 1}, {'a', 1}};
        string output_you = huffmanTreeToString(buildHuff(v));
        string result = "[14]([4]([7]([3,d],[2,c]),[2]([1,a],[1,b])),[34]([24]([10,e],[20,f]),[35]([20,g],[21,h])))";
        
        if(output_you != result)
        {
            cout << "fail test 9 \n";
            cout << "result     = " << result << endl;
            cout << "output_you = " << output_you << endl;
        }
        else cout << "pass test 9 \n";
    }
}

std::string huffmanTreeToString(const Node* tree) {
    std::stringstream ss;

    if (tree == nullptr) {
        return "";
    }

    if (tree->c) {
        ss << "[" << tree->weight << "," << tree->c << "]";
    } else {
        ss << "[" << tree->weight << "]";
    }

    if (tree->left != nullptr || tree->right != nullptr) {
        ss << "(";
        ss << huffmanTreeToString(tree->left);
        ss << ",";
        ss << huffmanTreeToString(tree->right);
        ss << ")";
    }

    return ss.str();
}


void printHuffmanTree(const Node* tree) {
    if (tree == nullptr) {
        return;
    }
    if(tree->c) std::cout << "[" << tree->weight << "," << tree->c << "]";
    else std::cout << "[" << tree->weight << "]";
    
    if (tree->left != nullptr || tree->right != nullptr) {
        std::cout << "(";
        printHuffmanTree(tree->left);
        std::cout << ",";
        printHuffmanTree(tree->right);
        std::cout << ")";
    }
}

bool areHuffmanTreesEqual(const Node* tree1, const Node* tree2) {
    // Nếu cả hai cây đều rỗng (nullptr), coi chúng là giống nhau
    if (tree1 == nullptr && tree2 == nullptr) {
        return true;
    }

    // Nếu chỉ một trong hai cây rỗng, coi chúng khác nhau
    if (tree1 == nullptr || tree2 == nullptr) {
        return false;
    }

    // So sánh giá trị và cấu trúc của hai nút
    return (tree1->weight == tree2->weight) &&
           (tree1->c == tree2->c) &&
           areHuffmanTreesEqual(tree1->left, tree2->left) &&
           areHuffmanTreesEqual(tree1->right, tree2->right);
}