#ifndef TAB_SINHVIEN_H
#define TAB_SINHVIEN_H

#include <iomanip>
#include <iostream>
#include <string>

#include "SinhVien.h"
#include "drawing.h"

using namespace std;


void highlightIndex(SinhVien *list[], int index) {
    SetColor(BLACK, BLUE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->maSV
             << setw(20) << list[index]->ho << setw(20)
             << list[index]->ten << setw(10) << list[index]->phai
             << setw(20) << list[index]->soDT << setw(10)
             << list[index]->maLop;

    SetColor();
}

void dehighlightIndex(SinhVien *list[], int index) {
    SetColor(BLACK, WHITE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->maSV
             << setw(20) << list[index]->ho << setw(20)
             << list[index]->ten << setw(10) << list[index]->phai
             << setw(20) << list[index]->soDT << setw(10)
             << list[index]->maLop;
    SetColor();
}


void loadSVToTable(SinhVien *list[], int length, int index) {
    ShowCur(false);
    clearTableContent();

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(15) << list[index + i]->maSV
             << setw(20) << list[index + i]->ho << setw(20)
             << list[index + i]->ten << setw(10) << list[index + i]->phai
             << setw(20) << list[index + i]->soDT << setw(10)
             << list[index + i]->maLop;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

int initSVTab(DSSV &dssv) {
    clearTable();
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
    gotoxy(TABLE_X + 85, TABLE_Y);
    cout << "Lop";
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    return 0;
}

#endif
