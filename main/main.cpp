#include "drawing.h"
#include "import.h"

using namespace std;

int main() {
    initUI();
    drawSelectedTab(0);

    while (true) {
        displayNotification("123132432354124213421734982197439827389123132432354124213421734982197439827389123132432354124213421734982197439827389123132432354124213421734982197439827389");

        char key = getch();
        switch (key) {
            case KEY_F1:
                drawSelectedTab(0);
                break;
            case KEY_F2:
                drawSelectedTab(1);
                break;
            case KEY_F3:
                drawSelectedTab(2);
                break;
            case KEY_F4:
                drawSelectedTab(3);
                break;
            case KEY_F5:
                drawSelectedTab(4);
                break;
        }
    }
    return 0;
}
