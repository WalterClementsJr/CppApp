#include "LTC.h"
#include "MonHoc.h"
#include "SinhVien.h"
#include "TabDangKy.h"
#include "TabLTC.h"
#include "TabMonHoc.h"
#include "TabSinhVien.h"
#include "TabThongKeDiem.h"
#include "TabThongKeDiemTheoLop.h"
#include "TabThongKeSV.h"
#include "TabXemDSDK.h"
#include "drawing.h"
#include "import.h"

using namespace std;

int main() {
    initUI();

    // declare data structures and load data
    DsMonHoc dsmh;
    dsmh.read();

    DSSV dssv;
    dssv.docFile();

    DsLTC dsltc;
    dsltc.read();

    // start first tab: MonHoc
    drawSelectedTab(0);
    int key = initMHTab(dsmh, dsltc);

    while (true) {
        if (key == KEY_F1) {
            drawSelectedTab(0);
            key = initMHTab(dsmh, dsltc);
        } else if (key == KEY_F2) {
            drawSelectedTab(1);
            key = initLTCTab(dsmh, dssv, dsltc);
        } else if (key == KEY_F3) {
            drawSelectedTab(2);
            key = initSVTab(dssv, dsltc);
        } else if (key == KEY_F4) {
            drawSelectedTab(3);
            key = initDKTab(dsmh, dssv, dsltc);
        } else if (key == KEY_F5) {
            drawSelectedTab(4);
            key = initXemDSDKTab(dsmh, dssv, dsltc);
        } else if (key == KEY_F6) {
            drawSelectedTab(5);
            key = initThongKeDiemTab(dsmh, dssv, dsltc);
        } else if (key == KEY_F7) {
            drawSelectedTab(6);
            key = initThongKeSVTab(dsmh, dssv, dsltc);
        } else if (key == KEY_F8) {
            drawSelectedTab(7);
            key = initThongKeDiemTheoLopTab(dsmh, dssv, dsltc);
        } else if (ALT_F4) {
            break;
        } else {
            drawSelectedTab(0);
            key = initMHTab(dsmh, dsltc);
        }
    }

    SetColor();
    initExitScreen();
    return 0;
}
