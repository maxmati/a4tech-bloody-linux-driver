//
// Created by maxmati on 4/18/15.
//

#pragma once

#include <map>
#include <libusb.h>

static const int A4TECH_VID = 0x09da;

static const int BLOODY_V5_PID = 0x172A;
static const int BLOODY_V7_PID = 0xF613;
static const int BLOODY_V8_PID = 0x11F5;
static const int BLOODY_R7_PID = 0x1485;
static const int BLOODY_R8_1_PID = 0x14ee;

static const int COMPATIBLE_PIDS[] = {BLOODY_V5_PID, BLOODY_V7_PID, BLOODY_V8_PID, BLOODY_R7_PID, BLOODY_R8_1_PID};
static const size_t COMPATIBLE_PIDS_SIZE = sizeof(COMPATIBLE_PIDS)/sizeof(COMPATIBLE_PIDS[0]);

static const int A4TECH_MAGIC = 0x07;

static const int BACKLIGHT_OPCODE = 0x11;
static const int BACKLIGHT_WRITE = 0x80;
static const int BACKLIGHT_READ = 0x00;


class Mouse {
public:
    ~Mouse();
    void init();
    void listDevices();
    bool selectDevice(int address);
    int setBackLightLevel(uint8_t level);
    uint8_t getBackLightLevel();
private:
    std::map<int, libusb_device_handle*> devices;
    libusb_device_handle* currentDevice = nullptr;
    libusb_context* context = nullptr;

    int writeToMouse(uint8_t data[], size_t size);
    int readFromMouse(uint8_t* request, size_t requestSize,
                       uint8_t* response, size_t responseSize);

    void discoverDevices();

    bool isCompatibleDevice(libusb_device_descriptor &desc);
};
