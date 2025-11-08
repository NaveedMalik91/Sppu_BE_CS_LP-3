#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int val;
    string symbol;
    string huffman;
    Node *left;
    Node *right;

    Node(int n, string s)
    {
        this->val = n;
        this->symbol = s;
        this->huffman = "";
        this->left = nullptr;
        this->right = nullptr;
    }
};

struct Compare
{
    bool operator()(const Node *a, const Node *b)
    {
        return a->val > b->val;
    }
};

class HuffmanEncoding
{
    Node *root;
    string inputText;
    unordered_map<string, int> freqs;
    unordered_map<string, string> codes;
    // Priority queue (min-heap) that stores Node pointers.
    // It uses the Compare struct to order nodes by smallest frequency first,
    // which is required for building the Huffman Tree.
    priority_queue<Node *, vector<Node *>, Compare> pq;

    void encode(Node *node, const string &val = "")
    {
        string newVal = val + node->huffman;

        //Recursive calls
        if (node->left != nullptr)
        {
            encode(node->left, newVal);
        }
        if (node->right != nullptr)
        {
            encode(node->right, newVal);
        }

        //add the huffman code to corresponding symbol in map
        if (node->left == nullptr && node->right == nullptr)
        {
            codes[node->symbol] = newVal;
        }
    }

public:
    HuffmanEncoding(string text)
    {
        this->inputText = text;
        this->root = nullptr;

        for (char c : inputText)
        {
            string s(1, c);
            freqs[s]++;
        }

        for (auto it : freqs)
        {
            Node *node = new Node(it.second, it.first);
            pq.push(node);
        }
    }

    void buildTree()
    {
        while (pq.size() > 1)
        {
            Node *l = pq.top();
            pq.pop();
            Node *r = pq.top();
            pq.pop();

            l->huffman = "0";
            r->huffman = "1";

            Node *node = new Node(l->val + r->val, l->symbol + r->symbol);
            node->left = l;
            node->right = r;
            pq.push(node);
        }

        this->root = pq.top();
        pq.pop();
    }

    void displayResult()
    {
        cout << "The character coding is as follows: " << endl;
        encode(root);
        for (auto it : codes)
        {
            cout << it.first << " --> " << it.second << endl;
        }
        cout << endl;

        string encodedText = "";
        for (char c : inputText)
        {
            string s(1, c);
            encodedText += codes[s];
        }

        cout << "The encoded text is.." << endl;
        cout << encodedText << endl;
    }
};

int main()
{
    string text;
    cout << "Enter text to encode" << endl;
    cin >> text;

    HuffmanEncoding he(text);
    he.buildTree();
    he.displayResult();

    return 0;
}
/* 
Time and Space Complexity of Huffman Encoding

Let:
N = length of the input string
n = number of distinct characters

1) Counting Frequency:
   We scan each character once.
   Time = O(N)

2) Inserting nodes into Priority Queue:
   We insert 'n' nodes.
   Each insertion takes O(log n).
   Time = O(n log n)

3) Building Huffman Tree:
   We repeatedly remove two smallest nodes and insert one new node.
   This happens (n - 1) times.
   Each pop/push operation takes O(log n).
   Time = O(n log n)

4) Generating Huffman Codes (tree traversal):
   We visit each node once.
   Time = O(n)

5) Encoding the Input String:
   We replace each character with its code.
   Time = O(N)

Total Time Complexity:
   O(N) + O(n log n) + O(n log n) + O(n) + O(N)
   = O(N + n log n)
   Worst case: n = N, so complexity becomes O(N log N)

Space Complexity:
   We store frequency table, priority queue, Huffman tree, and code table.
   Each of these requires O(n) space.
   So total Space Complexity = O(n)
*/
