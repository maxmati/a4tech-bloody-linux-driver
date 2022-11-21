a4tech-bloody-linux-driver
====================

Linux driver for a4tech bloody mouse series.
This tool allows setting backlight level of A4TECH wired mouse (USB connected), e.g. A4TECH V7M.

# Build instructions
## Fedora 29
```
dnf install gcc-c++ cmake libusbx-devel
git clone https://github.com/maxmati/a4tech-bloody-linux-driver
cd ./a4tech-bloody-linux-driver
cmake .
make
```

## Add new bloody devices

1. Get USB PID of device:
```
~$ lsusb -d 09da: | cut -d ' ' -f6 | cut -d ':' -f2
```

2. Add that PID to Mouse.h & Mouse.cpp

Mouse.h: add line with PID and add name to COMPATIBLE_PIDS variable as all the other mouses.

Mouse.cpp: add 3 lines: case, name and break; as all the other mouses.


## Run
```
sudo ./bloody
Available devices:
36:Bloody V7
Enter device address: 36
Current backlight level: 3
Select backlight level(0-3):0
```
