#pragma once
#include <iostream>
#include <list>
#include <string>

#include <algorithm>
#include <vector>

using namespace std;


const int ALPHA_BET_SIZE = 26;


class TrieNode
{
public:
	list<TrieNode*> node;
	bool isLeaf;
	char letter;

	void searchOnList(val)
	{
		for (list<TrieNode*>::iterator it = node.begin(); it != node.end(); it++)
		{
			if (this->letter == val[0])
			{


			}
		}
	}


};

class Trie
{
public:
	TrieNode* root;
	void insert(string word);
	bool del(string word);
	bool search(string word);
	int printAutoSuggestions(string word);
	Trie() { root = NULL; }
};

void Trie::insert(string val)
{
	if (search(val))
		return;// the word is exist
	/*else*/





	//while (!val.empty)
	//{

	//	if (val[0] == root->letter)
	//	{


	//	}

	//	// function to check every letter in the string if it is exsit in the system,if yes continue if no create new path.
	//}///its salay
}
