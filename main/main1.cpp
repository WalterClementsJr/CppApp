// walterclements's main

#include "import.h"
#include "drawing.h"
#include "DsMonHoc.h"
#include "MonHocPanel.h"
#include "LTC.h"
#include "SinhVien.h"

using namespace std;

int main() {
    // initUI();
    // drawSelectedTab(0);

    // DsMonHoc dsmh;
    // testDSMH(dsmh);
    // initMHTab(dsmh);

    // DSSV dssv;

    // DsDangKy dsdk;
    // testDSDK(dsdk);

    DsLTC dsltc;
    // testDSLTC(dsltc, dsdk);
    testDSLTC(dsltc);

    return 0;
}
