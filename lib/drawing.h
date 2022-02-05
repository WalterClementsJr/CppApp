#ifndef DRAWING_H
#define DRAWING_H

#include "import.h"

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

    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ',
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

void drawLine(int x1, int y1, int x2, int y2) {
    int t = (y1 == y2) ? THANH_NGANG : THANH_DOC;

    int m_new = 2 * (y2 - y1);
    int slope_error_new = m_new - (x2 - x1);
    for (int x = x1, y = y1; x <= x2; x++) {
        gotoxy(x, y);
        cout << char(t);

        // Add slope to increment angle formed
        slope_error_new += m_new;

        // Slope error reached limit, time to
        // increment y and update slope error.
        if (slope_error_new >= 0) {
            y++;
            slope_error_new -= 2 * (x2 - x1);
        }
    }
}

// clear screen and set cursor at 0,0
void cls(HANDLE hConsole) {
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ',
        dwConSize, coordScreen, &cCharsWritten))
        return;

    // Get the current text attribute
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
        return;

    // Set the buffer's attributes accordingly
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten))
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
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

// Vô hiệu hóa các nút Minimize, Maximize và Close
void DisableCtrButton(bool Close, bool Min, bool Max) {
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

void drawRec(int x, int y, int dai, int rong) {
    gotoxy(x, y);
    cout << char(GOC_TREN_TRAI);
    gotoxy(x + dai, y);
    cout << char(GOC_TREN_PHAI);
    gotoxy(x, y + rong);
    cout << char(GOC_DUOI_TRAI);
    gotoxy(x + dai, y + rong);
    cout << char(GOC_DUOI_PHAI);

    // cột ngang
    for (int i = x + 1; i <= x + dai - 1; i++) {
        gotoxy(i, y);
        cout << char(THANH_NGANG);
        gotoxy(i, y + rong);
        cout << char(THANH_NGANG);
    }

    // cột dọc
    for (int i = y + 1; i <= y + rong - 1; i++) {
        gotoxy(x, i);
        cout << char(THANH_DOC);
        gotoxy(x + dai, i);
        cout << char(THANH_DOC);
    }
}

void drawTab(int x, int y, string title, string key, bool selected = false) {
    int dai = 15, rong = 2;

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

        //cột ngang
        for (int i = x + 1; i <= x + dai - 1; i++) {
            gotoxy(i, y);
            cout << char(THANH_NGANG);
            gotoxy(i, y + rong);
            cout << " ";
        }

        //cột dọc
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

void drawCol(int x) {
    for (size_t i = 10; i < 48; i++) {
        gotoxy(x, i);
        cout << char(THANH_DOC);
    }
}

void drawRow(int y) {
    for (size_t i = 5; i < 103; i++) {
        gotoxy(i, y);
        cout << char(THANH_NGANG);
    }
}

void clearNotification() {
    CursorVisibility(false);
    for (int i = 0; i < 5; i++) {
        gotoxy(NOTIF_X, NOTIF_Y + i);
        cout << string(37, ' ');
    }
    CursorVisibility(true);
}

// in thông báo, auto xuống dòng (37 từ/dòng)
void displayNotification(string notif, int color = WHITE) {
    clearNotification();

    SetColor(BLACK, color);
    for (unsigned i = 0, j = 0; i < notif.length(); i += 37) {
        gotoxy(NOTIF_X, NOTIF_Y + j);
        cout << notif.substr(i, 37);
        j++;
    }
    SetColor();
}

void drawSelectedTab(int index) {
    int space = 16;
    int tabx = 3, taby = 7;

    switch(index) {
        case 1:
        drawTab(tabx, taby, "Tab name", "F1", true);
        drawTab(tabx + space, taby, "Tab name", "F2");
        drawTab(tabx + space * 2, taby, "Tab name", "F3");
        drawTab(tabx + space * 3, taby, "Tab name", "F4");
        drawTab(tabx + space * 4, taby, "Tab name", "F5");
        break;
        case 2:
        drawTab(tabx, taby, "Tab name", "F1");
        drawTab(tabx + space, taby, "Tab name", "F2", true);
        drawTab(tabx + space * 2, taby, "Tab name", "F3");
        drawTab(tabx + space * 3, taby, "Tab name", "F4");
        drawTab(tabx + space * 4, taby, "Tab name", "F5");
        break;
    }
}

void initUI() {
    clrscr();
    resizeConsole(1200, 1000);
    SetScreenBufferSize(1200, 1000);
    DisableResizeWindow();
    DisableCtrButton(0, 0, 1);
    DisableSelection();
    ShowScrollbar(0);
    SetTextColor(WHITE);

    gotoxy(50, 2);
    cout << "Hoc Vien Cong Nghe Buu Chinh Vien Thong TP.HCM";

    drawRec(1, 1, 143, 51);
    drawRec(2, 9, 141, 41);

    drawSelectedTab(2);

    gotoxy(4, 51);
    SetTextColor(BLUE);
    cout << char(17) << " " << char(16);
    SetTextColor(DARKWHITE);
    cout << " PrevPage/NextPage";

    gotoxy(33, 51);
    SetTextColor(BLUE);
    cout << char(30) << " " << char(31);
    SetTextColor(DARKWHITE);
    cout << " Up/Down";

    gotoxy(53, 51);
    SetTextColor(BLUE);
    cout << "ENTER";
    SetTextColor(DARKWHITE);
    cout << " Select/Update";

    gotoxy(80, 51);
    SetTextColor(BLUE);
    cout << "DEL";
    SetTextColor(DARKWHITE);
    cout << " Delete";

    gotoxy(98, 51);
    SetTextColor(BLUE);
    cout << "TAB";
    SetTextColor(DARKWHITE);
    cout << " Find/Search";

    gotoxy(120, 51);
    SetTextColor(BLUE);
    cout << "ESC";
    SetTextColor(DARKWHITE);
    cout << " Exit/Cancel/Back";

    for (size_t i = 10; i <= 49; i++) {
        gotoxy(105, i);
        cout << char(THANH_DOC);
    }
    gotoxy(120, 10);
    cout << "DETAILS";

    for (size_t i = 106; i < 143; i++) {
        gotoxy(i, 38);
        cout << char(THANH_NGANG);
    }
    gotoxy(118, 39);
    cout << "NOTIFICATION";
}

#endif // DRAWING_H
