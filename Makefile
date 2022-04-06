CC_CPP := g++
CXXFLAGS := -O2 -g -std=c++14 -Wall -Werror -pthread

PUB_DIR := /mnt/remote/bbmonitor
PROJ_NAME := baby_monitor
SRC_FILES := $(wildcard monitor/*.cpp)
OPENCV := `pkg-config --cflags --libs opencv`
LFLAGS := -lrt -lpthread

baby_monitor:
	$(CC_CPP) $(CXXFLAGS) $(SRC_FILES) -o $(PROJ_NAME) 
	cp $(PROJ_NAME) $(PUB_DIR)/

local:
	g++ $(CXXFLAGS) $(OPENCV) $(SRC_FILES) -o $(PROJ_NAME) $(LFLAGS)


clean:
	rm -f *.o $(PROJ_NAME)