#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include "led_module.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("yaro");

static int led_on(struct LED* self){
	self->gpio->setctrl(self->gpio, OUTOVER, 0x3);
	return 1;
}

static int led_off(struct LED* self){
	self->gpio->setctrl(self->gpio, OUTOVER, 0x2);
	return 1;
}

struct LED* create_led(int pin){
	if(pin<0 || pin>27)return NULL;

	struct LED* new_led;
	new_led = kmalloc(sizeof(*new_led), GFP_KERNEL);
	if(!new_led)return NULL;

	struct GPIO* led_gpio = create_gpio(pin);
	if(led_gpio==NULL)return NULL;
	led_gpio->setctrl(gpio, FUNCSEL, 7);
	led_gpio->setctrl(gpio, OEOVER, 0x3);
	led_gpio->setpads(gpio, OD, 0);
	led_gpio->setpads(gpio, DRIVE, 0x1);

	new_led->gpio = led_gpio;
	new_led->on = led_on;
	new_led->off = led_off;	

	return new_led;
}
EXPORT_SYMBOL(create_led);

void destroy_led(struct LED* led){
	if(led){
		destory_gpio(led->gpio);
		kfree(led);
	}
}
EXPORT_SYMBOL(destroy_led);

static int __init init_mod(void){
	pr_info("[[** led module init **]]\n");
	return 0;	
}

static void __exit exit_mod(void){
	pr_info("[[** led module exit **]]\n");

}

module_init(init_mod);
module_exit(exit_mod);