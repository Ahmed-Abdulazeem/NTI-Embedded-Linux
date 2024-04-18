# BusyBox for QEMU

BusyBox is a handy software suite that bundles multiple Unix utilities into a single executable file, ideal for embedded systems. Here's how you can set up BusyBox for QEMU:

## Download or Clone

You can obtain BusyBox either by downloading the BusyBox binary suitable for your target architecture or by cloning the main BusyBox repository.

### Clone the Main Repository
```bash
# Clone the BusyBox repository:
git clone https://git.busybox.net/busybox --depth=1
```

### Compilation

Compile BusyBox for QEMU by following these simple steps:

```bash
cd busybox

# Configure BusyBox for your target architecture (e.g., ARM)
make defconfig ARCH=arm CROSS_COMPILE=<Path To Compiler>

# Customize BusyBox configuration if needed
make menuconfig ARCH=arm CROSS_COMPILE=<Path To Compiler>

# Compile BusyBox
make ARCH=arm CROSS_COMPILE=<Path To Compiler> -j$(nproc)

# Install BusyBox binaries
make install
```
### Integrating with Rootfs for QEMU

Once BusyBox is compiled, integrate its binaries into the root filesystem (rootfs) for QEMU:

```bash
# Navigate out of the BusyBox directory
cd ..

# Create a rootfs directory
mkdir rootfs

# Copy BusyBox binaries to the rootfs directory
cp -rp ./busybox/_install/ ./rootfs

# Copy sysroot directory content from the generated toolchain for shared libraries
rsync -a ~/x-tools/arm-cortexa9_neon-linux-musleabihf/arm-cortexa9_neon-linux-musleabihf/sysroot/ ./rootfs

# Ensure correct ownership of files and directories
sudo chown root:root rootfs/

# Navigate to the rootfs directory
cd rootfs

# Create additional necessary folders
mkdir -p ./dev /etc /run /mnt /sys /proc

# Create inittab file
touch /etc/inittab
```

#### Configure Inittab

We need to setup **inittab** file because it's the first thing that the **init** process look at

```bash
# inittab file 
::sysinit:/etc/init.d/rcS
# Start an "askfirst" shell on the console (whatever that may be)
ttyAMA0::askfirst:-/bin/sh
# Stuff to do when restarting the init process
::restart:/sbin/init
```
# Mount rootfs through Emulated SD Card

```bash
# mount the sd card on the host file system
sudo mount /dev/loop<chosen number>p1 BOOT/
sudo mount /dev/loop<chosen number>p2 ROOTFS/

# copy rootfs into the sd card
cd ROOTFS
sudo cp -rp * ROOTFS/

# unmount the SD card
sudo umount ROOTFS/
```

## Setup Bootargs in U-boot

```bash
setenv bootargs "console=ttyAMA0,38400n8 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init"
# console is set depends on the machine
```

# Mount rootfs Through NFS

## Install NFS

```bash
# Install an NFS server
sudo apt install nfs-kernel-server

# Add exported directory to `/etc/exports` file, with target ip as follows
/home/abdelaziz/NTI_WS/Linux_Workspace/EmulatedSD/NFS_rootfs  192.168.1.101(rw,no_root_squash,no_subtree_check)

# Ask NFS server to apply this new configuration (reload this file)
sudo exportfs -r
```

## Setup Bootargs in U-Boot

```bash
setenv bootargs "console=ttyAMA0,38400n8 root=/dev/nfs ip=192.168.1.101:::::eth0 nfsroot=192.168.1.99:/home/abdelaziz/NTI_WS/Linux_Workspace/EmulatedSD/NFS_rootfs,nfsvers=3,tcp rw init=/sbin/init"
# make sure the console tty represet the machine you working on
```

# System configuration and startup 

The first user space program that gets executed by the kernel is `/sbin/init` and its configuration
file is `/etc/inittab`. in `inittab` we are executing `::sysinit:/etc/init.d/rcS`but this file doesn't exist.

create `/etc/init.d/rcS` startup script and in this script mount `/proc` `/sys` filesystems:

```sh 
#!/bin/sh
# mount a filesystem of type `proc` to /proc
mount -t proc comment /proc
# mount a filesystem of type `sysfs` to /sys
mount -t sysfs comment /sys
# you can create `/dev` and execute `mount -t devtmpfs comment /dev` if you missed the `devtmpfs` configuration  
```

Note: `can't run '/etc/init.d/rcS': Permission denied` , use 

```sh
#inside `rootfs` folder
chmod +x ./etc/init.d/rcS # to give execution permission for rcS script
#restart
reboot
```