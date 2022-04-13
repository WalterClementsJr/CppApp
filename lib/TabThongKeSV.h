#ifndef TK_DIEM_H
#define TK_DIEM_H

#include <iomanip>
#include <iostream>
#include <string>

#include "SinhVien.h"
#include "drawing.h"

using namespace std;

void loadSinhVienToTable(SinhVien *list[], int length, int index) {
    ShowCur(false);

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(20) << list[index + i]->maSV
             << setw(20) << list[index + i]->ho << setw(20)
             << list[index + i]->ten << setw(10) << list[index + i]->phai
             << setw(10) << list[index + i]->soDT;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}


int initThongKeSVTab(DSSV dssv) {
    SetColor(BLACK, WHITE);

    gotoxy(TABLE_X, TABLE_Y);
    cout << "Ma SV";
    gotoxy(TABLE_X + 15, TABLE_Y);
    cout << "Ho";
    gotoxy(TABLE_X + 35, TABLE_Y);
    cout << "Ten";
    gotoxy(TABLE_X + 55, TABLE_Y);
    cout << "Phai";
    gotoxy(TABLE_X + 65, TABLE_Y);
    cout << "SDT";
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    gotoxy(TABLE_X + 10, TABLE_Y + 3);
    cout << "INSERT de nhap ma lop can xem";

    int key;
    int exit = 0;
    int nOfRowRemains;
    int currentPage, nPage;
    int dsLength = 0;

    SinhVien *list[dssv.dem];

    dssv.filterSinhVienTheoMaLop(list, dsLength, "D18CQCP02");

    loadSinhVienToTable(list, dsLength, 0);

    return 0;
}

#endif
