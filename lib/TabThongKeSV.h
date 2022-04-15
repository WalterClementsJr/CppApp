#ifndef TK_DIEM_H
#define TK_DIEM_H

#include <iomanip>
#include <iostream>
#include <string>

#include "SinhVien.h"
#include "drawing.h"

using namespace std;

void printInput(string input) {
    ShowCur(false);
    string label = "Nhap ma lop: ";

    gotoxy(INSERT_X + label.length(), INSERT_Y);
    cout << string(20, ' ');

    gotoxy(INSERT_X + label.length(), INSERT_Y);
    cout << input;

    gotoxy(INSERT_X + label.length() + input.length(), INSERT_Y);

    ShowCur(true);
}

string inputMaLop() {
    string input = "";
    unsigned limit = 10;
    unsigned index = 0;
    unsigned count = 0;
    unsigned key;

    gotoxy(INSERT_X, INSERT_Y);

    cout << "Nhap ma lop: ";
    ShowCur(true);

    while (true) {
        key = _getch();

        // catch special input first
        if (key == 224 || key == 0) {
            key = _getch();

            if (key == KEY_LEFT) {
                count = count <= 0 ? input.length() : (count - 1);
                gotoxy(INSERT_X + input.length() + count, INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input.length() ? 0 : (count + 1);
                gotoxy(INSERT_X + input.length() + count, INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            // if input is empty
            if (input.empty() || count == 0) {
                continue;
            }

            input.erase(count - 1, 1);
            count--;
            printInput(input);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            // check
            clearDetail();
            return input;
        } else {
            // catch character input
            printInput(input);

            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                (key >= '0' && key <= '9')) {
                // out of range
                if (input.length() >= limit) {
                    continue;
                }
                input.insert(count, 1, toupper(char(key)));
                count++;
                printInput(input);
            }
        }
    }
    ShowCur(false);
    return input;
}

void loadSinhVienToTable(SinhVien *list[], int length, int index) {
    ShowCur(false);
    clearTableContent();

    if (length == 0) {
        return;
    }

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
             << setw(10) << list[index + i]->soDT;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

int initThongKeSVTab(DSSV dssv) {
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
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    gotoxy(TABLE_X + 10, TABLE_Y + 3);
    cout << "Nhan INSERT de nhap ma lop can xem";

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
        // special keys
        if (key == 0 || key == 224) {
            if (key == 0) {
                key = _getch();
                // change tab keys
                if (key == KEY_F1 || key == KEY_F2 || key == KEY_F4 ||
                    key == KEY_F5 || key == KEY_F6 || key == KEY_F7 ||
                    key == KEY_F8) {
                    clearTable();
                    return key;
                }
            } else if (key == 224) {
                key = _getch();

                if (key == KEY_LEFT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;
                    loadSinhVienToTable(list, dsLength, index);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }

                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;
                    loadSinhVienToTable(list, dsLength, index);
                } else if (key == INSERT) {
                    string maLop = inputMaLop();

                    if (maLop.empty()) {
                        continue;
                    }

                    dssv.filterSinhVienTheoMaLop(list, dsLength, maLop);

                    if (dsLength == 0) {
                        displayNotification("Lop khong ton tai");
                    } else {
                        index = 0;
                        loadSinhVienToTable(list, dsLength, index);
                    }
                }
            }
        } else if (key == ESC) {
            clearTable();
            return ESC;
        }
    }

    SetColor();
    return 0;
}

#endif
