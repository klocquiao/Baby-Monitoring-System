CC_CPP := arm-linux-gnueabihf-g++
CXXFLAGS := -O2 -g -std=c++14 -Wall -Werror -pthread

PUB_DIR := $(HOME)/cmpt433/public/myApps
PROJ_NAME := baby_monitor
SRC_FILES := $(wildcard monitor/*.cpp)
OPENCV := `pkg-config --cflags --libs opencv`
LFLAGS := -lrt –lpthread

baby_monitor:
	$(CC_CPP) $(CXXFLAGS) $(SRC_FILES) -o $(PROJ_NAME)
	cp $(PROJ_NAME) $(PUB_DIR)/

local:
	g++ $(CXXFLAGS) $(SRC_FILES) -o $(PROJ_NAME)
	cp $(PROJ_NAME) $(PUB_DIR)/


clean:
	rm -f *.o $(PROJ_NAME)