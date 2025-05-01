#!/bin/bash

set -e

sudo rmmod mydev1_driver
sudo rmmod led_module
sudo rmmod gpio_module

if [ -e /dev/mydev1 ]; then
    sudo rm -f /dev/mydev1
fi

cat /dev/mydev1

make -C src clean
make -C modules clean