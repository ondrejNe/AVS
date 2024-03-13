#ifndef INTERNAL_H
#define INTERNAL_H

#include "stm32h7xx_hal.h"

void SystemClock_Config(void);

void Error_Handler(void);

/* Common ---------------------------------------------------------------------------------- */
typedef void (*void_function)(void);

__unused static void noop(void) {
    // No operation performed here
}

/* Timer custom API ------------------------------------------------------------------------ */
void TIM6_init(void_function tick_fuction);


#endif // INTERNAL_H
