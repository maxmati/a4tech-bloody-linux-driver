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

# Usage
```
sudo ./bloody
Available devices:
36:Bloody V7
Enter device address: 36
Current backlight level: 3
Select backlight level(0-3):0
```
