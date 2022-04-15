#ifndef TAB_DK_H
#define TAB_DK_H

#include <iomanip>
#include <iostream>
#include <string>

#include "DangKy.h"
#include "LTC.h"
#include "drawing.h"

using namespace std;

const string DK_FIELDS[] = {"MSSV: ", "Diem: ", "Huy (0: false, 1: true): "};

const unsigned DK_LIMITS[] = {10, 2, 1};

void highlightIndex(DangKy *list[], int index) {
    SetColor(BLACK, BLUE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(20) << list[index]->maSV << setw(10)
         << list[index]->diem << setw(10) << to_string(list[index]->huy);

    SetColor();
}

void dehighlightIndex(DangKy *list[], int index) {
    SetColor(BLACK, WHITE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(20) << list[index]->maSV << setw(10)
         << list[index]->diem << setw(10) << to_string(list[index]->huy);
    SetColor();
}

void loadDSDKToTable(DangKy *list[], int length, int index) {
    ShowCur(false);
    clearTableContent();

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(20) << list[index + i]->maSV
             << setw(10) << list[index + i]->diem << setw(10)
             << to_string(list[index + i]->huy);
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

void printDKField(int index, string input) {
    ShowCur(false);

    gotoxy(INSERT_X + DK_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << string(DK_LIMITS[index], ' ');

    gotoxy(INSERT_X + DK_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << input;

    ShowCur(true);
}

void initDKTab(DsLTC &dsltc, LTC *ltc) {
    clearTable();
    SetColor(BLACK, WHITE);

    gotoxy(TABLE_X, TABLE_Y);
    cout << "Ma SV";
    gotoxy(TABLE_X + 20, TABLE_Y);
    cout << "Diem";
    gotoxy(TABLE_X + 30, TABLE_Y);
    cout << "Huy";
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    gotoxy(TABLE_X, LAST_ROW + 1);
    cout << "DSDK Mon: " << ltc->maMH << ", nien khoa: " << ltc->nienKhoa
         << ", hoc ky: " << ltc->hocKy << ", nhom: " << ltc->nhom;

    int key;
    int index = 0;
    int nOfRowRemains;
    int currentPage, nPage;
    int dsLength = 0;

    DangKy *list[10000];

    ltc->dsdk->toArray(list, dsLength);

    if (dsLength > 0) {
        loadDSDKToTable(list, dsLength, index);
        highlightIndex(list, index);
    }

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
            } else if (key == 224) {
                key = _getch();

                if (key == KEY_UP) {
                    if (dsLength == 0) {
                        continue;
                    }
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
                    if (dsLength == 0) {
                        continue;
                    }
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
                    // prev page
                    if (dsLength == 0) {
                        continue;
                    }
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;

                    loadDSDKToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // next page
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;

                    loadDSDKToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == INSERT) {
                    // TODO insert

                    if (dsLength == 0) {
                        continue;
                    }
                    index = 0;
                    loadDSDKToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == DEL) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // delete
                    if (showConfirmDialog("Xac nhan xoa dk cua " +
                                          list[index]->maSV + "? Y/N")) {
                        ltc->dsdk->remove(list[index]->maSV);
                        ltc->dsdk->toArray(list, dsLength);
                        dsltc.write();

                        if (dsLength == 0) {
                            clearNotification();
                            continue;
                        }

                        index = 0;
                        clearNotification();
                        loadDSDKToTable(list, dsLength, index);
                        highlightIndex(list, index);
                    } else {
                        clearNotification();
                        continue;
                    }
                }
            }
        } else if (key == ENTER) {
            if (dsLength == 0) {
                continue;
            }

            // edit row
            // editDK(dsmh, list, index);
            index = 0;

            loadDSDKToTable(list, dsLength, index);
            highlightIndex(list, index);
        } else if (key == ESC) {
            clearTable();
            return;
        }
    }
    SetColor();
}

#endif
