#include "../lib/import.h"
#include "../lib/drawing.h"
#include "../lib/Alert.h"
#include <thread>

int main() {
    initUI();
    drawSelectedTab(1);

    while (true) {
        char key = getch();
        switch (key) {
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
