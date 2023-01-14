#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include <string>
#include<queue>
#include<vector>
#include<map>
#include<unordered_map>
typedef long long int li;
typedef long double ld;
using namespace std;


//Made a Node Class that will contain the character, its frequency, and its left and right nodes
class Node{
    public : 
    char c;
    int freq;
    Node *left, *right;

    Node(char c, int freq, Node* left, Node* right){
        this -> c = c;
        this -> freq = freq;
        this -> left = left;
        this -> right = right;
    }
};

//Made a function to sort the nodes based on their frequencies so as to insert them into the priority queue
struct comparatorFunc{
    bool operator()(Node* a, Node* b){
        return a -> freq > b -> freq;
    }
};


void encodeHuffMan(Node* root, string str, map<char,string>& HuffManCodes){
    if(root == NULL){
        return;
    }
    //If leaf node is reached, store the string corresponding to char in the map
    if(root -> left == NULL && root -> right == NULL){
        HuffManCodes[root -> c] = str;
    }
    //Add 0 to str for left, 1 for right
    encodeHuffMan(root -> left, str + '0', HuffManCodes);
    encodeHuffMan(root -> right, str + '1', HuffManCodes);

}
// Made a function to decode the string back to original
string decodeString(Node* root, string encodedString){
    string ans = "";
    Node* curr = root;
    for(int i = 0; i < encodedString.size(); i++){
        if(encodedString[i] == '0'){                //While encoding, char 0 was given to left node
            curr = curr -> left;
        }else{
            curr = curr -> right;
        }
        if(curr -> left == NULL && curr -> right == NULL){      //Leaf node reached
            ans += curr -> c;
            curr = root;
        }
    }
    return ans;
}


void makingHuffManCode(string input){
    map<char,int> frequencies;  //To store the frequency of each character 
    for(auto i : input){
        frequencies[i]++;
    }
    /*Now we have the frequencies of each character. We now need to build the huffman tree for 
    which we will be using min prioirty queue*/

    //Made min priority queue and inserted all the nodes of characters based on their frequencies
    priority_queue<Node*,vector<Node*>,comparatorFunc> HuffmanTree;

    for(auto x : frequencies){
        Node* newNode = new Node(x.first,x.second,NULL,NULL);
        HuffmanTree.push(newNode);
    }

    //Now we have to make the final tree;
    while(HuffmanTree.size() != 1){
        Node* left = HuffmanTree.top();
        HuffmanTree.pop();
        Node* right = HuffmanTree.top();
        HuffmanTree.pop();

        //Make a new node whose left and right will be the upper two nodes and frequency will be the sum of its left and right node frequencies
        Node* newNode = new Node('$',left -> freq + right -> freq, left, right);
        HuffmanTree.push(newNode);
    }
    //Now the priorityQueue has only one node and this node is the root of our Tree
    Node* root = HuffmanTree.top();

    //Now we need to encode ()
    //For this we will use a map and for each character, store a string of 0s and 1s
    map<char, string> HuffManCodes;
    encodeHuffMan(root,"",HuffManCodes);
    //The encodeHuffMan function has allocated Huffman cades for each character in the input string

    //Printing huffman codes of each character   (commenting out for now)
    // for(auto i : HuffManCodes){
    //     cout << i.first << " ->";
    //     for(auto j : i.second){
    //         cout << j;
    //     }
    //     cout << endl;
    // }
    
    //To get our encoded string 
    string encodedString = "";
    for(auto c : input){
        encodedString += HuffManCodes[c];
    }
    //We have obtained our encoded string, now to decode this string back to the original string, we will make a decode function
    string decodedString = decodeString(root,encodedString);


    cout << "The Original string was : " << endl;
    cout << input << endl;
    cout << "The Encoded string is : " << endl;
    cout << encodedString << endl;
    cout << "The Decoded string is : " << endl;
    cout << decodedString << endl;

    //To find compression rate
    int lengthOfOriginalString = 8*(input.length());   //Chars take 8 bytes
    int lengthOfReducedString = ceil(encodedString.length()/8);
    double compression = (double)lengthOfReducedString/lengthOfOriginalString;
    cout << "The string has been compressed upto : " << compression*100 << "% of the original string" << endl;

}

signed main(){
    string s;
    cout << "Please enter the input string:- " << endl;
    getline(cin,s);
    makingHuffManCode(s);
}
