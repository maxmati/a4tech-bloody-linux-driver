a4tech-bloody-linux-driver
====================

Linux driver for a4tech bloody mouse series.

## Compile
```
~$ git clone <repo> <dir>
~$ cd <dir>
~$ cmake ./
~$ make
```

## Run
```
./bloody
```

## Add new bloody devices

1. Get USB PID of device:
```
~$ lsusb -d 09da: | cut -d ' ' -f6 | cut -d ':' -f2
```

2. Add that PID to Mouce.h & Mouce.cpp
