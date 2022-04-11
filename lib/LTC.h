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

    LTC *search(string maMH, string nienKhoa, int hocKy, int nhom) {
        string key = maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
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
        // string key = maMH + nienKhoa + to_string(hocKy) + to_string(nhom);

        // check exist
        // if (search(maMH, nienKhoa, hocKy, nhom) != NULL) {
        //     return 0;
        // }
        LTC *lop = NULL;

        // insert with auto increment on
        if (maLTC == -1) {
            lop = new LTC(++currentMax, maMH, nienKhoa, hocKy, nhom, min, max,
                          huy);
            dsltc[count] = lop;
        } else {
            lop = new LTC(maLTC, maMH, nienKhoa, hocKy, nhom, min, max, huy);
            dsltc[count] = lop;
        }
        count += 1;
        return lop;
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
        ifstream reader("./build/data/loptinchi.csv");
        if (reader.is_open()) {
            string temp;
            string line;
            int index = 0;

            // read currentMax
            getline(reader, line);
            currentMax = stoi(line);

            while (getline(reader, line)) {
                index = 0;
                temp = "";

                string ltcData[9] = {""};
                string dkData[3] = {""};

                // read data for ltc ','
                for (unsigned i = 0; i < line.size(); i++) {
                    if (line[i] == ',') {
                        ltcData[index] = temp;
                        temp = "";
                        index++;
                    } else if (i == line.size() - 1) {
                        // if end of line => last string
                        temp += line[i];
                        ltcData[index] = temp;
                    } else {
                        temp += line[i];
                    }
                }
                int dsdkLength = stoi(ltcData[8]);

                LTC *lop =
                    insert(ltcData[1], ltcData[2], stoi(ltcData[3]),
                           stoi(ltcData[4]), stoi(ltcData[5]), stoi(ltcData[6]),
                           stoi(ltcData[7]), stoi(ltcData[0]));
                // insert success
                if (lop) {
                    // get dsdk
                    for (int i = 0; i < dsdkLength; i++) {
                        getline(reader, line);
                        temp = "";
                        index = 0;

                        for (unsigned j = 0; j < line.size(); j++) {
                            if (line[j] == ',') {
                                dkData[index] = temp;
                                temp = "";
                                index++;
                            } else if (j == line.size() - 1) {
                                // if end of line => last string
                                temp += line[j];
                                dkData[index] = temp;
                            } else {
                                temp += line[j];
                            }
                        }
                        lop->dsdk->insertOrder(dkData[0], stoi(dkData[1]), stoi(dkData[2]));
                    }
                }
            }
        }
        reader.close();
    }
};

void testDSLTC(DsLTC &ds, DsDangKy &dsdk) {
    // ds.insert("INT2", "21-22", 2, 1, 1, 100, 0, -1);
    // ds.insert("INT3", "22-23", 2, 1, 1, 100, 0, -1);
    // ds.insert("ENG1", "20-21", 2, 1, 1, 100, true, -1);
    // ds.insert("ENG2", "20-21", 2, 1, 1, 123, 0, -1);
    // ds.print();

    // LTC *a = ds.search("3", "20-21", 2, 1);
    // if (a) a->max = 999;
    // ds.dsltc[1]->dsdk = &dsdk;
    // ds.remove("2", "22-23", 2, 1);
    // ds.print();
    // ds.write();
}

void testDSLTC(DsLTC &ds) {
    // ds.write();
    ds.read();
    ds.print();
}

#endif
