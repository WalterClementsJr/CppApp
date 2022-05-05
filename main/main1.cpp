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
    // MonHoc *list[1000];
    // float *diem = new float[1000];
    // int len = 0;
    // dsltc.thongKeDiemMonHocTheoMSSV(dsmh, "N18DCCN214", list, diem, len);
    // printTKDiemMH(list, diem, len);
    // dsltc.thongKeDiemMonHocTheoMSSV(dsmh, "N18DCCN212", list, diem, len);
    // printTKDiemMH(list, diem, len);
    // dsltc.thongKeDiemMonHocTheoMSSV(dsmh, "N18DCCN214", list, diem, len);
    // printTKDiemMH(list, diem, len);
    // dsltc.thongKeDiemMonHocTheoMSSV(dsmh, "N18DCCN212", list, diem, len);
    // printTKDiemMH(list, diem, len);
    // delete[] diem;

    // initMHTab(dsmh, dsltc);
    // initSVTab(dssv, dsltc);
    // initLTCTab(dsmh, dssv, dsltc);
    // initDKTab(dsmh, dssv, dsltc);

    initThongKeSVTab(dsmh, dssv, dsltc);
    // initLTCTab(dsmh, dssv, dsltc);
    // initXemDSDKTab(dsmh, dssv, dsltc);
    // initThongKeDiemTab(dsmh, dssv, dsltc);
    // initThongKeDiemTheoLopTab(dsmh, dssv, dsltc);

    return 0;
}

int main1() {
    initUI();
    // keyTest();
    // testDSDK();

    return 0;
}
