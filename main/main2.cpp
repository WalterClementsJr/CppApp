#include "drawing.h"
#include "import.h"

using namespace std;

int main() {
    initUI();
    drawSelectedTab(1);

    while (true) {
        char key = getch();
        switch (key) {
            case KEY_F1:
                drawSelectedTab(1);
                break;
            case KEY_F2:
                drawSelectedTab(2);
                break;
        }
    }
    return 0;
}
