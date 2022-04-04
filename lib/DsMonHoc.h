#ifndef DSMH_H
#define DSMH_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "MonHoc.h"
#include "Helper.h"

using namespace std;

class DsMonHoc {
   public:
    DsMonHoc();
    ~DsMonHoc();

    void insert(string ms, string ten, int sltclt, int sltcth);
    void update(string msOld, string ten, int sltclt, int sltcth, string msNew);
    void remove(string ms);
    MonHoc *search(string ms);
    bool isEmpty();
    int getSize();
    void read();
    void write();
    void toArray(MonHoc *arr[]);

    // debugging
    void displayPostOrder();
    void displayInOrder();

   private:
    NodeMonHoc *root;
    int getHeight(NodeMonHoc *root);
    int getSize(NodeMonHoc *root);
    bool isBalanced(NodeMonHoc *root);
    int balanceFactor(NodeMonHoc *root);
    NodeMonHoc *emptyTree(NodeMonHoc *root);
    NodeMonHoc *search(NodeMonHoc *root, string ms);

    void traverseInOrder(NodeMonHoc *root);
    void traversePostOrder(NodeMonHoc *root);

    NodeMonHoc *insertNode(NodeMonHoc *root, MonHoc &m);
    NodeMonHoc *findLeft(NodeMonHoc *root);
    NodeMonHoc *removeNode(NodeMonHoc *root, string ms);

    NodeMonHoc *RotateRight(NodeMonHoc *n2);
    NodeMonHoc *RotateLeft(NodeMonHoc *n2);
    NodeMonHoc *RotateLR(NodeMonHoc *n3);
    NodeMonHoc *RotateRL(NodeMonHoc *n3);

    NodeMonHoc *readFromFile(NodeMonHoc *root, ifstream &reader);
    void writeToFile(NodeMonHoc *root, ofstream &writer);
    void addNodeToArray(NodeMonHoc *root, MonHoc *arr[], int &index);
};

// public
DsMonHoc::DsMonHoc() { root = NULL; }

DsMonHoc::~DsMonHoc() { root = emptyTree(root); }

void DsMonHoc::insert(string ms, string ten, int sltclt, int sltcth) {
    MonHoc m(ms, ten, sltclt, sltcth);

    root = insertNode(root, m);
}

void DsMonHoc::update(string msOld, string ten, int sltclt, int sltcth,
                      string msNew) {
    if (msOld == msNew) {
        MonHoc *m = search(msOld);

        if (m == NULL) return;

        m->ten = ten;
        m->sltclt = sltclt;
        m->sltcth = sltcth;
    } else {
        remove(msOld);
        insert(msNew, ten, sltclt, sltcth);
    }
}

void DsMonHoc::remove(string ms) { root = removeNode(root, ms); }

MonHoc *DsMonHoc::search(string ms) { return &search(root, ms)->monhoc; }

void DsMonHoc::displayInOrder() {
    cout << "\nDisplay inorder\n";
    traverseInOrder(root);
}

void DsMonHoc::displayPostOrder() {
    cout << "\nDisplay postorder\n";
    traversePostOrder(root);
}

bool DsMonHoc::isEmpty() { return root != NULL; }

int DsMonHoc::getSize() { return getSize(root); }

void DsMonHoc::toArray(MonHoc *arr[]) {
    int index = 0;
    addNodeToArray(root, arr, index);
}

void DsMonHoc::read() {
    ifstream fileReader("./build/data/monhoc.csv");

    if (fileReader.is_open()) {
        root = readFromFile(root, fileReader);
    }
    fileReader.close();
}

void DsMonHoc::write() {
    ofstream fileWriter("./build/data/monhoc.csv");

    if (fileWriter.is_open()) {
        writeToFile(root, fileWriter);
    }

    fileWriter.close();
}

// private
// get tree height
int DsMonHoc::getHeight(NodeMonHoc *root) {
    if (root == NULL)
        return -1;
    else {
        return max(getHeight(root->left), getHeight(root->right)) + 1;
    }
}

// get node count
int DsMonHoc::getSize(NodeMonHoc *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + getSize(root->left) + getSize(root->right);
}

bool DsMonHoc::isBalanced(NodeMonHoc *root) {
    if (root == NULL) {
        return true;
    } else {
        return abs(getHeight(root->left) - getHeight(root->right)) > 1;
    }
}

int DsMonHoc::balanceFactor(NodeMonHoc *root) {
    return getHeight(root->left) - getHeight(root->right);
}

void DsMonHoc::traverseInOrder(NodeMonHoc *root) {
    if (root != NULL) {
        traverseInOrder(root->left);
        cout << root->monhoc.toString()
             << " Height: " << to_string(root->height) << endl;
        if (root->left) {
            cout << "\tleft child: " << root->left->monhoc.toString()
                 << " Height: " << to_string(root->left->height) << endl;
        }
        if (root->right) {
            cout << "\tright child: " << root->right->monhoc.toString()
                 << " Height: " << to_string(root->right->height) << endl;
        }
        traverseInOrder(root->right);
    }
}

