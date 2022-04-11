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
    PTRSinhVien search(string maSV);
    int ghiFile();
    int docFile();
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

PTRSinhVien DSSV::search(string maSV) {
    for (PTRSinhVien p = First; p != NULL; p = p->next) {
        if (p->sinhVien.maSV == maSV) {
            return p;
        }
    }
    return NULL;
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

int DSSV::docFile() {
    ifstream reader("./build/data/sinhvien.csv");

    if (reader.is_open()) {
        string line;
        int index;
        string temp;

        while (getline(reader, line)) {
            string data[6] = {""};
            index = 0;
            temp = "";

            for (unsigned i = 0; i < line.size(); i++) {
                if (line[i] == ',') {
                    data[index] = temp;
                    temp = "";
                    index++;
                } else if (i == line.size() - 1) {
                    temp += line[i];
                    data[index] = temp;
                } else {
                    temp += line[i];
                }
            }
            insertOrder(data[0], data[1], data[2], data[3], data[4], data[5]);
        }
    } else {
        return 0;
    }
    reader.close();
    return 1;
}

void testDSSV(DSSV &ds) {
    ds.docFile();
    ds.duyet();
    // ds.ghiFile();
}

#endif