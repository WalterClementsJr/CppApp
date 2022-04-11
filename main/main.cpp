#include "LTC.h"
#include "MonHoc.h"
#include "SinhVien.h"
#include "TabLTC.h"
#include "TabMonHoc.h"
#include "drawing.h"
#include "import.h"

using namespace std;

int main() {
    initUI();
    drawSelectedTab(0);

    // declare data structures and load data
    // TODO: also do the same for everything else here, or in switch cases
    DsMonHoc dsmh;
    dsmh.read();

    DSSV dssv;
    dssv.docFile();

    DsLTC dsltc;
    dsltc.read();

    // start first tab: MonHoc
    int key = initMHTab(dsmh);

    while (key != ESC) {
        // TODO: put other tab in here
        switch (key) {
            case KEY_F2:
                drawSelectedTab(1);
                initLTCTab(dsltc, dsmh, dssv);
                break;
            case KEY_F3:
                drawSelectedTab(2);
                break;
            case KEY_F4:
                drawSelectedTab(3);
                break;
            case KEY_F5:
                drawSelectedTab(4);
                break;
            case KEY_F6:
                drawSelectedTab(5);
                break;
            case KEY_F7:
                drawSelectedTab(6);
                break;
            case KEY_F8:
                drawSelectedTab(7);
                break;
        }

        // TODO: remove these 2 lines
        drawSelectedTab(0);
        key = initMHTab(dsmh);
    }
    SetColor();
    return 0;
}
