#ifndef DRAWING_H
#define DRAWING_H

#include <windows.h>

#include <iostream>
#include <string>

#include "import.h"

using namespace std;

// kích thước cửa sổ console
void resizeConsole(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void gotoxy(int x, int y) {
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

// get location of column
int wherex() {
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;

    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    return screen_buffer_info.dwCursorPosition.X;
}

// get location of row
int wherey() {
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;

    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    return screen_buffer_info.dwCursorPosition.Y;
}

// clear current line
void clrEol() {
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    coord.X = info.dwCursorPosition.X;
    coord.Y = info.dwCursorPosition.Y;

    FillConsoleOutputCharacter(
        GetStdHandle(STD_OUTPUT_HANDLE), ' ',
        info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y,
        coord, &written);
    gotoxy(info.dwCursorPosition.X, info.dwCursorPosition.Y);
}

// set text color
void SetTextColor(WORD color) {
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// set background color
void SetBGColor(WORD color) {
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void SetColor(WORD background = BLACK, WORD text = WHITE) {
    SetBGColor(background);
    SetTextColor(text);
}

void CursorVisibility(bool show) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cur = {1, show};
    SetConsoleCursorInfo(h, &cur);
}

// clear screen and set cursor at 0,0
void cls(HANDLE hConsole) {
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize,
                                    coordScreen, &cCharsWritten))
        return;

    // Get the current text attribute
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

    // Set the buffer's attributes accordingly
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize,
                                    coordScreen, &cCharsWritten))
        return;

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void clrscr() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hConsole);
}

// vô hiệu hóa thay đổi kích thước cửa sổ
void DisableResizeWindow() {
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE,
                  GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

// Vô hiệu hóa các nút Minimize, Maximize và Close
void DisableTitleBarControls(bool Close, bool Min, bool Max) {
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1) {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1) {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1) {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

// vô hiệu hóa bôi đen
void DisableSelection() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

// ẩn hiện con trỏ
void ShowCur(bool CursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}

void SetScreenBufferSize(SHORT width, SHORT height) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}

// vô hiệu hóa thanh cuộn
void ShowScrollbar(BOOL show) {
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, show);
}


void drawCol(int x, int y, int len) {
    for (int i = y; i <= y + len; i++) {
        gotoxy(x, i);
        cout << char(THANH_DOC);
    }
}

void drawRow(int x, int y, int len) {
    for (int i = x; i <= x + len; i++) {
        gotoxy(i, y);
        cout << char(THANH_NGANG);
    }
}

void drawRec(int x, int y, int dai, int rong) {
    gotoxy(x, y);
    cout << char(GOC_TREN_TRAI);
    gotoxy(x + dai, y);
    cout << char(GOC_TREN_PHAI);
    gotoxy(x, y + rong);
    cout << char(GOC_DUOI_TRAI);
    gotoxy(x + dai, y + rong);
    cout << char(GOC_DUOI_PHAI);

    drawRow(x + 1, y, dai - 2);
    drawRow(x + 1, y + rong, dai - 2);

    drawCol(x, y + 1 , rong - 2);
    drawCol(x + dai, y + 1, rong - 2);
}

// fill an area with space
void clearArea(int x, int y, int width, int height) {
    for (int i = y; i < y + height; i++) {
        gotoxy(x, i);
        cout << string(width, ' ');
    }
}

void clearDetail() { clearArea(NOTIF_X, 11, NOTIF_WORD_PER_LINE, 27); }

void clearNotification() {
    clearArea(NOTIF_X, NOTIF_Y, NOTIF_WORD_PER_LINE, UI_LIMIT_Y - NOTIF_Y - 2);
}

// in thông báo, auto xuống dòng (60 từ/dòng)
void displayNotification(string message, int color = WHITE) {
    clearNotification();

    SetColor(BLACK, color);
    for (unsigned i = 0, j = 0; i < message.length();
         i += NOTIF_WORD_PER_LINE) {
        gotoxy(NOTIF_X, NOTIF_Y + j);
        cout << message.substr(i, NOTIF_WORD_PER_LINE);
        j++;
    }
    SetColor();
}

void clearTab() {
    // clear tabs
    gotoxy(3, 111);
    for (size_t i = 10; i < 50; i++) {
        gotoxy(3, i);
        for (size_t i = 0; i < 102; i++) {
            cout << " ";
        }
    }
    clearDetail();
    clearNotification();
}

