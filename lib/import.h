#ifndef IMPORT_H
#define IMPORT_H

#include <conio.h>
#include <windows.h>

#include <iostream>
#include <string>

// color values
#define BLACK 0
#define DARKBLUE 1
#define DARKGREEN 2
#define DARKCYAN 3
#define DARKRED 4
#define DARKPINK 5
#define DARKYELLOW 6
#define DARKWHITE 7
#define GREY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15

// keyboard values
// normal
#define SPACE 32
#define TAB 9
#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define CTRL_F 6
#define CTRL_S 19
// a-z: 97-122
// A-Z: 65-90
// 0-9: 48-57

// with extra keycode 0
#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67
#define KEY_F10 68

#define ALT_F4 107

// with extra keycode 224
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define PAGE_DOWN 81
#define PAGE_UP 73
#define INSERT 82
#define DEL 83
#define HOME 71
#define END 79
#define KEY_F11 133
#define KEY_F12 134

// drawing characters
// single-lined
#define GOC_TREN_PHAI 191
#define GOC_DUOI_PHAI 217
#define GOC_TREN_TRAI 218
#define GOC_DUOI_TRAI 192
#define THANH_NGANG 196
#define THANH_DOC 179

// double-lined
#define D_GOC_TREN_PHAI 187
#define D_GOC_DUOI_PHAI 188
#define D_GOC_TREN_TRAI 201
#define D_GOC_DUOI_TRAI 200
#define D_THANH_NGANG 205
#define D_THANH_DOC 186

// size line
#define colTabSize 38
#define rowTabSize 100

// UI limit
const int UI_LIMIT_X = 170;
const int UI_LIMIT_Y = 55;

// table
const int TABLE_X = 5, TABLE_Y = 10;
const int FIRST_ROW = 12;
const int LAST_ROW = 44;

const int MAX_ROW = 35;
const int TABLE_WIDTH = 101;
const int MAX_TABLE_ROW = 15;

// Details
const int DETAIL_X = 110, DETAIL_Y = 10;

// Insert area
const int INSERT_X = DETAIL_X, INSERT_Y = DETAIL_Y + 2;

// Notification
const int NOTIF_X = 110, NOTIF_Y = 40;
const int NOTIF_WORD_PER_LINE = 60;

//
const int MAX_LTC = 10000;
const int MAX_MH = 10000;

#endif
