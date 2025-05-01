#!/bin/bash

set -e

echo "[BUILD DRIVER]"

echo "==Modules=="
make -C modules clean
make -C modules

echo "==src=="
make -C src clean
make -c src

echo "**Insert driver/modules**"
sudo insmod modules/gpio_module.ko
sudo insmod modules/led_module.ko
sudo insmod src/mydev1_driver.ko

if [ -e /dev/mydev1 ]; then
    echo "[SUCCESS]"
else
    echo "[FAIL]"
    exit 1
fi