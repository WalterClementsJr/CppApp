#ifndef HELPER_H
#define HELPER_H

#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
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
    cout << "ESC\n";
}

#endif
