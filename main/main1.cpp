// walterclements's main

#include "DsMonHoc.h"
#include "LTC.h"
#include "LTCPanel.h"
#include "MonHocPanel.h"
#include "SinhVien.h"
#include "drawing.h"
#include "import.h"

using namespace std;

int main() {
    initUI();
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
    // dsltc.read();

    initLTCPanel(dsltc);

    return 0;
}
