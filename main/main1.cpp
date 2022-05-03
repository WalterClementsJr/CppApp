#include "DsMonHoc.h"
#include "LTC.h"
#include "SinhVien.h"
#include "TabDangKy.h"
#include "TabLTC.h"
#include "TabMonHoc.h"
#include "TabThongKeDiem.h"
#include "TabThongKeDiemTheoLop.h"
#include "TabThongKeSV.h"
#include "TabXemDSDK.h"
#include "drawing.h"
#include "import.h"

using namespace std;

int main() {
    initUI();

    DsMonHoc dsmh;
    dsmh.read();
    // testDSMH(dsmh);

    DSSV dssv;
    dssv.docFile();
    // testDSSV(dssv);

    DsLTC dsltc;
    dsltc.read();
    // testDSLTC(dsltc);

    // initMHTab(dsmh, dsltc);
    // initLTCTab(dsmh, dssv, dsltc);
    initDKTab(dsmh, dssv, dsltc);

    // initThongKeSVTab(dssv);
    // initLTCTab(dsmh, dssv, dsltc);
    // initXemDSDKTab(dsmh, dssv, dsltc);
    // initThongKeDiemTab(dsmh, dssv, dsltc);
    // initThongKeDiemLTCTab(dsmh, dssv, dsltc);

    return 0;
}

int main1() {
    initUI();
    // keyTest();
    // testDSDK();
    string a;
    int b;
    inputNkHk(a, b);
    gotoxy(0, 20);
    return 0;
}
