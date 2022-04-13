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
    "Ma MH: ",     "Nien khoa: ", "Hoc ky: ",    "Nhom: ",
    "So sv min: ", "So sv max: ", "Huy (0, 1): "};

const unsigned int LTC_LIMITS[] = {10, 9, 1, 1, 3, 3, 1};

void highlightIndex(LTC *list[], int index) {
    SetColor(BLACK, BLUE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->maLTC << setw(15)
         << list[index]->maMH << setw(15) << list[index]->nienKhoa << setw(10)
         << list[index]->hocKy << setw(8) << list[index]->nhom << setw(10)
         << list[index]->min << setw(10) << list[index]->max << setw(10)
         << list[index]->huy << setw(10) << list[index]->dsdk->count;

    SetColor();
}

void dehighlightIndex(LTC *list[], int index) {
    SetColor(BLACK, WHITE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->maLTC << setw(15)
         << list[index]->maMH << setw(15) << list[index]->nienKhoa << setw(10)
         << list[index]->hocKy << setw(8) << list[index]->nhom << setw(10)
         << list[index]->min << setw(10) << list[index]->max << setw(10)
         << list[index]->huy << setw(10) << list[index]->dsdk->count;
    SetColor();
}

void loadLTCToTable(LTC *list[], int length, int index) {
    ShowCur(false);

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;

    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(15) << list[index + i]->maLTC
             << setw(15) << list[index + i]->maMH << setw(15)
             << list[index + i]->nienKhoa << setw(10) << list[index + i]->hocKy
             << setw(8) << list[index + i]->nhom << setw(10)
             << list[index + i]->min << setw(10) << list[index + i]->max
             << setw(10) << list[index + i]->huy << setw(10)
             << list[index]->dsdk->count;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

void clearLTCField(int index) {
    gotoxy(INSERT_X + LTC_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << string(LTC_LIMITS[index], ' ');
}

void printInsertLTCField(int index, string input) {
    ShowCur(false);

    clearLTCField(index);
    gotoxy(INSERT_X + LTC_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << input;

    ShowCur(true);
}

void insertLTC(DsLTC &dsltc, DsMonHoc dsmh) {
    gotoxy(INSERT_X, INSERT_Y - 1);
    cout << "THEM LTC";

    string input[] = {"", "", "0", "0", "0", "0", "0"};
    unsigned fieldMaxIndex = 6;
    unsigned index = 0;
    unsigned count = 0;
    unsigned key;
    unsigned exit = 0;

    for (unsigned i = 0; i <= fieldMaxIndex; i++) {
        gotoxy(INSERT_X, INSERT_Y + i * 2);
        cout << LTC_FIELDS[i];
        printInsertLTCField(i, input[i]);
    }

    gotoxy(INSERT_X + LTC_FIELDS[0].length(), INSERT_Y);

    while (exit == 0) {
        key = _getch();

        // catch special input first
        if (key == 224 || key == 0) {
            key = _getch();
            if (key == KEY_UP) {
                index = index <= 0 ? fieldMaxIndex : index - 1;
                count = !input[index].empty() ? input[index].length() : 0;
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
                printInsertLTCField(index, input[index]);
            } else if (key == KEY_DOWN) {
                index = index >= fieldMaxIndex ? 0 : index + 1;
                count = !input[index].empty() ? input[index].length() : 0;
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
                printInsertLTCField(index, input[index]);
            } else if (key == KEY_LEFT) {
                count = count <= 0 ? input[index].length() : (count - 1);
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input[index].length() ? 0 : (count + 1);
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            // if input is empty
            if (input[index].empty() || count == 0) {
                continue;
            }

            input[index].erase(count - 1, 1);
            count--;
            printInsertLTCField(index, input[index]);

            // move cursor
            gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                   INSERT_Y + index * 2);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            if (index == fieldMaxIndex) {
                clearNotification();
                // check if one of the inputs is empty
                for (string s : input) {
                    if (s.empty()) {
                        displayNotification("Hay dien day du thong tin.", RED);
                        continue;
                    }
                }

                // check fields
                if (dsmh.search(input[0]) == NULL) {
                    // check mamh
                    displayNotification("MS mon hoc khong ton tai.", RED);
                    index = 0;
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                    continue;
                } else if (stoi(input[3]) > stoi(input[4])) {
                    // check min > max
                    displayNotification("So sv min > so sv max. Hay nhap lai.",
                                        RED);
                    index = 4;
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                    continue;
                }

                // confirm insert
                clearNotification();
                SetColor(BLACK, RED);
                gotoxy(INSERT_X, INSERT_Y + 20);
                cout << "Xac nhan them? Y/N";
                SetColor();
                key = _getch();

                while (key != ESC) {
                    if (key == 0 || key == 224) {
                        _getch();
                    } else if (key == 'y' || key == 'Y') {
                        gotoxy(INSERT_X, INSERT_Y + 20);
                        cout << string(40, ' ');

                        // insert to dsltc
                        LTC *ltc = dsltc.insert(
                            input[0], input[1], stoi(input[2]), stoi(input[3]),
                            stoi(input[4]), stoi(input[5]), stoi(input[6]));
                        if (ltc) {
                            displayNotification("Luu lop tin chi thanh cong");
                            dsltc.write();
                        } else {
                            displayNotification(
                                "Luu lop tin chi khong thanh cong");
                        }
                        return;
                    } else if (key == 'n' || key == 'N') {
                        gotoxy(INSERT_X, INSERT_Y + 20);
                        cout << string(40, ' ');
                        break;
                    } else {
                        key = _getch();
                    }
                }
            } else {
                index++;
                count = input[index].length();
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else {
            // catch character input
            printInsertLTCField(index, input[index]);

            if (index == 0) {
                // field is MAMH
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')) {
                    // out of range
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, toupper(char(key)));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 1) {
                // Nien khoa
                if ((key >= '0' && key <= '9') || key == '-') {
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 2 || index == 3 || index == 4 || index == 5) {
                // hoc ky / nhom / min / max
                if (key >= '0' && key <= '9') {
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 6) {
                // huy
                if (key == '0' || key == '1') {
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            }
        }
    }
}

void editLTC(DsLTC &dsltc, DsMonHoc dsmh, LTC *ltc) {
    gotoxy(INSERT_X, INSERT_Y - 1);
    cout << "EDIT LTC";

    string oldKey = ltc->getKey();

    string input[] = {ltc->maMH,
                      ltc->nienKhoa,
                      to_string(ltc->hocKy),
                      to_string(ltc->nhom),
                      to_string(ltc->min),
                      to_string(ltc->max),
                      to_string(ltc->huy)};
    unsigned fieldMaxIndex = 6;
    unsigned index = 0;
    unsigned count = 0;
    unsigned key;
    unsigned exit = 0;

    for (unsigned i = 0; i <= fieldMaxIndex; i++) {
        gotoxy(INSERT_X, INSERT_Y + i * 2);
        cout << LTC_FIELDS[i];
        printInsertLTCField(i, input[i]);
    }

    gotoxy(INSERT_X + LTC_FIELDS[0].length(), INSERT_Y);

    while (exit == 0) {
        key = _getch();

        // catch special input first
        if (key == 224 || key == 0) {
            key = _getch();
            if (key == KEY_UP) {
                index = index <= 0 ? fieldMaxIndex : index - 1;
                count = !input[index].empty() ? input[index].length() : 0;
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
                printInsertLTCField(index, input[index]);
            } else if (key == KEY_DOWN) {
                index = index >= fieldMaxIndex ? 0 : index + 1;
                count = !input[index].empty() ? input[index].length() : 0;
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
                printInsertLTCField(index, input[index]);
            } else if (key == KEY_LEFT) {
                count = count <= 0 ? input[index].length() : (count - 1);
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input[index].length() ? 0 : (count + 1);
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            // if input is empty
            if (input[index].empty() || count == 0) {
                continue;
            }

            input[index].erase(count - 1, 1);
            count--;
            printInsertLTCField(index, input[index]);

            // move cursor
            gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                   INSERT_Y + index * 2);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            if (index == fieldMaxIndex) {
                clearNotification();
                // check if one of the inputs is empty
                for (string s : input) {
                    if (s.empty()) {
                        displayNotification("Hay dien day du thong tin.", RED);
                        continue;
                    }
                }

                // check fields
                if (dsmh.search(input[0]) == NULL) {
                    // check mamh
                    displayNotification("MS mon hoc khong ton tai.", RED);
                    index = 0;
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                    continue;
                } else if (stoi(input[3]) > stoi(input[4])) {
                    // check min > max
                    displayNotification("So sv min > so sv max. Hay nhap lai.",
                                        RED);
                    index = 4;
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                    continue;
                }

                // confirm insert
                clearNotification();
                SetColor(BLACK, RED);
                gotoxy(INSERT_X, INSERT_Y + 20);
                cout << "Xac nhan sua? Y/N";
                SetColor();
                key = _getch();

                while (key != ESC) {
                    if (key == 0 || key == 224) {
                        _getch();
                    } else if (key == 'y' || key == 'Y') {
                        gotoxy(INSERT_X, INSERT_Y + 20);
                        cout << string(40, ' ');

                        // if key doesnt change -> edit properties
                        if (oldKey ==
                            (input[0] + input[1] + input[2] + input[3])) {
                            ltc->min = stoi(input[4]);
                            ltc->max = stoi(input[5]);
                            ltc->huy = stoi(input[6]);
                            displayNotification(
                                "Chinh sua lop tin chi thanh cong");
                            clearDetail();
                            dsltc.write();
                            return;
                        }
                        // remove old ltc
                        int isRemoved = dsltc.remove(oldKey);

                        if (isRemoved) {
                            // insert to dsltc
                            LTC *newLTC =
                                dsltc.insert(input[0], input[1], stoi(input[2]),
                                             stoi(input[3]), stoi(input[4]),
                                             stoi(input[5]), stoi(input[6]));
                            if (newLTC) {
                                displayNotification(
                                    "Chinh sua lop tin chi thanh cong");
                                newLTC->dsdk = ltc->dsdk;
                                clearDetail();
                                dsltc.write();
                            } else {
                                displayNotification(
                                    "Chinh sua lop tin chi khong thanh cong");
                                break;
                            }
                        } else {
                            displayNotification(
                                "Chinh sua lop tin chi khong thanh cong");
                            break;
                        }

                        return;
                    } else if (key == 'n' || key == 'N') {
                        gotoxy(INSERT_X, INSERT_Y + 20);
                        cout << string(40, ' ');
                        break;
                    } else {
                        key = _getch();
                    }
                }
            } else {
                index++;
                count = input[index].length();
                gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else {
            // catch character input
            printInsertLTCField(index, input[index]);

            if (index == 0) {
                // field is MAMH
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')) {
                    // out of range
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, toupper(char(key)));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 1) {
                // Nien khoa
                if ((key >= '0' && key <= '9') || key == '-') {
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 2 || index == 3 || index == 4 || index == 5) {
                // hoc ky / nhom / min / max
                if (key >= '0' && key <= '9') {
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 6) {
                // huy
                if (key == '0' || key == '1') {
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertLTCField(index, input[index]);
                    gotoxy(INSERT_X + LTC_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            }
        }
    }
}

void deleteLTC(DsLTC &dsltc, LTC *ltc) {
    // TODO: delete with dsdk not empty
    displayNotification("Xac nhan xoa LTC " + ltc->maMH + "? Y/N", RED);
    int key = _getch();

    while (true) {
        if (key == 0 || key == 224) {
            _getch();
        } else if (key == 'y' || key == 'Y') {
            dsltc.remove(ltc->getKey());
            dsltc.write();
            break;
        } else if (key == 'n' || key == 'N') {
            break;
        } else {
            key = _getch();
        }
    }
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
    cout << "Huy";
    gotoxy(TABLE_X + 93, TABLE_Y);
    cout << "So DK";

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
                    key == KEY_F5 || key == KEY_F6 || key == KEY_F7 ||
                    key == KEY_F8) {
                    clearTable();

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
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;
                    clearTableContent();
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                } else if (key == KEY_RIGHT) {
                    // next page
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;
                    clearTableContent();
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                } else if (key == INSERT) {
                    // insert
                    insertLTC(dsltc, dsmh);
                    clearTableContent();
                    index = 0;
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                } else if (key == DEL) {
                    // remove
                    deleteLTC(dsltc, dsltc.dsltc[index]);
                    clearTableContent();
                    index = 0;
                    loadLTCToTable(dsltc.dsltc, dsltc.count, index);
                    highlightIndex(dsltc.dsltc, index);
                }
            }
        } else if (key == TAB) {
            // TODO: view dsdk
        } else if (key == ENTER) {
            // edit
            editLTC(dsltc, dsmh, dsltc.dsltc[index]);
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