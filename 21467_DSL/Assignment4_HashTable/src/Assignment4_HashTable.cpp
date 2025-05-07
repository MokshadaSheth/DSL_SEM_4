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

#include<iostream>
#include<vector>
using namespace std;

int Tsize = 10;
class TableStruct
{
    long long num;
    string name;
    bool occupied;

    public:
        TableStruct()
        {
            num = -1;
            name = "";
            occupied = false;
        }
        TableStruct(long long n, string na)
        {
            num = n;
            name = na;
            occupied = true;
        }

        friend class HashTable;
};

class HashTable
{
    vector <TableStruct> withoutReplace;
    vector <TableStruct> withReplce;

    int hashFunction(long long num)
    {
        return num%Tsize;
    }

    public:
        HashTable()
        {
            withoutReplace.resize(Tsize);
            withReplce.resize(Tsize);
        }
        void insertD();
        void insertWithout(long long n, string name);
        void insertWith(long long n, string name);
        void search();
        int searchD(long long n, vector<TableStruct> &t);
};

void HashTable :: insertD()
{
    long long n;
    string name;

    cout<<"\nEnter number: ";
    cin>>n;
    cout<<"Enter name: ";
    cin>>name;

    cout<<"\nInserting Data in Without Replacement:\n";
    insertWithout(n,name);
    cout<<"\nInsert Data in With Repalcement: \n";
    insertWith(n,name);
}

void HashTable :: insertWithout(long long n, string name)
{
    int comparisons = 1;
    int index = hashFunction(n);
    int original = index;

    while(withoutReplace[index].occupied)
    {
        index = (index + 1) % Tsize;
        comparisons++;
        if(index == original)
        {
            cout<<"\nHashTable is already Full";
            return;
        }
    }

    withoutReplace[index] = TableStruct(n,name);
    cout<<"\nTotal comparisons used: "<<comparisons;
}
void HashTable :: insertWith(long long n, string name)
{
    int comparisons = 1;
    int index = hashFunction(n);
    int original = index;
    bool flag = false;
    TableStruct temp;

    if(withReplce[index].occupied)
    {   //Already an element
        int existing = hashFunction(withReplce[index].num);

        if(index != existing) 
        {
            //Wrong ele so replace
            cout<<"\nReplacing Element\n";
            temp = withReplce[index];
            withReplce[index] = TableStruct(n,name);

            index = (index+1)%Tsize; 
            flag = true;
        }
        while(withReplce[index].occupied)
        {
            index = (index + 1) % Tsize;
            comparisons++;
            if(index == existing)
            {
                cout<<"\nHashTable is already Full";
                return;
            }
        }
        if(flag)
            withReplce[index] = temp;
        else
            withReplce[index] = TableStruct(n,name);

        cout<<"\nComparison: "<<comparisons;
    }
    else{
        //Slot is free
        withReplce[index] = TableStruct(n,name);
        cout<<"\nComparison: "<<comparisons;
    }
}

void HashTable :: search()
{
    cout<<"\nEnter number to be searched: ";
    long long n;
    cin>>n;

    cout<<"\nSearching in Without Replacement:\n";
    int ans = searchD(n,withoutReplace);
    if(ans == -1)
    {
        cout<<"\nNot in HashTable";
    }
    else{
        cout<<"--------------------------------\nWithout Repelacement Comparisons:"<<ans;
    }
    cout<<"\nSearching in With Replace: \n";
    ans = searchD(n,withReplce);
    if(ans == -1)
    {
        cout<<"\nNot in HashTable";
    }
    else{
        cout<<"--------------------------------\nWith Repelacement Comparisons:"<<ans;
    }
}

int HashTable  :: searchD(long long n, vector<TableStruct> &t)
{
    int index = hashFunction(n);
    int org = index;
    int comparison = 1;


    if(t[index].num == n)
    {
        return comparison;
    }
    else{
        while(t[index].occupied)
        {
            index = (index + 1) % Tsize;
            comparison++;
            if(index == org)
            {
                cout<<"\nNo such number";
                return -1;
            }
            if(t[index].num == n)
            {
                return comparison;
            }
        }
        return -1;
    }
}

int main()
{
    int choice;
    bool t = true;
    HashTable obj;
    while(t)
    {
        cout<<"\n1.Insert Data\n2.Search Data\n3.Delete";
        cout<<"\nEnter choice code:";
        cin>>choice;

        switch(choice)
        {
            case 1:
                obj.insertD();
                break;
            case 2:
                obj.search();
                break;
            case 3:
                cout<<"\nByee";
                t = false;
                break;
            default:
                cout<<"\nInvalid ip";
                break;
        }
    }
}
