/*
ProbingHash.h
 *
 *  Created on: Apr 20, 2019
 */

#ifndef PROBINGHASH_H_
#define PROBINGHASH_H_

#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

class ProbingHash
{
private:
	int bucket;    // No. of buckets; prime
	string* table; //hash table
	double loadFactor;
	bool prime(int p); //checks whether the number is prime or not

public:
	ProbingHash(int b);  // Constructor
	~ProbingHash();
	void insertItem(string x); // inserts a key into hash table
	bool findItem(string key);
	int hashFunction(string x); //hash function to map values to key
	void displayHash();
};

ProbingHash::ProbingHash(int b)
{
	int numberCount = b;

	loadFactor = 0.5; //ideal loadFactor is 0.5 for this hash table
	bucket = numberCount*(1/loadFactor);
	while (!prime(bucket))
	{
		if (bucket%2 == 0)
			bucket += 1;
		else
			bucket += 2;
	}
	//cout << bucket << endl;
	table = new string[bucket];
}

ProbingHash::~ProbingHash()
{
	delete[] table;
	table = NULL;
}

void ProbingHash::insertItem(string key)
{
	for (unsigned int i = 0; i < key.length(); i++)
	{
		key[i] = tolower(key[i]);
	}

	int index = hashFunction(key);
	if (table[index] == "")
	{
		table[index] = key;
		//cout << key << " is placed at index: " << index << endl;
	}
	else
	{
		int i = 1;
		int jump = 0; //number of jumps
		int tempIndex = index;

		while (table[tempIndex] != "")
		{
			tempIndex = (index + (int)pow(i, 2)) % bucket;
			//cout << "tempIndex is " << tempIndex << endl;
			jump = pow(i, 2);

			if (table[tempIndex] == key)
			{
				//cout << "duplicate value " << key << " is not inserted" << endl;
				break;
			}

			if (jump % bucket == 0 && table[tempIndex] != "")
			{
				//cout << "all possible spots filled... " << key << " is not inserted" << endl;
				break;
			}
			//cout << "jump: " << jump << ", table content: " << table[tempIndex] << endl;
			i++;
		}

		if (jump % bucket != 0 && table[tempIndex] != key)
		{
			table[tempIndex] = key;
			//cout << key << " is placed at index: " << tempIndex << endl;
		}
	}
}

bool ProbingHash::findItem(string key)
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

	if (table[index] == key)
	{
		found = true;
		//cout << index << ", found (right away): " << key << endl;
	}
	else
	{
		int i = 1;
		int tempIndex = index;

		while (!found && table[tempIndex] != "")
		{
			tempIndex = (index + (int)pow(i++, 2)) % bucket;
			//cout << "temp: " << tempIndex << ", index: " << index
			//<< ", i: " << i << ", increment: " << (int)pow(i, 2)
			//<< ", looking for: " << key << ", current word: "
			//<< table[tempIndex] << endl;

			if (table[tempIndex] == key)
			{
				found = true;
				//cout << index << ", found: " << key << endl;
			}
		}
	}
	return found;
}

int ProbingHash::hashFunction(string key)
{
	/*
	int temp = 0;

	for (int i = 0; i < x.length(); i++)
	{
		temp += tolower(x[i]);
		//cout << x[i] << ", " << temp << endl;
	}

	//cout << x << ": " << (temp % bucket) << endl;
	return (temp % bucket);
	 */
	unsigned int hashValue = 0;

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

// function to display hash table
void ProbingHash::displayHash() {
	for (int i = 0; i < bucket; i++) {
		cout << i << " --> " << table[i] << endl;
	}
}

bool ProbingHash::prime(int p) {
	bool prime = true;
	for (int i = 2; i < p; i++)
	{
		if (p % i == 0)
		{
			prime = false;
			break;
		}
	}

	return prime;
}



#endif /* PROBINGHASH_H_ */
