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
//#include <cctype>
//#include<cstddef>
using namespace std;


const int ALPHA_BET_SIZE = 26;
const int BIGEST_WORD = 500;





class TrieNode
{
public:
	TrieNode* node[ALPHA_BET_SIZE];
	bool isLeaf;
	TrieNode* pointOnDad;// father pointer
	TrieNode();
	~TrieNode();
	bool IHaveKids() {
		for (int i = 0; i < ALPHA_BET_SIZE; i++)
		{ if (node[i])
			return true; 
		}
		return false;
	}
};

// c-tor and d-tor
TrieNode::TrieNode()
{
	for (int i = 0; i < ALPHA_BET_SIZE; i++)
	{
		node[i] = NULL;
	}
	pointOnDad = NULL;
	isLeaf = false;
}

TrieNode::~TrieNode()
{
	for (int i = 0; i < ALPHA_BET_SIZE; i++)
	{
		if (!node[i])// if the char does not exist
		{
			delete node[i]; 
			node[i] = NULL;
		}

	}

}


class Trie 
{
	bool Search(TrieNode* Root, string val);
	void Insert(TrieNode* Root, string val);
	void remove(TrieNode* Root, string val);
	void storeInColtainer(TrieNode* Root, char* wordArr, string word, int rank);
	void printWord(char* wordArr, int level,int beginChar);
	bool nodeHaveChilderns(TrieNode* Root);
	TrieNode* root;
public:
	void insert(string word);
	bool del(string word);
	bool search(string word);
	int printAutoSuggestions(string word);
	Trie() { root = new TrieNode; }
	TrieNode* findEndL(TrieNode* ptr,string Root);

};

bool Trie::search(string word)
{
	return Search(root, word);
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
	TrieNode* endChar = findEndL(root, val);

	for (size_t i = 0; i < ALPHA_BET_SIZE; i++) //check if the last leeter have childerns
	{
		if (endChar->node[i])
		{
			endChar->isLeaf = false;// beacuse we dont wont to del it
			return;
		}

	}


	// now after we check and we know that that we need to delete all the upper nodes->
	TrieNode* show = endChar;
	int check = val.length() - 1;
	while ((show->pointOnDad!=root)&&(nodeHaveChilderns(show->pointOnDad)))
	{
		show = show->pointOnDad;
		check--;
	}
	show->pointOnDad->node[val[check] - 'a'] = NULL;
	delete show;

}

int Trie::printAutoSuggestions(string word)
{


	char words[BIGEST_WORD];
	for (int i = 0; i < word.length(); i++)
	{
		words[i] = word[i];
	}
	TrieNode* pointer = root;
	for (size_t i = 0; i < word.length(); i++)
	{
		if (pointer->node[word[i] - 'a']) { pointer = pointer->node[word[i] - 'a']; }
		else { /*cout << "No string exist with this prefix\n";*/ return 0; }
	}

	storeInColtainer(pointer, words, word, 0);


	return 1;
}

void Trie::storeInColtainer(TrieNode* pointer, char* wordArr, string word, int rank)
{
	bool flag = false;
	for (size_t i = 0; i < ALPHA_BET_SIZE; i++)
	{
		if (pointer->node[i]) { flag = true; break;}
	}
	if (!flag) //this is wihtot childerns
	{
		wordArr[rank]= '\0';
		cout << word << wordArr;
		cout<< endl;
	}

	for (int j = 0; j < ALPHA_BET_SIZE; j++)
	{
		if (pointer->node[j]) {
			wordArr[rank] = j + 'a';
			storeInColtainer(pointer->node[j], wordArr, word, rank + 1);
		}
	}

}
void Trie::printWord(char* wordArr, int level, int beginChar)
{
	//function to print word that contain in an arry.

	char ch = beginChar;
	cout << ch;
	for (int i = 0; i < level; i++)
	{
		cout << wordArr[i] /*<< " "*/;
	}
	cout << endl;
}
void Trie::Insert(TrieNode* Root, string val)
{
	if (val.length() == 0) {
		Root->isLeaf = true;
		return;
	}
	//char ch = *(val.begin());
	//val.erase(val.begin());
	int chars[BIGEST_WORD];

	for (int ch = 0; ch < val.length(); ch++)
	{
		if (!Root->node[val[ch] - 'a'])
		{
			Root->node[val[ch] - 'a'] = new TrieNode(); // create the node
			Root->node[val[ch] - 'a']->pointOnDad = Root;// and say to point on dad

		}
		 if (ch < val.length()-1)// we want to procced
		{
			Root = Root -> node[val[ch]- 'a'];
		}

	}
	Root->node[val[val.length()-1]-'a']->isLeaf = true;

	//Insert(Root->node[ch - 'a'], val);
}
bool Trie::Search(TrieNode* Root, string val)
{

	int chars[BIGEST_WORD];
	for (size_t i = 0; i < val.length(); i++)
	{
		chars[i] = val[i] - 'a';

	}
	int ch = 0;
	for (; ch < val.length(); ch++)
	{
		if (Root->node[chars[ch]]) //if its exist
		{
			if (ch < val.length() - 1)// we want to procced withot exepeion
			{
				Root = Root->node[chars[ch]];
			}
		}
		else return false;
		
	}
	if ((Root->node[chars[ch-1]]->isLeaf)) //the last letter is 
	{
		return true;
	}

	return false;
}
TrieNode* Trie::findEndL(TrieNode* Root,string val)
{
	if (!Search( Root,val))
	{
		return NULL;
	}

	for (int ch = 0; ch < val.length(); ch++)
	{
		if (Root->node[val[ch]-'a'])
		{
			if (ch < val.length() - 1)
			{
				Root = Root->node[val[ch]-'a'];
			}

		}
		else return NULL;

	}


	if (Root->node[val[val.length() - 1] - 'a']->isLeaf && Root->node[val[val.length() - 1] - 'a'])
	{
		return Root->node[val[val.length() - 1] - 'a'];
	}
	else
	{
		return NULL;
	}
}

bool Trie:: nodeHaveChilderns(TrieNode* Root)
{
	if (Root->isLeaf)
	{return false;}
	int count = 0;

	for (size_t i = 0; i < ALPHA_BET_SIZE; i++)
	{
		if (Root->node[i])
		{
			count++;
			if (count > 1) { return true; }

		}

	}return false;

}

