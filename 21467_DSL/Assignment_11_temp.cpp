#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNumber;
    string name;
    string division;
    string address;

    void getDetails() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        getline(cin, division);
        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display() const {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

void addStudent() {
    Student student;
    student.getDetails();
    ofstream outFile("students.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    outFile << student.rollNumber << endl;
    outFile << student.name << endl;
    outFile << student.division << endl;
    outFile << student.address << endl;
    outFile.close();
    cout << "Student record added successfully." << endl;
}

void deleteStudent(int rollNumber) {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Error opening file." << endl;
        return;
    }
    Student student;
    bool found = false;
    while (inFile >> student.rollNumber) {
        inFile.ignore();
        getline(inFile, student.name);
        getline(inFile, student.division);
        getline(inFile, student.address);
        if (student.rollNumber == rollNumber) {
            found = true;
            cout << "Deleted record: " << endl;
            student.display();
        } else {
            outFile << student.rollNumber << endl;
            outFile << student.name << endl;
            outFile << student.division << endl;
            outFile << student.address << endl;
        }
    }
    inFile.close();
    outFile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (!found) {
        cout << "No record found with Roll Number: " << rollNumber << endl;
    } else {
        cout << "Record deleted successfully." << endl;
    }
}

void displayStudent(int rollNumber) {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "Error opening file." << endl;
        return;
    }
    Student student;
    bool found = false;
    while (inFile >> student.rollNumber) {
        inFile.ignore();
        getline(inFile, student.name);
        getline(inFile, student.division);
        getline(inFile, student.address);
        if (student.rollNumber == rollNumber) {
            found = true;
            student.display();
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "No record found with Roll Number: " << rollNumber << endl;
    }
}

int main() {
    int choice, rollNumber;
    while (true) {
        cout << "\nStudent Information System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            cout << "Enter Roll Number to delete: ";
            cin >> rollNumber;
            deleteStudent(rollNumber);
            break;
        case 3:
            cout << "Enter Roll Number to display: ";
            cin >> rollNumber;
            displayStudent(rollNumber);
            break;
        case 4:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}
