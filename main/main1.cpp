#include "import.h"
#include "drawing.h"
#include "DsMonHoc.h"
#include "MonHocPanel.h"

using namespace std;

int main() {
    initUI();
    drawSelectedTab(1);
    initMHPanel();
    // drawRec(1, 1, 80, 50);


    gotoxy(0, 50);
    return 0;
}
