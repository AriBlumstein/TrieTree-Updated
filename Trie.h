// C++ program to demonstrate auto-complete feature 
// using Trie data ure. 
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Alphabet size (# of symbols) 
#define ALPHABET_SIZE (26) 

// Converts key current character into index 
// use only 'a' through 'z' and lower case 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 


class Trie
{
	
    // trie node 
    struct TrieNode
    {
	    TrieNode* children[ALPHABET_SIZE];

	    // isWordEnd is true if the node represents 
	    // end of a word 
	    bool isWordEnd;
	    TrieNode();
    };
	TrieNode* root;

public:
	Trie() { root = new TrieNode; }
	~Trie() { deleteAll(root); root = NULL; }
	bool insert(string wrd) { return insertT(root, wrd); }
	bool delW(string wrd) { return delT(root, wrd); }
	int printAutoSuggestions(string wrd) { return printAutoSuggestionsT(root, wrd); }
	bool search(string key) { return searchT(root, key); }
	void printTrie() { printT(root, 0); }
	
private:
	bool isLastNode(TrieNode* root);
	bool insertT(TrieNode* root, string key);
	bool delT(TrieNode* cur, string key);
	void delR(TrieNode* curNode, string key);
	bool searchT(TrieNode* root, string key);
	int suggestionsRec(TrieNode* root, string currPrefix);
	int printAutoSuggestionsT(TrieNode* root, string query);
	void printT(TrieNode* t, int level);
	void deleteAll(TrieNode* cur);

};


