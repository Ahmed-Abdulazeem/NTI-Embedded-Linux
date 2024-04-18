# Linux Kernel for QEMU vexpress

The Linux kernel forms the heart of the Linux operating system, acting as the vital link between hardware and software. It provides essential functionalities like process management, memory management, device drivers, and system calls.


## Clone the Repository

### Main Linux Kernel Repository

You can either clone the main Linux kernel repository or opt for a repository tailored for running QEMU vexpress virtual machines.

```bash
# you can either choose the linux kernel version and download it or clone the last commit
git clone --depth=1 https://github.com/torvalds/linux.git
```
### Building the Kernel
After cloning, you need to configure and build the Linux kernel, ensuring specific configurations are in place:

#### 1. **Configure the Kernel:**
-   Enable **'devtmpfs'**.
-   Change kernel compression to **'XZ'**.
-   Customize kernel local version (append your name with -v1.0)

#### 2. **Build the kernal**

```bash
cd linux[version]
make vexpress_defconfig ARCH=arm CROSS_COMPILE=<Path To Compiler>
make menuconfig ARCH=arm CROSS_COMPILE=<Path To Compiler>
make zImage modules dtbs ARCH=arm CROSS_COMPILE=<Path To Compiler> -j$(nproc)
```

## Booting Kernel on QEMU VExpress

### Boot from sd-card

Copy the **'zImage'** and **'dtb'** file to the boot partition of the sd-card
```bash
sudo cp linux/arch/arm/boot/zImage <path to boot patition>
sudo cp linux/arch/arm/boot/dts/vexpress-v2p-ca9.dtb <path to boot patition>
```
Start **'Qemu'** to boot on U-boot
```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel <Path To the u-boot>/u-boot -sd <Path To the sd.img>/sd.img -net tap,script=<Path To the script>/qemu-ifup -net nic
```
Set the bootargs to
```bash
bootargs=console=ttyAMA0,38400n8
```
load kernel image zImage and DTB vexpress-v2p-ca9.dtb from sd-card into RAM
```bash
fatload mmc 0:1 $kernel_addr_r zImage
fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb
```
boot the kernel with its device tree
```bash
bootz $kernel_addr_r - $fdt_addr_r
```

### Boot from TFTP

Copy the **'zImage'** and **'dtb'** file to the tftp server as configured in /etc/default/tftpd-hpa
```bash
sudo cp linux/arch/arm/boot/zImage /srv/tftp/
sudo cp linux/arch/arm/boot/dts/vexpress-v2p-ca9.dtb /srv/tftp/
```
Start Qemu to boot on U-boot
```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel <Path To the u-boot>/u-boot -sd <Path To the sd.img>/sd.img -net tap,script=<Path To the script>/qemu-ifup -net nic
```
Set the bootargs to
```bash
bootargs=console=ttyAMA0,38400n8
```
load kernel image zImage and DTB vexpress-v2p-ca9.dtb from sd-card into RAM
```bash
tftp $kernel_addr_r zImage
tftp $fdt_addr_r vexpress-v2p-ca9.dtb
```
boot the kernel with its device tree
```bash
bootz $kernel_addr_r - $fdt_addr_r
```
**The Kernel Fails to Boot: It Panics!**