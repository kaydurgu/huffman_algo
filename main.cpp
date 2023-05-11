#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>

using namespace std;

struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;
    
    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator() (Node* n1, Node* n2) {
        return n1->freq > n2->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }
    
    if (root->data != '\0') {
        codes[root->data] = code;
    }
    
    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

Node* buildTree(unordered_map<char, int>& freqTable) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    
    for (auto& p : freqTable) {
        minHeap.push(new Node(p.first, p.second));
    }
    
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }
    
    return minHeap.top();
}

void buildFrequencyTable(string inputFile, unordered_map<char, int>& freqTable) {
    ifstream fin(inputFile);
    if (fin.is_open()) {
        char c;
        while (fin.get(c)) {
            freqTable[c]++;
        }
        fin.close();
    }
}

void writeCompressedData(string inputFile, string outputFile, unordered_map<char, string>& codes) {
    ifstream fin(inputFile);
    ofstream fout(outputFile, ios::binary);
    if (fin.is_open() && fout.is_open()) {
        char c;
        string code;
        while (fin.get(c)) {
            code += codes[c];
            while (code.length() >= 8) {
                char byte = 0;
                for (int i = 0; i < 8; i++) {
                    byte <<= 1;
                    if (code[i] == '1') {
                        byte |= 1;
                    }
                }
                fout.write(&byte, 1);
                code.erase(0, 8);
            }
        }
        if (code.length() > 0) {
            char byte = 0;
            for (int i = 0; i < code.length(); i++) {
                byte <<= 1;
                if (code[i] == '1') {
                    byte |= 1;
                }
            }
            byte <<= 8 - code.length();
            fout.write(&byte, 1);
        }
        fin.close();
        fout.close();
    }
}

// Read the compressed data from the input
