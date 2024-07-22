---
layout: post
title:  "Cross compile connectedhomeip project for Raspberry Pi"
date:   2024-07-22 12:30:00 +0800
categories: linux raspberrypi
--- 
## Goal

[connectedhomeip](https://github.com/project-chip/connectedhomeip.git) is an open-source that supports Matter protocol for multiple platforms. Although the detailed guides are available in the repository, this article notes the steps of compiling the source code for Raspberry Pi.

- Host OS: Ubuntu 22.04
- Target OS: Raspbian GNU/Linux 12 (bookworm, armv7l)

## Steps

**Step 1.** On the target machine, install the necessary libraries. Some devel packages may be required.

```sh
sudo apt-get update
sudo apt-get install libssl-dev libglib2.0-dev pi-bluetooth avahi-utils
```

**Step 2.** On the host machine, mount the target machine's drive to prepare sysroot folder. (You can also copy the data via ssh but that can be slower). Switch to root by issuing `sudo -i` before doing following steps.

```sh
# Mount
mkdir -p /home/hanmai/mountpoint
mount /dev/sdb2 /home/hanmai/mountpoint/

# ENV
MOUNT_ROOT=/home/hanmai/mountpoint
TARGET_SYSROOT=/home/hanmai/sysroot

mkdir -p $TARGET_SYSROOT

# Copy dirs
rsync -avL $MOUNT_ROOT/usr/lib             $TARGET_SYSROOT/usr
rsync -avL $MOUNT_ROOT/usr/include         $TARGET_SYSROOT/usr
rsync -avL $MOUNT_ROOT/usr/share/pkgconfig $TARGET_SYSROOT/usr/share
rsync -avL $MOUNT_ROOT/usr/local/lib       $TARGET_SYSROOT/usr/local
rsync -avL $MOUNT_ROOT/usr/local/include   $TARGET_SYSROOT/usr/local

# Take ownership
chown -R hanmai:hanmai $TARGET_SYSROOT

# Make lib dir as same as in RPI image
pushd $TARGET_SYSROOT
ln -s usr/lib lib
popd
# 
```

**Step 3.** On host machine, install the necessary library and programs.

```sh
sudo apt-get update

# Install prerequisites
sudo apt-get install git gcc g++ pkg-config libssl-dev libdbus-1-dev \
     libglib2.0-dev libavahi-client-dev ninja-build python3-venv python3-dev \
     python3-pip unzip libgirepository1.0-dev libcairo2-dev libreadline-dev \
     gn ninja

# Install the cross compiler
sudo apt-get install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
```

**Step 4.** Fetch source code from github.

```sh
# Cloning
git clone --depth=1 https://github.com/project-chip/connectedhomeip.git
cd connectedhomeip/

# Checkout sub modules for linux platform:
./scripts/checkout_submodules.py --shallow --platform  linux
```

**Step 5.** Compile.

```sh
source scripts/activate.sh

gn gen out/rpi --args='is_debug=true host_cpu="arm" host_toolchain="gcc-arm-linux-gnueabihf" sysroot="/home/hanmai/sysroot" system_libdir="lib/arm-linux-gnueabihf"'

ninja -C out/rpi
```

The output should be available at `out/rpi` after this step.
