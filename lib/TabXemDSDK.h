#ifndef TAB_XEM_DSDK_H
#define TAB_XEM_DSDK_H

#include <iomanip>
#include <iostream>
#include <string>

#include "DangKy.h"
#include "DsMonHoc.h"
#include "LTC.h"
#include "SinhVien.h"
#include "TabLTC.h"
#include "drawing.h"

string inputThongTinLop(DsMonHoc dsmh) {
    SetColor();

    string input[] = {"", "", "0", "0"};
    unsigned fieldMaxIndex = 3;
    unsigned index = 0;
    unsigned count = 0;
    unsigned key;

    gotoxy(INSERT_X, INSERT_Y - 1);
    cout << "Tim LTC";

    for (unsigned i = 0; i <= fieldMaxIndex; i++) {
        gotoxy(INSERT_X, INSERT_Y + i * 2);
        cout << LTC_FIELDS[i];
        printInsertLTCField(i, input[i]);
    }

    gotoxy(INSERT_X + LTC_FIELDS[0].length(), INSERT_Y);

    while (true) {
        key = _getch();

        // catch special input first
        if (key == 224 || key == 0) {
            key = _getch();
            if (key == KEY_UP) {
                index = index <= 0 ? fieldMaxIndex : index - 1;
                count = !input[index].empty() ? input[index].length() : 0;

                printInsertLTCField(index, input[index]);
            } else if (key == KEY_DOWN) {
                index = index >= fieldMaxIndex ? 0 : index + 1;
                count = !input[index].empty() ? input[index].length() : 0;

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

                if (dsmh.search(input[0]) == NULL) {
                    // check mamh
                    displayNotification("MS mon hoc khong ton tai.", RED);

                    index = 0;
                    count = input[index].length();
                    printInsertLTCField(index, input[index]);
                    continue;
                }

                return input[0] + input[1] + input[2] + input[3];
            } else {
                index++;
                count = input[index].length();
                printInsertLTCField(index, input[index]);
            }
        } else {
            // catch character input
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
                }
            } else if (index == 2 || index == 3) {
                // hoc ky / nhom
                if (key >= '0' && key <= '9') {
                    if (input[index].length() >= LTC_LIMITS[index]) {
                        continue;
                    }
                    input[index].insert(count, 1, char(key));
                    count++;
                    printInsertLTCField(index, input[index]);
                }
            }
        }
    }
    return "";
}

void getHoTenSV(DSSV dssv, DangKy *list[], string *hoten[], int length) {
    for (int i = 0; i < length; i++) {
        NodeSinhVien *s = dssv.search(list[i]->maSV);

        hoten[i] = new string(s->sinhVien.ho + " " + s->sinhVien.ten);
    }
}

void deleteHoTen(string *hoten[], int length) {
    for (int i = 0; i < length; i++) {
        delete hoten[i];
    }
}

void highlightIndex(DangKy *list[], string *hoten[], int index) {
    SetColor(BLACK, BLUE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(20) << list[index]->maSV << setw(50)
         << *hoten[index] << setw(10) << list[index]->diem << setw(10)
         << to_string(list[index]->huy);

    SetColor();
}

void dehighlightIndex(DangKy *list[], string *hoten[], int index) {
    SetColor(BLACK, WHITE);
    ShowCursor(false);

    gotoxy(TABLE_X, TABLE_Y + 2 + (index % MAX_TABLE_ROW) * 2);
    cout << setfill(' ') << left << setw(20) << list[index]->maSV << setw(50)
         << *hoten[index] << setw(10) << list[index]->diem << setw(10)
         << to_string(list[index]->huy);
    SetColor();
}

void loadDSDKToTable(DangKy *list[], string *hoten[], int length, int index) {
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
             << setw(50) << *hoten[index + i] << setw(10)
             << list[index + i]->diem << setw(10)
             << to_string(list[index + i]->huy);
        drawRow(x, y + 1, TABLE_WIDTH);
        y += 2;
    }
}

