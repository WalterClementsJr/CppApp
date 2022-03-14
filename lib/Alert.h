#ifndef ALERT_H
#define ALERT_H

#include "drawing.h"
#include "import.h"
#include "regex"
#include <conio.h>
#include <iomanip>
#include <iostream>

using namespace std;

void showError(string error, string subject) {
    gotoxy(106, 41);
    SetTextColor(12);
    cout << error;
    gotoxy(106, 43);
    SetTextColor(14);
    cout << subject;
    SetTextColor(7);
}

int ShowAlert(string message) {
    int col = 10;
    int row = 20;

    SetColor(BLACK, RED);

    gotoxy(col, row - 1);
    std::cout << char(201) << std::setfill(char(205))
              << std::setw(message.size() + 1) << char(187);

    gotoxy(col, row);
    std::cout << char(186) << message << char(186);

    gotoxy(col, row + 1);
    std::cout << char(200) << std::setfill(char(205))
              << std::setw(message.size() + 1) << char(188);

    char key;
    key = _getch();
    // detect Function keys
    if (key == 0) {
        switch (_getch())
        {
        case (KEY_F3):
            key = KEY_F3;
            break;
        case (KEY_F4):
            key = KEY_F4;
            break;
        case (KEY_F1):
            key = KEY_F1;
            break;
        case (KEY_F2):
            key = KEY_F2;
            break;
        }
    }
    //detect arrow keys
    else if (key == 224) {
        switch (_getch())
        {
        case (KEY_UP):
            key = KEY_UP;
            break;
        case (KEY_DOWN):
            key = KEY_DOWN;
            break;
        }
    }
    else {
        switch (key)
        {
        case (ENTER):
            key = ENTER;
            break;
        case (SPACE):
            key = SPACE;
            break;
        case (TAB):
            key = TAB;
            break;
        }
    }

    return key;
    SetColor();
}

bool regexCheck(string attribute, string value) {
    regex rgID("[a-zA-Z]{2}\\d{5}");
    regex rgNull("[a-zA-Z0-9 ]{1,20}");
    regex rgSoChoNgoi("[0-9]{3}");
    regex rgDate("^(0?[1-9]|[12][0-9]|3[01])(0?[1-9]|1[012])\\d{4}$");
    regex rgTime("^(0[0-9]|1[0-9]|2[0-3])[0-5][0-9]$");
    regex rgCMND("[a-zA-Z0-9 ]{9}|[a-zA-Z0-9 ]{12}");
    regex rgPhai("1|0");
    smatch m;
    if (attribute == "ID" && !regex_match(value, m, rgID)) {
        showError("Khong dung dinh dang!", value);
        return false;
    }
    if (attribute == "null" && !regex_match(value, m, rgNull)) {
        showError("Khong dung dinh dang!", value);
        return false;
    }
    if (attribute == "soChoNgoi" && !regex_match(value, m, rgSoChoNgoi)) {
        showError("Khong dung dinh dang!", "So Cho Ngoi: 10, 200,...");
        return false;
    }
    if (attribute == "soChoNgoi" && (stoi(value) < 10 || stoi(value) > 1000)) {
        showError("So luong qua lon hoac qua nho!", "So Cho Ngoi: 10, 1000,...");
        return false;
    }
    if (attribute == "date" && !regex_match(value, m, rgDate)) {
        showError("Khong dung dinh dang!", "Ngay Khoi Hanh: ddMMyyyy");
        return false;
    }
    if (attribute == "time" && !regex_match(value, m, rgTime)) {
        showError("Khong dung dinh dang!", "Thoi Gian KH: hhmm");
        return false;
    }
    if (attribute == "cmnd" && !regex_match(value, m, rgCMND)) {
        showError("Khong dung dinh dang!", "CMND: 9 so hoac 12 so");
        return false;
    }
    if (attribute == "phai" && !regex_match(value, m, rgPhai)) {
        showError("Khong dung dinh dang!", "Nam = 1, Nu = 0");
        return false;
    }
    return true;
}

void keyTest() {
    int ch;

    while ((ch = _getch()) != ESC)
    {
        cout << ch << endl;
        if (ch == 0 || ch == 224)
            cout << _getch();
        cout << "\n";
    }
    cout << "ESC \n";
}

#endif
