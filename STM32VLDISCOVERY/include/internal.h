#ifndef INTERNAL_H
#define INTERNAL_H

#include "stm32f1xx_hal.h"

void SystemClock_Config(void);

void Error_Handler(void);

/* Common ---------------------------------------------------------------------------------- */
typedef void (*void_function)(void);

static void noop(void) {
    // No operation performed here
}


#endif // INTERNAL_H
