#ifndef LTC_PANEL_H
#define LTC_PANEL_H

#include <conio.h>

#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

#include "DangKy.h"
#include "DsMonHoc.h"
#include "LTC.h"
#include "MonHoc.h"
#include "SinhVien.h"
#include "drawing.h"

using namespace std;

const string LTC_FIELDS[] = {
    "Ma MH: ",     "Nien khoa: ", "Hoc ky: ",   "Nhom: ",
    "So sv min: ", "So sv max: ", "Huy (0, 1):"};

const unsigned int LTC_LIMITS[] = {10, 9, 1, 1, 3, 3, 1};

void highlightIndex(LTC *list[], int index) {
    SetColor(GREY, BLACK);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->maLTC << setw(15)
         << list[index]->maMH << setw(15) << list[index]->nienKhoa << setw(10)
         << list[index]->hocKy << setw(10) << list[index]->nhom << setw(8)
         << list[index]->min << setw(10) << list[index]->max << setw(10)
         << list[index]->huy;

    SetColor();
}

void dehighlightIndex(LTC *list[], int index) {
    SetColor(BLACK, WHITE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->maLTC << setw(15)
         << list[index]->maMH << setw(15) << list[index]->nienKhoa << setw(10)
         << list[index]->hocKy << setw(10) << list[index]->nhom << setw(8)
         << list[index]->min << setw(10) << list[index]->max << setw(10)
         << list[index]->huy;
    SetColor();
}

void loadLTCToTable(LTC *list[], int length, int index) {
    ShowCur(false);

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;

    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(15) << list[index + i]->maLTC
             << setw(15) << list[index + i]->maMH << setw(15)
             << list[index + i]->nienKhoa << setw(10) << list[index + i]->hocKy
             << setw(10) << list[index + i]->nhom << setw(8)
             << list[index + i]->min << setw(10) << list[index + i]->max
             << setw(10) << list[index + i]->huy;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

void clearLTCField(int index) {
    gotoxy(INSERT_X + LTC_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << string(LTC_LIMITS[index], ' ');
}

int initLTCTab(DsLTC &dsltc, DsMonHoc &dsmh, DSSV &dssv) {
    SetColor(BLACK, WHITE);

    gotoxy(TABLE_X, TABLE_Y);
    cout << "Ma LTC";
    gotoxy(TABLE_X + 15, TABLE_Y);
    cout << "Ma MH";
    gotoxy(TABLE_X + 30, TABLE_Y);
    cout << "Nien khoa";
    gotoxy(TABLE_X + 45, TABLE_Y);
    cout << "Hoc ky";
    gotoxy(TABLE_X + 55, TABLE_Y);
    cout << "Nhom";
    gotoxy(TABLE_X + 63, TABLE_Y);
    cout << "SV min";
    gotoxy(TABLE_X + 73, TABLE_Y);
    cout << "SV max";
    gotoxy(TABLE_X + 83, TABLE_Y);
    cout << "Huy (0 false, 1 true)";

    int key, exit = 0,
             // số hàng còn lại
        nOfRowRemains,
             // index trong list
        index = 0,
             // current page
        currentPage,
             // max number of pages
        nPage;

    if (dsltc.count > 0) {
        loadLTCToTable(dsltc.dsltc, dsltc.count, index);
        highlightIndex(dsltc.dsltc, index);
    }

    while (exit == 0) {
        currentPage = index / MAX_TABLE_ROW;
        nPage = dsltc.count / MAX_TABLE_ROW;
        nOfRowRemains = dsltc.count - currentPage * MAX_TABLE_ROW;
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
                    key == KEY_F5) {
                    return key;
                }
            } else if (key == 224) {
                // "224" keys
                key = _getch();
                if (key == KEY_UP) {
                    // first row -> last row
                    if (index <= currentPage * MAX_TABLE_ROW) {
                        dehighlightIndex(dsltc.dsltc, index);
                        index = currentPage * MAX_TABLE_ROW + nOfRowRemains - 1;
                        highlightIndex(dsltc.dsltc, index);
                    } else {
                        index--;
                        highlightIndex(dsltc.dsltc, index);
                        dehighlightIndex(dsltc.dsltc, index + 1);
                    }
                } else if (key == KEY_DOWN) {
                    // last row -> first row
                    if (index >=
                        currentPage * MAX_TABLE_ROW + nOfRowRemains - 1) {
                        dehighlightIndex(dsltc.dsltc, index);
                        index = currentPage * MAX_TABLE_ROW;
                        highlightIndex(dsltc.dsltc, index);
                    } else {
                        index++;
                        highlightIndex(dsltc.dsltc, index);
                        dehighlightIndex(dsltc.dsltc, index - 1);
                    }
                } else if (key == KEY_LEFT) {
                    // prev page
                    index =
                        (currentPage > 0 ? currentPage - 1 : nPage) * MAX_TABLE_ROW;
                    clearTableContent();
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                } else if (key == KEY_RIGHT) {
                    // next page
                    currentPage =
                        currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;
                    clearTableContent();
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                } else if (key == INSERT) {
                    // insert
                    // insertMonHoc(dsmh, dsltc.dsltc);
                    clearTableContent();
                    index = 0;
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                } else if (key == DEL) {
                    // remove
                    // deleteMonHoc(dsmh, list, index);
                    clearTableContent();
                    index = 0;
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                }
            }
        } else if (key == TAB) {
            // search + edit
            // searchMonHoc(dsmh);
            // loadLTCToTable(list, dsLength, index);
            // highlightIndex(list, index);
        } else if (key == ENTER) {
            // edit row
            // editMonHoc(dsmh, list, index);
            index = 0;
            clearTableContent();
            loadLTCToTable(dsltc.dsltc, dsltc.count, index);
            highlightIndex(dsltc.dsltc, index);
        } else if (key == ESC) {
            return ESC;
        }
    }

    return 1;
}

#endif