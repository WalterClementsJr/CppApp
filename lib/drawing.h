#ifndef DRAWING_H
#define DRAWING_H

#include <windows.h>

#include <iostream>
#include <string>
#include <vector>

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

    drawCol(x, y + 1, rong - 2);
    drawCol(x + dai, y + 1, rong - 2);
}

// fill an area with space
void clearArea(int x, int y, int width, int height) {
    for (int i = y; i < y + height; i++) {
        gotoxy(x, i);
        cout << string(width, ' ');
    }
}

void clearTable() { clearArea(TABLE_X, TABLE_Y, TABLE_WIDTH + 1, LAST_ROW); }

void clearTableContent() {
    clearArea(TABLE_X, TABLE_Y + 1, TABLE_WIDTH + 1, 31);
}

void clearPageNumber() {
    clearArea(TABLE_X, LAST_ROW - 1, 20, 0);
}

void showPageNumber(int current, int total) {
    clearPageNumber();
    gotoxy(TABLE_X, LAST_ROW - 1);
    cout << "Page " << ++current << "/" << ++total;
}

void clearDetail() { clearArea(NOTIF_X, 11, NOTIF_WORD_PER_LINE, 27); }

void clearNotification() {
    ShowCur(false);
    clearArea(NOTIF_X, NOTIF_Y, NOTIF_WORD_PER_LINE, UI_LIMIT_Y - NOTIF_Y - 2);
}

// in thông báo, auto xuống dòng (60 từ/dòng)
void displayNotification(string message, int color = WHITE) {
    ShowCur(false);
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

void clearInfo() {
    ShowCur(false);
    clearArea(TABLE_X, LAST_ROW + 3, 80, 4);
}

void clearTab() {
    clearTable();
    clearDetail();
    clearNotification();
}

void drawTab(int x, int y, string title, string key, bool selected = false) {
    int dai = 20, rong = 2;
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

    const string tabName[] = {"DS Mon Hoc",   "DS LTC",       "DSSV",
                              "Dang ky LTC",  "In DSDK",      "Nhap diem",
                              "Thong ke lop", "Thong ke (i)", "Thong ke (j)",
                              "Thong ke (k)", "Thong ke (l)", "Thong ke (?)"};
    const string shortcut[] = {"F1", "F2", "F3", "F4",  "F5",  "F6",
                               "F7", "F8", "F9", "F10", "F11", "F12"};

    for (unsigned int i = 0; i < sizeof(tabName) / sizeof(tabName[0]); i++) {
        drawTab(tabx + space * i, taby, tabName[i], shortcut[i],
                (i == (unsigned)index));
    }
}

int showConfirmDialog(string message, int color = RED) {
    displayNotification(message, color);

    int key = _getch();

    while (true) {
        if (key == 0 || key == 224) {
            _getch();
        } else if (key == 'y' || key == 'Y') {
            return 1;
        } else if (key == 'n' || key == 'N') {
            return 0;
        } else {
            key = _getch();
        }
    }
}

void initUI() {
    clrscr();
    resizeConsole(1450, 1000);
    DisableResizeWindow();
    DisableTitleBarControls(0, 0, 1);
    DisableSelection();
    ShowScrollbar(0);
    ShowCur(false);

    gotoxy(UI_LIMIT_X / 2, 2);
    SetTextColor(WHITE);
    cout << "PTIT TP.HCM";

    drawRec(1, 1, UI_LIMIT_X, UI_LIMIT_Y);
    drawRec(2, 9, UI_LIMIT_X - 2, UI_LIMIT_Y - 10);

    gotoxy(15, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << char(17) << " " << char(16);
    SetTextColor(DARKWHITE);
    cout << " PrevPage/NextPage";

    gotoxy(45, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << char(30) << " " << char(31);
    SetTextColor(DARKWHITE);
    cout << " Up/Down";

    gotoxy(65, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "ENTER";
    SetTextColor(DARKWHITE);
    cout << " Select";

    gotoxy(85, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "INS";
    SetTextColor(DARKWHITE);
    cout << " INSERT";

    gotoxy(115, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "DEL";
    SetTextColor(DARKWHITE);
    cout << " Delete";

    gotoxy(135, UI_LIMIT_Y);
    SetTextColor(BLUE);
    cout << "ESC";
    SetTextColor(DARKWHITE);
    cout << " Exit";

    for (size_t i = 10; i <= UI_LIMIT_Y - 2; i++) {
        gotoxy(NOTIF_X - 1, i);
        cout << char(THANH_DOC);
    }

    gotoxy(UI_LIMIT_X - 35, 10);
    cout << "CHI TIET";

    for (size_t i = NOTIF_X; i < UI_LIMIT_X; i++) {
        gotoxy(i, NOTIF_Y - 2);
        cout << char(THANH_NGANG);
    }
    gotoxy(UI_LIMIT_X - 35, NOTIF_Y - 1);
    cout << "THONG BAO";
}

#endif  // DRAWING_H
