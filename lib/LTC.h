#ifndef DSLTC_H
#define DSLTC_H

#include <iostream>
#include <string>

#include "DangKy.h"

using namespace std;

const int DSLTC_MAX = 10000;

struct LTC {
    int maLTC;
    string maMH;
    string nienKhoa;
    int hocKy;
    int nhom;
    int min, max;
    bool huy;
    DsDangKy *dssv;

    LTC() {
        this->maLTC = 0;
        this->maMH = "";
        this->nienKhoa = "";
        this->hocKy = 0;
        this->nhom = 0;
        this->min = 0;
        this->max = 0;
        this->huy = false;
    }

    LTC(int maLTC, string maMH, string nienKhoa, int hocKy, int nhom, int min,
        int max, bool huy = false) {
        this->maLTC = maLTC;
        this->maMH = maMH;
        this->nienKhoa = nienKhoa;
        this->hocKy = hocKy;
        this->nhom = nhom;
        this->min = min;
        this->max = max;
        this->huy = huy;
    }

    string toString() {
        return to_string(maLTC) + "," + maMH + "," + nienKhoa + "," +
               to_string(hocKy) + "," + to_string(nhom) + "," + to_string(min) +
               "," + to_string(max) + "," + to_string(huy);
    }

    string getKey() {
        return maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
    }
};

class DsLTC {
   private:
    int currentMax, count;

   public:
    LTC *dsltc[DSLTC_MAX];

    DsLTC() {
        currentMax = 0;
        count = 0;
    }

    ~DsLTC() {
        for (int i = 0; i < count; i++) {
            delete dsltc[i];
        }
    }

    bool isEmpty() { return count == 0; }

    bool isFull() { return count == DSLTC_MAX; }

    LTC *search(string maMH, string nienKhoa, int hocKy, int nhom) {
        string key = maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
        for (int i = 0; i < count; i++) {
            if (dsltc[i]->getKey() == key) {
                return dsltc[i];
            }
        }
        return NULL;
    }

    int insert(string maMH, string nienKhoa, int hocKy, int nhom, int min,
               int max) {
        string key = maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
        if (count >= DSLTC_MAX) {
            return 0;
        }

        // check exist
        if (search(maMH, nienKhoa, hocKy, nhom) != NULL) {
            return 0;
        }

        // insert
        LTC *lop = new LTC(++currentMax, maMH, nienKhoa, hocKy, nhom, min, max);
        dsltc[count] = lop;
        count += 1;

        return 1;
    }

    int edit(int maLTC, string maMH, string nienKhoa, int hocKy, int nhom,
             int min, int max, bool huy) {
        // TODO: not implemented
        LTC *lop = search(maMH, nienKhoa, hocKy, nhom);

        if (lop == NULL) {
            return 0;
        }
        return 1;
    }

    int remove(string maMH, string nienKhoa, int hocKy, int nhom) {
        if (count == 0) {
            return 0;
        }

        string key = maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
        bool found = false;

        for (int i = 0; i < count; i++) {
            if (!found) {
                if (dsltc[i]->getKey() == key) {
                    found = true;
                    dsltc[i] = dsltc[i + 1];
                }
            } else {
                dsltc[i] = dsltc[i + 1];
            }
        }
        if (found) {
            delete dsltc[count--];
        }
        return found;
    }

    void print() {
        cout << "\n\tTraverse DSLTC:\n";
        if (count == 0) {
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << i << ": " << dsltc[i]->toString() << endl;
        }
    }

    void write() {
        ofstream fileWriter("./build/data/monhoc.csv");

        if (fileWriter.is_open()) {
            // save currentMax and count
            fileWriter << currentMax << "," << count << endl;

            // TODO: write DSSV on new lines
            for (int i = 0; i < count; i++) {
                fileWriter << dsltc[i]->toString() << endl;
            }
        }
        fileWriter.close();
    }
};

void testDSLTC(DsLTC &ds) {
    ds.insert("3", "21-22", 2, 1, 1, 100);
    ds.insert("2", "22-23", 2, 1, 1, 100);
    ds.insert("3", "20-21", 2, 1, 1, 100);
    ds.insert("4", "20-21", 2, 1, 1, 123);
    ds.print();

    LTC *a = ds.search("3", "20-21", 2, 1);
    if (a) a->max = 999;
    ds.remove("2", "22-23", 2, 1);
    ds.print();
}

#endif
