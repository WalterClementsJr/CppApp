/*
    Test các module
*/

#include "model/DsMonHoc.h"
#include "model/LTC.h"
#include "model/SinhVien.h"
#include "ui/TabDangKy.h"
#include "ui/TabLTC.h"
#include "ui/TabMonHoc.h"
#include "ui/TabSinhVien.h"
#include "ui/TabThongKeDiem.h"
#include "ui/TabThongKeDiemTheoLop.h"
#include "ui/TabThongKeSV.h"
#include "ui/TabXemDSDK.h"
#include "ui/drawing.h"
#include "util/import.h"

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
