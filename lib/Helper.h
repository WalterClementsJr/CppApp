#ifndef HELPER_H
#define HELPER_H

#include <conio.h>
#include <windows.h>

#include <iostream>
#include <string>

#include "drawing.h"
#include "import.h"

using namespace std;

void keyTest() {
    int ch;

    while ((ch = _getch()) != ESC) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            cout << "a-z A-Z: " << ch << endl;
        } else if (ch >= '0' && ch <= '9') {
            cout << "0-9: " << ch << endl;
        } else if (ch == ' ') {
            cout << "space: " << ch << endl;
        } else if (ch == 0) {
            cout << "0:" << _getch() << endl;
        } else if (ch == 224) {
            cout << "224:" << _getch() << endl;
        } else {
            cout << "normal:" << ch << endl;
        }
        cout << "\n";
    }
    cout << "ESC\n";
}

void printInputString(string label, string input, unsigned limit) {
    SetColor();
    ShowCur(false);

    gotoxy(INSERT_X + label.length(), INSERT_Y);
    cout << string(limit, ' ');

    gotoxy(INSERT_X + label.length(), INSERT_Y);
    cout << input;

    // gotoxy(INSERT_X + label.length() + input.length(), INSERT_Y);
    ShowCur(true);
}

string inputString(string label, unsigned limit, string input = "") {
    SetColor();
    clearDetail();

    unsigned index = 0;
    unsigned count = input.length();
    unsigned key;

    gotoxy(INSERT_X, INSERT_Y);
    cout << label;
    cout << input;
    ShowCur(true);

    while (true) {
        key = _getch();

        // catch special input first
        if (key == 224 || key == 0) {
            key = _getch();

            if (key == KEY_LEFT) {
                count = count <= 0 ? input.length() : (count - 1);
                gotoxy(INSERT_X + label.length() +  count, INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input.length() ? 0 : (count + 1);
                gotoxy(INSERT_X  + label.length() +  count, INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            // if input is empty
            if (input.empty() || count == 0) {
                continue;
            }
            input.erase(count - 1, 1);
            count--;

            printInputString(label, input, limit);
            gotoxy(INSERT_X+ label.length() + count, INSERT_Y + index * 2);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            // check
            clearDetail();
            return input;
        } else {
            // catch character input
            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                (key >= '0' && key <= '9')) {
                // out of range
                if (input.length() >= limit) {
                    continue;
                }
                input.insert(count, 1, toupper(char(key)));
                count++;

                printInputString(label, input, limit);
                gotoxy(INSERT_X + label.length() + count, INSERT_Y + index * 2);
            }
        }
    }
    ShowCur(false);
    return "";
}

#endif
