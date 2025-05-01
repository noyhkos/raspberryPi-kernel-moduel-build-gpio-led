#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include "gpio_module.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yaro");

static volatile uint32_t *PERI_BASE = NULL;
static volatile uint32_t *IO_BANK0 = NULL;
static volatile uint32_t *PADS_BANK0 = NULL;

static int set_ctrl(struct GPIO* self, enum gpio_ctrl_cmd cmd, unsigned int value){
	switch(cmd){
		case FUNCSEL:
			// 4:0
			if(value>0x1f)return -1;
			*self->CTRL &= ~(0x1f);
			*self->CTRL |= value;
			break;
		case OEOVER:
			// 15:14
			if(value>0x3)return -1;
			*self->CTRL &= ~(0x3<<14);
			*self->CTRL |= (value<<14);
			break;
		case OUTOVER:
			// 13:12
			if(value>0x3)return -1;
			*self->CTRL &= ~(0x3<<12);
			*self->CTRL |= (value<<12);
			break;
		default:
			break; 
	}
	return 0;
}

static int set_pads(struct GPIO* self, enum gpio_pads_cmd cmd, unsigned int value){
	switch(cmd){
		case OD:
			// 7:7
			if(value>1)return -1;
			*self->PADS &= ~(0x1<<7);
			*self->PADS |= (value<<7);
			break;
		case DRIVE:
			// 5:4
			if(value>0x3)return -1;
			*self->PADS &= ~(0x3<<4);
			*self->PADS |= (value<<4);
		default:
			break;
	}
	return 0;
}

struct GPIO* create_gpio(int pin){
	if(pin<0 || pin>27)return NULL;
	struct GPIO* gpio;
	gpio = kmalloc(sizeof(*gpio), GFP_KERNEL);
	if(!gpio)return NULL;

	gpio->pin = pin;
	gpio->STATUS = IO_BANK0 + pin*2;
	gpio->CTRL = IO_BANK0 + pin*2+1;
	gpio->PADS = PADS_BANK0 + pin+1; 
	gpio->setctrl = set_ctrl;
	gpio->setpads = set_pads;
	return gpio;
}
EXPORT_SYMBOL(create_gpio);

void destroy_gpio(struct GPIO* gpio){
	if(gpio)kfree(gpio);
}
EXPORT_SYMBOL(destroy_gpio);


static int __init init_mod(void){
	pr_info("[[** led module init **]]\n");
	
	PERI_BASE = (uint32_t*)ioremap(0x1f00000000, 2*1024*1024);
	IO_BANK0 = PERI_BASE + 0xd0000/4;
	PADS_BANK0 = PERI_BASE + 0xf0000/4;


	return 0;	
}

static void __exit exit_mod(void){
	
	iounmap(PERI_BASE);
	pr_info("[[** led module exit **]]\n");
	
}

module_init(init_mod);
module_exit(exit_mod);