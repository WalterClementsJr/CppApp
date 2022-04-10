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
    DsDangKy *dsdk;

    LTC() {
        this->maLTC = 0;
        this->maMH = "";
        this->nienKhoa = "";
        this->hocKy = 0;
        this->nhom = 0;
        this->min = 0;
        this->max = 0;
        this->huy = false;

        dsdk = new DsDangKy;
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

        dsdk = new DsDangKy;
    }

    ~LTC() {
        delete dsdk;
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
        cout << "\n\tDSLTC, size: " << count << endl;
        for (int i = 0; i < count; i++) {
            cout << i << ": " << dsltc[i]->toString() << endl;
            if (dsltc[i]->dsdk->count > 0) {
                cout << "\n\t Dsdk\n";
                cout << dsltc[i]->dsdk->toString();
            }
        }
    }

    void write() {
        ofstream writer("./build/data/loptinchi.csv");

        if (writer.is_open()) {
            // write currentMax
            writer << currentMax << endl;

            // write LTC and dsdk on new lines
            for (int i = 0; i < count; i++) {
                LTC *temp = dsltc[i];
                // write data and number of DangKy in dsdk
                writer << temp->toString() << "," << temp->dsdk->count << endl;
                writer << temp->dsdk->toString();
            }
        }
        writer.close();
    }

    void read() {
        ifstream reader("./build/data/monhoc.csv");

        if (reader.is_open()) {
            // read currentMax

            // TODO: write DSSV on new lines
            for (int i = 0; i < count; i++) {
            }
        }
        reader.close();
    }
};

void testDSLTC(DsLTC &ds, DsDangKy &dsdk) {
    ds.insert("INT2", "21-22", 2, 1, 1, 100);
    ds.insert("INT3", "22-23", 2, 1, 1, 100);
    ds.insert("ENG1", "20-21", 2, 1, 1, 100);
    ds.insert("ENG2", "20-21", 2, 1, 1, 123);
    // ds.print();

    // LTC *a = ds.search("3", "20-21", 2, 1);
    // if (a) a->max = 999;
    ds.dsltc[0]->dsdk = &dsdk;
    // ds.remove("2", "22-23", 2, 1);
    ds.print();
    ds.write();

}

void testDSLTC(DsLTC &ds) {
    // ds.write();
}

#endif
