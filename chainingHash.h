/*
 * chainingHash.h
 *
 *  Created on: Apr 20, 2019
 */

#ifndef CHAININGHASH_H_
#define CHAININGHASH_H_

#include <cstring>
//#include <vector>
//#include <list>
#include <iostream>
//#include "LL.h"

using namespace std;

class Node
{
private:
	string content;
	Node* next;

public:
	Node();
	Node(string key, Node *next);
	Node* getNext() {return next;};
	string getContent() {return content;};
};

class ChainingHash
{
private:
	int bucket; // No. of buckets
	Node** table; //hash table of nodes
	double loadFactor; //ideally 1

public:
	ChainingHash(int b);  // Constructor
	~ChainingHash();
	void insertItem(string key); // inserts a key into hash table
	bool findItem(string key);
	int hashFunction(string key); //hash function to map values to key
	void displayHash();
};

Node::Node()
{
	content = "";
	next = NULL;
}

Node::Node(string key, Node* pNext)
{
	content = key;
	next = pNext;
}

ChainingHash::ChainingHash(int b)
{
	int numberCount = b;
	loadFactor = 1; //ideal loadFactor is 1 for this hash table
	bucket = numberCount*(1/loadFactor);
	table = new Node*[bucket];
	//table = new list<int>[BUCKET];
}

ChainingHash::~ChainingHash()
{
	delete[] table;
	table = NULL;
}

void ChainingHash::insertItem(string key)
{
	int index = hashFunction(key);
	Node* temp = table[index];

	for (unsigned int i = 0; i < key.length(); i++)
	{
		key[i] = tolower(key[i]);
	}

	table[index] = new Node(key, temp);
}

bool ChainingHash::findItem(string key)
{
	bool found = false;

	if (ispunct(key[key.size() - 1]))
	{
		key = key.erase(key.size() - 1, 1);
	}
	for (unsigned int i = 0; i < key.length(); i++)
	{
		key[i] = tolower(key[i]);
	}

	int index = hashFunction(key);

	Node* temp = table[index];

	while (temp != NULL && !found)
	{
		if (temp->getContent() == key)
		{
			//cout << "found" << endl;
			found = true;
		}

		if (!found)
		{
			temp = temp->getNext();
		}
	}

	return found;
}

int ChainingHash::hashFunction(string key)
{
	unsigned int hashValue = 0; //prevent negative numbers

	for (unsigned int i = 0; i < key.length(); i++)
	{
		hashValue = 37*hashValue + tolower(key[i]);
		//Horner hash function
		//experiments have shown that 33, 37, 39, 41 are particularly good choices

		//cout << x[i] << ", " << temp << endl;
	}

	//cout << key << ": " << (hashValue % bucket) << endl;
	return (hashValue % bucket);
}

void ChainingHash::displayHash()
{
	for (int i = 0; i < bucket; i++)
	{
		cout << i;
		Node* temp = table[i];
		while (temp != NULL)
		{
			cout << " --> " << temp->getContent();
			temp = temp->getNext();
		}
		cout << endl;
	}
}

#endif /* CHAININGHASH_H_ */
