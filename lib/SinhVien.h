#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct SinhVien {
    string maSV;
    string ho;
    string ten;
    string phai;
    string soDT;
    string maLop;

    SinhVien() {
        maSV = "";
        ho = "";
        ten = "";
        phai = "";
        soDT = "";
        maLop = "";
    }

    SinhVien(string maSV, string ho, string ten, string phai, string soDT,
             string maLop) {
        this->maSV = maSV;
        this->ho = ho;
        this->ten = ten;
        this->phai = phai;
        this->soDT = soDT;
        this->maLop = maLop;
    }

    string toString() {
        return maSV + "," + ho + "," + ten + "," + phai + "," + soDT + "," +
               maLop;
    }
};

struct NodeSinhVien {
    SinhVien sinhVien;
    NodeSinhVien *next;

    NodeSinhVien() { next = NULL; }
};

typedef NodeSinhVien *PTRSinhVien;

struct DangKy {
    string maSV;
    float diem;
    bool huyDK;
};

class DSSV {
   private:
    PTRSinhVien First;

   public:
    int dem;
    DSSV();
    ~DSSV();

    void duyet();
    int insertFirst(string maSV, string ho, string ten, string phai,
                    string soDT, string maLop);
    int insertAfter(string maGoc, string maSV, string ho, string ten,
                    string phai, string soDT, string maLop);
};

DSSV::DSSV() {
    First = NULL;
    dem = 0;
}

DSSV::~DSSV() {
    PTRSinhVien p;
    while (First != NULL) {
        p = First;
        First = First->next;
        delete p;
    }
    delete First;
}

// DsSinhVien:DsSinhVien(){}
int DSSV::insertFirst(string maSV, string ho, string ten, string phai,
                      string soDT, string maLop) {
    SinhVien sv(maSV, ho, ten, phai, soDT, maLop);

    PTRSinhVien p = new NodeSinhVien;
    p->sinhVien = sv;
    p->next = First;
    First = p;
    dem++;
    return 1;
}

int DSSV::insertAfter(string maGoc, string maSV, string ho, string ten,
                      string phai, string soDT, string maLop) {
    if (First == NULL) {
        return 0;
    }
    // TODO: tim PTRSinhVien p voi maGoc, roi insert sau do
    PTRSinhVien p = NULL;
    // PTRSinhVien p = timkiem(maGoc);

    SinhVien sv(maSV, ho, ten, phai, soDT, maLop);

    PTRSinhVien q = new NodeSinhVien;
    q->sinhVien = sv;
    q->next = p->next;
    p->next = q;

    dem++;
    return 1;
}

void DSSV::duyet() {
    PTRSinhVien p;
    cout << "\n\tDuyet dssv:\n";
    for (p = First; p != NULL; p = p->next) {
        cout << p->sinhVien.toString() << endl;
    }
}

void testDSSV(DSSV &ds) {
    ds.insertFirst("1", "A", "N", "nam", "2", "524");
    ds.insertFirst("2", "B", "N", "nam", "21", "234");
    ds.insertFirst("3", "C", "N", "nam", "3", "523");
    ds.insertFirst("4", "D", "N", "nam", "23", "34");

    ds.duyet();
    cout << "So luong sinh vien: " << ds.dem;
}

#endif