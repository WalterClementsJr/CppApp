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
        return maSV + "," + ss.str() + "," + to_string(huy);
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
    int insertLast(string maSV, float diem, bool huy = false);
    int insertAfter(string maGoc, string maSV, float diem, bool huy = false);
    int insertOrder(string maSV, float diem, bool huy = false);
    DangKy *search(string maSV);
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

int DsDangKy::insertLast(string maSV, float diem, bool huy) {
    NodeDangKy *temp = first;

    while (temp != NULL) {
        temp = temp->next;
    }

    NodeDangKy *ndk = new NodeDangKy;
    ndk->dk = DangKy(maSV, diem, huy);

    temp = ndk;
    count++;
}

int DsDangKy::insertAfter(string maGoc, string maSV, float diem, bool huy) {
    if (first == NULL) {
        return 0;
    }
    // TODO:
    NodeDangKy *p = NULL;
    // NodeDangKy * p = search(maGoc);

    DangKy dk(maSV, diem, huy);

    NodeDangKy *ndk = new NodeDangKy;
    ndk->dk = dk;
    ndk->next = p->next;
    p->next = ndk;

    count++;
    return 1;
}

int DsDangKy::insertOrder(string maSV, float diem, bool huy) {
    DangKy dk(maSV, diem, huy);

    if (first == NULL) {
        first = new NodeDangKy;
        DangKy d(maSV, diem, huy);

        first->dk = d;
        count++;
        return 1;
    }
    NodeDangKy *temp = first;

    while (temp != NULL) {
        if (temp->dk.maSV > maSV) {
            break;
        }
        temp = temp->next;
    }

    NodeDangKy *ndk = new NodeDangKy;
    // DangKy dk(maSV, diem, huy);

    ndk->dk = DangKy(maSV, diem, huy);
    ndk->next = temp->next;
    temp->next = ndk;

    count++;
    return 1;
}

DangKy *DsDangKy::search(string maSV) {
    NodeDangKy *temp;
    for (temp = first; temp != NULL; temp = temp->next)
        if (temp->dk.maSV == maSV) {
            return &temp->dk;
        }
    return NULL;
}

void DsDangKy::print() {
    cout << "\n\tPrint DsDangKy:\n";

    for (NodeDangKy *temp = first; temp != NULL; temp = temp->next) {
        cout << temp->dk.toString() << endl;
    }
}

void testDSDK(DsDangKy &dsdk) {
    // dsdk.insertOrder("N1", 7, 1);
    // dsdk.insertLast("N3", 7, 1);
    // dsdk.insertOrder("N2", 7, 1);
    // dsdk.insertOrder("N5", 7, 1);

    dsdk.insertFirst("N1", 7, 1);
    dsdk.insertFirst("N2", 7, 1);
    dsdk.insertLast("N3", 7, 1);

    // dsdk.insertFirst("N3", 7, 1);
    // dsdk.insertFirst("N4", 7, 1);

    dsdk.print();
}

#endif