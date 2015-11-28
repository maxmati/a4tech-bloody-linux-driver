//
// Created by maxmati on 4/18/15.
//

#include "Mouse.h"

#include <iostream>

using std::cout; using std::endl;

void Mouse::init() {
    int ret = libusb_init(&context);
    if(ret < 0) {
        cout<<"Init Error "<<ret<<endl;
        return;
    }

    libusb_set_debug(context, LIBUSB_LOG_LEVEL_INFO);

    discoverDevices();

}

void Mouse::discoverDevices() {
    libusb_device** devs;
    ssize_t cnt = libusb_get_device_list(context, &devs);
    if(cnt < 0) {
        cout<<"Get Device Error"<<endl;
        return;
    }

    for(int i = 0; i < cnt; ++i) {
        libusb_device_descriptor desc;
        libusb_get_device_descriptor(devs[i], &desc);
        if (isCompatibleDevice(desc)) {
            if(libusb_open(devs[i], &currentDevice) != 0)
                continue;

            if(libusb_kernel_driver_active(currentDevice, 2) == 1)
                if(libusb_detach_kernel_driver(currentDevice, 2) != 0) {
                    libusb_close(currentDevice);
                    continue;
                }

            devices.insert(std::pair<int, libusb_device_handle*>(libusb_get_device_address(devs[i]), currentDevice));

        }

    }
    libusb_free_device_list(devs, 1);

    if(devices.size() == 0){
        cout<<"No suitable device found."<<endl;
        return;
    }

    currentDevice = devices.begin()->second;
}

bool Mouse::isCompatibleDevice(libusb_device_descriptor &desc) {
    if(desc.idVendor != A4TECH_VID)
        return false;

    for(size_t i = 0; i < COMPATIBLE_PIDS_SIZE; ++i)
        if(desc.idProduct == COMPATIBLE_PIDS[i])
            return true;

    return false;
}

Mouse::~Mouse() {
    for (auto& dev : devices)
        libusb_close(dev.second);
    if(context != nullptr)
        libusb_exit(context);
}

int Mouse::setBackLightLevel(uint8_t level) {
    uint8_t data[72] = {A4TECH_MAGIC, BACKLIGHT_OPCODE,0x00,0x00,
                        BACKLIGHT_WRITE,0x00,0x00,0x00, level, 0x00, };

    if(level < 0 || level > 3){
        return -1;
    }

    if(writeToMouse(data, sizeof(data)) < 0)
        return -2;

    return 0;
}

int Mouse::writeToMouse(uint8_t data[], size_t size) {
    int res =  libusb_control_transfer(currentDevice,0x21,9,
                                       0x0307,2,data,size,10000);
    if(res < 0){
        cout<<"Unnable to send command"<<endl;
        return -1;
    }

    return 0;
}

int Mouse::readFromMouse(uint8_t *request, size_t requestSize, uint8_t *response, size_t responseSize) {
    if(writeToMouse(request, requestSize) < 0){
        return -1;
    }

    int res =  libusb_control_transfer(currentDevice,0xa1,1,
                                       0x0307,2,response,responseSize,10000);
    if(res < 0){
        cout<<"Unnable to receive data"<<endl;
        return -2;
    }


}

uint8_t Mouse::getBackLightLevel() {
    uint8_t request[72] = {A4TECH_MAGIC, BACKLIGHT_OPCODE,0x00,0x00,
                        BACKLIGHT_READ,0x00,};
    uint8_t response[72];

    readFromMouse(request, sizeof(request), response, sizeof(response));

    return response[8];
}

void Mouse::listDevices() {
    std::cout<<"Available devices:"<<endl;
    for (auto&devHand : devices){
        libusb_device* device = libusb_get_device(devHand.second);

        libusb_device_descriptor desc;
        libusb_get_device_descriptor(device, &desc);

        std::string name;

        switch (desc.idProduct){
            case BLOODY_V5_PID:
                name = "Bloody V5";
                break;
            case BLOODY_V7_PID:
                name = "Bloody V7";
                break;
            case BLOODY_V8_PID:
                name = "Bloody V8";
                break;
            case BLOODY_R7_PID:
                name = "Bloody R7";
                break;
            case BLOODY_R8_1_PID:
                name = "Bloody R8-1";
                break;
            default:
                name = "Unknown";
        }

        std::cout<< devHand.first<<":"<<name<<endl;
    }

}

bool Mouse::selectDevice(int address) {
    if(devices.count(address) == 0)
        return false;

    currentDevice = devices.at(address);
    return true;
}
