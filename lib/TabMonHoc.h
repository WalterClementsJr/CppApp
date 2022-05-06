#ifndef MH_PANEL_H
#define MH_PANEL_H

#include <conio.h>

#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

#include "DsMonHoc.h"
#include "LTC.h"
#include "MonHoc.h"
#include "drawing.h"
#include "import.h"

using namespace std;

const string MH_FIELDS[] = {"Ma so: ", "Ten MH: ", "SLTC LT: ", "SLTC TH: "};

const unsigned int MH_FIELD_LIMITS[] = {10, 50, 1, 1};

void highlightIndex(MonHoc *list[], int index) {
    SetColor(BLACK, BLUE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->ms << setw(60)
         << list[index]->ten << setw(10) << list[index]->sltclt << setw(6)
         << list[index]->sltcth;

    SetColor();
}

void dehighlightIndex(MonHoc *list[], int index) {
    SetColor();
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(15) << list[index]->ms << setw(60)
         << list[index]->ten << setw(10) << list[index]->sltclt << setw(6)
         << list[index]->sltcth;
    SetColor();
}

// display MonHoc to table based on index
void loadMonHocToTable(MonHoc *list[], int length, int index) {
    ShowCur(false);
    clearTableContent();

    if (length == 0) {
        return;
    }
    index = index / MAX_TABLE_ROW * MAX_TABLE_ROW;

    int x = TABLE_X, y = TABLE_Y + 2;
    int currentPage = index / MAX_TABLE_ROW;
    showPageNumber(currentPage, length / MAX_TABLE_ROW);

    int rowsLeft = length - currentPage * MAX_TABLE_ROW;
    rowsLeft = rowsLeft > MAX_TABLE_ROW ? MAX_TABLE_ROW : rowsLeft;

    for (int i = 0; i < rowsLeft; i++) {
        gotoxy(x, y);
        cout << setfill(' ') << left << setw(15) << list[index + i]->ms
             << setw(60) << list[index + i]->ten << setw(10)
             << list[index + i]->sltclt << setw(6) << list[index + i]->sltcth;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

void clearInsertField(int index) {
    gotoxy(INSERT_X + MH_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << string(MH_FIELD_LIMITS[index], ' ');
}

void printInsertMHField(int index, string input) {
    ShowCur(false);

    clearInsertField(index);
    gotoxy(INSERT_X + MH_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << input;
    gotoxy(INSERT_X + MH_FIELDS[index].length() + input.length(),
           INSERT_Y + index * 2);

    ShowCur(true);
}

int insertMonHoc(DsMonHoc &dsmh) {
    gotoxy(INSERT_X, INSERT_Y - 1);
    cout << "THEM MON HOC";

    string input[] = {"", "", "0", "0"};

    // print fields
    for (unsigned i = 0; i < sizeof(MH_FIELDS) / sizeof(MH_FIELDS[0]); i++) {
        gotoxy(INSERT_X, INSERT_Y + i * 2);
        cout << MH_FIELDS[i];
        printInsertMHField(i, input[i]);
    }

    gotoxy(INSERT_X + MH_FIELDS[0].length(), INSERT_Y);

    unsigned index = 0;
    unsigned count = 0;
    unsigned key;

    while (true) {
        key = _getch();

        // catch special input first
        if (key == 0 || key == 224) {
            key = _getch();
            // left/right: move while editing text, up/down: move between lines
            if (key == KEY_UP) {
                index = index <= 0 ? 3 : index - 1;
                count = input[index].length();

                printInsertMHField(index, input[index]);
            } else if (key == KEY_DOWN) {
                index = index >= 3 ? 0 : index + 1;
                count = input[index].length();

                printInsertMHField(index, input[index]);
            } else if (key == KEY_LEFT) {
                count = count <= 0 ? input[index].length() : (count - 1);
                gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input[index].length() ? 0 : (count + 1);
                gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            // if input is empty
            if (input[index].empty() || count == 0) {
                continue;
            }

            input[index].erase(count - 1, 1);
            count--;
            printInsertMHField(index, input[index]);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            if (index == 3) {
                clearNotification();

                bool pass = true;
                for (string s : input) {
                    if (s.empty()) {
                        displayNotification("Hay dien day du thong tin.", RED);
                        pass = false;
                        break;
                    }
                }
                if (!pass) {
                    index = 0;
                    count = input[index].length();
                    printInsertMHField(index, input[index]);

                    continue;
                }

                // check format
                if (!regex_match(input[0], MSMH_REGEX)) {
                    displayNotification(
                        "MS mon hoc khong dung dinh dang (VD: ABC1)");
                    index = 0;
                    count = input[index].length();
                    printInsertMHField(index, input[index]);
                    continue;
                }

                // check if ms already exist
                if (dsmh.search(input[0]) != NULL) {
                    displayNotification("Ma mon hoc da ton tai.", RED);
                    index = 0;
                    count = input[index].length();
                    printInsertMHField(index, input[index]);
                    continue;
                }

                // confirm insert
                clearNotification();

                if (showConfirmDialog("Xac nhan them mon hoc? Y/N")) {
                    dsmh.insert(input[0], input[1], stoi(input[2]),
                                stoi(input[3]));
                    dsmh.write();

                    clearDetail();
                    clearNotification();
                    return 1;
                } else {
                    clearNotification();

                    index = 0;
                    count = input[index].length();
                    printInsertMHField(index, input[index]);
                    continue;
                }
            } else {
                index++;
                // move to end of next row if input is not empty
                count = input[index].length();
                printInsertMHField(index, input[index]);
            }
        } else {
            if (index == 0) {
                // field is ms
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')) {
                    // out of range
                    if (input[index].length() >= MH_FIELD_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, toupper(char(key)));
                    count++;
                    printInsertMHField(index, input[index]);
                    gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 1) {
                // field is ten
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9') || key == ' ' || key == '-' ||
                    key == ',') {
                    if (input[index].length() >= MH_FIELD_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertMHField(index, input[index]);
                    gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 2 || index == 3) {
                // sltc lt - sltc th
                if (key >= '0' && key <= '9') {
                    if (input[index].length() >= MH_FIELD_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertMHField(index, input[index]);
                    gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            }
        }
    }
    return 0;
}

int editMonHoc(DsMonHoc &dsmh, DsLTC &dsltc, MonHoc *list[], int index_arr) {
    gotoxy(INSERT_X, INSERT_Y - 1);
    cout << "SUA MON HOC";

    MonHoc *m = list[index_arr];
    string input[] = {m->ms, m->ten, to_string(m->sltclt),
                      to_string(m->sltcth)};

    unsigned index = 0;
    unsigned count = input[index].length();
    unsigned key;

    // print fields
    for (unsigned i = 0; i < sizeof(MH_FIELDS) / sizeof(MH_FIELDS[0]); i++) {
        gotoxy(INSERT_X, INSERT_Y + i * 2);
        cout << MH_FIELDS[i];
        printInsertMHField(i, input[i]);
    }
    gotoxy(INSERT_X + MH_FIELDS[index].length() + count, INSERT_Y);

    while (true) {
        key = _getch();

        // catch special input first
        if (key == 0 || key == 224) {
            key = _getch();
            if (key == KEY_UP) {
                index = index <= 0 ? 3 : index - 1;
                count = input[index].length();

                printInsertMHField(index, input[index]);
            } else if (key == KEY_DOWN) {
                index = index >= 3 ? 0 : index + 1;
                count = input[index].length();

                printInsertMHField(index, input[index]);
            } else if (key == KEY_LEFT) {
                count = count <= 0 ? input[index].length() : (count - 1);
                gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input[index].length() ? 0 : (count + 1);
                gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            // if input is empty
            if (input[index].empty() || count == 0) {
                continue;
            }

            input[index].erase(count - 1, 1);
            count--;
            printInsertMHField(index, input[index]);
            gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                   INSERT_Y + index * 2);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            if (index == 3) {
                clearNotification();
                // check if one of the inputs is empty
                bool pass = true;
                for (string s : input) {
                    if (s.empty()) {
                        displayNotification("Hay dien day du thong tin.", RED);
                        pass = false;
                        break;
                    }
                }
                if (!pass) {
                    index = 0;
                    count = input[index].length();
                    printInsertMHField(index, input[index]);

                    continue;
                }

                // check format
                if (!regex_match(input[0], MSMH_REGEX)) {
                    displayNotification(
                        "MS mon hoc khong dung dinh dang (VD: ABC123)");
                    index = 0;
                    count = input[index].length();
                    printInsertMHField(index, input[index]);
                    continue;
                }

                // check ms already exist
                if (dsmh.search(input[0]) != NULL) {
                    if (input[0] != m->ms) {
                        displayNotification("MS mon hoc da ton tai.", RED);
                        index = 0;
                        count = input[index].length();
                        printInsertMHField(index, input[index]);
                        continue;
                    }
                }

                if (showConfirmDialog("Xac nhan sua? Y/N")) {
                    // update if ms is the same, else remove and re-insert
                    // then change all ltc with maMH
                    if (m->ms == input[0]) {
                        m->ten = input[1];
                        m->sltclt = stoi(input[2]);
                        m->sltcth = stoi(input[3]);
                    } else {
                        dsltc.replaceMaMH(m->ms, input[0]);
                        dsltc.write();

                        dsmh.remove(m->ms);
                        dsmh.insert(input[0], input[1], stoi(input[2]),
                                    stoi(input[3]));
                    }
                    dsmh.write();
                    clearDetail();
                    clearNotification();
                    return 1;
                } else {
                    clearNotification();

                    index = 0;
                    count = input[index].length();
                    printInsertMHField(index, input[index]);
                }
            } else {
                index++;
                // move to end of next row if input is not empty
                count = input[index].length();
                printInsertMHField(index, input[index]);
            }
        } else {
            // catch character input
            if (index == 0) {
                // field is ms
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')) {
                    // out of range
                    if (input[index].length() >= MH_FIELD_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, toupper(char(key)));
                    count++;

                    printInsertMHField(index, input[index]);
                    gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 1) {
                // field is ten
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9') || key == ' ' || key == '-' ||
                    key == ',') {
                    if (input[index].length() >= MH_FIELD_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;

                    printInsertMHField(index, input[index]);
                    gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }

            } else if (index == 2 || index == 3) {
                if (key >= '0' && key <= '9') {
                    if (input[index].length() >= MH_FIELD_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;

                    printInsertMHField(index, input[index]);
                    gotoxy(INSERT_X + MH_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            }
        }
    }
    return 0;
}

int initMHTab(DsMonHoc &dsmh, DsLTC &dsltc) {
    clearTable();
    SetColor();

    gotoxy(TABLE_X, TABLE_Y);
    cout << "Ma MH";
    gotoxy(TABLE_X + 15, TABLE_Y);
    cout << "Ten mon hoc";
    gotoxy(TABLE_X + 75, TABLE_Y);
    cout << "STC LT";
    gotoxy(TABLE_X + 85, TABLE_Y);
    cout << "STC TH";

    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    int key;
    // số hàng còn lại
    int nOfRowRemains;
    // index trong list
    int index = 0;
    // current page
    int currentPage;
    // max number of pages
    int nPage;
    int dsLength = 0;

    MonHoc *list[10000];
    // load to array
    dsmh.toArray(list, dsLength);

    // if not empty
    if (dsLength > 0) {
        loadMonHocToTable(list, dsLength, index);
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
                // change tab keys
                if (key == KEY_F1 || key == KEY_F2 || key == KEY_F3 || key == KEY_F4 ||
                    key == KEY_F5 || key == KEY_F6 || key == KEY_F7 ||
                    key == KEY_F8 || key == KEY_F9) {
                    return key;
                } else if (key == ALT_F4) {
                    clearTab();
                    return ALT_F4;
                }
            } else if (key == 224) {
                // "224" keys
                key = _getch();
                if (key == KEY_UP) {
                    // first row -> last row
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index <= currentPage * MAX_TABLE_ROW) {
                        dehighlightIndex(list, index);
                        index = currentPage * MAX_TABLE_ROW + nOfRowRemains - 1;
                        highlightIndex(list, index);
                    } else {
                        dehighlightIndex(list, index);
                        index--;
                        highlightIndex(list, index);
                    }
                } else if (key == KEY_DOWN) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // last row -> first row
                    if (index >=
                        currentPage * MAX_TABLE_ROW + nOfRowRemains - 1) {
                        dehighlightIndex(list, index);
                        index = currentPage * MAX_TABLE_ROW;
                        highlightIndex(list, index);
                    } else {
                        dehighlightIndex(list, index);
                        index++;
                        highlightIndex(list, index);
                    }
                } else if (key == KEY_LEFT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // prev page
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;

                    loadMonHocToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // next page
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;

                    loadMonHocToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == INSERT) {
                    // insert
                    if (insertMonHoc(dsmh)) {
                        dsmh.toArray(list, dsLength);
                    }

                    if (dsLength == 0) {
                        continue;
                    }

                    // index = 0;
                    loadMonHocToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == DEL) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // check DSLTC
                    if (dsltc.coMonHoc(list[index]->ms)) {
                        displayNotification(
                            "Khong the xoa mon hoc nay vi da dc dang ky");
                        continue;
                    }
                    // delete
                    if (showConfirmDialog("Xac nhan xoa mon hoc " +
                                          list[index]->ten + "? Y/N")) {
                        dsmh.remove(list[index]->ms);
                        dsmh.write();

                        dsmh.toArray(list, dsLength);

                        if (dsLength == 0) {
                            clearTableContent();
                            continue;
                        }

                        index = 0;
                        clearNotification();
                        loadMonHocToTable(list, dsLength, index);
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

            if (editMonHoc(dsmh, dsltc, list, index)) {
                dsmh.toArray(list, dsLength);
            }

            // index = 0;
            loadMonHocToTable(list, dsLength, index);
            highlightIndex(list, index);
        }
    }
    return 0;
}

#endif
