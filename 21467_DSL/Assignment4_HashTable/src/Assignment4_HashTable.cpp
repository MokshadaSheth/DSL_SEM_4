//============================================================================
// Name        : Assignment4_HashTable.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Consider telephone book database of N clients. Make use of
// a hash table implementation to quickly look up clients telephe number. Make use of
// linear probing with and without replacement. Compare required comparisons to find a
// set of telephone numbers.
//============================================================================

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int Tsize = 10;

class tableStruct
{
	long long number;
	string name;
	bool occupied;

public:
	tableStruct()
	{
		number = -1;
		name = "";
		occupied = false;
	}
	tableStruct(long long n, string name)
	{
		number = n;
		name = name;
		occupied = true;
	}
	friend class HashTable;
};

class HashTable
{
	vector<tableStruct> table1;
	vector<tableStruct> table;

	int hashFunction(long long number)
	{
		return number % Tsize;
	}

public:
	HashTable()
	{
		table.resize(Tsize);
		table1.resize(Tsize);
	}

	void insertData();
	void insertWithoutReplacement(long long n, string name);
	void insertWithReplacement(long long n, string name);
	void searchR();
	void searchInWithoutReplacement(long long n);
	void searchInWithReplacement(long long n);
};

void HashTable ::insertData()
{
	long long n;
	string name;
	cout << "\nEnter number: ";
	cin >> n;
	cout << "\nEnter name: ";
	cin >> name;
	cout << "\nInserting using Without Replacement...\n";
	insertWithoutReplacement(n, name);
	cout << "\nInserting using With Replacement...\n";
	insertWithReplacement(n, name);
}

void HashTable ::insertWithoutReplacement(long long n, string name)
{
	int index = hashFunction(n);
	int original_index = index;
	int comparisons = 1;

	while (table1[index].occupied)
	{
		index = (index + 1) % Tsize;
		comparisons++;

		if (index == original_index)
		{
			cout << "\nTable is full!!\n";
			return;
		}
	}
	table1[index] = tableStruct(n, name);
	cout << "\nComparisons: " << comparisons << " required to insert data\n";
	cout << "\nInserted " << name << " at index " << index << endl;
}

void HashTable ::insertWithReplacement(long long n, string name)
{
	int index = hashFunction(n);
	int original_index = index;
	int comparisons = 1;

	// If position occupied
	if (table[index].occupied)
	{
		int existingIndex = hashFunction(table[index].number);

		if (existingIndex != index)
		{
			// Replace the current data at that index
			tableStruct temp = table[index]; // Store existing
			table[index] = tableStruct(n, name);

			cout << "\nReplaced " << temp.name << " with " << name << endl;

			// Find new place
			int newIndex = (index + 1) % Tsize;
			comparisons++;
			while (table[newIndex].occupied)
			{
				newIndex = (newIndex + 1) % Tsize;
				comparisons++;
				if (newIndex == index)
				{
					cout << "\nHash Table is full!!";
					return;
				}
			}
			table[newIndex] = temp;
			cout << "\nMoved" << temp.name << " to index " << newIndex << endl;
		}
		else // existing is equal to index
		{
			int newIndex = (index + 1) % Tsize;
			comparisons++;
			while (table[newIndex].occupied)
			{
				newIndex = (newIndex + 1) % Tsize;
				comparisons++;
				if (newIndex == index)
				{
					cout << "\nHash Table is full!!";
					return;
				}
			}
			table[newIndex] = tableStruct(n, name);
			cout << "\nInserted " << name << " at index " << index << endl;
		}
	}
	else
	{
		table[index] = tableStruct(n, name);
		cout << "\nInserted " << name << " at index " << index << endl;
	}
	cout << "\nComparisons: " << comparisons << " to insert " << name << endl;
}
void HashTable ::searchR()
{
	long long n;
	cout << "\nEnter number to search: ";
	cin >> n;
	cout << "\nSearching in Without Replacement Table...\n";
	searchInWithoutReplacement(n);
	cout << "\nSearching in With Replacement Table...\n";
	searchInWithReplacement(n);
}
void HashTable ::searchInWithoutReplacement(long long n)
{
	int index = hashFunction(n);
	int comparisons = 1;
	int originalIndex = index;

	while (true)
	{
		if (table1[index].number == n)
		{
			cout << "\nFound at index " << index << " name: " << table1[index].name;
			cout << "Comparisons: " << comparisons << endl;
			return;
		}
		else
		{
			index = (index + 1) % Tsize;
			comparisons++;
			if (index == originalIndex)
			{
				cout << "\nNumber is not present in Hash Table\n";
				return;
			}
		}
	}
}
void HashTable ::searchInWithReplacement(long long n)
{
	int index = hashFunction(n);
	int comparisons = 1;
	int originalIndex = index;

	while (true)
	{
		if (table[index].number == n)
		{
			cout << "\nFound at index " << index << " name: " << table[index].name;
			cout << "Comparisons: " << comparisons << endl;
			return;
		}
		else
		{
			index = (index + 1) % Tsize;
			comparisons++;
			if (index == originalIndex)
			{
				cout << "\nNumber is not present in Hash Table\n";
				return;
			}
		}
	}
}

int main()
{
	int choice;
	HashTable obj;
	do
	{
		cout << "\n1.Insert Data\n2.Search number\n3.Exit\n\nEnter choice code: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			obj.insertData();
			break;
		case 2:
			obj.searchR();
			break;
		case 3:
			cout<<"\nByee";
			break;

		default:
			cout<<"\nInvalid ip";
			break;
		}

	} while (choice != 3);

	return 0;
}
