#ifndef DSMH_H
#define DSMH_H

#include <algorithm>
#include <fstream>
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
    void displayLevelOrder();

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
    bool traverseLevel(NodeMonHoc *root, int level);

    NodeMonHoc *insertNode(NodeMonHoc *root, MonHoc m);
    NodeMonHoc *findLeft(NodeMonHoc *root);
    NodeMonHoc *removeNode(NodeMonHoc *root, string ms);

    NodeMonHoc *RotateRight(NodeMonHoc *n2);
    NodeMonHoc *RotateLeft(NodeMonHoc *n2);
    NodeMonHoc *RotateLR(NodeMonHoc *n3);
    NodeMonHoc *RotateRL(NodeMonHoc *n3);

    NodeMonHoc *readFromFile(NodeMonHoc *root, ifstream &reader);
    bool writeToFile(NodeMonHoc *root, ofstream &writer, int level);
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
    cout << "\n\tDisplay inorder\n";
    traverseInOrder(root);
}

void DsMonHoc::displayPostOrder() {
    cout << "\n\tDisplay postorder\n";
    traversePostOrder(root);
}

void DsMonHoc::displayLevelOrder() {
    cout << "\n\tDisplay level order\n";
    // start from level 1 — till the height of the tree
    int level = 1;

    // run till printLevel() returns false
    while (traverseLevel(root, level)) {
        level++;
    }
}

bool DsMonHoc::isEmpty() { return root != NULL; }

int DsMonHoc::getSize() { return getSize(root); }

void DsMonHoc::toArray(MonHoc *arr[]) {
    int index = 0;
    addNodeToArray(root, arr, index);
}

void DsMonHoc::read() {
    ifstream reader("./build/data/monhoc.csv");

    if (reader.is_open()) {
        root = readFromFile(root, reader);
    }
    reader.close();
}

void DsMonHoc::write() {
    ofstream writer("./build/data/monhoc.csv");

    // if (fileWriter.is_open()) {
    //     writeToFile(root, fileWriter);
    // }
    int level = 1;

    // run till printLevel() returns false
    while (writeToFile(root, writer, level)) {
        level++;
    }
    writer.close();
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

bool DsMonHoc::traverseLevel(NodeMonHoc *root, int level) {
    if (root == NULL) {
        return false;
    }

    if (level == 1) {
        cout << root->monhoc.toString() << endl;

        // return true if at least one node is present at a given level
        return true;
    }

    bool left = traverseLevel(root->left, level - 1);
    bool right = traverseLevel(root->right, level - 1);

    return left || right;
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

NodeMonHoc *DsMonHoc::insertNode(NodeMonHoc *root, MonHoc m) {
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
        // node has 2 child
        temp = findLeft(root->right);
        root->monhoc = temp->monhoc;
        root->right = removeNode(root->right, root->monhoc.ms);
    } else {
        // node is leaf or has only 1 child
        temp = root;
        if (root->left == NULL) {
            root = root->right;
        } else {
            root = root->left;
        }
        delete temp;
        return root;
    }

    // balancing
    int balance = balanceFactor(root);

    if (balance > 1) {
        if (balanceFactor(root->left) >= 0) {
            // left left
            root = RotateRight(root);
        } else {
            // left right
            root = RotateLR(root);
        }
    } else if (balance < -1) {
        if (balanceFactor(root->right) <= 0) {
            // right right
            root = RotateLeft(root);
        } else {
            // right left
            root = RotateRL(root);
        }
    }
    return root;
}

NodeMonHoc *DsMonHoc::RotateLeft(NodeMonHoc *n1) {
    NodeMonHoc *n2 = n1->right;
    n1->right = n2->left;
    n2->left = n1;
    return n2;
}

NodeMonHoc *DsMonHoc::RotateRight(NodeMonHoc *n3) {
    NodeMonHoc *n2 = n3->left;
    n3->left = n2->right;
    n2->right = n3;
    return n2;
}

NodeMonHoc *DsMonHoc::RotateLR(NodeMonHoc *n3) {
    n3->left = RotateLeft(n3->left);
    return RotateRight(n3);
}

NodeMonHoc *DsMonHoc::RotateRL(NodeMonHoc *n3) {
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

bool DsMonHoc::writeToFile(NodeMonHoc *root, ofstream &writer, int level) {
    // write level order
    // if (root != NULL) {
    //     writer << root->monhoc.toString() << endl;
    //     writeToFile(root->left, writer);
    //     writeToFile(root->right, writer);
    // }

    if (root == NULL) {
        return false;
    }

    if (level == 1) {
        writer << root->monhoc.toString() << endl;

        // return true if at least one node is present at a given level
        return true;
    }

    bool left = writeToFile(root->left, writer, level - 1);
    bool right = writeToFile(root->right, writer, level - 1);

    return left || right;
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
    ds.write();

    ds.displayLevelOrder();
    // ds.update("6", "HDH123", 2, 1, "6");
    // MonHoc *m = ds.search("6");
    // ds.remove("3");

    // ds.displayPostOrder();

    // ds.displayPostOrder();

    // int len = ds.getSize();
    // cout << "Number of mh: " << len << endl;

    // MonHoc *arr[len];
    // ds.toArray(arr);

    // for (unsigned i = 0; i < len; i++) {
    //     cout << arr[i]->toString() << endl;
    // }
}

#endif
