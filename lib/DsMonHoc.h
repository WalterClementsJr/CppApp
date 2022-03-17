#include <iostream>
#include <string>

#include "Helper.h"
#include "MonHoc.h"

using namespace std;

class DsMonHoc {
   public:
    DsMonHoc();
    ~DsMonHoc();

    void insert(string ms, string ten, int sltclt, int sltcth);
    void remove(string ms);
    void update(MonHoc mh);
    void read();
    void write();

    // debugging
    void displayPostOrder();
    void displayInOrder();

   private:
    NodeMonHoc *root;
    int getHeight(NodeMonHoc *root);
    bool isBalanced(NodeMonHoc *root);
    NodeMonHoc *emptyTree(NodeMonHoc *root);
    NodeMonHoc *search(NodeMonHoc *root, string cmnd);
    void traverseInOrder(NodeMonHoc *root);
    void traversePostOrder(NodeMonHoc *root);
    NodeMonHoc *insertNode(NodeMonHoc *root, MonHoc &m);
    // NodeMonHoc *updateNode(NodeMonHoc *root, MonHoc &m);
    // NodeMonHoc *removeNode(NodeMonHoc *root, string ms);
    // NodeMonHoc *readFromFile(NodeMonHoc *root, ifstream *reader);
    // void writeToFile(NodeMonHoc *root, ofstream *writer);
};

// public
DsMonHoc::DsMonHoc() { root = nullptr; }

DsMonHoc::~DsMonHoc() { root = emptyTree(root); }

void DsMonHoc::insert(string ms, string ten, int sltclt, int sltcth) {
    MonHoc m(ms, ten, sltclt, sltcth);

    root = insertNode(root, m);
}

void DsMonHoc::remove(string ms) {}

void DsMonHoc::update(MonHoc m) {}

void DsMonHoc::displayInOrder() {
    cout << "\nDisplay inorder\n";
    traverseInOrder(root);
}

void DsMonHoc::displayPostOrder() {
    cout << "\nDisplay postorder\n";
    traversePostOrder(root);
}

// private
int DsMonHoc::getHeight(NodeMonHoc *root) {
    if (root == NULL)
        return -1;
    else {
        return max(getHeight(root->left), getHeight(root->right)) + 1;
    }
}

bool DsMonHoc::isBalanced(NodeMonHoc *root) {
    if (root == NULL) {
        return true;
    } else {
        return abs(getHeight(root->left) - getHeight(root->right)) > 1;
    }
}

void DsMonHoc::traverseInOrder(NodeMonHoc *root) {
    if (root != NULL) {
        traverseInOrder(root->left);
        cout << root->monhoc.toString() << endl;
        if (root->left) {
            cout << "\tleft child: " << root->left->monhoc.toString() << endl;
        }
        if (root->right) {
            cout << "\tright child: " << root->right->monhoc.toString() << endl;
        }
        traverseInOrder(root->right);
    }
}

void DsMonHoc::traversePostOrder(NodeMonHoc *root) {
    if (root != NULL) {
        cout << root->monhoc.toString() << endl;
        if (root->left) {
            cout << "\tleft: " << root->left->monhoc.toString() << endl;
        }
        if (root->right) {
            cout << "\tright: " << root->right->monhoc.toString() << endl;
        }
        traversePostOrder(root->left);
        traversePostOrder(root->right);
    }
}

// set all tree's nodes to null
NodeMonHoc *DsMonHoc::emptyTree(NodeMonHoc *root) {
    if (root == NULL) return NULL;

    emptyTree(root->left);
    emptyTree(root->right);

    return NULL;
}

NodeMonHoc *DsMonHoc::search(NodeMonHoc *root, string ms) {
    if (root == NULL)
        return NULL;
    else if (ms < root->monhoc.ms)
        return search(root->left, ms);
    else if (ms > root->monhoc.ms)
        return search(root->right, ms);
    else
        return root;
}

NodeMonHoc *DsMonHoc::insertNode(NodeMonHoc *root, MonHoc &m) {
    if (root == NULL) {
        root = new NodeMonHoc;
        root->monhoc = m;
    } else if (m.ms < root->monhoc.ms)
        root->left = insertNode(root->left, m);
    else if (m.ms > root->monhoc.ms)
        root->right = insertNode(root->right, m);

    return root;
}

// NodeMonHoc *DsMonHoc::removeNode(NodeMonHoc *root, string ms) {
    // NodeMonHoc *temp;

    // if (root == NULL)
    //     return NULL;
    // else if (ms < root->monhoc.ms)
    //     root->left = removeNode(root->left, ms);
    // else if (ms > root->monhoc.ms)
    //     root->right = removeNode(root->right, ms);
    // else if (root->left && root->right) {
    //     temp = findLeft(root->right);
    //     root->monhoc = temp->monhoc;
    //     root->right = removeNode(root->right, root->monhoc.ms);
    // } else {
    //     temp = root;
    //     if (root->left == NULL)
    //         root = root->right;
    //     else if (root->right == NULL)
    //         root = root->left;
    //     delete temp;
    // }
    // return root;
    // return NULL;
// }

void testDSMH() {
    DsMonHoc ds;
    ds.insert("6", "", 1, 1);
    ds.insert("4", "", 1, 1);
    ds.insert("3", "", 1, 1);
    ds.insert("5", "", 1, 1);
    ds.insert("8", "", 1, 1);
    ds.insert("7", "", 1, 1);
    ds.insert("9", "", 1, 1);

    ds.displayInOrder();
    ds.displayPostOrder();
}
