#ifndef TAB_SINHVIEN_H
#define TAB_SINHVIEN_H

#include <iomanip>
#include <iostream>
#include <string>

#include "LTC.h"
#include "SinhVien.h"
#include "drawing.h"

using namespace std;

const string SV_FIELDS[] = {
    "MSSV: ", "Ho: ", "Ten: ", "Phai: ", "SDT: ", "Lop: "};

const unsigned int SV_LIMITS[] = {10, 20, 20, 3, 10, 10};

void highlightIndex(SinhVien *list[], int index) {
    SetColor(BLACK, BLUE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left
         << setw(15) << list[index]->maSV
         << setw(20) << list[index]->ho
         << setw(20) << list[index]->ten
         << setw(10) << list[index]->phai
         << setw(20) << list[index]->soDT
         << setw(10) << list[index]->maLop;

    SetColor();
}

void dehighlightIndex(SinhVien *list[], int index) {
    SetColor();
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left
         << setw(15) << list[index]->maSV
         << setw(20) << list[index]->ho
         << setw(20) << list[index]->ten
         << setw(10) << list[index]->phai
         << setw(20) << list[index]->soDT
         << setw(10) << list[index]->maLop;
    SetColor();
}

void loadSVToTable(SinhVien *list[], int length, int index) {
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
        cout << setfill(' ') << left
             << setw(15) << list[index + i]->maSV
             << setw(20) << list[index + i]->ho
             << setw(20) << list[index + i]->ten
             << setw(10) << list[index + i]->phai
             << setw(20) << list[index + i]->soDT
             << setw(10) << list[index + i]->maLop;
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

void printInsertSVField(int index, string input) {
    ShowCur(false);
    gotoxy(INSERT_X + SV_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << string(SV_LIMITS[index], ' ');

    gotoxy(INSERT_X + SV_FIELDS[index].length(), INSERT_Y + index * 2);
    cout << input;
    gotoxy(INSERT_X + SV_FIELDS[index].length() + input.length(),
           INSERT_Y + index * 2);

    ShowCur(true);
}

int insertSV(DSSV &dssv) {
    clearDetail();

    SetColor();
    gotoxy(INSERT_X, INSERT_Y - 1);
    cout << "THEM SINH VIEN";

    bool ok = false;
    string malop;
    int added = 0;

    while (!ok) {
        ok = true;
        malop = inputString("Nhap ma lop: ", 10);

        if (malop.empty()) {
            clearDetail();
            clearNotification();
            return 0;
        } else if (!regex_match(malop, MA_LOP_REGEX)) {
            displayNotification("Ma lop sai cu phap");
            ok = false;
        }
    }
    clearNotification();
    clearDetail();

    SetColor(BLACK, GREEN);
    gotoxy(INSERT_X + 20, INSERT_Y - 1);
    cout << "Lop: " << malop;
    SetColor();

    displayNotification("Nhap ma so rong de ket thuc");

    string input[] = {"", "", "", "", ""};

    for (unsigned i = 0; i < 5; i++) {
        gotoxy(INSERT_X, INSERT_Y + i * 2);
        cout << SV_FIELDS[i];
        printInsertSVField(i, input[i]);
    }

    unsigned index = 0;
    unsigned count = input[index].length();
    unsigned key;

    gotoxy(INSERT_X + SV_FIELDS[0].length() + count, INSERT_Y);

    while (true) {
        key = _getch();

        if (key == 0 || key == 224) {
            key = _getch();
            if (key == KEY_UP) {
                index = index <= 0 ? 4 : index - 1;
                count = input[index].length();

                printInsertSVField(index, input[index]);
            } else if (key == KEY_DOWN) {
                index = index >= 4 ? 0 : index + 1;
                count = input[index].length();

                printInsertSVField(index, input[index]);
            } else if (key == KEY_LEFT) {
                count = count <= 0 ? input[index].length() : (count - 1);
                gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input[index].length() ? 0 : (count + 1);
                gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            if (input[index].empty() || count == 0) {
                continue;
            }

            input[index].erase(count - 1, 1);
            count--;

            printInsertSVField(index, input[index]);
            gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                   INSERT_Y + index * 2);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            if (index == 4) {
                clearNotification();

                bool pass = true;
                // check if one of the inputs is empty
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
                    printInsertSVField(index, input[index]);

                    continue;
                }

                // check format
                if (!regex_match(input[0], MA_SV_REGEX)) {
                    displayNotification(
                        "MSSV khong dung dinh dang (VD: N18DCCN000)");
                    index = 0;
                    count = input[index].length();
                    printInsertSVField(index, input[index]);
                    continue;
                }

                // check if ms already exist
                if (dssv.search(input[0]) != NULL) {
                    displayNotification("Ma SV da ton tai.", RED);

                    index = 0;
                    count = input[index].length();
                    printInsertSVField(index, input[index]);
                    continue;
                }

                // confirm insert
                clearNotification();

                if (showConfirmDialog("Xac nhan them SV? Y/N")) {
                    dssv.insertOrder(input[0], input[1], input[2], input[3],
                                     input[4], malop);
                    dssv.ghiFile();

                    clearNotification();

                    input[0] = "";
                    input[1] = "";
                    input[2] = "";
                    input[3] = "";
                    input[4] = "";

                    added++;

                    for (unsigned i = 0; i < 5; i++) {
                        printInsertSVField(i, input[i]);
                    }
                    index = 0;
                    count = input[index].length();
                    printInsertSVField(index, input[index]);
                } else {
                    clearNotification();

                    index = 0;
                    count = input[index].length();
                    printInsertSVField(index, input[index]);
                }
            } else {
                index++;
                count = input[index].length();
                printInsertSVField(index, input[index]);
            }
        } else {
            if (index == 0) {
                // field is ms
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                    (key >= '0' && key <= '9')) {
                    if (input[index].length() >= SV_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, toupper(char(key)));
                    count++;
                    printInsertSVField(index, input[index]);
                    gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 1 || index == 2 || index == 3) {
                // ho/ten/phai
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
                    if (input[index].length() >= SV_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;

                    printInsertSVField(index, input[index]);
                    gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 4) {
                // sdt
                if (key >= '0' && key <= '9') {
                    if (input[index].length() >= SV_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;

                    printInsertSVField(index, input[index]);
                    gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            }
        }
    }
    return added;
}

int editSV(DSSV &dssv, DsLTC &dsltc, SinhVien *sv) {
    clearDetail();

    SetColor();
    gotoxy(INSERT_X, INSERT_Y - 1);
    cout << "THEM SINH VIEN";

    clearNotification();
    clearDetail();

    string input[] = {sv->maSV, sv->ho, sv->ten, sv->phai, sv->soDT, sv->maLop};

    unsigned index = 0;
    unsigned maxIndex = 5;
    unsigned count = input[index].length();
    unsigned key;

    for (unsigned i = 0; i <= maxIndex; i++) {
        gotoxy(INSERT_X, INSERT_Y + i * 2);
        cout << SV_FIELDS[i];
        printInsertSVField(i, input[i]);
    }

    gotoxy(INSERT_X + SV_FIELDS[index].length() + count, INSERT_Y);

    while (true) {
        key = _getch();

        if (key == 0 || key == 224) {
            key = _getch();
            if (key == KEY_UP) {
                index = index <= 0 ? maxIndex : index - 1;
                count = input[index].length();

                printInsertSVField(index, input[index]);
            } else if (key == KEY_DOWN) {
                index = index >= maxIndex ? 0 : index + 1;
                count = input[index].length();

                printInsertSVField(index, input[index]);
            } else if (key == KEY_LEFT) {
                count = count <= 0 ? input[index].length() : (count - 1);
                gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input[index].length() ? 0 : (count + 1);
                gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                       INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            if (index == 0) {
                continue;
            }

            if (input[index].empty() || count == 0) {
                continue;
            }

            input[index].erase(count - 1, 1);
            count--;

            printInsertSVField(index, input[index]);
            gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                   INSERT_Y + index * 2);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            if (index == maxIndex) {
                clearNotification();

                bool pass = true;
                // check if one of the inputs is empty
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
                    printInsertSVField(index, input[index]);

                    continue;
                }

                // check format
                if (!regex_match(input[0], MA_SV_REGEX)) {
                    displayNotification(
                        "MSSV khong dung dinh dang (VD: N18DCCN000)");
                    index = 0;
                    count = input[index].length();
                    printInsertSVField(index, input[index]);
                    continue;
                }

                if (dssv.search(input[0]) != NULL) {
                    if (input[0] != sv->maSV) {
                        displayNotification("MSSV da ton tai.", RED);
                        index = 0;
                        count = input[index].length();
                        printInsertSVField(index, input[index]);
                        continue;
                    }
                }

                if (showConfirmDialog("Xac nhan sua SV? Y/N")) {
                    // update if ms is the same, else remove and re-insert
                    // then change all mssv in dsdk
                    if (sv->maSV == input[0]) {
                        sv->ho = input[1];
                        sv->ten = input[2];
                        sv->phai = input[3];
                        sv->soDT = input[4];
                        sv->maLop = input[5];
                    } else {
                        // remove and reinsert
                        dsltc.replaceMaSV(sv->maSV, input[0]);
                        dsltc.write();

                        dssv.xoa(sv->maSV);
                        dssv.insertOrder(input[0], input[1],
                                         input[2], input[3],
                                         input[4], input[5]);
                    }

                    dssv.ghiFile();

                    clearDetail();
                    clearNotification();
                    return 1;
                } else {
                    clearNotification();

                    index = 0;
                    count = input[index].length();
                    printInsertSVField(index, input[index]);
                }
            } else {
                index++;
                count = input[index].length();
                printInsertSVField(index, input[index]);
            }
        } else {
            if (index == 0) {
                // ms/malop
                continue;
                // if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                //     (key >= '0' && key <= '9')) {
                //     if (input[index].length() >= SV_LIMITS[index]) {
                //         continue;
                //     }
                //     input[index].insert(count, 1, toupper(char(key)));
                //     count++;
                //     printInsertSVField(index, input[index]);
                //     gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                //            INSERT_Y + index * 2);
                // }
            } else if (index == 1 || index == 2 || index == 3) {
                // ho/ten/phai
                if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z')) {
                    if (input[index].length() >= SV_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;

                    printInsertSVField(index, input[index]);
                    gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            } else if (index == 4) {
                // sdt
                if (key >= '0' && key <= '9') {
                    if (input[index].length() >= SV_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;

                    printInsertSVField(index, input[index]);
                    gotoxy(INSERT_X + SV_FIELDS[index].length() + count,
                           INSERT_Y + index * 2);
                }
            }
        }
    }
    return 0;
}

int initSVTab(DSSV &dssv, DsLTC &dsltc) {
    clearTab();
    SetColor();

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

    int key;
    int nOfRowRemains;
    int index = 0;
    int currentPage;
    int nPage;
    int dsLength = 0;

    SinhVien *list[10000];

    dssv.toArray(list, dsLength);

    if (dsLength > 0) {
        loadSVToTable(list, dsLength, index);
        highlightIndex(list, index);
    }

    while (true) {
        currentPage = index / MAX_TABLE_ROW;
        nPage = dsLength / MAX_TABLE_ROW;
        nOfRowRemains = dsLength - currentPage * MAX_TABLE_ROW;
        nOfRowRemains = nOfRowRemains > MAX_TABLE_ROW ? MAX_TABLE_ROW : nOfRowRemains;

        key = _getch();
        if (key == 0 || key == 224) {
            if (key == 0) {
                key = _getch();
                // change tab keys
                if (key >= KEY_F1 && key <= KEY_F8) {
                    return key;
                } else if (key == ALT_F4) {
                    clearTab();
                    return ALT_F4;
                }
            } else if (key == 224) {
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
                    index = (currentPage > 0 ? currentPage - 1 : nPage) * MAX_TABLE_ROW;

                    loadSVToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;

                    loadSVToTable(list, dsLength, index);
                    highlightIndex(list, index);
                } else if (key == INSERT) {
                    // insert
                    if (insertSV(dssv)) {
                        dssv.toArray(list, dsLength);
                        if (dsLength == 0) {
                            continue;
                        }
                        index = 0;
                        loadSVToTable(list, dsLength, index);
                        highlightIndex(list, index);
                    }
                } else if (key == DEL) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // check DSLTC
                    if (dsltc.coSinhVien(list[index]->maSV)) {
                        displayNotification("Khong the xoa sinh vien nay vi da dang ky");
                        continue;
                    }
                    // delete
                    if (showConfirmDialog("Xac nhan xoa sinh vien " +
                                          list[index]->ho + " " + list[index]->ten + "? Y/N")) {
                        dssv.xoa(list[index]->maSV);
                        dssv.ghiFile();

                        dssv.toArray(list, dsLength);

                        if (dsLength == 0) {
                            clearTableContent();
                            continue;
                        }

                        clearNotification();
                        index = 0;
                        loadSVToTable(list, dsLength, index);
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

            if (editSV(dssv, dsltc, list[index])) {
                dssv.toArray(list, dsLength);
                if (dsLength == 0) {
                    continue;
                }
                // index = 0;
                loadSVToTable(list, dsLength, index);
                highlightIndex(list, index);
            }
        }
    }
    return 0;
}

#endif
