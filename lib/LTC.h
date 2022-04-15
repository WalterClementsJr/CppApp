#ifndef DSLTC_H
#define DSLTC_H

#include <fstream>
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
        this->maLTC = -1;
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

    ~LTC() { delete dsdk; }

    string toString() {
        return to_string(maLTC) + "|" + maMH + "|" + nienKhoa + "|" +
               to_string(hocKy) + "|" + to_string(nhom) + "|" + to_string(min) +
               "|" + to_string(max) + "|" + to_string(huy);
    }

    string getKey() {
        return maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
    }
};

class DsLTC {
   private:
    int currentMax;

   public:
    LTC *dsltc[DSLTC_MAX];
    int count;

    DsLTC() {
        currentMax = 0;
        count = 0;
    }

    ~DsLTC() {
        for (int i = 0; i < count; i++) {
            delete dsltc[i];
        }
        count = 0;
    }

    bool isEmpty() { return count == 0; }

    bool isFull() { return count == DSLTC_MAX; }

    LTC *search(string key) {
        // string key = maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
        for (int i = 0; i < count; i++) {
            if (dsltc[i]->getKey() == key) {
                return dsltc[i];
            }
        }
        return NULL;
    }

    LTC *insert(string maMH, string nienKhoa, int hocKy, int nhom, int min,
                int max, bool huy, int maLTC = -1) {
        if (count >= DSLTC_MAX) {
            return NULL;
        }
        LTC *lop = NULL;

        // insert with auto increment on
        if (maLTC == -1) {
            lop = new LTC(++currentMax, maMH, nienKhoa, hocKy, nhom, min, max,
                          huy);
            dsltc[count] = lop;
        } else {
            lop = new LTC(maLTC, maMH, nienKhoa, hocKy, nhom, min, max, huy);
            currentMax = currentMax > maLTC ? currentMax : maLTC;
            dsltc[count] = lop;
        }
        count++;
        return lop;
    }

    int remove(string key) {
        if (count == 0) {
            return 0;
        }
        bool found = false;

        for (int i = 0; i < count; i++) {
            if (!found) {
                if (dsltc[i]->getKey() == key) {
                    found = true;
                    delete dsltc[i];
                    dsltc[i] = dsltc[i + 1];
                }
            } else {
                dsltc[i] = dsltc[i + 1];
            }
        }

        if (found) {
            delete dsltc[count];
            count--;
        }
        return found;
    }

    void print() {
        cout << "\tDSLTC, size: " << count << endl;
        for (int i = 0; i < count; i++) {
            cout << dsltc[i]->toString() << endl;
            if (dsltc[i]->dsdk->count > 0) {
                cout << "\n\tDsdk\n";
                cout << dsltc[i]->dsdk->toString() << endl;
            }
        }
    }

    void write() {
        ofstream writer("./build/data/loptinchi.csv");

        if (writer.is_open()) {
            // write LTC and dsdk on new lines
            for (int i = 0; i < count; i++) {
                LTC *temp = dsltc[i];
                // write data and number of DangKy in dsdk
                writer << temp->toString() << "|" << temp->dsdk->count << endl;
                writer << temp->dsdk->toString();
            }
        }
        writer.close();
    }

    void read() {
        ifstream reader("./build/data/loptinchi.csv");

        if (!reader.is_open()) {
            return;
        }
        string line;
        string delim = "|";

        while (getline(reader, line)) {
            string ltcData[9] = {""};

            int index = 0;
            size_t start = 0;
            size_t end = line.find(delim, start);

            while (end != string::npos) {
                ltcData[index] = line.substr(start, end - start);
                start = end + delim.length();
                end = line.find(delim, start);
                index++;
            }

            ltcData[index] = line.substr(start, end);

            int dsdkLength = stoi(ltcData[index]);

            LTC *lop =
                insert(ltcData[1], ltcData[2], stoi(ltcData[3]),
                       stoi(ltcData[4]), stoi(ltcData[5]), stoi(ltcData[6]),
                       stoi(ltcData[7]), stoi(ltcData[0]));
            // endl; insert success
            if (lop) {
                // get dsdk
                for (int i = 0; i < dsdkLength; i++) {
                    string dkData[3] = {""};

                    getline(reader, line);
                    index = 0;
                    start = 0;
                    end = line.find(delim, start);

                    while (end != string::npos) {
                        dkData[index] = line.substr(start, end - start);
                        start = end + delim.length();
                        end = line.find(delim, start);
                        index++;
                    }
                    dkData[index] = line.substr(start, end);

                    lop->dsdk->insertOrder(dkData[0], stoi(dkData[1]),
                                           stoi(dkData[2]));
                }
            }
        }
        reader.close();
    }
};

void testDSLTC(DsLTC &ds, DsDangKy &dsdk) {
    // ds.insert("INT2", "21-22", 2, 1, 1, 100, 0, -1);
    // ds.insert("INT3", "22-23", 2, 1, 1, 100, 0, -1);
    // ds.insert("INT0", "20-21", 2, 1, 1, 100, true, -1);
    // ds.insert("INT1", "20-21", 2, 1, 1, 123, 0, -1);
    // ds.print();

    // LTC *a = ds.search("3", "20-21", 2, 1);
    // if (a) a->max = 999;
    // ds.dsltc[1]->dsdk = &dsdk;
    // ds.remove("2", "22-23", 2, 1);
    // ds.print();
    // ds.write();
}

void testDSLTC(DsLTC &dsltc) {
    dsltc.read();
    dsltc.print();

    // dsltc.insert("INT2", "22-23", 2, 1, 12, 100, 0, -1);
    // dsltc.insert("INT3", "22-23", 2, 1, 1, 100, 0, -1);
    // dsltc.insert("INT0", "20-21", 2, 1, 1, 100, true, -1);
    // dsltc.insert("INT1", "20-21", 2, 1, 1, 123, 0, -1);
    // LTC *ltc = dsltc.search("INT022-2321");

    // dsltc.remove("INT022-2321");
    // dsltc.print();

    // ds.write();
}

#endif
