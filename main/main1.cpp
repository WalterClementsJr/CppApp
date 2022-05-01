#include "DsMonHoc.h"
#include "LTC.h"
#include "SinhVien.h"
#include "TabLTC.h"
#include "TabMonHoc.h"
#include "TabThongKeDiem.h"
#include "TabThongKeDiemLTC.h"
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

    initMHTab(dsmh, dsltc);
    // initLTCTab(dsltc, dsmh, dssv);
    // initDKTab(dsmh, dssv, dsltc, dsltc.dsltc[1]);

    // initThongKeSVTab(dssv);
    // initLTCTab(dsmh, dssv, dsltc);
    // initXemDSDKTab(dsmh, dssv, dsltc);
    // initThongKeDiemTab(dsmh, dssv, dsltc);
    // initThongKeDiemLTCTab(dsmh, dssv, dsltc);

    return 0;
}

int main1() {
    // initUI();
    keyTest();
    return 0;
}
