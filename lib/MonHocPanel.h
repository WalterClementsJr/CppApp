#ifndef MH_PANEL_H
#define MH_PANEL_H

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>

#include "drawing.h"
#include "MonHoc.h"
#include "DsMonHoc.h"

using namespace std;

const int TABLE_X = 5, TABLE_Y = 10;
const int INSERT_X = 106, INSERT_Y = 11;

const int TABLE_WIDTH = 83;
const int MAX_TABLE_ROW = 15;

// const string MH_FIELDS[] = {"Ma so: ", "Ten mon hoc: ", "SLTC LT: ", "SLTC TH: "};
const unsigned int MH_FIELD_LIMITS[] = {10, 50, 2, 2};

void initMHPanel() {
    SetColor(BLACK, WHITE);

    gotoxy(TABLE_X, TABLE_Y);
    cout << "Ma so";
    gotoxy(TABLE_X + 10, TABLE_Y);
    cout << "Ten mon hoc";
    gotoxy(TABLE_X + 60, TABLE_Y);
    cout << "STC LT";
    gotoxy(TABLE_X + 70, TABLE_Y);
    cout << "STC TH";

    drawLine(TABLE_X, TABLE_Y + 1, TABLE_WIDTH + 6, TABLE_Y + 1);
    SetColor();
}

#endif
