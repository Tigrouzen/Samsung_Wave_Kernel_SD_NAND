#!/bin/bash

export CROSS_COMPILE=toolchain/bin/arm-linux-gnueabihf-
export ARCH=arm
cp -f arch/arm/mach-s5pv210/setup-sdhci-gpioNAND.c arch/arm/mach-s5pv210/setup-sdhci-gpio.c
make nand_defconfig
make zImage
make modules
