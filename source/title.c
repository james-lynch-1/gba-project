#include "title.h"

void handleInputTitle() {
    key_poll();
    if (key_hit(KEY_START)) {
        switchGameState(NORMAL);
    }
}
