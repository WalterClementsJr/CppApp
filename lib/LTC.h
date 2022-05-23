#ifndef DSLTC_H
#define DSLTC_H

#include <fstream>
#include <iostream>
#include <string>

#include "DangKy.h"
#include "DsMonHoc.h"
#include "Helper.h"
#include "MonHoc.h"

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
    }

    bool isEmpty() { return count == 0; }

    bool isFull() { return count == DSLTC_MAX; }

    // search ltc by mamh, nienkhoa, hocky, nhom
    LTC *search(string key) {
        // string key = maMH + nienKhoa + to_string(hocKy) + to_string(nhom);
        for (int i = 0; i < count; i++) {
            if (dsltc[i]->getKey() == key) {
                return dsltc[i];
            }
        }
        return NULL;
    }

    // binary search theo maLTC
    LTC *search(int maLtc) {
        int left = 0;
        int right = count - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (maLtc == dsltc[mid]->maLTC) {
                return dsltc[mid];
            } else if (maLtc > dsltc[mid]->maLTC) {
                left = mid + 1;
            } else {
                right = mid - 1;
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

        if (maLTC == -1) {
            // insert with auto increment on
            lop = new LTC(++currentMax, maMH, nienKhoa, hocKy, nhom, min, max, huy);
            dsltc[count] = lop;
        } else {
            // insert without auto increment
            lop = new LTC(maLTC, maMH, nienKhoa, hocKy, nhom, min, max, huy);
            currentMax = currentMax > maLTC ? currentMax : maLTC;
            dsltc[count] = lop;
        }
        count++;
        return lop;
    }

    // int remove(string key) {
    //     if (count == 0) {
    //         return 0;
    //     }
    //     bool found = false;

    //     for (int i = 0; i < count; i++) {
    //         if (!found) {
    //             if (dsltc[i]->getKey() == key) {
    //                 found = true;
    //                 delete dsltc[i];
    //                 dsltc[i] = dsltc[i + 1];
    //             }
    //         } else {
    //             dsltc[i] = dsltc[i + 1];
    //         }
    //     }

    //     if (found) {
    //         delete dsltc[count - 1];
    //         count--;
    //     }
    //     return found;
    // }

    int remove(int maltc) {
        if (count == 0) {
            return 0;
        }
        int left = 0;
        int right = count - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (maltc == dsltc[mid]->maLTC) {
                // remove
                for (int i = mid; i < count; i++) {
                    dsltc[i] = dsltc[i + 1];
                }
                delete dsltc[--count];

                return 1;
            } else if (maltc > dsltc[mid]->maLTC) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return 0;
    }

    void print() {
        cout << "\n\tDSLTC, size: " << count << endl;
        for (int i = 0; i < count; i++) {
            cout << dsltc[i]->toString() << endl;
            if (dsltc[i]->dsdk->count > 0) {
                cout << "\n\tDsdk\n";
                cout << dsltc[i]->dsdk->toString() << endl;
            }
        }
    }

    bool coMonHoc(string maMH) {
        for (int i = 0; i < count; i++) {
            if (dsltc[i]->maMH == maMH) {
                return true;
            }
        }
        return false;
    }

    bool coSinhVien(string maSV) {
        for (int i = 0; i < count; i++) {
            if (dsltc[i]->dsdk->count > 0) {
                if (dsltc[i]->dsdk->search(maSV)) {
                    return true;
                }
            }
        }
        return false;
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

            LTC *lop = insert(ltcData[1], ltcData[2], stoi(ltcData[3]),
                              stoi(ltcData[4]), stoi(ltcData[5]), stoi(ltcData[6]),
                              stoi(ltcData[7]), stoi(ltcData[0]));

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

                    lop->dsdk->insertOrder(dkData[0], stod(dkData[1]), stoi(dkData[2]));
                }
            }
        }
        reader.close();
    }

    void replaceMaMH(string oldId, string newId) {
        for (int i = 0; i < count; i++) {
            if (dsltc[i]->maMH == oldId) {
                dsltc[i]->maMH = newId;
            }
        }
    }

    void replaceMaSV(string oldId, string newId) {
        for (int i = 0; i < count; i++) {
            dsltc[i]->dsdk->replaceMaSV(oldId, newId);
        }
    }

    // lọc các lớp có số sv đk < min sv
    void filterLtcCoTheHuy(LTC *list[], string nk, int hk, int &len) {
        len = 0;

        for (int i = 0; i < count; i++) {
            if (dsltc[i]->huy) {
                continue;
            }

            if ((dsltc[i]->nienKhoa == nk) && (dsltc[i]->hocKy == hk)) {
                if (dsltc[i]->dsdk->getSoSVDK() < dsltc[i]->min) {
                    list[len++] = dsltc[i];
                }
            }
        }
    }

    // loc cac ltc theo nien khoa, hoc ky
    // status 0: loc cac ltc sv da dk
    // status 1: loc cac ltc sv da huy dk
    // status 2: loc cac ltc sv co the dk/da huy dk (k đc trùng môn học nếu đã đk)
    void filterLtcTheoNkHk(LTC *list[], string mssv, string nk, int hk, int &len, int status) {
        len = 0;
        // for (int i = 0; i < count; i++) {
        //     if (dsltc[i]->huy) {
        //         continue;
        //     }

        //     if ((dsltc[i]->nienKhoa == nk) && (dsltc[i]->hocKy == hk)) {
        //         DangKy *dk = dsltc[i]->dsdk->search(mssv);
        //         int sosv = dsltc[i]->dsdk->getSoSVDK();

        //         if (status == 0) {
        //             if (dk && !dk->huy) {
        //                 list[len++] = dsltc[i];
        //             }
        //         } else if (status == 1) {
        //             if (dk && dk->huy) {
        //                 list[len++] = dsltc[i];
        //             }
        //         } else if (status == 2) {
        //             // ds có thể dk
        //             // tìm ds ltc sv đã đk trong nk - hk
        //             LTC *dkList[100];
        //             int dkListLength = 0;
        //             filterLtcTheoNkHk(dkList, mssv, nk, hk, dkListLength, 0);

        //             // kiểm tra môn học đã đk chưa
        //             bool found = false;
        //             for (int j = 0; j < dkListLength; j++) {
        //                 if (dsltc[i]->maMH == dsltc[j]->maMH) {
        //                     cout << "\nfound mh\n";

        //                     found = true;
        //                     break;
        //                 }
        //             }
        //             // found -> đã đk môn học trong nk học kỳ đó
        //             if (!found) {
        //                 if (sosv >= dsltc[i]->max) {
        //                     // ltc full
        //                     continue;
        //                 } else if (!dk || dk->huy) {
        //                     // chưa đk hoặc đã hủy
        //                     list[len++] = dsltc[i];
        //                 }
        //             }
        //         }
        //     }
        // }

        if (status == 0) {
            for (int i = 0; i < count; i++) {
                if (dsltc[i]->huy) {
                    continue;
                }
                DangKy *dk = dsltc[i]->dsdk->search(mssv);

                if (dk && !dk->huy) {
                    list[len++] = dsltc[i];
                }
            }
        } else if (status == 2) {
            // ds có thể dk
            // tìm ds ltc sv đã đk trong nk - hk
            LTC *dkList[100];
            int dkListLength = 0;
            filterLtcTheoNkHk(dkList, mssv, nk, hk, dkListLength, 0);

            for (int i = 0; i < count; i++) {
                if (dsltc[i]->huy) {
                    continue;
                }
                DangKy *dk = dsltc[i]->dsdk->search(mssv);
                int sosv = dsltc[i]->dsdk->getSoSVDK();
                bool found = false;

                for (int j = 0; j < dkListLength; j++) {
                    // kiểm tra môn học đã đk chưa
                    if (dsltc[i]->maMH == dkList[j]->maMH) {
                        found = true;
                        break;
                    }
                }

                // found -> đã đk môn học trong nk học kỳ đó
                if (!found) {
                    if (sosv >= dsltc[i]->max) {
                        // ltc full
                        continue;
                    } else if (!dk || dk->huy) {
                        // chưa đk hoặc đã hủy
                        list[len++] = dsltc[i];
                    }
                }
            }
        }
    }

    float getDtbCuaSV(DsMonHoc &dsmh, string mssv) {
        MonHoc *list[1000];
        float *diem = new float[1000];
        int len = 0;

        thongKeDiemMonHocTheoMSSV(dsmh, mssv, list, diem, len);

        float soDiem = 0;
        int soTC = 0;

        for (int i = 0; i < len; i++) {
            soDiem += diem[i] * (list[i]->sltclt + list[i]->sltcth);
            soTC += list[i]->sltclt + list[i]->sltcth;
        }

        if (soTC == 0) return 0;
        delete[] diem;

        return soDiem / soTC;
    }

    void thongKeDiemMonHocTheoMSSV(DsMonHoc &dsmh, string mssv, MonHoc *list[], float *diem, int &len) {
        len = 0;
        for (int i = 0; i < count; i++) {
            // check lop huy
            if (dsltc[i]->huy) {
                continue;
            }

            DangKy *dk = dsltc[i]->dsdk->search(mssv);

            if (dk && !dk->huy) {
                string mamh = dsltc[i]->maMH;
                bool coMH = false;

                for (int j = 0; j < len; j++) {
                    if (list[j]->ms == mamh) {
                        coMH = true;
                        diem[j] = diem[j] > dk->diem ? diem[j] : dk->diem;
                    }
                }
                if (!coMH) {
                    MonHoc *mh = dsmh.search(dsltc[i]->maMH);
                    if (mh) {
                        list[len] = mh;
                        diem[len] = dk->diem;
                        len++;
                    }
                }
            }
        }
    }
};

void printTKDiemMH(MonHoc *list[], float *diem, int len) {
    cout << "\n\tPrint thong ke diem mh\n";
    for (int i = 0; i < len; i++) {
        cout << i + 1 << " - " << list[i]->ms << " - " << list[i]->ten << " - " << diem[i] << endl;
    }
}

void printDsDk(LTC *list[], int len) {
    cout << "\n\tPrint dsdk/ds co the dk mh\n";

    for (int i = 0; i < len; i++) {
        cout << list[i]->toString() << endl;
    }
}

void testDSLTC(DsLTC &dsltc) {
    // dsltc.read();
    dsltc.print();

    // dsltc.insert("INT2", "22-23", 2, 1, 12, 100, 0, -1);
    // dsltc.insert("INT3", "22-23", 2, 1, 1, 100, 0, -1);
    // dsltc.insert("INT0", "20-21", 2, 1, 1, 100, true, -1);
    // dsltc.insert("INT1", "20-21", 2, 1, 1, 123, 0, -1);
    // dsltc.print();

    // LTC *ltc = dsltc.search("INT022-2321");
    // dsltc.replaceMaMH("INT8", "AAA12");

    dsltc.remove(5);
    dsltc.print();

    // dsltc.write();
}

#endif
