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
    int insertOrder(string maSV, string ho, string ten, string phai,
                    string soDT, string maLop);
    int ghiFile();
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

int DSSV::insertOrder(string maSV, string ho, string ten, string phai,
                      string soDT, string maLop) {
    if (First == NULL || First->sinhVien.maSV > maSV) {
        return insertFirst(maSV, ho, ten, phai, soDT, maLop);
    } else if (First->sinhVien.maSV == maSV) {
        // neu masv trung first -> return 0
        return 0;
    }

    PTRSinhVien current = First->next;
    PTRSinhVien prev = First;

    while (current != NULL) {
        // neu masv trung -> return 0
        if (current->sinhVien.maSV == maSV) {
            cout << "\n found trung \n";
            return 0;
        } else if (current->sinhVien.maSV > maSV) {
            break;
        }
        prev = current;
        current = current->next;
    }

    PTRSinhVien ndk = new NodeSinhVien;
    ndk->sinhVien = SinhVien(maSV, ho, ten, phai, soDT, maLop);

    prev->next = ndk;
    ndk->next = current;

    dem++;
    return 1;
}

void DSSV::duyet() {
    PTRSinhVien p;
    cout << "\n\tDuyet dssv, so sv: " << dem << endl;
    for (p = First; p != NULL; p = p->next) {
        cout << p->sinhVien.toString() << endl;
    }
}

int DSSV::ghiFile() {
    ofstream writer("./build/data/sinhvien.csv");
    if (writer.is_open()) {
        for (PTRSinhVien p = First; p != NULL; p = p->next) {
            writer << p->sinhVien.toString() << endl;
        }
    } else {
        return 0;
    }

    writer.close();
    return 1;
}

void testDSSV(DSSV &ds) {
    ds.insertOrder("2", "A", "N", "nam", "2", "524");
    ds.insertOrder("1", "B", "N", "nam", "21", "234");
    ds.insertOrder("1", "C", "N", "nam", "3", "523");
    ds.insertOrder("3", "D", "N", "nam", "23", "34");

    ds.duyet();
    // ds.ghiFile();
}

#endif