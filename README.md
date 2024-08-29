# OSC2024

| Github Account | Student ID | Name          |
|----------------|------------|---------------|
| kjw5656        | B112007    | Kai-Jay Wong  |

## Requirements

* a cross-compiler for aarch64
* (optional) qemu-system-arm

## Build 

```
make kernel.img
```

## Test With QEMU

```
qemu-system-aarch64 -M raspi3b -kernel kernel.img -initrd initramfs.cpio -serial null -serial stdio -dtb bcm2710-rpi-3-b-plus.dtb
```

## Labs list
* Lab0: Environment Setup

* Lab1: Hello World

* Lab2: Booting

* Lab3: Exception and Interrupt

* Lab4: Allocator

* Lab5: Thread and User Process