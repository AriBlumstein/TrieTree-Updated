#include "Trie.h"

//method that returns the address to a node, node will have Null chuildren and parent
Trie::TrieNode::TrieNode()
{
	for_each(children, children + 26, [](TrieNode*& cur) {cur = NULL; });

	isWordEnd = false;
}

//method that returns whether a node is the last of its word
bool Trie::isLastNode(TrieNode* cur)
{
	return cur->isWordEnd;
}

//method to insert a word into the tree, reiceves aa node and a string as parameters
bool Trie::insertT(TrieNode* root, string key)
{
	if (searchT(root, key))
	{
		return false;
	}
	
		
    TrieNode* cur = root;
	//let us look at every letter in the string
	for (int x = 0; x < key.size(); ++x)
	{
		//check to see if we don't already have a a child for the current letter, if we don't dynamically allocate a new child
		if (!(cur->children[CHAR_TO_INDEX(key[x])]))
		{
			cur->children[CHAR_TO_INDEX(key[x])] = new TrieNode;
		}

		cur = cur->children[CHAR_TO_INDEX(key[x])];
	}

	cur->isWordEnd = true;

	return true;
}

bool Trie::delT(TrieNode* curNode, string key)
{
	//only need to delete if the word exists from the current node
	if (searchT(curNode, key))
	{
		delR(curNode, key);
		return true;
	}
	else
	{
		return false;
	}


}

//method to remove a word from a tree, recieves a node of the tree and the word to remove
void Trie::delR(TrieNode* curNode, string key)
{
	//if we made it trough the entire string, we reached the end of the word, set endofword as false and return true
	if (key == "")
	{
		if (curNode->isWordEnd)
		{
			curNode->isWordEnd = false;
			return;
		}
	}

	//let us get the first char of key, and the rest of the string after the first char
	char cur = key[0];
	string rest = key;
	rest.erase(rest.begin());

	//if there is no child for the current letter, return, the word wasn't in the tree
	if (!curNode->children[CHAR_TO_INDEX(cur)])
	{
		return;
	}

	//continue down the current path of the word, get the value returned and save it in flag
	delR(curNode->children[CHAR_TO_INDEX(cur)], rest);

	//we wil now begin the delete process, lets get the correct child to delete first
	TrieNode* child = curNode->children[CHAR_TO_INDEX(cur)];

	//only delete if it was not an end of word in its own right, return flag
	if (child->isWordEnd)
	{
		return;
	}

	//let us also make sure the child itself is childless, only if it is do we delete it
	bool childless = true;

	for (char letter = 'a'; letter <= 'z'; ++letter)
	{
		if (child->children[CHAR_TO_INDEX(letter)])
		{
			childless = false;
			break;
		}
	}

	if (childless)
	{
		delete child;
		curNode->children[CHAR_TO_INDEX(cur)] = NULL; //must set the parent pointer to this to null
	}


}

//bool delR(TrieNode* prev, TrieNode* root, string key, int ind);

//method to search for a word, returns true if its there, false otherwise
bool Trie::searchT(TrieNode* root, string key)
{
	TrieNode* cur = root;

	//iterate through the string, if the current child determined by the current letter is not null, set our current node to be that child
	for (int x = 0; x < key.size(); ++x)
	{
		if (cur->children[CHAR_TO_INDEX(key[x])])
		{
			cur = cur->children[CHAR_TO_INDEX(key[x])];
		}

		//we at this point know that the word is not in the tree
		else
		{
			return false;
		}
	}

	//now we will just return isendofword, it will tell us if thw word was in the tree
	return cur->isWordEnd;

}

//recurssive method to print words withe a given prefix in the tree
int Trie::suggestionsRec(TrieNode* cur, string currPrefix)
{
	//if the current node is null, nothing exists here, return 0
	if (!cur)
	{
		return 0;
	}

	int total = 0;

	//if we reached an end of word, print and increment total
	if (cur->isWordEnd)
	{
		cout << currPrefix << endl;
		total += 1;
	}

	//iterate through all the children
	for (char letter = 'a'; letter <= 'z'; ++letter)
	{
		//set total as equal to all the words that were printed from the children, append the current letter to prifix
		total += suggestionsRec(cur->children[CHAR_TO_INDEX(letter)], currPrefix + letter);
	}

	//return the total words printed
	return total;
}

//method that will print words in the tree with the given prefix, returns the number of words that have that prefix in the tree
int Trie::printAutoSuggestionsT(TrieNode* cur, string query)
{
	for (int x = 0; x < query.size(); ++x)
	{
		if (!cur->children[CHAR_TO_INDEX(query[x])])
			{
				return 0;
			}
		cur = cur->children[CHAR_TO_INDEX(query[x])];
	}

	return suggestionsRec(cur, query);
}

//method that prints all the letters in the tree by their level, this method assumes that the root will never be null
void Trie::printT(TrieNode* t, int level)
{
	//iterate throught the children
	for (char letter = 'a'; letter <= 'z'; ++letter)
	{
		//if a node exists at the current child, print it
		if (t->children[CHAR_TO_INDEX(letter)])
		{
			//print the number of spaces needed 
			for (int x = 0; x < level; ++x)
			{
				cout << "  ";
			}
			cout << letter << ':' << endl;

			//print all the children of the current letter
			printT(t->children[CHAR_TO_INDEX(letter)], level + 1);
		}
		
	}

}

//method that deletes all the nodes starting from the one originally passed to it
void Trie::deleteAll(TrieNode* cur)
{
	if (!cur)
	{
		return;
	}

	for (char letter = 'a'; letter <= 'z'; ++letter)
	{
		deleteAll(cur->children[CHAR_TO_INDEX(letter)]);
	}

	delete cur;
}