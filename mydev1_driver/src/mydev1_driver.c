#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/fs.h>
#include <linux/device.h>
#include "led_module.h"

#define NOD_NAME "mydev1"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yaro");

static int NOD_MAJ;
static dev_t dev;
static struct class* devCls;
static struct LED* led1;
	
static ssize_t devfile_ioctl(struct file *fileP, unsigned int cmd, unsigned long arg){
	switch(cmd){
		case _IO(3,0):
			led1->on(led1);
			break;
		case _IO(4,0):
			led1->off(led1);
			break;
		default:
			break;
	}
	return 0;
}

struct char* mydev1_devnode(struct device* dev, umode_t* mode){
	if(mode)*mode = 0666;
	return NULL;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = devfile_ioctl,
};

static int __init init_driver(void){
	pr_info("[[** Driver init **]]\n");
	NOD_MAJ = register_chrdev(0, NOD_NAME, &fops);
	
	dev = MKDEV(NOD_MAJ, 0);
	devCls = class_create(THIS_MODULE, NOD_NAME);
	devCls->devnode = mydev1_devnode;	
	
	device_create(devCls, NULL, dev, NULL, NOD_NAME);
	
	led1 = create_led(20);	
	if(led1==NULL){
		pr_info("[create_LED] error\n");
		return -EINVAL;
	}

	return 0;
}

static void __exit exit_driver(void){
	destroy_led(led1);

	device_destroy(devCls, dev);
	class_destroy(devCls);

	unregister_chrdev(NOD_MAJ, NOD_NAME);

}

module_init(init_driver);
module_exit(exit_driver);