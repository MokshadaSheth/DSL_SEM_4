#include<iostream>
#include<fstream>
using namespace std;

class Student
{
    int rollNo;
    string name;
    string division;
    string address;
    fstream file;
    public:
        Student()
        {
            file.open("Temp.txt", ios::in | ios::out | ios::app);
            if(!file)
            {
                cout<<"\nError opening file...";
            }
            else{
                 cout<<"File created successfully..\n";
            }
        }
        Student(string fname)
        {
            file.open(fname, ios::in | ios::out | ios::app);
            if(!file)
            {
                cout<<"\nError opening file...";
            }
            else{
                 cout<<"File created successfully..\n";
            }
        }
        ~Student()
        {
            cout<<"\nClosing file...";
            file.close();
        }

        void writeData();
        void getData();
        void readR();
        void deleteR();
        void displaySpecific();
};

void Student :: getData()
{
    cout<<"\nEnter Roll No. Name Division Address: ";
    cin>>rollNo>>name>>division>>address;
}
void Student :: writeData()
{
    getData();
    file<<rollNo<<endl<<name<<endl<<division<<endl<<address<<endl;
}
void Student::readR()
{
    int r;
    string n, d, a;

    file.clear();         // Clear EOF flag
    file.seekg(0);        // Go to beginning

    while (file >> r >> n >> d >> a)
    {
        cout << "\nName: " << n
             << "\nRollNo.: " << r
             << "\nDivision: " << d
             << "\nAddress: " << a << endl;
    }
}
void Student :: displaySpecific()
{
    int r,roll;
    string n,d,a;
    cout<<"\nEnter roll number to display data of: ";
    cin>>r;
    file.clear();
    file.seekg(0);

    while(file>>roll>>n>>d>>a)
    {
        if(r == roll)
        {
            cout << "\nName: " << n
             << "\nRollNo.: " << r
             << "\nDivision: " << d
             << "\nAddress: " << a << endl;
             return;
        }
    }
    cout<<"\nRecord not found...!\n";
}
void Student :: deleteR()
{
    ofstream out;
    out.open("Temp.txt", ios::out | ios::trunc);

    int r,roll;
    string n,d,a;
    bool found = false;
    cout<<"\nEnter rollnumber to delete: ";
    cin>>r;

    file.clear();
    file.seekg(0);

    while(file>>roll>>n>>d>>a)
    {
        if(r == roll)
        {
            found = true;
        }
        else{
            out<<roll<<endl<<n<<endl<<d<<endl<<a<<endl;
        }
    }
    if(!found)
    {
        cout<<"\nRecord not found\n";
        remove("Temp.txt");
        
    }
    else{
        cout<<"\nDeletion succesfull";
        file.close();
        remove("Data.txt");
        rename("Temp.txt","Data.txt");
        file.open("Data.txt", ios::in | ios::out | ios::app);
    }
}
int main()
{
    Student obj("Data.txt");
    obj.writeData();
    
    // obj.displaySpecific();
    obj.deleteR();
    obj.readR();
    return 0;
}