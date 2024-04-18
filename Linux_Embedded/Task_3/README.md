# Creating Your Emulated SD Card

## 1. Create a New Folder and File:

- Make a new directory:
```bash
mkdir EmulatedSD && cd EmulatedSD/
```

-   Create a new file named **'sd.img'**:
```bash
touch sd.img
```

## 2. Set File Size:
-   Specify the desired file size, such as 1 GB:
```bash
dd if=/dev/zero of=sd.img bs=1M count=1024
```

## 3. Partition the File:
-   Use **'cfdisk'** to add a partition table and partition the file:
```bash
cfdisk sd.img
```
-   **Notes:** 

    -   **Choose partition table type as DOS/MBR.**
  
    -   **Create two partitions: boot (FAT 16) and rootfs (Linux/ext4).**
  
    -   **Set the boot partition as bootable.**

 ## 4. Attach to a Virtual Storage Device:
 -  Attach the SD card file to a virtual storage device (/dev/loop):

```bash
 sudo losetup -f --show --partscan sd.img
```
- **Notes:** 

    -  `-f, --find :` Find  the first unused loop device.
  
    -   `--show:` Display the name of the assigned loop device
  
    -   `-P, --partscan:` Force the kernel to scan the partition table on a newly created loop device.

## 5. Create Filesystem Structures:
- Create folders (equal to the number of partitions) and add filesystem data structures:
```bash
sudo mkfs.vfat -F 16 -n boot /dev/loop<chosen number>p1
sudo mkfs.ext4 -L rootfs /dev/loop<chosen number>p2
```
## 6. Mount Filesystem:
- Mount the filesystem to the partitions, treating each partition as a device:

```bash
sudo mount /dev/loop<chosen number>p1 BOOT/
sudo mount /dev/loop<chosen number>p2 ROOTFS/
```
## 7.   List Block Devices:
- View a list of block devices:
```bash
lsblk 
```












  