void DsMonHoc::traversePostOrder(NodeMonHoc *root) {
    if (root != NULL) {
        cout << root->monhoc.toString()
             << " Height: " << to_string(root->height) << endl;
        if (root->left) {
            cout << "\tleft: " << root->left->monhoc.toString()
                 << " Height: " << to_string(root->left->height) << endl;
        }
        if (root->right) {
            cout << "\tright: " << root->right->monhoc.toString()
                 << " Height: " << to_string(root->right->height) << endl;
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
    } else if (m.ms < root->monhoc.ms) {
        root->left = insertNode(root->left, m);
    } else if (m.ms > root->monhoc.ms) {
        root->right = insertNode(root->right, m);
    }

    int balance = balanceFactor(root);

    // left heavier than right
    if (balance > 1) {
        if (m.ms < root->left->monhoc.ms) {
            root = RotateRight(root);
        } else {
            root = RotateLR(root);
        }
    } else if (balance < -1) {
        if (m.ms < root->right->monhoc.ms) {
            root = RotateRL(root);
        } else {
            root = RotateLeft(root);
        }
    }
    return root;
}

NodeMonHoc *DsMonHoc::findLeft(NodeMonHoc *root) {
    if (root == NULL) {
        return NULL;
    } else if (root->left == NULL) {
        return root;
    } else {
        return findLeft(root->left);
    }
}

NodeMonHoc *DsMonHoc::removeNode(NodeMonHoc *root, string ms) {
    NodeMonHoc *temp;

    if (root == NULL) {
        return NULL;
    } else if (ms < root->monhoc.ms) {
        root->left = removeNode(root->left, ms);
    } else if (ms > root->monhoc.ms) {
        root->right = removeNode(root->right, ms);
    } else if (root->left && root->right) {
        temp = findLeft(root->right);
        root->monhoc = temp->monhoc;
        root->right = removeNode(root->right, root->monhoc.ms);
    } else {
        temp = root;
        if (root->left == NULL)
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        delete temp;
    }

    int balance = balanceFactor(root);

    if (balance > 1) {
        // if (ms < root->left->monhoc.ms) {
        //     root = RotateRight(root);
        // } else {
        //     root = RotateLR(root);
        // }
    } else if (balance < -1) {
        // if (ms < root->right->monhoc.ms) {
        //     root = RotateRL(root);
        // } else {
        //     root = RotateLeft(root);
        // }
    }
    return root;
}

NodeMonHoc *DsMonHoc::RotateLeft(NodeMonHoc *n1) {
    cout << "left rotate\n";

    NodeMonHoc *n2 = n1->right;
    n1->right = n2->left;
    n2->left = n1;
    return n2;
}

NodeMonHoc *DsMonHoc::RotateRight(NodeMonHoc *n3) {
    cout << "right rotate\n";

    NodeMonHoc *n2 = n3->left;
    n3->left = n2->right;
    n2->right = n3;
    return n2;
}

NodeMonHoc *DsMonHoc::RotateLR(NodeMonHoc *n3) {
    cout << "lr rotate\n";

    n3->left = RotateLeft(n3->left);
    return RotateRight(n3);
}

NodeMonHoc *DsMonHoc::RotateRL(NodeMonHoc *n3) {
    cout << "rl rotate\n";

    n3->right = RotateRight(n3->right);
    return RotateLeft(n3);
}

NodeMonHoc *DsMonHoc::readFromFile(NodeMonHoc *root, ifstream &reader) {
    string line;
    string data[4] = {""};
    int index;
    string temp;

    while (getline(reader, line)) {
        index = 0;
        data[0] = "";
        data[1] = "";
        data[2] = "";
        data[3] = "";

        temp = "";

        // read every character to find ','
        for (unsigned i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                data[index] = temp;
                temp = "";
                index++;
            } else if (i == line.size() - 1) {
                // if end of line => last string
                temp += line[i];
                data[index] = temp;
            } else {
                temp += line[i];
            }
        }
        MonHoc m(data[0], data[1], stoi(data[2]), stoi(data[3]));
        root = insertNode(root, m);
    }
    return root;
}

void DsMonHoc::writeToFile(NodeMonHoc *root, ofstream &writer) {
    // write pre-order
    if (root != NULL) {
        writer << root->monhoc.toString() << endl;
        writeToFile(root->left, writer);
        writeToFile(root->right, writer);
    }
}

void DsMonHoc::addNodeToArray(NodeMonHoc *root, MonHoc *array[], int &index) {
    if (root == NULL) {
        return;
    }
    addNodeToArray(root->left, array, index);

    array[index] = &root->monhoc;
    index++;
    addNodeToArray(root->right, array, index);
}

void testDSMH(DsMonHoc &ds) {
    ds.read();

    ds.displayPostOrder();
    // ds.update("6", "MONHOC EDIT", 2, 1);
    // MonHoc *m = ds.search("6");

    // ds.displayPostOrder();

    // int len = ds.getSize();
    // cout << "Number of mh: " << len << endl;

    // MonHoc *arr[len];
    // ds.toArray(arr);

    // for (unsigned i = 0; i < len; i++) {
    //     cout << arr[i]->toString() << endl;
    // }

    // arr[2]->ten = "FUCK FUCK";

    // ds.displayPostOrder();
}

#endif
