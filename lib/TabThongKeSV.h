#ifndef TK_SV_DIEM_MH_H
#define TK_SV_DIEM_MH_H

#include <iomanip>
#include <iostream>
#include <string>

#include "LTC.h"
#include "SinhVien.h"
#include "drawing.h"

using namespace std;

void loadTkDiemToTable(MonHoc *list[], float *diem, int len, int index) {
    ShowCur(false);
    clearTableContent();

    if (len == 0) {
        return;
    }
    index = index / MAX_TABLE_ROW * MAX_TABLE_ROW;

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    int rowsLeft = len - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    showPageNumber(currentPage, len / MAX_TABLE_ROW);

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(10) << index + i + 1 << setw(15)
             << list[index + i]->ms << setw(60) << list[index + i]->ten
             << setw(10) << diem[index + i];
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

void xemBangDiem(DsMonHoc &dsmh, DsLTC &dsltc, SinhVien sv) {
    SetColor();
    clearTable();

    gotoxy(TABLE_X, TABLE_Y);
    cout << "STT";
    gotoxy(TABLE_X + 10, TABLE_Y);
    cout << "Ma MH";
    gotoxy(TABLE_X + 25, TABLE_Y);
    cout << "Ten MH";
    gotoxy(TABLE_X + 85, TABLE_Y);
    cout << "Diem";
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    clearInfo();
    gotoxy(TABLE_X, LAST_ROW + 1);
    cout << "MSSV: " << sv.maSV;
    gotoxy(TABLE_X, LAST_ROW + 2);
    cout << "Ho ten: " << sv.ho << " " << sv.ten;

    MonHoc *list[1000];
    float *diem = new float[1000];

    int key;
    int index = 0;
    int nOfRowRemains;
    int currentPage, nPage;
    int len = 0;

    dsltc.thongKeDiemMonHocTheoMSSV(dsmh, sv.maSV, list, diem, len);

    if (len > 0) {
        loadTkDiemToTable(list, diem, len, index);
    }

    while (true) {
        currentPage = index / MAX_TABLE_ROW;
        nPage = len / MAX_TABLE_ROW;
        nOfRowRemains = len - currentPage * MAX_TABLE_ROW;
        nOfRowRemains =
            nOfRowRemains > MAX_TABLE_ROW ? MAX_TABLE_ROW : nOfRowRemains;

        key = _getch();

        if (key == 0 || key == 224) {
            if (key == 0) {
                key = _getch();
            } else if (key == 224) {
                key = _getch();
                if (key == KEY_LEFT) {
                    if (len == 0) {
                        continue;
                    }
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;
                    loadTkDiemToTable(list, diem, len, index);
                } else if (key == KEY_RIGHT) {
                    if (len == 0) {
                        continue;
                    }
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;
                    loadTkDiemToTable(list, diem, len, index);
                }
            }
        } else if (key == ESC) {
            clearDetail();
            break;
        }
    }
    delete[] diem;
}

void highlightIndex(int index, SinhVien *list[]) {
    SetColor(BLACK, BLUE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(10) << index + 1 << setw(15)
         << list[index]->maSV << setw(20) << list[index]->ho << setw(20)
         << list[index]->ten << setw(10) << list[index]->phai << setw(20)
         << list[index]->soDT;

    SetColor();
}

void dehighlightIndex(int index, SinhVien *list[]) {
    SetColor();
    ShowCur(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(10) << index + 1 << setw(15)
         << list[index]->maSV << setw(20) << list[index]->ho << setw(20)
         << list[index]->ten << setw(10) << list[index]->phai << setw(20)
         << list[index]->soDT;
    SetColor();
}

void loadSinhVienToTable(SinhVien *list[], int length, int index) {
    ShowCur(false);
    clearTableContent();

    if (length == 0) {
        return;
    }

    index = index / MAX_TABLE_ROW * MAX_TABLE_ROW;
    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(10) << index + i + 1 << setw(15)
             << list[index + i]->maSV << setw(20) << list[index + i]->ho
             << setw(20) << list[index + i]->ten << setw(10)
             << list[index + i]->phai << setw(10) << list[index + i]->soDT;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

int initThongKeSVTab(DsMonHoc &dsmh, DSSV &dssv, DsLTC &dsltc) {
    clearTab();
    SetColor(BLACK, RED);

    gotoxy(TABLE_X, TABLE_Y);
    cout << "STT";
    gotoxy(TABLE_X + 10, TABLE_Y);
    cout << "Ma SV";
    gotoxy(TABLE_X + 25, TABLE_Y);
    cout << "Ho";
    gotoxy(TABLE_X + 45, TABLE_Y);
    cout << "Ten";
    gotoxy(TABLE_X + 65, TABLE_Y);
    cout << "Phai";
    gotoxy(TABLE_X + 75, TABLE_Y);
    cout << "SDT";
    SetColor();
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);
    gotoxy(TABLE_X, LAST_ROW + 1);
    cout << "CTRL + F de tim ma lop can xem";
    gotoxy(TABLE_X, LAST_ROW + 2);
    cout << "Enter de xem bang diem tong ket cac mon cua sv do";

    int key;
    int index = 0;
    int nOfRowRemains;
    int currentPage, nPage;
    int dsLength = 0;

    SinhVien *list[dssv.dem];

    while (true) {
        currentPage = index / MAX_TABLE_ROW;
        nPage = dsLength / MAX_TABLE_ROW;
        nOfRowRemains = dsLength - currentPage * MAX_TABLE_ROW;
        nOfRowRemains =
            nOfRowRemains > MAX_TABLE_ROW ? MAX_TABLE_ROW : nOfRowRemains;

        key = _getch();

        if (key == 0 || key == 224) {
            if (key == 0) {
                key = _getch();
                if (key >= KEY_F1 && key <= KEY_F8) {
                    return key;
                } else if (key == ALT_F4) {
                    clearTab();
                    return ALT_F4;
                }
            } else if (key == 224) {
                key = _getch();

                if (key == KEY_UP) {
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index <= currentPage * MAX_TABLE_ROW) {
                        dehighlightIndex(index, list);
                        index = currentPage * MAX_TABLE_ROW + nOfRowRemains - 1;
                        highlightIndex(index, list);
                    } else {
                        dehighlightIndex(index, list);
                        index--;
                        highlightIndex(index, list);
                    }
                } else if (key == KEY_DOWN) {
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index >=
                        currentPage * MAX_TABLE_ROW + nOfRowRemains - 1) {
                        dehighlightIndex(index, list);
                        index = currentPage * MAX_TABLE_ROW;
                        highlightIndex(index, list);
                    } else {
                        dehighlightIndex(index, list);
                        index++;
                        highlightIndex(index, list);
                    }
                } else if (key == KEY_LEFT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;
                    loadSinhVienToTable(list, dsLength, index);
                    highlightIndex(index, list);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;
                    loadSinhVienToTable(list, dsLength, index);
                    highlightIndex(index, list);
                }
            }
        } else if (key == CTRL_F) {
            string maLop = inputString("Nhap ma lop: ", 10);

            if (maLop.empty()) {
                continue;
            }

            dssv.filterSinhVienTheoMaLop(list, dsLength, maLop);

            if (dsLength == 0) {
                displayNotification("Lop khong ton tai");
                clearTableContent();
                index = 0;
            } else {
                index = 0;
                loadSinhVienToTable(list, dsLength, index);
                highlightIndex(index, list);
            }
        } else if (key == ENTER) {
            if (dsLength == 0) {
                continue;
            }

            xemBangDiem(dsmh, dsltc, *list[index]);

            // redraw
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
            cout << "Phai";
            gotoxy(TABLE_X + 75, TABLE_Y);
            cout << "SDT";
            drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

            gotoxy(TABLE_X, LAST_ROW + 1);
            cout << "CTRL + F de tim ma lop can xem";
            gotoxy(TABLE_X, LAST_ROW + 2);
            cout << "Enter de xem bang diem tong ket cac mon cua sv do";

            // index = 0;
            loadSinhVienToTable(list, dsLength, index);
            highlightIndex(index, list);
        }
    }
    return 0;
}

#endif
