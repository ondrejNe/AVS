#include "rp2040_time.h"

uint32_t millis() {
    return to_ms_since_boot(get_absolute_time());
}

uint32_t micros() {
    return to_us_since_boot(get_absolute_time());
}

uint32_t s_to_ms(float seconds) {
    return (uint32_t) (seconds * 1000);
}
