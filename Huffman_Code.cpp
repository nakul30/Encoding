#include <bits/stdc++.h>
using namespace std;
unordered_map<char, string > decoder ;
// A Huffman tree node
struct MinHeapNode {
 
    // One of the input characters
    char data;
 
    // Frequency of the character
    unsigned freq;
 
    // Left and right child
    MinHeapNode *left, *right;
 
    MinHeapNode(char data, unsigned freq)
 
    {
 
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
 
MinHeapNode* finaltree= NULL ; 
// Prints huffman codes from
// the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, string str)
{
 
    if (!root)
        return;
 
    if (root->data != '$'){
        // cout << root->data << ": " << str << "\n";
        // decoder[root->data] = stoi(str) ; 
        decoder[root->data] = str ;

    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
// For comparison of
// two heap nodes (needed in min heap)
struct compare {
 
    bool operator()(MinHeapNode* l, MinHeapNode* r)
 
    {
        return (l->freq > r->freq);
    }
};
 
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(unordered_map<char , int > frequency_collector, int size)
{
    struct MinHeapNode *left, *right, *top;
 
    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>,  compare > minHeap;
 
    for( auto i : frequency_collector ){
        char data = i.first ; int freq = i.second ; 
        minHeap.push(new MinHeapNode( data , freq )) ; 
    }
 
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
 
        // Extract the two minimum
        // freq items from min heap
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();
 
        top = new MinHeapNode('$',  left->freq + right->freq);
 
        top->left = left;
        top->right = right;
 
        minHeap.push(top);
    }
    finaltree = minHeap.top() ; 
    printCodes(minHeap.top(), "");
}
string decodeHuffman( string encoded) {
    string decoded;
    MinHeapNode* curr = finaltree;

    for (char bit : encoded) {
        if (bit == '0') {
            curr = curr->left;
        } else if (bit == '1') {
            curr = curr->right;
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            decoded += curr->data;
            curr = finaltree; // Reset to the root for the next character
        }
    }

    return decoded;
}
string decodedstring( string start  ){
    string decoded = decodeHuffman(start);
    return decoded ;
}
string encodeString(string input, unordered_map<char, string>& huffmanTable) {
    string encoded;
    for (char ch : input) {
        auto it = huffmanTable.find(ch);
        if (it != huffmanTable.end()) {
            encoded += it->second;
        } else {
            // Handle characters not found in the Huffman table (optional, based on your requirement)
            // You can choose to ignore or use some default replacement behavior.
            // For simplicity, I'll use '?' to represent unknown characters.
            encoded += '?';
        }
    }
    return encoded;
}


// Driver Code
int main()
{
    string start  ; 
    cin >> start ; 

    unordered_map<char , int > frequency_collector ; 
    for( int i = 0 ; i < start.length() ; i++ ){
        frequency_collector[start[i]]++ ; 
    }
    
    int size = frequency_collector.size(); 
 
    HuffmanCodes(frequency_collector , size);
    
    // for(auto i : decoder ){
    //     cout << i.first << ":" << i.second << endl ; 
    // }
    string encodedone =  encodeString(start , decoder ) ; 
    string decodedone = decodedstring(encodedone) ; 
    return 0;
}