void drawTab(int x, int y, string title, string key, bool selected = false) {
    int dai = 15, rong = 2;
    SetTextColor(WHITE);

    gotoxy(x, y);
    cout << char(GOC_TREN_TRAI);
    gotoxy(x + dai, y);
    cout << char(GOC_TREN_PHAI);

    if (selected) {
        gotoxy(x, y + rong);
        cout << char(GOC_DUOI_PHAI);
        gotoxy(x + dai, y + rong);
        cout << char(GOC_DUOI_TRAI);

        SetColor(BLACK, WHITE);
        gotoxy(x + 1, y + 1);
        cout << title;
        SetColor();

        // cột ngang
        for (int i = x + 1; i <= x + dai - 1; i++) {
            gotoxy(i, y);
            cout << char(THANH_NGANG);
            gotoxy(i, y + rong);
            cout << " ";
        }

        // cột dọc
        for (int i = y + 1; i <= y + rong - 1; i++) {
            gotoxy(x, i);
            cout << char(THANH_DOC);
            gotoxy(x + dai, i);
            cout << char(THANH_DOC);
        }
    } else {
        SetColor(BLACK, DARKWHITE);
        gotoxy(x + 1, y + 1);
        cout << title;
        SetColor();

        for (int i = x + 1; i <= x + dai - 1; i++) {
            gotoxy(i, y);
            cout << char(THANH_NGANG);
            gotoxy(i, y + rong);
            cout << char(THANH_NGANG);
        }
        for (int i = y + 1; i <= y + rong - 1; i++) {
            gotoxy(x, i);
            cout << char(THANH_DOC);
            gotoxy(x + dai, i);
            cout << char(THANH_DOC);
        }
    }

    gotoxy(x + dai - 2, y + 1);
    SetColor(BLACK, GREEN);
    cout << key;
    SetColor();
}

void drawSelectedTab(int index) {
    int space = 16;
    int tabx = 3, taby = 7;
    int rong = 2;

    SetTextColor(WHITE);
    drawRow(tabx, taby + rong, space * 4);

    switch (index) {
        case 1:
            drawTab(tabx, taby, "MON HOC", "F1", true);
            drawTab(tabx + space, taby, "Tab name", "F2");
            drawTab(tabx + space * 2, taby, "Tab name", "F3");
            drawTab(tabx + space * 3, taby, "Tab name", "F4");
            drawTab(tabx + space * 4, taby, "Tab name", "F5");
            break;
        case 2:
            drawTab(tabx, taby, "MON HOC", "F1");
            drawTab(tabx + space, taby, "Tab name", "F2", true);
            drawTab(tabx + space * 2, taby, "Tab name", "F3");
            drawTab(tabx + space * 3, taby, "Tab name", "F4");
            drawTab(tabx + space * 4, taby, "Tab name", "F5");
            break;
    }
}

void initUI() {
    clrscr();
    resizeConsole(1500, 1000);
    SetScreenBufferSize(1500, 1000);
    DisableResizeWindow();
    DisableTitleBarControls(0, 0, 1);
    DisableSelection();
    ShowScrollbar(0);
    SetTextColor(WHITE);
    CursorVisibility(false);

    gotoxy(UI_LIMIT_X / 2, 2);
    cout << "PTIT TP.HCM";

    drawRec(1, 1, UI_LIMIT_X, UI_LIMIT_Y);
    drawRec(2, 9, UI_LIMIT_X - 2, UI_LIMIT_Y - 10);

    gotoxy(4, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << char(17) << " " << char(16);
    SetTextColor(DARKWHITE);
    cout << " PrevPage/NextPage";

    gotoxy(33, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << char(30) << " " << char(31);
    SetTextColor(DARKWHITE);
    cout << " Up/Down";

    gotoxy(53, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "ENTER";
    SetTextColor(DARKWHITE);
    cout << " Select";

    gotoxy(80, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "DEL";
    SetTextColor(DARKWHITE);
    cout << " Delete";

    gotoxy(98, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "TAB";
    SetTextColor(DARKWHITE);
    cout << " Find/Search";

    gotoxy(120, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "ESC";
    SetTextColor(DARKWHITE);
    cout << " Exit/Cancel/Back";

    for (size_t i = 10; i <= UI_LIMIT_Y - 2; i++) {
        gotoxy(NOTIF_X - 1, i);
        cout << char(THANH_DOC);
    }

    gotoxy(UI_LIMIT_X - 35, 10);
    cout << "DETAILS";

    for (size_t i = NOTIF_X; i < UI_LIMIT_X; i++) {
        gotoxy(i, NOTIF_Y - 2);
        cout << char(THANH_NGANG);
    }
    gotoxy(UI_LIMIT_X - 35, NOTIF_Y - 1);
    cout << "NOTIFICATION";
}

#endif  // DRAWING_H
