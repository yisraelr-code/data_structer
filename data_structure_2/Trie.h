#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;


const int ALPHA_BET_SIZE = 26;


class TrieNode
{
public:
	TrieNode* node[ALPHA_BET_SIZE];
	bool isLeaf;
	char letter;
};

class Trie
{
	TrieNode* remove(TrieNode* Root, string val, int level);
	TrieNode* getNode();
	TrieNode* root;
public:
	void insert(string word);
	bool del(string word);
	bool search(string word);
	int printAutoSuggestions(string word);
	Trie() { root = NULL; }
};
TrieNode* Trie::getNode()
{
	TrieNode* curr = new TrieNode;
	curr->isLeaf = false;
	for (int i = 0; i < ALPHA_BET_SIZE; i++)
	{
		curr->node[i] = nullptr;
	}
	return curr;
}
bool Trie::search(string word)
{
	TrieNode* temp = root;
	for (int i = 0; i < word.length(); i++)
	{
		int index = word[i] - 'a';
		if (temp->node[index]->letter != word[i])
		{
			return false;
		}
		temp = temp->node[index];
	}
	return (temp != nullptr && temp->isLeaf);
}
void Trie::insert(string val)
{
	if (search(val))
	{
		cout << "the word is exist!\n";
		return;
	}
	else
	{
		TrieNode* father = root;
		for (int i = 0; i < val.length(); i++)
		{
			int index = val[i] - 'a';
			if (!father->node[index])
				father->node[index] = getNode();
			father = father->node[index];
		}
		father->isLeaf = true;
	}
}
bool Trie::del(string word)
{
	//if the word is not exist in the system, return false.
	if (!search(word))
		return false;
	remove(root, word, 0);
	return true;
}
TrieNode* Trie::remove(TrieNode* Root, string val, int level)
{
	if (!Root)
		return nullptr;
	//in case that the last character of the word are being processed.
	if (level == val.size())
	{
		//change the flag.
		if (Root->isLeaf)
			Root->isLeaf = false;
		//if it's not prefix of another word.
		if (Root)
		{
			delete Root;
			Root = nullptr;
		}
		return Root;
	}
	//if we not in  the last character in the word,continue to the child using ASCII table.
	int index = val[level] - 'a';
	Root->node[index] = remove(Root->node[index], val, level + 1);
	// if the root does not have child,and it's not end of another wordl
	if (Root && Root->isLeaf == false)
	{
		delete Root;
		Root = nullptr;
	}
	return Root;
}
int Trie::printAutoSuggestions(string word)
{
	////if the word isn't exist.
	//if (!search(word))
	//	return 0;
	//TrieNode* father = root;
	//for (int i = 0; i < word.length(); i++)
	//{
	//	int index = word[i] - 'a';
	//	father = father->node[index];
	//}
}