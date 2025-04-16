#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Student {
    int rollNumber;
    char name[50];
    char address[100];
};

void writeRecords(const string& filename) {
    fstream file;
    file.open(filename, ios::in | ios::out | ios::binary | ios::trunc);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student student;
    int numberOfRecords;
    cout << "Enter number of records to write: ";
    cin >> numberOfRecords;

    for (int i = 0; i < numberOfRecords; i++) {
        cout << "Enter Roll Number: ";
        cin >> student.rollNumber;
        cin.ignore();  
        cout << "Enter Name: ";
        cin.getline(student.name, 50);
        cout << "Enter Address: ";
        cin.getline(student.address, 100);
        file.seekp(student.rollNumber * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }

    file.close();
    cout << "Records written successfully." << endl;
}

void readRecords(const string& filename) {
    fstream file;
    file.open(filename, ios::in | ios::binary);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    int rollNumber;
    cout << "Enter Roll Number to read: ";
    cin >> rollNumber;

    Student student;
    file.seekg(rollNumber * sizeof(Student), ios::beg);
    file.read(reinterpret_cast<char*>(&student), sizeof(Student));

    if (student.rollNumber != 0) {
        cout << "Roll Number: " << student.rollNumber << endl;
        cout << "Name: " << student.name << endl;
        cout << "Address: " << student.address << endl;
    } else {
        cout << "No record found with Roll Number: " << rollNumber << endl;
    }

    file.close();
}

void deleteRecord(const string& filename) {
    fstream file;
    file.open(filename, ios::in | ios::out | ios::binary);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    int rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;

    Student student;
    file.seekg(rollNumber * sizeof(Student), ios::beg);
    file.read(reinterpret_cast<char*>(&student), sizeof(Student));

    if (student.rollNumber != 0) {
        student.rollNumber = 0;
        file.seekp(rollNumber * sizeof(Student), ios::beg);
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        cout << "Record with Roll Number " << rollNumber << " deleted successfully." << endl;
    } else {
        cout << "No record found with Roll Number: " << rollNumber << endl;
    }

    file.close();
}

void displayMenu() {
    cout << "\nStudent Records Menu:" << endl;
    cout << "1. Write Records" << endl;
    cout << "2. Read Records" << endl;
    cout << "3. Delete Records" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    string filename;
    cout << "Enter the filename for student records: ";
    cin >> filename;  

    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                writeRecords(filename);
                break;
            case 2:
                readRecords(filename);
                break;
            case 3:
                deleteRecord(filename);
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 4);

    return 0;
}
