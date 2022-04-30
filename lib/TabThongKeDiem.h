#ifndef TK_SINHVIEN_H
#define TK_SINHVIEN_H

#include <iomanip>
#include <iostream>
#include <string>

#include "DangKy.h"
#include "DsMonHoc.h"
#include "LTC.h"
#include "MonHoc.h"
#include "SinhVien.h"
#include "TabXemDSDK.h"
#include "drawing.h"

using namespace std;

void highlightIndex(string *hoten, DangKy *list[], int index) {
    SetColor(BLACK, BLUE);
    ShowCur(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(10) << index + 1 << setw(20)
         << list[index]->maSV << setw(50) << hoten[index] << setw(10)
         << list[index]->diem;

    SetColor();
}

void dehighlightIndex(string *hoten, DangKy *list[], int index) {
    SetColor(BLACK, WHITE);
    ShowCur(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(10) << index + 1 << setw(20)
         << list[index]->maSV << setw(50) << hoten[index] << setw(10)
         << list[index]->diem;
    SetColor();
}

void loadDiemToTable(string *hoten, DangKy *list[], int length, int index) {
    ShowCur(false);
    clearTableContent();

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(10) << index + i + 1 << setw(20)
             << list[index + i]->maSV << setw(50) << hoten[index + i]
             << setw(10) << list[index + i]->diem;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

int initThongKeDiemTab(DsMonHoc dsmh, DSSV dssv, DsLTC dsltc) {
    clearTable();
    gotoxy(TABLE_X, TABLE_Y);
    cout << "STT";
    gotoxy(TABLE_X + 10, TABLE_Y);
    cout << "Ma SV";
    gotoxy(TABLE_X + 30, TABLE_Y);
    cout << "Ho ten";
    gotoxy(TABLE_X + 80, TABLE_Y);
    cout << "Diem";

    gotoxy(TABLE_X, LAST_ROW + 1);
    cout << "CTRL + F de tim lop";
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    int key;
    int index = 0;
    int nOfRowRemains;
    int currentPage, nPage;
    int dsLength = 0;

    DangKy *list[1000];
    string *hoten = new string[1000];

    while (true) {
        currentPage = index / MAX_TABLE_ROW;
        nPage = dsLength / MAX_TABLE_ROW;
        nOfRowRemains = dsLength - currentPage * MAX_TABLE_ROW;
        nOfRowRemains =
            nOfRowRemains > MAX_TABLE_ROW ? MAX_TABLE_ROW : nOfRowRemains;

        key = _getch();
        // special keys
        if (key == 0 || key == 224) {
            // "0" keys
            if (key == 0) {
                key = _getch();
                // change tab keys
                if (key == KEY_F1 || key == KEY_F2 || key == KEY_F4 ||
                    key == KEY_F5 || key == KEY_F6 || key == KEY_F7 ||
                    key == KEY_F8) {
                    delete[] hoten;

                    return key;
                }
            } else if (key == 224) {
                key = _getch();

                if (key == KEY_UP) {
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index <= currentPage * MAX_TABLE_ROW) {
                        dehighlightIndex(hoten, list, index);
                        index = currentPage * MAX_TABLE_ROW + nOfRowRemains - 1;
                        highlightIndex(hoten, list, index);
                    } else {
                        index--;
                        highlightIndex(hoten, list, index);
                        dehighlightIndex(hoten, list, index + 1);
                    }
                } else if (key == KEY_DOWN) {
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index >=
                        currentPage * MAX_TABLE_ROW + nOfRowRemains - 1) {
                        dehighlightIndex(hoten, list, index);
                        index = currentPage * MAX_TABLE_ROW;
                        highlightIndex(hoten, list, index);
                    } else {
                        index++;
                        highlightIndex(hoten, list, index);
                        dehighlightIndex(hoten, list, index - 1);
                    }
                } else if (key == KEY_LEFT) {
                    // prev page
                    if (dsLength == 0) {
                        continue;
                    }
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;

                    loadDiemToTable(hoten, list, dsLength, index);
                    highlightIndex(hoten, list, index);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // next page
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;

                    loadDiemToTable(hoten, list, dsLength, index);
                    highlightIndex(hoten, list, index);
                }
            }
        } else if (key == ESC) {
            delete[] hoten;

            return ESC;
        } else if (key == CTRL_F) {
            string search = inputThongTinLop(dsmh);

            if (search.empty()) {
                continue;
            }
            LTC *ltc = dsltc.search(search);

            if (!ltc) {
                displayNotification("Khong tim thay lop");
                continue;
            }

            MonHoc *mh = dsmh.search(ltc->maMH);

            if (!mh) {
                continue;
            }

            // INT0|22-23|2|1 trr
            // INT9|21-22|2|1 human
            // INT8|20-21|2|1 account
            clearInfo();
            gotoxy(TABLE_X, LAST_ROW + 3);
            cout << "BANG DIEM MON: " << mh->ten;
            gotoxy(TABLE_X, LAST_ROW + 4);
            cout << "Nien khoa: " << ltc->nienKhoa << ", HK: " << ltc->hocKy
                 << ", Nhom: " << ltc->nhom;

            ltc->dsdk->filterDSDK(list, dsLength);

            for (int i = 0; i < dsLength; i++) {
                NodeSinhVien *sv = dssv.search(list[i]->maSV);

                if (sv) {
                    hoten[i] = sv->sinhVien.ho + " " + sv->sinhVien.ten;
                } else {
                    hoten[i] = "";
                }
            }
            clearTableContent();
            index = 0;

            if (dsLength > 0) {
                loadDiemToTable(hoten, list, dsLength, index);
                highlightIndex(hoten, list, index);
            }
        }
    }
    delete[] hoten;
    return 0;
}
#endif
