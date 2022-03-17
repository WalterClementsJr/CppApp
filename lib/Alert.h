#ifndef ALERT_H
#define ALERT_H

#include "drawing.h"
#include "import.h"
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

#endif
