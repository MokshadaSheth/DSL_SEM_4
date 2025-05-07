#include <iostream>
#include <string>
using namespace std;

class AVLTree {
private:
    class Node {
    public:
        string keyword;
        string meaning;
        Node* left;
        Node* right;

        Node(string k, string m) {
            keyword = k;
            meaning = m;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {
        cleanup(root);
    }

    void addKeyword() {
        string keyword, meaning;
        cout << "Enter keyword: ";
        cin.ignore();
        getline(cin, keyword);
        cout << "Enter meaning: ";
        getline(cin, meaning);

        Node* newNode = new Node(keyword, meaning);
        root = insertKeyword(root, newNode);
    }

    Node* insertKeyword(Node* root, Node* newNode) {
        if (root == nullptr) {
            return newNode;
        } 
        else if (newNode->keyword < root->keyword) {
            root->left = insertKeyword(root->left, newNode);
        } 
        else if (newNode->keyword > root->keyword) {
            root->right = insertKeyword(root->right, newNode);
        } 
        else {  //Means same keyword that is update
            root->meaning = newNode->meaning;
            delete newNode;
            return root;
        }

        return balance(root);
    }

    Node* balance(Node* root) {
        int balanceFactor = getBalanceFactor(root);

        if (balanceFactor > 1) {
            if (getBalanceFactor(root->left) < 0) {
                root->left = rotateLeft(root->left);
            }
            return rotateRight(root);
        }

        if (balanceFactor < -1) {
            if (getBalanceFactor(root->right) > 0) {
                root->right = rotateRight(root->right);
            }
            return rotateLeft(root);
        }

        return root;
    }

    int getBalanceFactor(Node* root) {
        if (root == nullptr)
            return 0;
        return getHeight(root->left) - getHeight(root->right);
    }

    int getHeight(Node* root) {
        if (root == nullptr)
            return 0;
        return max(getHeight(root->left), getHeight(root->right)) + 1;
    }

    Node* rotateLeft(Node* root) {
        Node* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        return newRoot;
    }

    Node* rotateRight(Node* root) {
        Node* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        return newRoot;
    }

    void searchKeyword() {
        string keyword;
        cout << "Enter the keyword to search: ";
        cin.ignore();
        getline(cin, keyword);

        Node* result = searchNode(root, keyword);
        if (result) {
            cout << "Keyword found! Meaning: " << result->meaning << endl;
        } else {
            cout << "Keyword not found!" << endl;
        }
    }

    Node* searchNode(Node* root, const string& keyword) {
        if (root == nullptr)
            return nullptr;

        if (root->keyword == keyword)
            return root;
        if (keyword < root->keyword)
            return searchNode(root->left, keyword);
        return searchNode(root->right, keyword);
    }

    void deleteKeyword() {
        string keyword;
        cout << "Enter the keyword to delete: ";
        cin.ignore();
        getline(cin, keyword);

        root = deleteNode(root, keyword);
    }

    Node* deleteNode(Node* root, const string& keyword) {
        if (root == nullptr)
            return root;

        if (keyword < root->keyword) {
            root->left = deleteNode(root->left, keyword);
        } 
        else if (keyword > root->keyword) {
            root->right = deleteNode(root->right, keyword);
        } 
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } 
            else {
                Node* temp = getMinNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        return balance(root);
    }

    Node* getMinNode(Node* root) {
        while (root->left != nullptr) root = root->left;
        return root;
    }

    void display() {
        cout << "\nKeywords in Ascending Order:\n";
        displaySorted(root, true);
        cout << "\nKeywords in Descending Order:\n";
        displaySorted(root, false);
    }

    void displaySorted(Node* root, bool ascending) {
        if (root == nullptr) return;

        if (ascending) {
            displaySorted(root->left, ascending);
            cout << root->keyword << ": " << root->meaning << endl;
            displaySorted(root->right, ascending);
        } 
        else {
            displaySorted(root->right, ascending);
            cout << root->keyword << ": " << root->meaning << endl;
            displaySorted(root->left, ascending);
        }
    }

    void cleanup(Node* root) {
        if (root != nullptr) {
            cleanup(root->left);
            cleanup(root->right);
            delete root;
        }
    }
};

int main() {
    AVLTree dictionary;
    char continueChoice;
    int choice;

    do {
        cout << "\n===== AVL Tree Dictionary Menu =====\n";
        cout << "1. Add Keyword\n";
        cout << "2. Display Keywords\n";
        cout << "3. Search Keyword\n";
        cout << "4. Delete Keyword\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                dictionary.addKeyword();
                break;
            case 2:
                dictionary.display();
                break;
            case 3:
                dictionary.searchKeyword();
                break;
            case 4:
                dictionary.deleteKeyword();
                break;
            case 5:
                cout<<"\nBye!";
                break;
            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 5);

    return 0;
}
