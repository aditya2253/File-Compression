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


//Making a Node Class that will contain the character, its freq, left node and right node
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

//function to sort the nodes based on their frequencies so as to insert int the priority queue
struct comparatorFunc{
    bool operator()(Node* a, Node* b){
        return a -> freq > b -> freq;
    }
};


void encodeHuffMann(Node* root, string str, map<char,string>& HuffMannCodes){
    if(root == NULL){
        return;
    }
    //if leafe node is reached store the string corresponding to char in the map
    if(root -> left == NULL && root -> right == NULL){
        HuffMannCodes[root -> c] = str;
    }
    //add 0 to str for left, 1 for right
    encodeHuffMann(root -> left, str + '0', HuffMannCodes);
    encodeHuffMann(root -> right, str + '1', HuffMannCodes);

}
//function to decode the string back to original
string decodeString(Node* root, string encodedString){
    string ans = "";
    Node* curr = root;
    for(int i = 0; i < encodedString.size(); i++){
        if(encodedString[i] == '0'){                //while encoding char 0 was given to left node
            curr = curr -> left;
        }else{
            curr = curr -> right;
        }
        if(curr -> left == NULL && curr -> right == NULL){      //leaf node reached
            ans += curr -> c;
            curr = root;
        }
    }
    return ans;
}


void makingHuffMannCode(string input){
    map<char,int> frequencies;  //to store the frequency of each character 
    for(auto i : input){
        frequencies[i]++;
    }
    /*now we have the frequencies of each character. We now need to build the huffmann tree for 
    which we will be using min prioirty queue*/

    //made  min priority queue and inserted all the nodes of characters based on their frequencies
    priority_queue<Node*,vector<Node*>,comparatorFunc> HuffmannTree;

    for(auto x : frequencies){
        Node* newNode = new Node(x.first,x.second,NULL,NULL);
        HuffmannTree.push(newNode);
    }

    //Now we have to make the final tree;
    while(HuffmannTree.size() != 1){
        Node* left = HuffmannTree.top();
        HuffmannTree.pop();
        Node* right = HuffmannTree.top();
        HuffmannTree.pop();

        //make a new node whose left and right will be the upper two nodes and frequency will be sum of its left and right node frequencies
        Node* newNode = new Node('$',left -> freq + right -> freq, left, right);
        HuffmannTree.push(newNode);
    }
    //Now the priorityQueue has only one node and this node is the root of our Tree
    Node* root = HuffmannTree.top();

    //Now we need to encode ()
    //for this we will use a map and for each character store a string of 0s and 1s
    map<char, string> HuffMannCodes;
    encodeHuffMann(root,"",HuffMannCodes);
    //the encodeHuffMann function has allocated Huffmann cades for each character in the input string

    //printing huffmann codes of each character   (commenting out for now)
    // for(auto i : HuffMannCodes){
    //     cout << i.first << " ->";
    //     for(auto j : i.second){
    //         cout << j;
    //     }
    //     cout << endl;
    // }
    //to get our encoded string 
    string encodedString = "";
    for(auto c : input){
        encodedString += HuffMannCodes[c];
    }
    //we have obtained our encoded string, no to decode this string back to the original string, we will make a decode function
    string decodedString = decodeString(root,encodedString);


    cout << "The original string was :" << endl;
    cout << input << endl;
    cout << "The encoded string is :" << endl;
    cout << encodedString << endl;
    cout << "The Decoded string is : " << endl;
    cout << decodedString << endl;

    //to find compression rate
    int lengthOfOriginalString = 8*(input.length());   //chars take 8 bytes
    int lengthOfReducedString = ceil(encodedString.length()/8);
    double compression = (double)lengthOfReducedString/lengthOfOriginalString;
    cout << "The string has been compressed upto " << compression*100 << "% of the original string" << endl;

}

signed main(){
    string s;
    cout << "Please enter the input string" << endl;
    getline(cin,s);
    makingHuffMannCode(s);
}