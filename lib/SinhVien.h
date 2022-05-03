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
        return maSV + "|" + ho + "|" + ten + "|" + phai + "|" + soDT + "|" +
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
    int xoa(string mssv);
    PTRSinhVien search(string maSV);
    int ghiFile();
    int docFile();
    void toArray(SinhVien *list[], int &dsLength);
    void filterSinhVienTheoMaLop(SinhVien *list[], int &dsLength, string maLop);
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

int DSSV::xoa(string mssv) {
    if (First == NULL) {
        return 0;
    } else if (First->sinhVien.maSV == mssv) {
        NodeSinhVien *current = First;
        First = First->next;
        delete current;
        dem--;
        return 1;
    }

    NodeSinhVien *current = First->next;
    NodeSinhVien *prev = First;
    bool found = false;

    while (current != NULL) {
        if (current->sinhVien.maSV == mssv) {
            found = true;
            break;
        }
        prev = current;
        current = current->next;
    }
    if (found) {
        prev->next = current->next;
        delete current;
        dem--;

        return 1;
    } else {
        return 0;
    }
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
        string delim = "|";
        string line;

        while (getline(reader, line)) {
            string data[6] = {""};

            int index = 0;
            size_t start = 0;
            size_t end = line.find(delim, start);

            while (end != string::npos) {
                data[index] = line.substr(start, end - start);
                start = end + delim.length();
                end = line.find(delim, start);
                index++;
            }
            data[index] = line.substr(start, end);

            insertOrder(data[0], data[1], data[2], data[3], data[4], data[5]);
        }
    } else {
        return 0;
    }
    reader.close();
    return 1;
}

void DSSV::toArray(SinhVien *list[], int &len) {
    len = 0;

    for (NodeSinhVien *p = First; p != NULL; p = p->next) {
        list[len++] = &p->sinhVien;
    }
}
void DSSV::filterSinhVienTheoMaLop(SinhVien *list[], int &listLength,
                                   string maLop) {
    listLength = 0;

    for (NodeSinhVien *p = First; p != NULL; p = p->next) {
        if (p->sinhVien.maLop == maLop) {
            // empty
            if (listLength == 0) {
                list[listLength++] = &p->sinhVien;
            } else {
                SinhVien *temp = NULL;
                string tenho = p->sinhVien.ten + p->sinhVien.ho;
                list[listLength] = &p->sinhVien;

                for (int i = listLength - 1; i >= 0; i--) {
                    if (list[i]->ten + list[i]->ho < tenho) {
                        break;
                    }
                    temp = list[i + 1];
                    list[i + 1] = list[i];
                    list[i] = temp;
                }
                listLength++;
            }
        }
    }
}

void testDSSV(DSSV &dssv) {
    dssv.docFile();
    dssv.duyet();
    dssv.ghiFile();

    // int dsLength = 0;

    // SinhVien *list[dssv.dem];
    // // dssv.duyet();

    // dssv.filterSinhVienTheoMaLop(list, dsLength, "D18CQCP02");

    // for (int i = 0; i < dsLength; i++) {
    //     cout << list[i]->toString() << endl;
    // }
}

#endif