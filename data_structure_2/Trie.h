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
public:
	TrieNode* root;
	void insert(string word);
	bool del(string word);
	bool search(string word);
	int printAutoSuggestions(string word);
	TrieNode* getNode();
	Trie() { root = NULL; }
	bool Contine(TrieNode* ptr);
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
	if (!search(word))return false;

	//it the word is the begginning of another word, we need to change only the flag.

	//TrieNode* father = root;
	//for (int i = 0; i < word.length(); i++)
	//{
	//	/*int index = word[i] - 'a';
	//	father = father->node[index];*/
	//	if (!father->node[i])
	//	{
	//		father->isLeaf = false;
	//		return true;
	//	}
	//}

	//here we need to delete all the letter in the word.
	int count = word.length() - 1;
	TrieNode* curr = father;

}
bool Trie::Contine(TrieNode* ptr)
{
	int counter = 0;
	if (ptr->isLeaf)
		return true;

	for (int i = 0; i < 26; i++)
	{
		if (ptr->node[i])//cheacking if the end of the word has a son
		{
			counter++;
			if (counter > 1)
				return true;
		}
	}
	return false;
}