#include "DsMonHoc.h"
#include "LTC.h"
#include "SinhVien.h"
#include "TabLTC.h"
#include "TabMonHoc.h"
#include "TabThongKeDiem.h"
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
    // testDSLTC(dsltc, dsdk, dssv);
    // testDSLTC(dsltc);

    // initMHTab(dsmh);
    // initLTCTab(dsltc, dsmh, dssv);
    // initDKTab(dsmh, dssv, dsltc, dsltc.dsltc[1]);

    // initThongKeSVTab(dssv);
    initXemDSDKTab(dsmh, dssv, dsltc);
    // displayNotification(inputThongTinLop(dsmh));

    return 0;
}

int main2() {
    // initUI();
    keyTest();
    return 0;
}
