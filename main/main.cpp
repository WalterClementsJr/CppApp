#include "LTC.h"
#include "MonHoc.h"
#include "MonHocPanel.h"
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

    // start first tab: MonHoc
    int key = initMHTab(dsmh);

    while (key != ESC) {
        // TODO: put other tab in here
        switch (key) {
            case KEY_F2:
                drawSelectedTab(1);
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
        }
        drawSelectedTab(0);
        key = initMHTab(dsmh);
    }
    SetColor();
    return 0;
}
