#ifndef MH_PANEL_H
#define MH_PANEL_H

#include <conio.h>
#include <iostream>
#include <string>

#include "DsMonHoc.h"
#include "MonHoc.h"
#include "drawing.h"

using namespace std;

const int TABLE_X = 5, TABLE_Y = 10;
const int INSERT_X = DETAIL_X, INSERT_Y = DETAIL_Y + 1;

const int TABLE_WIDTH = 100;
const int MAX_TABLE_ROW = 15;

const string MH_FIELDS[] = {
    "Ma so: ", "Ten mon hoc: ", "SLTC LT: ", "SLTC TH: "};
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

    drawRow(TABLE_X, TABLE_Y + 1, TABLE_WIDTH + 20);
    SetColor();
}

#endif
