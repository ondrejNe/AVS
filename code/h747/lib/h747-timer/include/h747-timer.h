
#ifndef B4M38AVS_CVUT_H747_TIMER_H
#define B4M38AVS_CVUT_H747_TIMER_H

#include "stm32h7xx_hal.h"

typedef void (*void_function)(void);

__unused static void noop(void) {
    // No operation performed here
}

void TIM6_init(void_function tick_function);

#endif //B4M38AVS_CVUT_H747_TIMER_H
