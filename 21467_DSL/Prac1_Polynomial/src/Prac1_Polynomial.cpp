#include <iostream>
using namespace std;

class Node
{
public:
    int coef;
    int exp;
    Node *next, *prev;

    Node()
    {
        coef = 0;
        exp = 0;
        next = nullptr;
        prev = nullptr;
    }

    Node(int c, int e) : coef(c), exp(e), next(nullptr), prev(nullptr) {}

    friend class Poly;
};

class Poly
{
private:
    Node *head;

public:
    Poly()
    {
        head = new Node();
        head->prev = head;
    }

    Node* createNode();
    void insertNode();
    void display();
};

Node* Poly::createNode()
{
    cout << "\nInside createNode\n";
    int c, e;
    cout << "\nEnter Coefficient: ";
    cin >> c;
    cout << "\nEnter Exponent: ";
    cin >> e;

    Node *newNode = new Node(c, e);
    return newNode;
}

void Poly::insertNode()
{
    int totalTerms;

    cout << "\nEnter how many terms you want to enter: ";
    cin >> totalTerms;

    for (int i = 0; i < totalTerms; i++)
    {
        Node *newTerm = createNode();

        // Insert the new node in the sorted position based on exponent
        Node *temp = head->next;
        while (temp != head && temp->exp > newTerm->exp) // Find where to insert
        {
            temp = temp->next;
        }

        // Insert new node
        newTerm->next = temp;
        newTerm->prev = temp->prev;
        temp->prev->next = newTerm;
        temp->prev = newTerm;
    }

    display();
}

void Poly::display()
{
    cout << "\nPolynomial List: \n";
    Node *temp = head->next;  // Skip the dummy head node

    if (temp == head) // Check if the list is empty
    {
        cout << "The list is empty!" << endl;
        return;
    }

    while (temp != head)
    {
        cout << temp->coef << "x^" << temp->exp;
        if (temp->next != head)
        {
            cout << " + ";
        }
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    Poly obj;
    obj.insertNode();
    return 0;
}
