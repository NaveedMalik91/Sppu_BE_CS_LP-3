#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string symbol;
    int value;
    string huffman;
    Node *left;
    Node *right;
    Node(string symbol, int val)
    {
        this->symbol = symbol;
        this->value = val;
        this->huffman = "";
        this->left = NULL;
        this->right = NULL;
    }
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->value > b->value;
    }
};

class Huffmanencoding
{
private:
    Node *root;
    string inputtext;
    unordered_map<string, int> freqs;
    unordered_map<string, string> codes;

    priority_queue<Node *, vector<Node *>, Compare> pq;
    void encode(Node *node, const string &val = "")
    {
        string newVal = val + node->huffman;
        if (node->left != NULL)
        {
            encode(node->left, newVal);
        }
        if (node->right != NULL)
        {
            encode(node->right, newVal);
        }
        if (node->left == NULL && node->right == NULL)
        {
            codes[node->symbol] = newVal;
        }
    }

public:
    Huffmanencoding(string text)
    {
        this->inputtext = text;
        this->root = NULL;

        for (auto ch : inputtext)
        {
            string s(1, ch);
            freqs[s]++;
        }
        for(auto it : freqs){
            Node* node = new Node(it.first, it.second);
            pq.push(node);
        }
    }
    void buildtree()
    {
        while (pq.size() > 1)
        {
            Node *l = pq.top();
            pq.pop();

            Node *r = pq.top();
            pq.pop();

            l->huffman = "0";
            r->huffman = "1";

            Node *node = new Node(l->symbol + r->symbol, l->value + r->value);
            node->left = l;
            node->right = r;
            pq.push(node);
        }
        this->root = pq.top();
        pq.pop();
    }

    void dispalytree()
    {

        cout << "Character encoding is as follows: " << endl;
        encode(root);
        for (auto it : codes)
        {
            cout << it.first << "---->" << it.second << endl;
        }
        cout << endl;
        string encodedtext = "";
        for (auto ch : inputtext)
        {
            string s(1, ch);
            encodedtext += codes[s];
        }
        cout<<endl;
        cout<<"Encoded text = "<<encodedtext;
    }
};

int main()
{
    string text;
    cout << "Enter text to encode" << endl;
    cin >> text;

    Huffmanencoding he(text);
    he.buildtree();
    he.dispalytree();

    return 0;
}
