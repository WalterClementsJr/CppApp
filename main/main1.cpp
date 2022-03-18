#include "import.h"
#include "drawing.h"
#include "DsMonHoc.h"
#include "MonHocPanel.h"

using namespace std;

int main() {
    initUI();
    drawSelectedTab(1);
    initMHPanel();
    return 0;
}
