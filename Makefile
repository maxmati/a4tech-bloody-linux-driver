CXXFLAGS += $(shell pkg-config --cflags libusb-1.0) -std=c++11
LDFLAGS  += $(shell pkg-config --libs   libusb-1.0)

bloody: main.cpp Mouse.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) bloody Mouse.o
