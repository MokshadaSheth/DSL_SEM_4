// Direct Access Data in File

#include <iostream>
#include <fstream>
#include <cstring>
#include<set>
using namespace std;

class Student
{
    int rollNo;
    char name[50];
    char add[100];

public:
    Student()
    {
        rollNo = -1;
        name[0] = '\0';
        add[0] = '\0';
    }
    Student(int r, char n[], char a[])
    {
        rollNo = r;
        strcpy(name, n);
        strcpy(add, a);
    }
    friend class DirectFile;
};
class DirectFile
{
    fstream file;
    set <int> allRecords;
    int current = 0;

public:
    DirectFile()
    {
        file.open("Temp", ios::in | ios::out | ios::binary | ios::trunc);
        if (!file)
        {
            cout << "\nError creating Temp.txt\n";
        }
        else
        {
            cout << "\nFile Created Successfully";
        }
    }
    DirectFile(string FileName)
    { // Note: Using trunc or app is imp
        file.open(FileName, ios::in | ios::out | ios::binary | ios::trunc);
        if (!file)
        {
            cout << "\nError creating " << FileName << endl;
        }
        else
        {
            cout << "\nFile Created Successfully";
        }
    }
    ~DirectFile()
    {
        cout << "\nIn Destructor Closing File..";
        file.close();
    }
    Student takeIP();
    void writeRecord();
    void readRecord();
    void displayRecord(Student obj);
    void deleteRecord();
    void displayAll();
};
Student DirectFile ::takeIP()
{
    Student obj;
    cout << "\nEnter rollNo,name, address: ";
    cin >> obj.rollNo >> obj.name >> obj.add;
    allRecords.insert(obj.rollNo);
    return obj;
}
void DirectFile ::writeRecord()
{
    Student data = takeIP();
    // To write seekp
    file.seekp(data.rollNo * sizeof(Student), ios::beg); // IMP
    file.write((char *)(&data), sizeof(Student));
}
void DirectFile ::readRecord()
{
    cout << "\nEnter roll number to read: ";
    int r;
    cin >> r;

    file.seekg(r * sizeof(Student), ios::beg);
    Student readData;
    file.read((char *)(&readData), sizeof(Student));

    if (readData.rollNo == r)
    {
        displayRecord(readData);
    }
    else
    {
        cout << "\nRecord Does not exists!\n";
    }
}
void DirectFile ::deleteRecord()
{
    int r;
    cout << "\nEnter roll number to be deleted: ";
    cin >> r;
    Student deleteData;
    file.seekg(r * sizeof(Student), ios ::beg);
    file.read((char *)(&deleteData), sizeof(Student));

    if (deleteData.rollNo == r)
    {
        file.seekp(r * sizeof(Student), ios ::beg);
        deleteData.rollNo = -1;
        file.write((char *)(&deleteData), sizeof(Student));
        allRecords.erase(r);
        cout << "\nDeletion Successfull...";
    }
    else
    {
        cout << "\nRecord Does not exist...\n";
    }
}
void DirectFile ::displayRecord(Student obj)
{
    cout << "\nName: " << obj.name << "\nRoll no.: " << obj.rollNo << "\nAddress:" << obj.add << endl;
}
void DirectFile ::displayAll()
{
    Student readData;
    for (auto it : allRecords)
    {
        file.seekg(it * sizeof(Student), ios::beg);
        file.read((char *)(&readData), sizeof(Student));

        displayRecord(readData);
    }
}
int main()
{
    // DirectFile obj;
    DirectFile obj1("Student"); // Note: Do not use .txt extension
    int choice;
    do
    {
        cout << "\n1.Write Record\n2.Read Record\n3.Delete Record\n4.Display All Records\n5.Exit";
        cout << "\nEnter choice code: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            obj1.writeRecord();
            break;
        case 2:
            obj1.readRecord();
            break;
        case 3:
            obj1.deleteRecord();
            break;
        case 4:
            obj1.displayAll();
            break;
        case 5:
            cout << "\nExiting...\n";
            break;
        default:
            cout << "\nInvalid Ip";
            break;
        }
    } while (choice != 5);

    return 0;
}