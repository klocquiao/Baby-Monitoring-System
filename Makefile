CC_CPP := arm-linux-gnueabihf-g++
CXXFLAGS := -g -std=c++14 -Wall -Werror -pthread

PUB_DIR := $(HOME)/cmpt433/public/myApps
PROJ_NAME := baby_monitor
SRC_FILES := $(wildcard monitor/*.cpp)

all: monitor

clean:
	rm $(PROJ_NAME)

monitor:
	$(CC_CPP) $(CXXFLAGS) $(SRC_FILES) -o $(PROJ_NAME)
	cp $(PROJ_NAME) $(PUB_DIR)/