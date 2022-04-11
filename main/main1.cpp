#include "DsMonHoc.h"
#include "LTC.h"
#include "TabLTC.h"
#include "TabMonHoc.h"
#include "SinhVien.h"
#include "drawing.h"
#include "import.h"

using namespace std;

int main() {
    initUI();
    // drawSelectedTab(0);

    DsMonHoc dsmh;
    dsmh.read();
    dsmh.write();
    // testDSMH(dsmh);

    DSSV dssv;
    dssv.docFile();

    // DsDangKy dsdk;
    // testDSDK(dsdk);

    DsLTC dsltc;
    dsltc.read();
    // testDSLTC(dsltc, dsdk, dssv);
    // testDSLTC(dsltc);

    // initMHTab(dsmh);
    initLTCTab(dsltc, dsmh, dssv);

    return 0;
}

// int main() {
//     // initUI();
//     keyTest();
// }
