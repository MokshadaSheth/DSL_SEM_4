#include <iostream>
#include <climits>
#include <string>
#include <vector>
using namespace std;

class node {
    string data;
    node *lchild, *rchild;

public:
    node(string x) {
        data = x;
        lchild = rchild = NULL;
    }
    friend class obst;
};

class obst {
    node *root;
    vector<string> keys;

public:
    obst() { root = NULL; }

    double w[100][100], c[100][100];
    int r[100][100];

    void calculate_wt(const double *p, const double *q, int n);
    node *create_tree(int i, int j);
    void build_tree(const vector<string> &keyList, const double *p, const double *q, int n);

    void print_tree(node *root) {
        if (root == NULL)
            return;
        cout << root->data << " ";
        print_tree(root->lchild);
        print_tree(root->rchild);
    }

    void print() {
        cout << "Optimal BST structure: ";
        print_tree(root);
        cout << endl;
    }
};

void obst::calculate_wt(const double *p, const double *q, int n) {
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        w[i][i + 1] = q[i] + q[i + 1] + p[i];
        c[i][i + 1] = w[i][i + 1];
        r[i][i + 1] = i;
    }

    for (int m = 2; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j - 1] + q[j];
            c[i][j] = INT_MAX;

            for (int k = r[i][j - 1]; k <= r[i + 1][j]; k++) { // Knuth's optimization
                double cost = c[i][k] + c[k + 1][j];
                if (cost < c[i][j]) {
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
            c[i][j] += w[i][j];
        }
    }
}

node *obst::create_tree(int i, int j) {
    if (i == j)
        return NULL;

    int k = r[i][j];
    node *t = new node(keys[k]);
    t->lchild = create_tree(i, k);
    t->rchild = create_tree(k + 1, j);
    return t;
}

void obst::build_tree(const vector<string> &keyList, const double *p, const double *q, int n) {
    keys = keyList;
    calculate_wt(p, q, n);
    root = create_tree(0, n);
}

int main() {
    obst tree;
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    vector<string> keys(n);
    vector<double> p(n), q(n + 1);

    cout << "Enter the keys:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Key " << i + 1 << ": ";
        cin >> keys[i];
    }

    cout << "Enter the probabilities for successful searches:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P(" << keys[i] << "): ";
        cin >> p[i];
    }

    cout << "Enter the probabilities for unsuccessful searches:" << endl;
    for (int i = 0; i <= n; i++) {
        if (i == 0)
            cout << "q(0): before first key: ";
        else if (i == n)
            cout << "q(" << n << "): after last key: ";
        else
            cout << "q(" << i << "): between " << keys[i - 1] << " and " << keys[i] << ": ";
        cin >> q[i];
    }

    tree.build_tree(keys, p.data(), q.data(), n);
    tree.print();

    return 0;
}
