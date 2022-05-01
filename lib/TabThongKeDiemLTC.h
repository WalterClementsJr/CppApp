#ifndef TK_DIEM_LTC_H
#define TK_DIEM_LTC_H

#include <iomanip>
#include <iostream>
#include <string>

#include "DangKy.h"
#include "LTC.h"
#include "SinhVien.h"
#include "TabThongKeSV.h"
#include "TabXemDSDK.h"
#include "drawing.h"

using namespace std;

void highlightIndex(SinhVien *list[], float *diem, int index) {
    SetColor(BLACK, BLUE);
    ShowCur(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(10) << index << setw(15)
         << list[index]->maSV << setw(20) << list[index]->ho << setw(20)
         << list[index]->ten << setw(10) << diem[index];

    SetColor();
}

void dehighlightIndex(SinhVien *list[], float *diem, int index) {
    SetColor(BLACK, WHITE);
    ShowCur(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(10) << index << setw(15)
         << list[index]->maSV << setw(20) << list[index]->ho << setw(20)
         << list[index]->ten << setw(10) << diem[index];
    SetColor();
}

void loadDiemToTable(SinhVien *list[], float *diem, int length, int index) {
    ShowCur(false);
    clearTableContent();

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(10) << index + i + 1 << setw(15)
             << list[index + i]->maSV << setw(20) << list[index + i]->ho
             << setw(20) << list[index + i]->ten << setw(10) << diem[index + i];
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

int initThongKeDiemLTCTab(DsMonHoc dsmh, DSSV dssv, DsLTC dsltc) {
    clearTable();
    SetColor();

    gotoxy(TABLE_X, TABLE_Y);
    cout << "STT";
    gotoxy(TABLE_X + 10, TABLE_Y);
    cout << "Ma SV";
    gotoxy(TABLE_X + 25, TABLE_Y);
    cout << "Ho";
    gotoxy(TABLE_X + 45, TABLE_Y);
    cout << "Ten";
    gotoxy(TABLE_X + 65, TABLE_Y);
    cout << "Diem";

    gotoxy(TABLE_X, LAST_ROW + 1);
    cout << "CTRL + F de tim lop";
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    int key;
    int index = 0;
    int nOfRowRemains;
    int currentPage, nPage;
    int dsLength = 0;

    SinhVien *list[10000];
    float *diem = new float[1000];

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
                    delete[] diem;

                    return key;
                }
            } else if (key == 224) {
                key = _getch();

                if (key == KEY_UP) {
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index <= currentPage * MAX_TABLE_ROW) {
                        dehighlightIndex(list, diem, index);
                        index = currentPage * MAX_TABLE_ROW + nOfRowRemains - 1;
                        highlightIndex(list, diem, index);
                    } else {
                        index--;
                        highlightIndex(list, diem, index);
                        dehighlightIndex(list, diem, index + 1);
                    }
                } else if (key == KEY_DOWN) {
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index >=
                        currentPage * MAX_TABLE_ROW + nOfRowRemains - 1) {
                        dehighlightIndex(list, diem, index);
                        index = currentPage * MAX_TABLE_ROW;
                        highlightIndex(list, diem, index);
                    } else {
                        index++;
                        highlightIndex(list, diem, index);
                        dehighlightIndex(list, diem, index - 1);
                    }
                } else if (key == KEY_LEFT) {
                    // prev page
                    if (dsLength == 0) {
                        continue;
                    }
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;

                    loadDiemToTable(list, diem, dsLength, index);
                    highlightIndex(list, diem, index);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // next page
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;

                    loadDiemToTable(list, diem, dsLength, index);
                    highlightIndex(list, diem, index);
                }
            }
        } else if (key == CTRL_F) {
            string malop = inputMaLop();

            dssv.filterSinhVienTheoMaLop(list, dsLength, malop);

            if (dsLength == 0) {
                displayNotification("Khong tim thay lop");
                continue;
            }
            // INT0|22-23|2|1 trr
            // INT9|21-22|2|1 human
            // INT8|20-21|2|1 account
            clearInfo();
            gotoxy(TABLE_X, LAST_ROW + 3);
            cout << "BANG DIEM Lop: " << malop;
            gotoxy(TABLE_X, LAST_ROW + 4);
            cout << "So sv: " << dsLength;

            for (int i = 0; i < dsLength; i++) {
                // get diem for list[i]
                diem[i] = (float)i;
            }
            clearTableContent();
            index = 0;

            if (dsLength > 0) {
                loadDiemToTable(list, diem, dsLength, index);
                highlightIndex(list, diem, index);
            }
        }
    }
    delete[] diem;

    return 0;
}

#endif