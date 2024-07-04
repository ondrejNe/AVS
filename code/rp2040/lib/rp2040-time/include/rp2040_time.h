
#ifndef RP2040_TIME_H
#define RP2040_TIME_H

/* standard libraries */
#include <stdbool.h>
#include <string.h>

/* pico SDK libraries*/
#include "pico/time.h"
#include "pico/stdlib.h"

uint32_t millis();

uint32_t micros();

uint32_t s_to_ms(float seconds);

#endif // RP2040_TIME_H
