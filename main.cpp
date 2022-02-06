#include "lib/import.h"
#include "lib/drawing.h"
#include "lib/Alert.h"
#include <thread>

int main() {
    initUI();

    while (true) {
        char keyTab = getch();
        switch (keyTab) {
            case KEY_F1:
            // clearTab();
            drawSelectedTab(1);
            break;
            case KEY_F2:
            // clearTab();
            drawSelectedTab(2);
            break;
        }
    }
    return 0;
}
