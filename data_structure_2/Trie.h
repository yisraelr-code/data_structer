#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;


const int ALPHA_BET_SIZE = 26;


class TrieNode
{
public:
	list<TrieNode*> node;
	bool isLeaf;
	char letter;

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
	else
		while (val)
		{
			// function to check every letter in the string if it is exsit in the system,if yes continue if no create new path.
		}///its salay
}
