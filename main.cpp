
#include "main.h"

int main(int argc, const char* argv[]) {

	//cout << "hashing" << endl; // prints !!!Hello World!!!

	try {
		if (argc < 2)
			throw std::invalid_argument("Input file needs to be at least one");

		//string fileName1 = "dictionaryFile.txt";
		//string fileName2 = "inputFile1.txt";
		string fileName1 = argv[1];
		string fileName2 = argv[2];

		ifstream dictionary(fileName1.c_str());
		ifstream input(fileName2.c_str());

		int probeError = 0;
		int chainingError = 0;

		clock_t timeBegin;
		clock_t timeEnd;
		double chainingTime = 0.0;
		double probingTime = 0.0;

		if (!dictionary)
		{
			string errMsg = "failed to open dictionary, check filename and path: ";
			errMsg += fileName1;

			throw invalid_argument(errMsg);
		}

		if (!input)
		{
			string errMsg = "failed to open input file, check filename and path: ";
			errMsg += fileName2;

			throw invalid_argument(errMsg);
		}

		string temp;
		int wordCount = 0;

		/************************************
		 *********** Probing Hash ***********
		 ************************************/


		timeBegin = clock();

		while (dictionary >> temp)
		{
			wordCount++;
		}

		//cout << "there are this many words: " << wordCount << endl;
		ProbingHash z(wordCount);

		dictionary.clear();
		dictionary.seekg(0, ios::beg);


		while (dictionary >> temp)
		{
			z.insertItem(temp);
		}

		while (input >> temp)
		{
			//cout << "read: " << temp << endl;
			if (isdigit(temp[0]))
			{
				bool allNumber = true;
				for (unsigned int i = 1; i < temp.size(); i++)
				{
					if (!isdigit(temp[i]))
					{
						allNumber = false;
					}
				}
				if (!allNumber)
				{
					//cout << temp << endl;
					if (!z.findItem(temp))
					{
						//cout << "word not found: " << temp << endl;
						probeError++;
					}
				}
			}
			else if (ispunct(temp[temp.size() - 1]))
			{
				temp.erase(temp.size() - 1, 1);
				//cout << temp << endl;
				if (!z.findItem(temp))
				{
					//cout << "word not found: " << temp << endl;
					probeError++;
				}
			}
			else
			{
				//cout << temp << endl;
				if (!z.findItem(temp))
				{
					//cout << "word not found: " << temp << endl;
					probeError++;
				}
			}
		}
		timeEnd = clock();
		probingTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;

		//z.displayHash();


		dictionary.clear();
		dictionary.seekg(0, ios::beg);

		input.clear();
		input.seekg(0, ios::beg);


		/************************************
		 *********** Chaining Hash **********
		 ************************************/


		timeBegin = clock();

		ChainingHash k(wordCount);

		while (dictionary >> temp)
		{
			k.insertItem(temp);
		}


		while (input >> temp)
		{
			//cout << "read: " << temp << endl;
			if (isdigit(temp[0]))
			{
				bool allNumber = true;
				for (unsigned int i = 1; i < temp.size(); i++)
				{
					if (!isdigit(temp[i]))
					{
						allNumber = false;
					}
				}
				if (!allNumber)
				{
					//cout << temp << endl;
					if (!k.findItem(temp))
					{
						//cout << "word not found: " << temp << endl;
						chainingError++;
					}
				}
			}
			else if (ispunct(temp[temp.size() - 1]))
			{
				temp.erase(temp.size() - 1, 1);
				//cout << temp << endl;
				if (!k.findItem(temp))
				{
					//cout << "word not found: " << temp << endl;
					chainingError++;
				}
			}
			else
			{
				//cout << temp << endl;
				if (!k.findItem(temp))
				{
					//cout << "word not found: " << temp << endl;
					chainingError++;
				}
			}
		}
		timeEnd = clock();
		chainingTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;

		//k.displayHash();

		cout << "*****Probing hash******" << endl;
		cout << "Number of misspelled words (probing hash): " << probeError << endl;
		cout << "Total runtime (probing hash): " << probingTime << endl;
		cout << "*****Chaining hash*****" << endl;
		cout << "Number of misspelled words (chaining hash): " << chainingError << endl;
		cout << "Total runtime (chaining hash): " << chainingTime << endl;
		cout<< endl;

		if (probingTime > chainingTime)
			cout << "Chaining hash is faster." << endl;
		else
			cout << "Probing hash is faster." << endl;
	}
	catch(...) {
		cout << "unknown exception caught" << endl;
	}

	return 0;
}
