# Simplified Guide to U-Boot

**U-Boot** (Universal Bootloader) is an **open-source bootloader** extensively used in embedded systems. It's adaptable to various architectures and platforms, making it ideal for booting embedded Linux systems and other operating systems.
## Building U-Boot

## 1. Clone U-Boot Repository:
```bash
git clone https://github.com/u-boot/u-boot.git
cd u-boot/
git checkout v2022.07
```
## 2. Configure U-Boot for Your Target Platform (Vexpress Cortex A9 - Qemu):

-   Find Supported Machines:

```bash
# In order to find the machine name supported by U-Boot
ls configs/ | grep vexpress
```
-   Default Configuration for Supported Architecture:

```bash
# load the default configuration of ARM Vexpress Cortex A9
make vexpress_ca9x4_defconfig ARCH=arm CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```

-   Modify Default Configuration:
```bash
make menuconfig ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-
```
**Notes**
### Varibles used by the u-boot makefile
```bash
CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf-

ARCH=arm
```

**Requirements**:

-   Support **'editenv'**.
-   Support **'bootd'**.
-   Store the environment variable inside file call **'uboot.env'**.
-   Unset support of **'Flash'**
-   Support **'FAT file system'**
    -   Configure the FAT interface to **'mmc'**
    -   Configure the partition where the fat is store to **'0:1'**


#
  
### Build U-Boot:
```bash
make ARCH=arm CROSS_COMPILE=<Path To the Compiler>/arm-cortexa9_neon-linux-musleabihf- -j<Number of cores>
```
## 3. Test U-Boot (Run Qemu):
```bash
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel <Path To the u-boot>/u-boot -sd <Path To the sd.img>/sd.img
```

## Initializing TFTP Protocol
TFTP (Trivial File Transfer Protocol) facilitates file transfer between networked devices. It's commonly used for bootstrapping devices or transferring configuration files.

### Ubuntu

```bash
# Install TFTP protocol
sudo apt-get install tftpd-hpa

# Configure TFTP
sudo vim /etc/default/tftpd-hpa
# Add
TFTP_OPTIONS="--secure --create"

# Restart TFTP
sudo systemctl restart tftpd-hpa

# Ensure TFTP is running
sudo systemctl status tftpd-hpa

# Change file owner
cd /srv
sudo chown tftp:tftp tftp

# Move file to server
sudo cp <File name> /srv/tftp

```

### TFTP Configuration:
```bash
# Create Virtual Ethernet For QEMU
```
Create a script `qemu-ifup` 

### Create script 'qemu-ifup':

```bash
#!/bin/bash
ip a add <server ip address(tap address)> dev $1
ip link set $1 up
```
#### Start Qemu

```bash
sudo qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel <Path To the u-boot>/u-boot -sd <Path To the sd.img>/sd.img -net tap,script=<Path To the script>/qemu-ifup -net nic
```

## uEnv.txt for U-Boot:

**'uEnv.txt'** is a configuration file commonly used with U-Boot as the bootloader. It specifies boot parameters and environment variables read by U-Boot during boot.
- Typical **'uEnv.txt'** includes key-value pairs specifying boot parameters and commands for U-Boot.

- If filename **'uEnv.txt'** is changed, U-Boot won't recognize it during boot automatically. Configure U-Boot to look for the new filename or specify it manually during boot.












  