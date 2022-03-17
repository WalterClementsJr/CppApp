#pragma once
using namespace std;

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>

#include "drawing.h"
#include "MonHoc.h"
#include "DsMonHoc.h"

const int TABLE_X = 10, TABLE_Y = 12;
const int INSERT_X = 106, INSERT_Y = 11;

const int TABLE_WIDTH = 83;
const int MAX_TABLE_ROW = 15;

const string INS_KH_FIELD[4] = {"Ma so: ", "Ten mon hoc: ", "SLTC LT: ", "SLTC TH: "};
const unsigned int INS_KH_LIMIT[4] = {10, 50, 15, 1};