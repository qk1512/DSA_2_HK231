#include <iostream>
#include <queue>
#include <math.h>
#include <unordered_map>

using namespace std;

// Node structure for the Huffman tree
struct Node
{
    char data;
    int frequency;
    Node *left;
    Node *right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparator for the priority queue (min heap)
struct CompareNodes
{
    bool operator()(Node *const &node1, Node *const &node2)
    {
        return node1->frequency > node2->frequency;
    }
};

// Function to build the Huffman tree
Node *buildHuffmanTree(const string &text)
{
    // Step 1: Build frequency table
    unordered_map<char, int> frequencyTable;
    for (char ch : text)
    {
        frequencyTable[ch]++;
    }

    // Step 2: Create nodes and push them into a min heap
    priority_queue<Node *, vector<Node *>, CompareNodes> minHeap;
    for (auto entry : frequencyTable)
    {
        minHeap.push(new Node(entry.first, entry.second));
    }

    // Step 3: Build the Huffman tree
    while (minHeap.size() > 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();

        Node *internalNode = new Node('$', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    // The root of the Huffman tree is the last remaining node in the heap
    return minHeap.top();
}

// Function to print the Huffman codes
void printHuffmanCodes(Node *root, string code = "")
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data != '$')
    {
        cout << root->data << ": " << code << endl;
    }

    printHuffmanCodes(root->left, code + "0");
    printHuffmanCodes(root->right, code + "1");
}

int main()
{
    string text = "001";
    int result = 0;
    for(int i = 0; i < text.size(); i++){
        result += (text[i] - '0') * pow(2, text.size() - 1 - i);
    }

    cout << result;

    return 0;
}
