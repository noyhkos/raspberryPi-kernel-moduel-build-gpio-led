#!/bin/bash

set -e

make

DEVICE_FILE = "/dev/mydev1"

if [ ! -e "$DEVICE_FILE" ]; then
	exit 1
fi

./app