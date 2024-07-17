---
layout: post
title:  "Merge multiple partitions"
date:   2024-07-17 21:30:00 +0800
categories: linux raspberrypi
--- 
**Problem:** You have a Raspberry Pi module running linux. When you try installing new software, you find that the memory is not enough. Checking the output of `df -h` and `sudo lsblk`, you find that your disk is fragmented and there are reusable partitions. Follow the below steps to reclaim more space.

## 1. Diagnosis

```sh
# To check the remaining disk space
df -h

# To check the disk partitions
sudo lsblk
```

## 2. Format disk

You can only merge the adjacent partitions.

> [!CAUTION]
> The data on subsequent partition (after the first one) will be erased.

```sh
# To check disk information and to attain the disk name (path)
sudo fdisk -l

# To format the disk name /dev/mmcblk0 (replace with your disk name)
sudo fdisk /dev/mmcblk0

# select d to delete partitions you want to merge.
# select n to create the new partition, the start sector should be right after
#     the previous partition and the end sector should be right before the next
#     partition (if any, or at the end, usually, the program will suggest the
#     numbers.
# select w to commit change.
# select q to quit.
```

## 3. Resize fs

After fortmatting disk, if you check `df -h` the output should be the same since file system is not updated yet. Use the following command to make it updated.

```sh
sudo resize2fs /dev/mmcblk0p2
```

## 4. Update boot config, mount config (if needed)

This step is optional.

```sh
# To update mount config
sudo nano /etc/fstab

# To update cmdline.txt on boot partition /dev/mmcblk0p1
mkdir -p /tmp/somename
sudo mount /dev/mmcblk0p1 /tmp/somename
sudo nano /tmp/somename/cmdline.txt
```

## 5. Reboot

```sh
sudo reboot
```
