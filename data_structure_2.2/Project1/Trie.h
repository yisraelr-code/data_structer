/* 
The goal of this program : Tire implementaion 
name of corse : Data data_structure
targil 2
AUTHORS:		Salay Shalom Shuker ,Yisrael Rolnick 
ID:				311600605 , 206672057
*/

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
	TrieNode();
	bool IHaveKids() {
		for (int i = 0; i < ALPHA_BET_SIZE; i++)
		{ if (node[i])
			return true; 
		}
		return false;
	}
};
TrieNode::TrieNode()
{
	for (int i = 0; i < ALPHA_BET_SIZE; i++)
	{
		node[i] = NULL;
	}
	isLeaf = false;
}

class Trie 
{
	bool Search(TrieNode* Root, string val);
	void Insert(TrieNode* Root, string val);
	void remove(TrieNode* Root, string val);
	void storeInColtainer(TrieNode* Root, char* wordArr, int level);
	void printWord(char* wordArr, int level);
	bool noBrothers(TrieNode* Root, int chek);
	TrieNode* root;
public:
	void insert(string word);
	bool del(string word);
	bool search(string word);
	int printAutoSuggestions(string word);
	Trie() { root = new TrieNode; }
};

bool Trie::search(string word)
{
	return Search(root,word);
}
void Trie::insert(string val)
{
	if (search(val))
	{
		//cout << "the word is exist!\n";
		return;
	}
	else
	{
		Insert(root, val);
	}
}
bool Trie::del(string word)
{
	//if the word is not exist in the system, return false.
	if (!search(word))
		return false;
	remove(root, word);
	return true;
}
void Trie::remove(TrieNode* Root, string val)
{
	if (val.length() == 0) 
	{     
		if (!Root->IHaveKids()) {
			delete Root;
			Root = NULL;
			return;
		}
		else
			Root->isLeaf = false;
		return;
	}
	char ch = *(val.begin());
	val.erase(val.begin());
	if (Root->node[ch - 'a'])
	{
		remove(Root->node[ch - 'a'], val);
	}
	if (noBrothers(Root->node[ch - 'a'], ch - 'a')) {
		if (!Root->isLeaf) {
			delete Root;
			Root = NULL;
		}
	}
}
bool Trie::noBrothers(TrieNode* Root, int chek)
{
	bool flag = true;
	for (int i = 0; i < ALPHA_BET_SIZE; i++) 
	{
		if (Root->node[i]) {
			if (i != chek)
				flag = false;
		}
	}
	return flag;
}
int Trie::printAutoSuggestions(string word)
{

	TrieNode* father = root;
	for (int i = 0; i < word.length(); i++)
	{
		int index = word[i] - 'a';
		father = father->node[index];
	}
	char wordArr[100];
	//we sending to the 'storeInColtainer' method node that has the last letter in the suggetsion word.  
	storeInColtainer(father,wordArr,0);
	return 1;
}
void Trie::storeInColtainer(TrieNode* Root, char* wordArr, int level)
{
	//function that goes over the subTree start from Root, and save all the letter in the path, and save them in arry. 
	if (!Root)
		return;
	//we sending the full arry that contain a word, to the printWord method.
	if (Root->isLeaf)
		printWord(wordArr, level);
	for (int i = 0; i < ALPHA_BET_SIZE; i++)
	{
		if (Root->node[i])
		{
			wordArr[level] = i + 'a';
			storeInColtainer(Root->node[i], wordArr, level + 1);
		}
	}
}
void Trie::printWord(char* wordArr, int level) 
{
	//function to print word that contain in an arry.
	cout << endl;
	for (int i = 0; i < level; i++) 
	{
		cout << wordArr[i] << " ";
	}
}
void Trie::Insert(TrieNode* Root, string val)
{
	if (val.length() == 0) {
		Root->isLeaf = true;
		return;
	}
	char ch = *(val.begin());
	val.erase(val.begin());
	if (!Root->node[ch - 'a'])
		Root->node[ch - 'a'] = new TrieNode;
	Insert(Root->node[ch - 'a'], val);
}
bool Trie::Search(TrieNode* Root, string val)
{
	if (val.length() == 0)
	{
			if (Root->isLeaf)
				return true;
			else
				return false;
	}
	char ch = *(val.begin());
	val.erase(val.begin());
	if (!Root->node[ch - 'a']) //there is no pointer
		return false;
	else
		return Search(Root->node[ch - 'a'], val);
}