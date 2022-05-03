#ifndef DSDANGKY_H
#define DSDANGKY_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct DangKy {
    string maSV;
    float diem;
    bool huy;

    DangKy() {
        maSV = "";
        diem = 0;
        huy = false;
    }

    DangKy(string maSV, float diem, bool huy = false) {
        this->maSV = maSV;
        this->diem = diem;
        this->huy = huy;
    }

    string toString() {
        stringstream ss;
        ss << diem;
        return maSV + "|" + ss.str() + "|" + to_string(huy);
    }
};

struct NodeDangKy {
    DangKy dk;
    NodeDangKy *next;

    NodeDangKy() { next = NULL; }
};

class DsDangKy {
   private:
    NodeDangKy *first;

   public:
    int count;
    DsDangKy();
    ~DsDangKy();

    void print();
    int insertFirst(string maSV, float diem, bool huy = false);
    int insertOrder(string maSV, float diem, bool huy = false);
    int getSoSVDK();
    DangKy *search(string maSV);
    int remove(string maSV);
    string toString();
    void toArray(DangKy *list[], int &length);
    void filterDSDK(DangKy *list[], int &length);
    void replaceMaSV(string oldId, string newId);
};

DsDangKy::DsDangKy() {
    first = NULL;
    count = 0;
}

DsDangKy::~DsDangKy() {
    NodeDangKy *temp;
    while (first != NULL) {
        temp = first;
        first = first->next;
        delete temp;
    }
    delete first;
}

int DsDangKy::insertFirst(string maSV, float diem, bool huy) {
    DangKy dk(maSV, diem, huy);

    NodeDangKy *ndk = new NodeDangKy;
    ndk->dk = DangKy(maSV, diem, huy);
    ndk->next = first;
    first = ndk;

    count++;
    return 1;
}

int DsDangKy::insertOrder(string maSV, float diem, bool huy) {
    if (first == NULL || first->dk.maSV > maSV) {
        return insertFirst(maSV, diem, huy);
    } else if (first->dk.maSV == maSV) {
        // neu masv trung first - edit huy
        first->dk.huy = huy;
        // first->dk.diem = diem;

        return 2;
    }

    NodeDangKy *current = first->next;
    NodeDangKy *prev = first;

    while (current != NULL) {
        if (current->dk.maSV == maSV) {
            // set huy
            current->dk.huy = false;
            // current->dk.diem = diem;

            return 2;
        } else if (current->dk.maSV > maSV) {
            break;
        }
        prev = current;
        current = current->next;
    }

    NodeDangKy *ndk = new NodeDangKy;
    ndk->dk = DangKy(maSV, diem, huy);

    prev->next = ndk;
    ndk->next = current;

    count++;
    return 1;
}

int DsDangKy::getSoSVDK() {
    int c = 0;

    for (NodeDangKy *temp = first; temp != NULL; temp = temp->next) {
        if (temp->dk.huy == false) {
            c++;
        }
    }
    return c;
}

DangKy *DsDangKy::search(string maSV) {
    NodeDangKy *temp;
    for (temp = first; temp != NULL; temp = temp->next) {
        if (temp->dk.maSV == maSV) {
            return &temp->dk;
        }
    }
    return NULL;
}

int DsDangKy::remove(string maSV) {
    if (first == NULL) {
        return 0;
    } else if (first->dk.maSV == maSV) {
        NodeDangKy *current = first;
        first = first->next;
        delete current;
        count--;
        return 1;
    }

    NodeDangKy *current = first->next;
    NodeDangKy *prev = first;
    bool found = false;

    while (current != NULL) {
        if (current->dk.maSV == maSV) {
            found = true;
            break;
        }
        prev = current;
        current = current->next;
    }
    if (found) {
        prev->next = current->next;
        delete current;
        count--;

        return 1;
    } else {
        return 0;
    }
}

void DsDangKy::print() {
    cout << "\n\tDsDangKy, count: " << count << endl;

    for (NodeDangKy *temp = first; temp != NULL; temp = temp->next) {
        cout << temp->dk.toString() << endl;
    }
}

string DsDangKy::toString() {
    string result = "";
    for (NodeDangKy *temp = first; temp != NULL; temp = temp->next) {
        result += temp->dk.toString() + "\n";
    }
    return result;
}

void DsDangKy::toArray(DangKy *list[], int &length) {
    length = 0;

    for (NodeDangKy *temp = first; temp != NULL; temp = temp->next) {
        list[length++] = &temp->dk;
    }
}

void DsDangKy::filterDSDK(DangKy *list[], int &length) {
    length = 0;

    for (NodeDangKy *temp = first; temp != NULL; temp = temp->next) {
        if (temp->dk.huy == 0) {
            list[length++] = &temp->dk;
        }
    }
}

void DsDangKy::replaceMaSV(string oldId, string newId) {
    for (NodeDangKy *temp = first; temp != NULL; temp = temp->next) {
        if (temp->dk.maSV == oldId) {
            temp->dk.maSV = newId;
        }
    }
}


void printDSDK(DangKy *list[], int length) {
    cout << "\nPrinting dsdk\n";

    for (int i = 0; i < length; i++) {
        cout << list[i]->toString() << endl;
    }
}

void testDSDK() {
    DsDangKy dsdk;
    dsdk.insertOrder("N1", 2, 1);
    dsdk.insertOrder("N1", 1, 0);
    dsdk.insertOrder("N1", 1, 1);

    dsdk.insertOrder("N2", 7, 1);
    dsdk.insertOrder("N2", 2, 1);
    dsdk.insertOrder("N3", 4, 1);
    dsdk.print();

    // dsdk.remove("N1");
    // DangKy *d = dsdk.search("N6");
    // d->maSV = "123123";
    // dsdk.print();
}

#endif