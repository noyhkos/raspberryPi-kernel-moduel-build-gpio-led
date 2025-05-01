#ifndef LED_MODULE_H
#define LED_MODULE_H

#include "gpio_module.h"

struct LED {
    struct GPIO* gpio;
    int (*on)(struct LED* self);
    int (*off)(struct LED* self);
};

struct LED* create_led(int pin);
void destroy_led(struct LED* led);

#endif