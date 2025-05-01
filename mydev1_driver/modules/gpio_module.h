#ifndef GPIO_MODULE_H
#define GPIO_MODULE_H

#include <linux/types.h>

enum gpio_ctrl_cmd {
    FUNCSEL,
    OEOVER,
    OUTOVER,
};

enum gpio_pads_cmd {
    OD,
    DRIVE,
};

struct GPIO {
    int pin;
    volatile uint32_t *STATUS;
    volatile uint32_t *CTRL;
    volatile uint32_t *PADS;

    int (*setctrl)(struct GPIO* self, enum gpio_ctrl_cmd cmd, unsigned int value);
    int (*setpads)(struct GPIO* self, enum gpio_pads_cmd cmd, unsigned int value);
};

struct GPIO* create_gpio(int pin);
void destroy_gpio(struct GPIO* gpio);

#endif