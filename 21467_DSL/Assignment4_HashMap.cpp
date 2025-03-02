#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int Tsize = 10; // Hash table size

class tableStruct {
    long long number;
    string name;
    bool occupied;

public:
    tableStruct() {
        number = -1;
        name = "0";
        occupied = false;
    }

    tableStruct(long long n, string na) {
        number = n;
        name = na;
        occupied = true;
    }

    friend class HashTable;
};

class HashTable {
    vector<tableStruct> table;

    int hashFunction(long long number) {
        return number % Tsize; // Simple modulo hash function
    }

public:
    HashTable() {
        table.resize(Tsize); // Initialize hash table
    }

    // Linear Probing Without Replacement
    void insertWithoutReplacement(long long number, string name) {
        int index = hashFunction(number);
        int originalIndex = index;
        int comparisons = 1;

        // Find an empty slot
        while (table[index].occupied) {
            index = (index + 1) % Tsize;
            comparisons++;
            if (index == originalIndex) { // Full table condition
                cout << "Hash table is full!\n";
                return;
            }
        }

        table[index] = tableStruct(number, name);
        cout << "Inserted " << name << " at index " << index << " with " << comparisons << " comparisons.\n";
    }

    // Linear Probing With Replacement
    void insertWithReplacement(long long number, string name) {
        int index = hashFunction(number);
        int originalIndex = index;
        int comparisons = 1;

        // If the position is occupied
        if (table[index].occupied) {
            int existingIndex = hashFunction(table[index].number);

            if (existingIndex != index) { // Replace if it doesn't belong here
                tableStruct temp = table[index]; // Store the old entry
                table[index] = tableStruct(number, name); // Insert new entry
                
                cout << "Replaced " << temp.name << " with " << name << " at index " << index << "\n";

                // Find a new slot for the displaced entry
                int newIndex = (index + 1) % Tsize;
                while (table[newIndex].occupied) {
                    newIndex = (newIndex + 1) % Tsize;
                    if (newIndex == index) { // Prevent infinite loop if table is full
                        cout << "Hash table is full!\n";
                        return;
                    }
                }
                table[newIndex] = temp; // Place the old entry in a new location
                cout << "Moved " << temp.name << " to index " << newIndex << "\n";
            }
        } else {
            table[index] = tableStruct(number, name);
            cout << "Inserted " << name << " at index " << index << " with " << comparisons << " comparisons.\n";
        }
    }

    // Search function
    void search(long long number) {
        int index = hashFunction(number);
        int originalIndex = index;
        int comparisons = 1;

        while (table[index].occupied) {
            if (table[index].number == number) {
                cout << "Found " << table[index].name << " at index " << index << " with " << comparisons << " comparisons.\n";
                return;
            }
            index = (index + 1) % Tsize;
            comparisons++;

            if (index == originalIndex) {
                break; // Table fully searched
            }
        }

        cout << "Phone number " << number << " not found after " << comparisons << " comparisons.\n";
    }

    // Display the hash table
    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < Tsize; i++) {
            if (table[i].occupied)
                cout << i << " --> " << table[i].number << " (" << table[i].name << ")\n";
            else
                cout << i << " --> Empty\n";
        }
    }
};

int main() {
    HashTable hashTable;

    cout << "Choose collision handling technique:\n";
    cout << "1. Linear Probing without Replacement\n";
    cout << "2. Linear Probing with Replacement\n";
    
    int choice;
    cin >> choice;

    int n;
    cout << "Enter number of records to insert: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        long long phone;
        string name;
        cout << "Enter phone number and name: ";
        cin >> phone >> ws;
        getline(cin, name);

        if (choice == 1) {
            hashTable.insertWithoutReplacement(phone, name);
        } else {
            hashTable.insertWithReplacement(phone, name);
        }
    }

    hashTable.display();

    cout << "\nEnter a number to search (or -1 to exit): ";
    while (true) {
        long long phone;
        cin >> phone;
        if (phone == -1) break;
        hashTable.search(phone);
        cout << "\nEnter another number to search (or -1 to exit): ";
    }

    return 0;
}
