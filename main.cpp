#include <iostream>
#include "Mouse.h"

int main() {
	Mouse m;
	int address, level;
	m.init();
	do {
		m.listDevices();
		std::cout << "Enter device address: ";
		std::cin >> address;
	}while(!m.selectDevice(address));

	std::cout<<"Current backlight level: "<<(int)m.getBackLightLevel()<<std::endl;

	do {
		std::cout << "Select backlight level(0-3):";
		std::cin >> level;
	}while(m.setBackLightLevel(level) < 0);

	return 0;
}