int initXemDSDKTab(DsMonHoc dsmh, DSSV dssv, DsLTC &dsltc) {
    clearTable();
    SetColor();

    gotoxy(TABLE_X, TABLE_Y);
    cout << "Ma SV";
    gotoxy(TABLE_X + 20, TABLE_Y);
    cout << "Ho ten";
    gotoxy(TABLE_X + 70, TABLE_Y);
    cout << "Diem";
    gotoxy(TABLE_X + 80, TABLE_Y);
    cout << "Huy";
    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH);

    int key;
    int index = 0;
    int nOfRowRemains;
    int currentPage, nPage;
    int dsLength = 0;

    DangKy *list[10000];
    string *hoten[10000];

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
                        dehighlightIndex(list, hoten, index);
                        index = currentPage * MAX_TABLE_ROW + nOfRowRemains - 1;
                        highlightIndex(list, hoten, index);
                    } else {
                        index--;
                        highlightIndex(list, hoten, index);
                        dehighlightIndex(list, hoten, index + 1);
                    }
                } else if (key == KEY_DOWN) {
                    if (dsLength == 0) {
                        continue;
                    }
                    if (index >=
                        currentPage * MAX_TABLE_ROW + nOfRowRemains - 1) {
                        dehighlightIndex(list, hoten, index);
                        index = currentPage * MAX_TABLE_ROW;
                        highlightIndex(list, hoten, index);
                    } else {
                        index++;
                        highlightIndex(list, hoten, index);
                        dehighlightIndex(list, hoten, index - 1);
                    }
                } else if (key == KEY_LEFT) {
                    // prev page
                    if (dsLength == 0) {
                        continue;
                    }
                    index = (currentPage > 0 ? currentPage - 1 : nPage) *
                            MAX_TABLE_ROW;

                    loadDSDKToTable(list, hoten, dsLength, index);
                    highlightIndex(list, hoten, index);
                } else if (key == KEY_RIGHT) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // next page
                    currentPage = currentPage >= nPage ? 0 : currentPage + 1;
                    index = currentPage * MAX_TABLE_ROW;

                    loadDSDKToTable(list, hoten, dsLength, index);
                    highlightIndex(list, hoten, index);
                } else if (key == INSERT) {
                    // TODO insert

                    if (dsLength == 0) {
                        continue;
                    }
                    index = 0;
                    loadDSDKToTable(list, hoten, dsLength, index);
                    highlightIndex(list, hoten, index);
                } else if (key == DEL) {
                    if (dsLength == 0) {
                        continue;
                    }
                    // delete
                    if (showConfirmDialog("Xac nhan xoa dk cua " +
                                          list[index]->maSV + "? Y/N")) {
                        deleteHoTen(hoten, dsLength);

                        // ltc->dsdk->remove(list[index]->maSV);
                        // ltc->dsdk->toArray(list, dsLength);

                        getHoTenSV(dssv, list, hoten, dsLength);

                        dsltc.write();

                        if (dsLength == 0) {
                            clearNotification();
                            continue;
                        }

                        index = 0;
                        clearNotification();
                        loadDSDKToTable(list, hoten, dsLength, index);
                        highlightIndex(list, hoten, index);
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

            loadDSDKToTable(list, hoten, dsLength, index);
            highlightIndex(list, hoten, index);
        } else if (key == ESC) {
            deleteHoTen(hoten, dsLength);

            return ESC;
        } else if (key == CTRL_F) {
            string search = inputThongTinLop(dsmh);

            LTC *ltc = dsltc.search(search);

            if (!ltc) {
                displayNotification("Khong tim thay lop");
                continue;
            }

            MonHoc *mh = dsmh.search(ltc->maMH);
            // INT0|22-23|2|1
            gotoxy(TABLE_X, LAST_ROW + 1);
            cout << "DSDK Mon: " << mh->ten << ", nien khoa: " << ltc->nienKhoa
                 << ", hoc ky: " << ltc->hocKy << ", nhom: " << ltc->nhom;

            ltc->dsdk->toArray(list, dsLength);
            getHoTenSV(dssv, list, hoten, dsLength);

            if (dsLength > 0) {
                loadDSDKToTable(list, hoten, dsLength, index);
                highlightIndex(list, hoten, index);
            }
        }
    }
    deleteHoTen(hoten, dsLength);
}

#endif