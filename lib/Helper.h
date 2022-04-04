#ifndef HELPER_H
#define HELPER_H

#include <conio.h>
#include <windows.h>

#include <iostream>
#include <string>

#include "import.h"

using namespace std;

void keyTest() {
    int ch;

    while ((ch = _getch()) != ESC) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            cout << "a-z A-Z: " << ch << endl;
        } else if (ch >= '0' && ch <= '9') {
            cout << "0-9: " << ch << endl;
        } else if (ch == 0 || ch == 224) {
            cout << _getch();
        } else
            cout << ch << endl;
        cout << "\n";
    }
    cout << "ESC\n";
}

#endif
