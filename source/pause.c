#include "pause.h"

void handleInputPause() {
    key_poll();
    if (key_hit(KEY_START)) {
        switchGameState(NORMAL);
        tte_get_context()->cursorX = 0;
    }
}
