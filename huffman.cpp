#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node {
    int freq;
    char data;
    Node* left;
    Node* right;
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generate_codes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;
    if (root->data != '\0') {
        codes[root->data] = code;
    }
    generate_codes(root->left, code + "0", codes);
    generate_codes(root->right, code + "1", codes);
}

Node* build_tree(unordered_map<char, int>& freq_table) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto it = freq_table.begin(); it != freq_table.end(); it++) {
        Node* node = new Node;
        node->data = it->first;
        node->freq = it->second;
        node->left = node->right = nullptr;
        pq.push(node);
    }
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node;
        parent->data = '\0';
        parent->freq = left->freq + right->freq;
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

void encode_file(const string& input_file, const string& output_file) {
    unordered_map<char, int> freq_table;
    ifstream ifs(input_file, ios::in | ios::binary);
    char ch;
    while (ifs.get(ch)) {
        freq_table[ch]++;
    }
    ifs.close();
    Node* root = build_tree(freq_table);
    unordered_map<char, string> codes;
    generate_codes(root, "", codes);
    ofstream ofs(output_file, ios::out | ios::binary);
    ifs.open(input_file, ios::in | ios::binary);
    while (ifs.get(ch)) {
        ofs << codes[ch];
    }
    ifs.close();
    ofs.close();
}

void decode_file(const string& input_file, const string& output_file) {
    ifstream ifs(input_file, ios::in | ios::binary);
    Node* root = new Node;
    root->data = '\0';
    root->left = root->right = nullptr;
    string code;
    char ch;
    while (ifs.get(ch)) {
        code.push_back(ch);
    }
    ifs.close();
    Node* current = root;
    ofstream ofs(output_file, ios::out | ios::binary);
    for (int i = 0; i < code.size(); i++) {
        if (code[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->data != '\0') {
            ofs << current->data;
            current = root;
        }
    }
    ofs.close();
}

int main() {
    string input_file = "input.txt";
    string encoded_file = "encoded.bin";
    string decoded_file = "decoded.txt";
    encode_file(input_file, encoded_file);
    decode_file(encoded_file, decoded_file);
    return 0;
}
