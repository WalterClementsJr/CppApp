#ifndef MH_PANEL_H
#define MH_PANEL_H

#include <conio.h>

#include <iomanip>
#include <iostream>
#include <string>

#include "DsMonHoc.h"
#include "MonHoc.h"
#include "drawing.h"

using namespace std;

const int INSERT_X = DETAIL_X, INSERT_Y = DETAIL_Y + 1;

const string MH_FIELDS[] = {
    "Ma so: ", "Ten mon hoc: ", "SLTC LT: ", "SLTC TH: "};

const unsigned int MH_FIELD_LIMITS[] = {10, 50, 2, 2};

void highlightIndex(MonHoc *list[], int index) {
    SetColor(GREY, BLACK);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(MH_FIELD_LIMITS[0]) << list[index]->ms
         << setw(MH_FIELD_LIMITS[1] + 5) << list[index]->ten << setw(10)
         << setw(MH_FIELD_LIMITS[2] + 5) << list[index]->sltclt
         << setw(MH_FIELD_LIMITS[2] + 5) << list[index]->sltcth;

    SetColor();
}

void dehighlightIndex(MonHoc *list[], int index) {
    SetColor(BLACK, WHITE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(MH_FIELD_LIMITS[0]) << list[index]->ms
         << setw(MH_FIELD_LIMITS[1] + 5) << list[index]->ten << setw(10)
         << setw(MH_FIELD_LIMITS[2] + 5) << list[index]->sltclt
         << setw(MH_FIELD_LIMITS[2] + 5) << list[index]->sltcth;
    SetColor();
}

string insertMonHoc(DsMonHoc &dsmh, MonHoc *list[]) {
    // TODO
    return "";
}

string editMonHoc(DsMonHoc &dsmh, MonHoc *list[], int index) {
    // TODO
    return "";
}

void deleteMonHoc(DsMonHoc &dsmh, MonHoc *list[], int index) {
    // xác nhận xóa
    displayNotification("Xac nhan xoa " + list[index]->ten + "? Y/N");
    int key = _getch();

    while (true) {
        if (key == 0 || key == 224) {
            _getch();
        } else if (key == 'y' || key == 'Y') {
            // TODO delete from ds and temp
            break;
        } else if (key == 'n' || key == 'N') {
            break;
        } else {
            key = _getch();
        }
    }
}

void loadMonHocToTable(MonHoc *list[], int index) {}

int initMHPanel(DsMonHoc &dsmh) {
    SetColor(BLACK, WHITE);

    gotoxy(TABLE_X, TABLE_Y);
    cout << "Ma so";
    gotoxy(TABLE_X + 10, TABLE_Y);
    cout << "Ten mon hoc";
    gotoxy(TABLE_X + 60, TABLE_Y);
    cout << "STC LT";
    gotoxy(TABLE_X + 70, TABLE_Y);
    cout << "STC TH";

    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    int key, exit = 0,
             // số hàng còn lại
        nOfRowRemains,
             // index trong list
        index = 0,
             // current page
        currentPage,
             // max number of pages
        nPage;

    MonHoc *list[10000];
    // load to array
    dsmh.toArray(list);

    // highlight if not empty
    if (!dsmh.isEmpty()) {
        loadMonHocToTable(list, index);
        highlightIndex(list, index);
    }

    while (exit == 0) {
        currentPage = index / MAX_TABLE_ROW;
        nPage = dsmh.getCount() / MAX_TABLE_ROW;
        nOfRowRemains = dsmh.getCount() - currentPage * MAX_TABLE_ROW;
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
                    return key - 59;
                }
            }
            // "224" keys
            else if (key == 224) {
                key = _getch();
                if (key == KEY_UP) {
                    // first row -> last row
                    if (index <= currentPage * MAX_TABLE_ROW) {
                        dehighlightIndex(list, index);
                        index = currentPage * MAX_TABLE_ROW + nOfRowRemains - 1;
                        highlightIndex(list, index);
                    } else {
                        index--;
                        highlightIndex(list, index);
                        dehighlightIndex(list, index + 1);
                    }
                } else if (key == KEY_DOWN) {
                    // last row -> first row
                    if (index >=
                        currentPage * MAX_TABLE_ROW + nOfRowRemains - 1) {
                        dehighlightIndex(list, index);
                        index = currentPage * MAX_TABLE_ROW;
                        highlightIndex(list, index);
                    } else {
                        index++;
                        highlightIndex(list, index);
                        dehighlightIndex(list, index - 1);
                    }
                } else if (key == KEY_LEFT) {
                    index =
                        (currentPage > 0 ? currentPage - 1 : 0) * MAX_TABLE_ROW;
                    clearTable();
                    loadMonHocToTable(list, index);
                    highlightIndex(list, index);
                } else if (key == KEY_RIGHT) {
                    currentPage =
                        currentPage >= nPage ? nPage : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;
                    clearTable();
                    loadMonHocToTable(list, index);
                    highlightIndex(list, index);
                } else if (key == INSERT) {
                    // insert
                    insertMonHoc(dsmh, list);
                    index = 0;
                    loadMonHocToTable(list, index);
                    highlightIndex(list, index);
                } else if (key == DEL) {
                    // remove
                    deleteMonHoc(dsmh, list, index);
                    index = 0;
                    loadMonHocToTable(list, index);
                    highlightIndex(list, index);
                }
            }
        } else if (key == TAB) {
            // search + edit
            // searchMonHoc(dsmh);
            loadMonHocToTable(list, index);
            highlightIndex(list, index);
        } else if (key == ENTER) {
            // edit row
            editMonHoc(dsmh, list, index);
            index = 0;
            // loadMonHocToTable(list, index);
            highlightIndex(list, index);
        }
    }

    SetColor();
    return 0;
}

#endif
