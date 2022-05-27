/*
    Test các module
*/

#include "DsMonHoc.h"
#include "LTC.h"
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
    // initSVTab(dssv, dsltc);
    // initLTCTab(dsmh, dssv, dsltc);


    // initDKTab(dsmh, dssv, dsltc);
    // initThongKeSVTab(dsmh, dssv, dsltc);
    // initLTCTab(dsmh, dssv, dsltc);
    // initXemDSDKTab(dsmh, dssv, dsltc);
    // initThongKeDiemTab(dsmh, dssv, dsltc);
    // initThongKeDiemTheoLopTab(dsmh, dssv, dsltc);

    return 0;
}
