// walterclements's main

#include "import.h"
#include "drawing.h"
#include "DsMonHoc.h"
#include "MonHocPanel.h"

using namespace std;

int main() {
    // keyTest();
    initUI();
    drawSelectedTab(1);

    DsMonHoc dsmh;
    testDSMH(dsmh);
    // dsmh.displayPostOrder();

    MonHoc *arr[1000];
    dsmh.toArray(arr);

    // initMHPanel(dsmh);

    // insertMonHoc(dsmh, arr);
    editMonHoc(dsmh, arr, 5);
    dsmh.displayPostOrder();

    return 0;
}
